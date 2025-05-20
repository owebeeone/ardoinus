#!python3

import argparse
import os
import sys
import re
import textwrap
import socket
import select
import PIL
from PIL import Image
import hashlib
import numpy as np
import binascii
import time
from datetime import datetime
from itertools import cycle

# Exceptions for dealing with argument checking.
class PlBaseException(Exception):
    '''Base exception functionality'''
    def __init__(self, message):
        self.message = message
        
class ImageSizeInvalidException(PlBaseException):
    '''Image size must be less than or equal to LEDS size.'''
    

class InvalidResultingImageSizeException(PlBaseException):
    '''Resulting size postcondition error.'''


class ControllerDiscoveryTimeoutException(PlBaseException):
    '''Unable to find address of controller.'''
    

class CropSpecifierErrorException(PlBaseException):
    '''The crop specifier provided is invalid.'''
    
class ColorSpecifierErrorException(PlBaseException):
    '''The color specifier provided is invalid.'''
    
class TimedBrightSpecErrorException(PlBaseException):
    '''The timed brightness specifier provided is invalid.'''
    
class MissingIpAddrException(PlBaseException):
    '''IP Address is required when using non-standard listener port.'''

    
    
LEDS_X_SIZE = 75
LEDS_Y_SIZE = 22
LEDS_COUNT = LEDS_X_SIZE * LEDS_Y_SIZE
PIXEL_Y_X_SIZE_RATIO = (990.0 / 21) / (1000.0 / 30)
LEDS_ASPECT_RATIO = float(LEDS_Y_SIZE) / LEDS_X_SIZE
FRAME_IDENT_SIZE = 4 + 4 + 8
FRAME_SIZE_WO_PADDING = FRAME_IDENT_SIZE + 3 * LEDS_COUNT
FRAME_SIZE = (FRAME_SIZE_WO_PADDING | 7) + 1
FRAME_PAD_BYTES = b'\000' * (FRAME_SIZE - FRAME_SIZE_WO_PADDING)

def assemble_bytes(frame_number, ident, image, fill_colour):
    if image.size[0] > LEDS_X_SIZE:
        raise ImageSizeInvalidException(
            'Image X size too large %r' % (image.size,))
    if image.size[1] > LEDS_Y_SIZE:
        raise ImageSizeInvalidException(
            'Image Y size too large %r' % (image.size,))
    
    # Create a "frame_ident" header.
    frame_ident = bytes([frame_number & 0xff,
           (frame_number >> 8) & 0xff,  # Little endian.
           (frame_number >> 16) & 0xff,
           (frame_number >> 24) & 0xff,
           0,  # Padding.
           0,
           0,
           0]) + ident[:8]
    
    fill_bytes = bytes(fill_colour[0:3])
    lhs_fill = int((image.size[0] - LEDS_X_SIZE) / 2)
    rhs_fill = LEDS_X_SIZE - image.size[0] - lhs_fill
    
    top_fill = int((image.size[1] - LEDS_Y_SIZE) / 2)
    bottom_fill = LEDS_Y_SIZE - image.size[1] - top_fill
    pixels = image.getdata()
    
    # Add the frame ident and the top rows of fill.
    data_chunks = [frame_ident] + [fill_bytes * top_fill * LEDS_X_SIZE]
    column = 0
    for pixel in pixels:
        if column < lhs_fill:
            # At the beginning of a line - add fill colour.
            data_chunks.append(fill_bytes * (lhs_fill - column))
            column = lhs_fill
        # Add the pixel's bytes.
        data_chunks.append(bytes(pixel[0:3]))
        column += 1
        
        if column > image.size[0] - rhs_fill:
            # At the end of a line - add more fill colour.
            data_chunks.append(fill_bytes * (image.size[0] - column))
            column = 0

    # Add the bottom fill lines and final padding.
    data_chunks.append(
        fill_bytes * bottom_fill * LEDS_X_SIZE + FRAME_PAD_BYTES)
    
    result = b''.join(data_chunks)
    
    if len(result) != FRAME_SIZE:
        raise InvalidResultingImageSizeException(
            'Expected a size of %s but got %s' % (FRAME_SIZE, len(result)))
    
    return result
    
def crop_and_scale(pil_image, crop_box):
    # Returns a scaled image that fits in the LEDS screen.
    # Scaling also adjusts for the rectangular pixel shape by
    # also applying a super unity scale along the x axis.
    new_crop_box = (
        crop_box[0] * PIXEL_Y_X_SIZE_RATIO, 
        crop_box[1],
        crop_box[2] * PIXEL_Y_X_SIZE_RATIO, 
        crop_box[3])
    
    crop_size = (new_crop_box[2] - new_crop_box[0],
                 new_crop_box[3] - new_crop_box[1])
    aspect_ratio = crop_size[1] / crop_size[0]
    if aspect_ratio > LEDS_ASPECT_RATIO:
        scaley = LEDS_X_SIZE / crop_size[0]
    else:
        scaley = LEDS_Y_SIZE / crop_size[1]
        
    scalex = PIXEL_Y_X_SIZE_RATIO * scaley
    
    newsize = (int(pil_image.size[0] * scalex), int(pil_image.size[1] * scaley))
    
    scaled_img = pil_image.resize(newsize)
    
    scaled_crop_box = (int(v * scaley) for v in new_crop_box)
    
    cropped_img = scaled_img.crop(scaled_crop_box)
    cropped_img = cropped_img.resize((LEDS_X_SIZE, LEDS_Y_SIZE))
    
    return cropped_img

def to_dc_image(pil_image, frame_number, name, crop_box, fill_colour):
    scaled_image = crop_and_scale(pil_image, crop_box)
    
    return assemble_bytes(
        frame_number, 
        hashlib.md5(name.encode('utf-8')).digest(), 
        scaled_image, 
        fill_colour)

def crop_func_all(pil_image):
    return (0, 0, pil_image.size[0], pil_image.size[1])

def file_to_dc_image(file_name, 
                     frame_number=1,
                     fill_colour=(0, 0, 0), 
                     crop_func=crop_func_all):
    image = Image.open(file_name);
    crop_box = crop_func(image)
    fill_colour=(0, 0, 0) # FIX THIS
    return to_dc_image(image, frame_number, file_name, crop_box, fill_colour)
    

UDP_IP = "0.0.0.0"
UDP_PORT = 4169
UDP_DC_PORT = 4159

NO_OPERATION = b'\000'
SET_HIGH = b'\001'
SET_LOW = b'\002'
PIN_OPS = {
    'noop' : NO_OPERATION,
    '1' : SET_HIGH,
    '0' : SET_LOW}

NEXT_FRAME = b'\001'
SET_BRIGHTNESS = b'\002'
SET_OUTPUTS = b'\003'
RESET_MCU = b'\xff'

# Message header magic strings.
MAGIC_SIZE = 4
MAGIC_INPUT = b'#PLI'
MAGIC_BROADCAST = b'#PLB'

MAX_GPIO_NUMBER = 16
    
DEFRAG_HEADER=b'\x0fr\xaaG'
MAX_PACKET_SIZE=1400
WAIT_FOR_ACK=False

class DcClient:
    """A client interface to the display controller. Also can listen for 
    display controller broadcast packets that can be used to discover the
    IP address.
    """
    def __init__(self, wait_for_ack=WAIT_FOR_ACK, localport=UDP_PORT):
        self.sock = socket.socket(socket.AF_INET, # Internet
                             socket.SOCK_DGRAM) # UDP
        self.sock.bind((UDP_IP, localport))
        
        self.addrs = set()
        self.last_data = None
        self.last_addr = None
        self.wait_for_ack = wait_for_ack
        self.sequence = int(time.time() * 1000)
        
    def get_data(self, wait_time=0.0):
        '''Reads controller broadcast data and optionally waits.'''
        r, _, _ = select.select([self.sock], [], [], wait_time)
        
        if r:
            data, addr = self.sock.recvfrom(65536)
            self.last_data = data
            self.last_addr = addr
            self.addrs.add(addr)
            return data, addr
        
        return None
    
    def get_ack(self, count=1):
        if count <= 0 or not self.wait_for_ack:
            return
        
        # Wait for the first one, it it shows up, wait much less time for
        # the rest.
        if self.get_data(0.1):
            for j in range(count):
                self.get_data(0.001)
    
    def send_bytes(self, data, addr):
        self.sequence += 1
        if len(data) < MAX_PACKET_SIZE:
            rsum = self.sock.sendto(data, addr)
            self.get_ack(1)
        else:
            # Create a sequence id.
            crc32 = binascii.crc32(data)
            header = DEFRAG_HEADER + bytes([
                crc32 & 0xff,
                (crc32 >> 8)& 0xff,
                (crc32 >> 16)& 0xff,
                (crc32 >> 24)& 0xff,
                self.sequence & 0xff,
                (self.sequence >> 8)& 0xff,
                (self.sequence >> 16)& 0xff,
                (self.sequence >> 24)& 0xff
                ])
            data_len = len(data)
            max_size = (data_len - 1) // MAX_PACKET_SIZE
            
            rsum = 0
            for i in range(max_size + 1):
                chunk = data[i * MAX_PACKET_SIZE : (i + 1) * MAX_PACKET_SIZE]
                rsum += self.sock.sendto(
                    header + bytes([i, max_size]) + chunk, addr)
            
            self.get_ack(max_size)
        return rsum
        
    
    def get_last_data(self):
        '''Returns the last data and address discovered.'''
        if self.last_data:
            return self.last_data, self.last_addr
        return None, None

    def get_addrs(self):
        '''Returns all addresses discovered so far.'''
        while self.get_data():
            pass
            
        if self.addrs:
            return self.addrs

    def send_reset(self, addr=None):
        '''
        Performs a reset on the display controller MCU.
        '''
        if not addr:
            addr = self.last_addr
        self.send_bytes(MAGIC_INPUT + RESET_MCU, addr)
        
    def send_set_output(self, pin_no, pin_setting, addr=None):
        '''
        Sets a GPIO pin to a given value. pin 0 should control the
        LED power supply.
        '''
        if not addr:
            addr = self.last_addr
        if pin_no < 0 or pin_no > MAX_GPIO_NUMBER:
            return False
        
        data = NO_OPERATION * (pin_no - 1) + pin_setting
        self.send_bytes(MAGIC_INPUT + SET_OUTPUTS + data, addr)
        return True
    
    def send_set_brightness(self, brightness, addr=None):
        '''
        Sets the brightness of the display.
        Args:
          brightness: A value from 0-255 that modulates LED brightness.
        '''
        if not addr:
            addr = self.last_addr
        self.send_bytes(
            MAGIC_INPUT + SET_BRIGHTNESS + bytes([brightness]), addr)
        
    def send_frame(self, frame_bytes, addr=None):
        '''
        Sends the next frame.
        Args:
          frame_bytes: The bytes representing the frame.
        '''
        if not addr:
            addr = self.last_addr
        
        self.send_bytes(
            MAGIC_INPUT + NEXT_FRAME + frame_bytes, addr)


def make_addr_from_args(pargs, dcclient):
    if pargs.ip:
        # Convert comma-separated IPs to a list of address tuples
        ip_addresses = pargs.ip.split(',')
        return [(ip.strip(), pargs.port) for ip in ip_addresses]
    
    if pargs.localport != UDP_PORT:
        raise MissingIpAddrException(
            'Cannot discover IP Address when using a different local port.'
            ' Use port %d' % UDP_PORT)
    
    # If IP not provided, use discovery to find clients
    discovered_clients = []
    start_time = time.time()
    
    while True:
        # Check if we've hit max clients or timeout
        elapsed_time = time.time() - start_time
        if (pargs.count > 0 and len(discovered_clients) >= pargs.count) or \
           (pargs.duration > 0 and elapsed_time >= pargs.duration):
            break
        
        # Try to get client data with a short timeout
        result = dcclient.get_data(min(1.0, pargs.timeout))
        
        if result:
            data, addr = result
            if addr not in discovered_clients:
                discovered_clients.append(addr)
                if not pargs.quiet:
                    print(f"Discovered client: {addr[0]}:{addr[1]}")
        
        # If we haven't found any clients and we've exceeded timeout, exit
        if not discovered_clients and time.time() - start_time > pargs.timeout:
            raise ControllerDiscoveryTimeoutException(
                'Timed out waiting for discovery - timeout time:%d' % pargs.timeout)
    
    if not discovered_clients:
        raise ControllerDiscoveryTimeoutException(
            'No clients discovered during search')
    
    if not pargs.quiet:
        print(f"Using {len(discovered_clients)} discovered clients:")
        for i, addr in enumerate(discovered_clients, 1):
            print(f"  {i}. {addr[0]}:{addr[1]}")
    
    return discovered_clients

def discover(pargs):
    dcclient = DcClient()
    discovered_clients = set()
    start_time = time.time()
    last_report_time = start_time
    
    while True:
        # Check if we've hit max clients or timeout
        elapsed_time = time.time() - start_time
        if (pargs.count > 0 and len(discovered_clients) >= pargs.count) or \
           (pargs.duration > 0 and elapsed_time >= pargs.duration):
            break
        
        # Try to get client data with a short timeout
        result = dcclient.get_data(min(1.0, pargs.timeout))
        
        # Report periodically if requested
        current_time = time.time()
        if pargs.report_interval > 0 and current_time - last_report_time >= pargs.report_interval:
            if discovered_clients:
                print(f"Discovered {len(discovered_clients)} clients so far:")
                for i, client in enumerate(discovered_clients, 1):
                    print(f"  {i}. {client[0]}:{client[1]}")
            last_report_time = current_time
            
        if result:
            data, addr = result
            if addr not in discovered_clients:
                discovered_clients.add(addr)
                if not pargs.quiet:
                    print(f"Discovered client: {addr[0]}:{addr[1]}")
                    print(data.decode("utf-8", errors="replace"))
                    
        # If we haven't found any clients and we've exceeded timeout, exit
        if not discovered_clients and time.time() - start_time > pargs.timeout:
            eprint("Timed out.")
            return 1
    
    # Final report
    if discovered_clients:
        print(f"Total discovered clients: {len(discovered_clients)}")
        for i, client in enumerate(discovered_clients, 1):
            print(f"  {i}. {client[0]}:{client[1]}")
        return 0
    else:
        eprint("No clients discovered.")
        return 1

def reset_controller(pargs):
    dcclient = DcClient(localport=pargs.localport)
    addrs = make_addr_from_args(pargs, dcclient)
    
    for addr in addrs:
        if not pargs.quiet:
            print(f"Resetting controller at {addr[0]}:{addr[1]}")
        dcclient.send_reset(addr)
    
    return 0

def check_0_255(value):
    ivalue = int(value)
    if ivalue < 0 or ivalue > 255:
        raise argparse.ArgumentTypeError("%s is not in range 0-255" % value)
    return ivalue

def check_0_max_gpio(value):
    ivalue = int(value)
    if ivalue < 0 or ivalue > MAX_GPIO_NUMBER:
        raise argparse.ArgumentTypeError("%s is not in range 0-%d" % 
                                         (value, MAX_GPIO_NUMBER))
    return ivalue

def brightness(pargs):
    dcclient = DcClient(localport=pargs.localport)
    addrs = make_addr_from_args(pargs, dcclient)
    
    for addr in addrs:
        if not pargs.quiet:
            print(f"Setting brightness on controller at {addr[0]}:{addr[1]}")
        dcclient.send_set_brightness(pargs.brightness[0], addr)
    
    return 0

MAX_WAIT_TIME=30
def timed_brightness(pargs):
    dcclient = DcClient(localport=pargs.localport)
    addrs = make_addr_from_args(pargs, dcclient)
    
    while True:
        current_brightness, wait_time, _ = pargs.timed_brightness[0].next()
        if wait_time > MAX_WAIT_TIME:
            wait_time = MAX_WAIT_TIME
        
        for addr in addrs:
            if not pargs.quiet:
                print(f"Setting brightness on controller at {addr[0]}:{addr[1]}")
            dcclient.send_set_brightness(current_brightness, addr)
        
        time.sleep(wait_time)
    
    return 0

def set_gpio(pargs):
    dcclient = DcClient(localport=pargs.localport)
    addrs = make_addr_from_args(pargs, dcclient)
    
    for addr in addrs:
        if not pargs.quiet:
            print(f"Setting GPIO on controller at {addr[0]}:{addr[1]}")
        dcclient.send_set_output(pargs.pin, pargs.setting, addr)
    
    return 0

def check_pin_setting(value):
    svalue = PIN_OPS.get(value, None)
    if svalue is None:
        raise argparse.ArgumentTypeError("%s is not one of %r" % 
                                         (value, tuple(PIN_OPS.keys())))
    return svalue

def monitor(pargs):
    max_count = pargs.packets
    count = 0
    
    while max_count < 0 or count < max_count:
        if not discover(pargs):
            count += 1
            print('packet %d' % count)
            
    return 0

def is_animated(image):
    if hasattr(image, 'is_animated'):
        return image.is_animated
    return False

class ImageProvider:
    '''Handles animated images.'''
    
    def __init__(self, filename, start_period, middle_period, end_period):
        self.image = image = Image.open(filename)
        self.animated = animated = is_animated(image)
        self.start_period = start_period
        self.middle_period = middle_period
        self.end_period = end_period
        if animated:
            self.count = image.n_frames
            self.frame_period = 0.1
            if 'duration' in image.info:
                # duration is in ms
                self.period = image.info['duration'] / 1000
                min_middle = self.frame_period * self.count
                count_loops = int(self.middle_period / min_middle + 0.9999)
                if count_loops < 1:
                    count_loops = 1
                self.middle_period = count_loops * min_middle
                    
            else:
                self.period = 0.1
        else:
            self.count = 1
            self.period = self.middle_period
            
        self.at_times = (self.start_period, 
                         self.middle_period + self.start_period, 
                         self.middle_period + self.start_period + self.end_period)
            
    def get_total_time(self):
        return self.start_period + self.middle_period + self.end_period
    
    def get_frame_at_time(self, at_time):
        period = self.at_times[0] - at_time
        if period > 0.01:
            return 0, period
        elif at_time >= self.at_times[1]:
            return self.count - 1, self.at_times[2] - at_time
        
        frame_no = int((at_time - self.start_period) / self.period) % self.count
        
        period = self.period
        if period + at_time > self.at_times[2]:
            period = self.at_times[2] - at_time
        
        return frame_no, period
        
    
    def get(self, at_time):
        
        frame_no, period = self.get_frame_at_time(at_time)
        
        if self.animated:
            self.image.seek(frame_no)
        
        return_image = (self.image 
                        if self.image.mode == 'RGB' 
                        else self.image.convert(mode='RGB'))

        return return_image, period
    
    def get_frame(self, frame_no):
        
        if self.animated:
            self.image.seek(frame_no)
        
        return_image = (self.image 
                        if self.image.mode == 'RGB' 
                        else self.image.convert(mode='RGB'))

        return return_image
    
    def size(self):
        return self.image.size()
    
    def end_at(self):
        return self.at_times[2]
    
    def get_image_at_end(self):
        return self.at_times[0]
    
    
class ImageState:
    
    def __init__(self, name, now_time,
                 start_period, middle_period, end_period,
                 crop_spec):
        self.image_provider = ImageProvider(name, 
                                            start_period, 
                                            middle_period, 
                                            end_period)
        self.start_at = now_time
        self.crop_spec = crop_spec
        self.curr_frame, self.curr_period = self.image_provider.get_frame_at_time(0)
        self.current_image = self.image_provider.get_frame(self.curr_frame)
        self.crop_box = self.crop_spec.apply_specifier(
            self.current_image.size[0], self.current_image.size[1])
        self.cropped_image = crop_and_scale(self.current_image, self.crop_box)
        
    def get_image_at(self, at_time):
        frame, period = self.image_provider.get_frame_at_time(at_time - self.start_at)
        if frame != self.curr_frame:
            self.curr_frame = frame
            self.current_image = self.image_provider.get_frame(self.curr_frame)
            self.cropped_image = crop_and_scale(self.current_image, self.crop_box)
            self.curr_period = period
        return self.cropped_image, period
    
    def size(self):
        return self.current_image.size()
    
    def get_image_at_end(self):
        return self.get_image_at(self.image_provider.end_at())
    
    def get_play_period(self):
        return self.image_provider.middle_period


class ImageFetcher():
    def __init__(self, 
                 dcclient, 
                 addr=None, 
                 files=[], 
                 fill_colour=None,
                 crop_spec=None,
                 blend_frames=0,
                 delay=1.0/25, 
                 key_frame_delay=1.0/2,
                 loop_count=-1):
        self.addr=addr
        self.files = files
        self.delay = delay
        self.loop_count = loop_count
        self.dcclient = dcclient
        self.crop_spec = crop_spec
        self.fill_colour = fill_colour
        self.blend_frames = blend_frames
        self.key_frame_delay = key_frame_delay
        self.load_images()
        
        
    def getImage(self, name, at_time):
        start_end_time = self.delay * self.blend_frames
        return ImageState(name, 
                          at_time,
                          start_end_time, 
                          self.key_frame_delay,
                          start_end_time, 
                          self.crop_spec)
        
    def load_images(self):
        frame_number = 1
        fill_colour = (0, 0, 0)
        at_time = 0
        if self.blend_frames and len(self.files) > 0:
            name = self.files[-1]
            next_image = self.getImage(name, at_time) 
            next_image.get_image_at_end()
            l = len(self.files)
            images = []
            for i in range(l):
                last_image = next_image
                last_at_time = at_time
                name = self.files[i if i < (l - 1) else 0]
                next_image = self.getImage(name, at_time)
                last_cropped_image = last_image.cropped_image
                for j in range(self.blend_frames):
                    alpha = j / self.blend_frames;
                    next_cropped_image, _ = next_image.get_image_at(at_time)
                    blended_image = Image.blend(
                        last_cropped_image, next_cropped_image, alpha)
                    images.append(
                        (assemble_bytes(
                            frame_number, 
                            hashlib.md5(name.encode('utf-8')).digest(), 
                            blended_image, 
                            fill_colour),
                            self.delay))
                    frame_number += 1
                    at_time += self.delay
                end_at_time = at_time + next_image.get_play_period()
                while at_time < end_at_time:
                    next_cropped_image, period = next_image.get_image_at(at_time)
                    if period > 0.01:
                        images.append(
                            (assemble_bytes(
                                frame_number, 
                                hashlib.md5(name.encode('utf-8')).digest(), 
                                next_cropped_image, 
                                fill_colour),
                                period))
                        frame_number += 1
                        at_time += period
                    else:
                        if end_at_time - at_time < 0.02:
                            at_time = end_at_time
                        else:
                            at_time += 0.01
            self.images = tuple(images)
        else:
            self.images = tuple(
                (file_to_dc_image(
                    file_name=file_name,
                    frame_number=i,
                    fill_colour=self.fill_colour,
                    crop_func=self.crop_spec.to_crop_fn()),
                    self.delay
                    ) 
                for i, file_name in enumerate(self.files))
        
    def run(self):
        
        prev_time = time.time() - self.images[0][1]
        i = 0
        while self.loop_count < 0 or i < self.loop_count:
            i += 1
            for dc_image in self.images:
                delay_time = prev_time - time.time()
                if delay_time > 0:
                    time.sleep(delay_time)
                else:
                    prev_time = time.time()
                prev_time = prev_time + dc_image[1]
                
                self.dcclient.send_frame(dc_image[0], addr=self.addr)
            

def loc_abs(image_size, wanted_loc):
    '''Returns the wanted location if it's within the image size.'''
    if wanted_loc > image_size:
        return image_size
    return int(wanted_loc)

def loc_rel(image_size, wanted_rel):
    '''Returns the relative (0-1) location of the image size.'''
    if wanted_rel > 1. or wanted_rel < 0:
        return image_size
    return (wanted_rel * image_size)

def nc(*re_strs, op='', g='?:'):
    return '(' + g + op.join('(?:' + str + ')' for str in re_strs) + ')'

INT_SPEC_POS='((?:0x[0-9a-fA-F]+)|(?:[0-9]+))'
FLOAT_SPEC_01='((?:1(?:\.0*)?)|(?:0?\\.[0-9]+))'
SPACES_SPEC='(?:[ \\t])*'
ABSOLUTE_SPEC=nc(SPACES_SPEC, '([Aa])', '(?:[Bb][Ss]?)?:?', SPACES_SPEC, INT_SPEC_POS)
RELATIVE_SPEC=nc(SPACES_SPEC, '([Rr])', '(?:[Ee][Ll]?)?:?', SPACES_SPEC, FLOAT_SPEC_01)
DESIGNATOR_SPEC=nc(SPACES_SPEC, nc('[Uu]|[Ll]', '[xX]|[yY]', g=''))
CROP_SPEC_RE_STR=nc(DESIGNATOR_SPEC + nc(ABSOLUTE_SPEC, RELATIVE_SPEC, op='|'))
CROP_SPEC_RE=re.compile(CROP_SPEC_RE_STR)
TIME_SPEC='((?:[01][0-9])|(?:2[0-3])):([0-5][0-9])(?::([0-5][0-9]))?'
TIMED_BRIGHTNESS=nc(SPACES_SPEC, TIME_SPEC, '[ \\t]', SPACES_SPEC, INT_SPEC_POS, SPACES_SPEC)
TIMED_BRIGHTNESS_RE=re.compile(TIMED_BRIGHTNESS)

class TimedBrightnessSpecifier:
    def __init__(self, spec_str):        
        specifier = list()
        itr = TIMED_BRIGHTNESS_RE.finditer(spec_str)
        cur_loc = 0
        for grp in itr:
            # Check for errors.
            span = grp.span()
            if span[0] != cur_loc:
                raise TimedBrightSpecErrorException(
                    'Timed brightness specification error at column: {col} in '
                    'provided specifier:\n    {begin}>>>{broken}<<<{rest}'
                    .format(col=cur_loc,
                            begin=spec_str[0:cur_loc],
                            broken=spec_str[cur_loc:span[1]],
                            rest=spec_str[span[1]:]))
                
            cur_loc = span[1]
            
            hours, minutes, seconds, brightness = grp.groups()
            daytime = (int(hours) * 60 * 60 + int(minutes) * 60 
                       + int(seconds if seconds else 0)) 
            brightness_value = check_0_255(brightness)
            
            specifier.append((daytime, brightness_value))
            
        if cur_loc != len(spec_str):
            raise TimedBrightSpecErrorException(
                'Timed brightness specification error at column: {col} in '
                'provided specifier:\n    {begin}>>>{broken}'
                .format(col=cur_loc,
                        begin=spec_str[0:cur_loc],
                        broken=spec_str[cur_loc:]))

        specifier.sort()                
        self.specifier = specifier
        
    def next(self):
        if not self.specifier:
            return None  # No specifiers returns None.
        
        now = datetime.now()
        seconds_since_midnight = (
            now - now.replace(hour=0, minute=0, second=0, microsecond=0)
                ).total_seconds()
                
        last = self.specifier[-1]
        for spec in self.specifier:
            if seconds_since_midnight < spec[0]:
                return last[1], spec[0] - seconds_since_midnight, spec[1]
            last = spec
        return last[1], self.specifier[0][0] + 24*60*60 - seconds_since_midnight, self.specifier[0][1]
                

SPECIFIER_FUNC_MAP={'a': loc_abs, 'r': loc_rel}
SPECIFIER_ORDER_MAP={'ux': 0, 'uy': 1, 'lx': 2, 'ly': 3}

DEFAULT_CROP_SPEC = [
    (loc_rel, 0.),
    (loc_rel, 0.),
    (loc_rel, 1.),
    (loc_rel, 1.)]

class CropSpecifier:
    def __init__(self, spec_str):
        
        specifier = list(DEFAULT_CROP_SPEC)
        itr = CROP_SPEC_RE.finditer(spec_str)
        cur_loc = 0
        for grp in itr:
            # Check for errors.
            span = grp.span()
            if span[0] != cur_loc:
                raise CropSpecifierErrorException(
                    'Crop specification error at column: {col} in '
                    'provided specifier:\n    {begin}>>>{broken}<<<{rest}'
                    .format(col=cur_loc,
                            begin=spec_str[0:cur_loc],
                            broken=spec_str[cur_loc:span[1]],
                            rest=spec_str[span[1]:]))
                
            cur_loc = span[1]
            
            corner, absolute, abs_param, relative, rel_param = grp.groups()
            corner_index = SPECIFIER_ORDER_MAP[corner.lower()]
            if absolute:
                specifier[corner_index] = (loc_abs, int(abs_param, 0))
            elif relative:
                specifier[corner_index] = (loc_rel, float(rel_param))
            else:
                raise CropSpecifierErrorException(
                    'Incomplete crop specification error at column: {col} in '
                    'provided specifier:\n    {begin}>>>{broken}<<<{rest}'
                    .format(col=span[0],
                            begin=spec_str[0:span[0]],
                            broken=spec_str[span[0]:span[1]],
                            rest=spec_str[span[1]:]))
            
        if cur_loc != len(spec_str):
            raise CropSpecifierErrorException(
                'Crop specification error at column: {col} in '
                'provided specifier:\n    {begin}>>>{broken}'
                .format(col=cur_loc,
                        begin=spec_str[0:cur_loc],
                        broken=spec_str[cur_loc:]))
                
        self.specifier = specifier
        
    def apply_specifier(self, sizex, sizey):
        '''Applies this crop specifier to the given x and y image sizes.'''
        return tuple(spec[0][0](spec[1], spec[0][1]) 
                  for spec in zip(self.specifier, (sizex, sizey) * 2))
        
    def to_crop_fn(self):
        def crop_fn(pil_image):
            return self.apply_specifier(pil_image.size[0], pil_image.size[1])
        return crop_fn

COLOUR_RE_STR=nc(SPACES_SPEC, INT_SPEC_POS, SPACES_SPEC, ',', 
                 SPACES_SPEC, INT_SPEC_POS, SPACES_SPEC, ',', 
                 SPACES_SPEC, INT_SPEC_POS)

COLOUR_SPEC_RE_STR=nc(
    nc(INT_SPEC_POS, SPACES_SPEC, ':', SPACES_SPEC) + '?', 
    COLOUR_RE_STR, 
    SPACES_SPEC)
COLOUR_SPEC_RE=re.compile(COLOUR_SPEC_RE_STR)

class ColourSpec:
    
    def __init__(self, color_spec_str):
        self.color_spec_str = color_spec_str
        colour_spec = []
        itr = COLOUR_SPEC_RE.finditer(color_spec_str)
        cur_loc = 0
        for grp in itr:
            # Check for errors.
            span = grp.span()
            if span[0] != cur_loc:
                raise ColorSpecifierErrorException(
                    'Colour specification error at column: {col} in '
                    'provided specifier:\n    {begin}>>>{broken}<<<{rest}'
                    .format(col=cur_loc,
                            begin=color_spec_str[0:cur_loc],
                            broken=color_spec_str[cur_loc:span[1]],
                            rest=color_spec_str[span[1]:]))
                
            cur_loc = span[1]
            
            repeat, red, green, blue = grp.groups()
            
            if repeat is None:
                repeat = '1'
                
            colour_spec.append((int(repeat, 0), 
                                (int(red, 0), int(green, 0), int(blue, 0))))

        if cur_loc != len(color_spec_str):
            raise CropSpecifierErrorException(
                'Colour specification error at column: {col} in '
                'provided specifier:\n    {begin}>>>{broken}'
                .format(col=cur_loc,
                        begin=color_spec_str[0:cur_loc],
                        broken=color_spec_str[cur_loc:]))
                
        self.colour_spec = tuple(colour_spec)
    
    def generate_image(self, save_name=None, repeat_no=1):
        data = np.zeros((LEDS_Y_SIZE, LEDS_X_SIZE, 3), dtype=np.uint8)
        
        i = 0
        data_len = LEDS_Y_SIZE * LEDS_X_SIZE
        while (True):
            if i >= data_len:
                break
            for repeat, colour in self.colour_spec:
                if i >= data_len:
                    break
                for _ in range(repeat):
                    if i >= data_len:
                        break
                    x = i % LEDS_X_SIZE
                    y = i // LEDS_X_SIZE
                    data[y][x][0] = colour[0]
                    data[y][x][1] = colour[1]
                    data[y][x][2] = colour[2]
                    i += 1


        img = Image.fromarray(data, 'RGB')
        if save_name:
            img.save(save_name)
        return img

    def generate_image_bytes(self, save_name=None, repeat_no=1):
        img = self.generate_image(save_name=save_name, repeat_no=repeat_no)
        image_bytes = assemble_bytes(repeat_no,
            hashlib.md5(self.color_spec_str.encode('utf-8')).digest(), 
            img,
            (255, 255, 0))
        return image_bytes
    
    
        
def t(restr, instr):
    r = re.compile(restr)
    i = r.finditer(instr)
    ms=[w for w in i]
    return list((g.groups(), g.span()) for g in ms), ms

def send_image(pargs):
    dcclient = DcClient(localport=pargs.localport)
    addrs = make_addr_from_args(pargs, dcclient)
    
    # Create image fetcher once
    image_fetcher = ImageFetcher(dcclient, 
                               files=pargs.files,
                               delay=pargs.delay,
                               key_frame_delay=pargs.key_frame_delay,
                               crop_spec=pargs.crop,
                               blend_frames=pargs.blend_frames,
                               fill_colour=pargs.fill_colour,
                               loop_count=pargs.loop_count)
    
    # For multiple clients, load the images once and send to each client
    images = image_fetcher.images
    i = 0
    prev_time = time.time() - images[0][1]
    
    while pargs.loop_count < 0 or i < pargs.loop_count:
        i += 1
        for dc_image in images:
            delay_time = prev_time - time.time()
            if delay_time > 0:
                time.sleep(delay_time)
            else:
                prev_time = time.time()
            prev_time = prev_time + dc_image[1]
            
            # Send to all clients
            for addr in addrs:
                dcclient.send_frame(dc_image[0], addr=addr)
    
    return 0

def send_pattern(pargs):
    dcclient = DcClient(localport=pargs.localport)
    addrs = make_addr_from_args(pargs, dcclient)
    frame_bytes = pargs.colour_spec.generate_image_bytes(
        save_name=pargs.save_to, repeat_no=pargs.rep)
    
    for addr in addrs:
        if not pargs.quiet:
            print(f"Sending pattern to controller at {addr[0]}:{addr[1]}")
        dcclient.send_frame(frame_bytes, addr)
    
    return 0

    
class CLCommand:
    def __init__(self, name, desc, func):
        self.name = name
        self.desc = desc
        self.func = func
        self.example_str = None
        self.parser_args = []
        self.add_argument(
            'sub_command',
            metavar='command',
            type=str,
            nargs=1,
            help='The sub-command. Must be first.')
        self.add_argument(
            '-q',
            '--quiet',
            action='store_true',
            help='Be quiet')
        self.add_argument(
            '--repeat',
            type=int,
            default=1,
            help='Repeat the command this many times.')
        
    def add_ip_args(self):
        self.add_argument(
            '--localport', 
            type=int, 
            help='Local port',
            default=UDP_PORT,
            required=False)
        self.add_argument(
            '--ip', 
            type=str, 
            help='IP address(es) of controller(s), comma-separated for multiple', 
            required=False)
        self.add_argument(
            '--port', 
            type=int,
            default=UDP_DC_PORT, 
            help='Port of controller', 
            required=False)
        self.add_argument(
            '--timeout', 
            type=int,
            default=30,
            help='Timeout time in seconds for address discovery', 
            required=False
        )
        self.add_argument(
            '--count',
            type=int,
            default=1,
            help='Number of clients to discover when IP not specified (-1 for unlimited)',
            required=False
        )
        self.add_argument(
            '--duration',
            type=int,
            default=-1,
            help='How long to listen for clients in seconds when IP not specified (-1 for unlimited)',
            required=False
        )
        return self
        
    def add_example(self, example_str):
        self.example_str = example_str
        return self
        
    def add_argument(self, *args, **kwds):
        self.parser_args.append((args, kwds))
        return self
    
    def apply_args(self, parser):
        for arg in self.parser_args:
            parser.add_argument(*(arg[0]), **(arg[1]))
        
    def perform(self, parser):
        self.apply_args(parser)
        args = parser.parse_args()
        for i in range(args.repeat):
            args.rep = i
            self.func(args)
        
    def describe(self):
        return '''\
            {name} : {desc}'''.format(name=self.name, desc=self.desc)
            
    def example(self):
        return '{argv0} {example_str}'.format(
            argv0=sys.argv[0], example_str=self.example_str)
        
def help_overall(args):
    eprint('''All commands for {cmd}
    (use {cmd} <option> --help for help on individual commands)
    '''.format(cmd=sys.argv[0]))
    for cl_cmd in CL_COMMANDS:
        eprint('  {name} - {desc}\n'.format(name=cl_cmd.name, desc=cl_cmd.desc))

CL_COMMANDS = (
    CLCommand('help', 'This help', help_overall),
    CLCommand('discover', 
              "Discovers Park Lights controller on local network", 
              discover
        ).add_argument(
            '--timeout', 
            type=int,
            default=30,
            help='Timeout time in seconds if no clients found', 
            required=False
        ).add_argument(
            '--count',
            type=int,
            default=1,
            help='Number of clients to discover (-1 for unlimited)',
            required=False
        ).add_argument(
            '--duration',
            type=int,
            default=-1,
            help='How long to listen for clients in seconds (-1 for unlimited)',
            required=False
        ).add_argument(
            '--report-interval',
            type=float,
            default=0,
            help='Interval in seconds to report discovered clients (0 to disable)',
            required=False
        ).add_example(
            'discover --count -1 --duration 300 --report-interval 30\nListens for all clients for 5 minutes, reporting every 30 seconds.'),
    CLCommand('reset', 
              'Resets the Park Lights display controller',
              reset_controller
        ).add_ip_args().add_argument(
            '--count',
            type=int,
            default=1,
            help='Number of clients to discover (-1 for unlimited)',
            required=False
        ).add_argument(
            '--duration',
            type=int,
            default=-1,
            help='How long to listen for clients in seconds (-1 for unlimited)',
            required=False
        ),
    CLCommand('brightness', 
              'Sets the display brightness',
              brightness
        ).add_ip_args().add_argument(
            'brightness', 
            metavar='brightness',
            type=check_0_255,
            nargs=1,
            help='Brightness value - range 0-255'
        ),
    CLCommand('timed_brightness',
              'Schedules a brightness change at a specified time of day.',
              timed_brightness
        ).add_ip_args().add_argument(
            'timed_brightness', 
            metavar='timed_brightness',
            type=TimedBrightnessSpecifier,
            nargs=1,
            help='Timed spec - {<time of day> <brightness>} eg: 17:45:30 200 23:00 100'
        ),
    CLCommand('set_gpio', 
              'Controls a GPIO pin',
              set_gpio
        ).add_ip_args().add_argument(
            '--pin', 
            type=check_0_max_gpio,
            help=('The pin number to set - range 0-%d' % MAX_GPIO_NUMBER), 
            required=True
        ).add_argument(
            '-s',
            '--setting', 
            type=check_pin_setting,
            help=('The setting to apply - one of %s' 
                  % repr(tuple(PIN_OPS.keys()))), 
            required=True
        ),
    CLCommand('monitor', 
              'Monitors lights controller information.',
              monitor
        ).add_argument(
            '--timeout', 
            type=int,
            default=30,
            help='Timeout time in seconds', 
            required=False
        ).add_argument(
            '--packets', 
            type=int,
            default=-1,
            help=('Prints controller status messages up to <--packets> times.'), 
            required=False
        ),
    CLCommand('send_image', 
              'Sends images from files to the Park Lights display',
              send_image
        ).add_ip_args().add_argument(
            'files', 
            metavar='files',
            type=str,
            nargs='+',
            help='List of image files.'
        ).add_argument(
            '--blend_frames', 
            type=int,
            default=0,
            help=('The number of blend frames.')
        ).add_argument(
            '--key_frame_delay', 
            type=float,
            default=1.0 / 2,
            help=('Blend key frame delay.')
        ).add_argument(
            '--delay', 
            type=float,
            default=1.0 / 25,
            help=('The delay between renders in seconds.')
        ).add_argument(
            '--fill_colour', 
            type=ColourSpec,
            default=ColourSpec('0x10,0x10,0x7f'),
            help=('The fill colour to use when image does not fill frame.')
        ).add_argument(
            '--loop_count', 
            type=int,
            default=1,
            help=('The number of loops to render, -1 means forever.')
        ).add_argument(
            '--crop', 
            type=CropSpecifier,
            default=CropSpecifier(''),
            help=('A crop specifier e.g. "uxr.1 uyr.1 lxr0.9 ly0.9" removes a 10%% sized border. '
                  'Specifiers are 4 values: upper x, upper y, lower x, lower y. '
                  'These are specified by ux, uy, lx, ly respectively. This can be followed by either a '
                  'relative "r" or "rel" followed by a floating point number between 0-1 or '
                  'absolute "a" or "abs" followed by a positive integer in pixels.')
        ).add_example(
            'send_image file1.png file2.png --delay 0.1 --loop_count 10'),
    CLCommand('send_pattern', 
              'Send a test image with the specified colours',
              send_pattern
        ).add_argument(
            '--save_to', 
            type=str,
            default=None,
            help=('The file name to save the resulting image to.')
        ).add_ip_args().add_argument(
            '--colour_spec', 
            type=ColourSpec,
            default=ColourSpec('0x7f,0x7f,0x7f'),
            help=('A color specifier is a list of colors optionally preceeded '
                  'by a positive integer indicating the number of times '
                  'that color is to be repeated before the next color in the '
                  'specifier is used. Once exhausted the whole sequence is '
                  'repeated. e.g. "25:255,255,0xff 50:10,10,0xa"')
        ),
    )


DESCRIPTION='''\
Park Lights display controller client.

'''

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

def main(argv):
    if len(sys.argv) > 1:
        cl_command = sys.argv[1]
    
        for cmd in CL_COMMANDS:
            if cmd.name == cl_command:
                    
                parser = argparse.ArgumentParser(
                        formatter_class=argparse.RawDescriptionHelpFormatter,
                        description=DESCRIPTION + cmd.describe(),
                        epilog=textwrap.dedent(cmd.example()))
        
                return cmd.perform(parser)
            
        eprint('''Error: {cmd} - requested option {cl_command} not found.
            Sub commands are one of:
        '''.format(
            cmd=sys.argv[0], 
            cl_command=cl_command))
    else:
        eprint('''Error: {cmd} - requires a sub command.
            Sub commands are one of:
        '''.format(cmd=sys.argv[0]))
    
    commands_map = dict([(cmd.name, cmd) for cmd in CL_COMMANDS])
    command_names = list(commands_map.keys())
    command_names.sort()
    
    for name in command_names:
        cmd = commands_map[name]
        eprint(cmd.describe())
    
    return 1


if __name__ == '__main__':
    if len(sys.argv) == 1:
        pass
        # sys.argv = [
        #     sys.argv[0], 
        #     'discover'
        # ]
        # sys.argv = [
        #     sys.argv[0], 
        #     'discover',
        #     "--count", "4",
        #     "--duration", "10",
        #     "--report-interval", "2"
        # ]
        
        # sys.argv = [
        #     sys.argv[0], 
        #     'send_pattern',
        #     "--ip", "10.1.0.48",
        #     '--colour_spec',
        #     "1:255,255,255 1:255,255,255"
        # ]
    exit(main(sys.argv))