#!/usr/local/bin/python3
# encoding: utf-8
'''

'''

import sys
import os
import re
import io
import subprocess
import tempfile
from dataclasses import dataclass
from dataclasses import field
from dataclasses import fields
from dataclasses import replace
from collections import OrderedDict
from pathlib import Path


from argparse import ArgumentParser
from argparse import RawDescriptionHelpFormatter



def getstatusoutput(cmd, env_overrides=()):
    """Return (exitcode, output) of executing cmd in a shell.

    Execute the string 'cmd' in a shell with 'check_output' and
    return a 2-tuple (status, output). The locale encoding is used
    to decode the output and process newlines.

    A trailing newline is stripped from the output.
    The exit status for the command can be interpreted
    according to the rules for the function 'wait'. Example:

    >>> import subprocess
    >>> subprocess.getstatusoutput('ls /bin/ls')
    (0, '/bin/ls')
    >>> subprocess.getstatusoutput('cat /bin/junk')
    (1, 'cat: /bin/junk: No such file or directory')
    >>> subprocess.getstatusoutput('/bin/junk')
    (127, 'sh: /bin/junk: not found')
    >>> subprocess.getstatusoutput('/bin/kill $$')
    (-15, '')
    """
    
    new_env = os.environ
    if env_overrides:
        new_env = new_env.copy()
        for k, v in env_overrides:
            new_env[k] = v
    try:
        data = subprocess.check_output(
            cmd, shell=True, text=True, stderr=subprocess.STDOUT, env=new_env)
        exitcode = 0
    except subprocess.CalledProcessError as ex:
        data = ex.output
        exitcode = ex.returncode
    if data[-1:] == '\n':
        data = data[:-1]
    return exitcode, data

class CLIError(Exception):
    '''Generic exception to raise and log different fatal errors.'''
    def __init__(self, msg):
        super(CLIError).__init__(type(self))
        self.msg = "E: %s" % msg
    def __str__(self):
        return self.msg
    def __unicode__(self):
        return self.msg
    
class FileNameErrorException(Exception):
    pass
    
FNAME_PARSER = re.compile('mcu_(.*)\\.txt')


# Special macro names.
AVR_AT_PARSER = re.compile('__AVR_AT([_A-Za-z0-9]+)__')
ARDUINO_AVR_PARSER = re.compile('ARDUINO_AVR_([_A-Za-z0-9]+)')

class Macro:
    def __init__(self, macro_name):
        self.macro_nane = macro_name
        self.values = set([])
        self.mcu_archs = []
        
    def add(self, value, arch):
        self.values.add(value)
        self.mcu_archs.append(arch)
    

class Macros:
    def __init__(self):
        self.macros = {}
        
    def add(self, macro_name, macro_value, arch):
        macro = self.macros.get(macro_name, None)
        if not macro:
            macro = Macro(macro_name)
            self.macros[macro_name] = macro
        macro.add(macro_value, arch)
        return macro

class MacroPair:
    def __init__(self, key, macro):
        self.key = key
        self.macro = macro
        self.mcu_archs = []
        self.final_archs = None

    def add(self, arch):
        self.mcu_archs.append(arch)
    
    def get_archs(self):
        if self.final_archs:
            return self.final_archs
        self.mcu_archs.sort()
        self.final_archs = tuple(self.mcu_archs)
        return self.final_archs
    

class MacroPairs:
    def __init__(self):
        self.macro_pairs = {}

    def add(self, macro_name, macro_value, arch, macro):
        key = (macro_name, macro_value)
        macro_pair = self.macro_pairs.get(key, None)
        if not macro_pair:
            macro_pair = MacroPair(key, macro)
            self.macro_pairs[key] = macro_pair
        macro_pair.add(arch)
        return macro_pair

class MultipleAvrArchException(Exception):
    pass
class MultipleArduinoAveException(Exception):
    pass

class Arch:
    def __init__(self, arch_key, file_name, macros, macro_pairs):
        self.arch_key = arch_key
        self.macro_pairs = {}
        self.avr_macro = None
        self.arduino_macro = None
        with open(file_name, "r") as f:
            for line in f:
                match = MACRO_PARSER.match(line)
                if match:
                    (macro_name, macro_value) = match.groups()
                    macro = macros.add(macro_name, macro_value, arch_key)
                    macro_pairs.add(macro_name, macro_value, arch_key, macro)
                    
                    avr_match = AVR_AT_PARSER.match(macro_name)
                    if avr_match:
                        if self.avr_macro and self.avr_macro != macro_name:
                            raise MultipleAvrArchException(
                                'Found multiple __AVR_AT* macros: '
                                f'{macro_name} and {self.avr_macro}.')
                        else:
                            self.avr_macro = macro_name
                            
                    arduino_avr_match = ARDUINO_AVR_PARSER.match(macro_name)
                    if arduino_avr_match:
                        if self.arduino_macro:
                            raise MultipleArduinoAveException(
                                'Found multiple ARDUINO_AVR_* macros '
                                f'{macro_name} and {self.arduino_macro}.')
                        else:
                            self.arduino_macro = macro_name
                    

class ArchSet:
    def __init__(self, key):
        self.key = key
        self.macro_pairs = []
        
    def add(self, macro_pair):
        self.macro_pairs.append(macro_pair)
        

class Archs:
    def __init__(self):
        self.archs = {}
        self.macros = Macros()
        self.macro_pairs = MacroPairs()
        self.arch_sets = None
        
    def add(self, arch_key, file_name):
        arch = Arch(arch_key, file_name, self.macros, self.macro_pairs)
        self.archs[arch.arch_key] = arch

    def process(self):
        arch_sets = {}
        for mp in self.macro_pairs.macro_pairs.values():
            key = mp.get_archs()
            arch_set = arch_sets.get(key, None)
            if not arch_set:
                arch_set = ArchSet(key)
                arch_sets[key] = arch_set
            arch_set.add(mp)
        
        self.arch_sets = list((tuple(mp.key for mp in mps.macro_pairs), key) for key, mps in arch_sets.items())
        self.arch_sets.sort()
        
        # Finds keys with identical macro sets.
        self.id_maps = dict()
        self.macro_table = dict()
        for arch_set in self.arch_sets:
            arch_set_as_set = set(arch_set[1])
            for arch in arch_set_as_set:
                arch_intersection = self.id_maps.get(arch, None)
                if arch_intersection is None:
                    self.id_maps[arch] = arch_set_as_set
                    self.macro_table[arch] = [arch_set]
                else:
                    self.id_maps[arch] = arch_intersection.intersection(arch_set_as_set)
                    self.macro_table[arch].append(arch_set)
        
        self.id_sets = tuple(sorted(set((tuple(sorted(i)) for i in self.id_maps.values()))))


# Function returns user's fully qualifier path to Arduino IDE installation.

def getArduinoPath():
    # Windows
    if os.name == 'nt':
        home_dir = os.path.expanduser('~')
        possible_paths = (
            os.path.join(home_dir, 'AppData', 'Local', 'Arduino15', 'packages', 'arduino'),
            'C:\\Program Files (x86)\\Arduino15\\packages\\arduino',
        )
        # Find the first path that exists.
        for path in possible_paths:
            if os.path.exists(path):
                return path
        
        # If none of the paths exist, return the first one.
        return possible_paths[0]
    if os.name == 'posix':
        # Linux
        return '/usr/share/arduino'
    if os.name == 'mac':
        # Mac
        return '/Applications/Arduino.app/Contents/Java'
    
    raise Exception('Unsupported OS')


ARDUINO_CORES=getArduinoPath()
ARDUINO_AVR_DIR=os.path.join(ARDUINO_CORES, 'hardware', 'avr', '1.8.6')
ARDUINO_BOARDS="boards.txt"
ARDUINO_PLATFORM="platform.txt"
ARDUINO_VARIANTS="variants"
ARDUINO_AVR_GNU_DIR=os.path.join(ARDUINO_CORES, 'tools', 'avr-gcc', '7.3.0-atmel3.6.1-arduino7')
ARDUINO_AVR_GNU_GPP="bin\\avr-g++.exe"
ARDUINO_AVR_GNU_DEV_SPECS="lib\\gcc\\avr\\{version}\\device-specs"
GCC_VERSION_PARSER=re.compile('.*\(GCC\) ((?:[0-9a-zA-Z]+\.)*[0-9a-zA-Z]+)')

class CompilerExecutionErrorException(Exception):
    pass

class CompilerVersionErrorException(Exception):
    pass

@dataclass
class ArduinoFiles:
    
    avr_dir: str
    avr_gnu_dir: str
    boards: str
    platform: str
    variants: str
    gnu_gpp: str
    gnu_gpp_version: str
    gnu_gpp_dev_specs: str
    
    @classmethod
    def create(cls, avr_dir=ARDUINO_AVR_DIR, avr_gnu_dir=ARDUINO_AVR_GNU_DIR):
        gnu_gpp = os.path.join(avr_gnu_dir, ARDUINO_AVR_GNU_GPP)
        print(f'gnu_gpp: {gnu_gpp}')
        cmd = f'"{gnu_gpp}" --version'
        result = getstatusoutput(cmd)
        if result[0]:
            raise CompilerExecutionErrorException(
                'Error getting compiler version: '
                f'command status: {result[0]}\n'
                f'command: "{cmd}"\n'
                f'error: {result[1]}\n')
        
        vers_match = GCC_VERSION_PARSER.match(result[1].split('\n')[0])
        if not vers_match:
            raise CompilerVersionErrorException(
                'Unable to determine compiler version from --version output:\n'
                f'{result[1]}\n')
        gnu_gpp_version = vers_match.groups()[0]
        
        return ArduinoFiles(
            avr_dir=avr_dir, 
            avr_gnu_dir=avr_gnu_dir, 
            boards=os.path.join(avr_dir, ARDUINO_BOARDS), 
            platform=os.path.join(avr_dir, ARDUINO_PLATFORM),
            variants=os.path.join(avr_dir, ARDUINO_VARIANTS), 
            gnu_gpp=gnu_gpp,
            gnu_gpp_version=gnu_gpp_version,
            gnu_gpp_dev_specs=os.path.join(
                avr_gnu_dir, 
                ARDUINO_AVR_GNU_DEV_SPECS.format(version=gnu_gpp_version)))
    
    def fillOptions(self, options):
        options.addValue(
            'runtime.tools.avr-gcc.path', self.arduino_files.avr_gnu_dir)
        
    def coresDir(self, platform):
        return os.path.join(self.avr_dir, 'cores', platform)
    
    def variantDir(self):
        return os.path.join(self.avr_dir, 'variants', '{build.variant}')
    
    def includeDirs(self, platform='arduino'):
        return (self.coresDir(platform), self.variantDir())
        
class MultipleAssignmentsException(Exception):
    pass

@dataclass
class PathNodeMatcher:
    match_regex: object = re.compile('.*')
    
    def match(self, other):
        return self.match_regex.match(other) != None
            

def tail_match(path, tail):
    tail_len = len(tail)
    if len(path) < tail_len:
        return False
    
    for i, j in zip(path[-tail_len:], tail):
        if i != j:
            if isinstance(j, PathNodeMatcher):
                if not j.match(i):
                    return False
            else:
                return False
    
    return True


@dataclass
class OptionsNode:
    name: str
    parent: object = field(default=None, repr=False, compare=False)
    nodes: dict = None
    value: str = None
    
    def add(self, path, value):
        if len(path):
            subnode = path[0]
            node = self.getOrAddNode(subnode)
            node.add(path[1:], value)
        else:
            last_value = self.value
            self.value = value
            if last_value != None:
                raise MultipleAssignmentsException('Already assigned.')
            
    def getOrAddNode(self, name):
        if self.nodes == None:
            self.nodes = {}
        node = self.nodes.get(name, None)
        if not node:
            node = OptionsNode(name, parent=self)
            self.nodes[name] = node
        return node
    
    def getLocalNode(self, name):
        if self.nodes == None:
            return None
        return self.nodes.get(name, None)
    
    def getNode(self, path):
        if len(path):
            subnode = path[0]
            node = self.getLocalNode(subnode)
            if node == None:
                return None
            return node.getNode(path[1:])
        else:
            return self

    def get(self, path):
        node = self.getNode(path)
        if node:
            return node.value
        
    def traverse(self, observer, parent_path=()):
        path = parent_path + (self.name,) if self.name != None else parent_path
        if self.nodes:
            node_names = list([node for node in self.nodes.keys()])
            node_names.sort()
            # observe all the leaf nodes before all the branches.
            for name in node_names:
                node = self.nodes.get(name)
                if node.value != None:
                    observer.value(path + (name,), node.value)

            # observe branches.
            for name in node_names:
                node = self.nodes.get(name)
                if node.nodes != None:
                    node.traverse(observer, path)
    @classmethod
    def rootFor(cls, node):
        name = node.name
        return cls('', None, {name:node}, None)
@dataclass         
class OptionsNodeObserverBase:
    tail_match: tuple = None
    
    def value(self, path, value):
        if self.tail_match:
            if not tail_match(path, self.tail_match):
                return
        self.matched(path, value)

    def matched(self, path, value):
        pass
           
@dataclass   
class OptionsNodeObserverPrinter(OptionsNodeObserverBase):
    ostream: io.TextIOWrapper = sys.stdout

    def matched(self, path, value):
        self.ostream.write('.'.join(path))
        self.ostream.write('=')
        self.ostream.write(f'{value}\n')

class MergedNodesProxy:
    
    def __init__(self, nodes, root, path, value):
        self.nodes = nodes
        self.root = root if root else self
        self.path = () if path is None else path
        self.value = value
        
    def makeProxy(self, alt_value=None):
        result = NodeStrProxy(alt_value if alt_value else self.value)
        result.merged_nodes_proxy = self
        return result
        
    def get(self, name):
        result_nodes = []
        result_str = None
        for node in self.nodes:
            child = node.getLocalNode(name)
            if child:
                result_nodes.append(child)
                if result_str is None and isinstance(child.value, str):
                    result_str = child.value.format_map(self.root.makeProxy())

        return MergedNodesProxy(
            tuple(result_nodes), self.root, self.path + (name,), result_str)
    
    def isEmpty(self):
        return False if self.nodes else True
    
    def getPath(self):
        return self.path
    
    def getPathName(self):
        return '.'.join(self.getPath())


class NodeStrProxy(str):
    '''A proxy for a node or string value contained.'''
    def __getattribute__(self, name):
        if name == '__getattribute__':
            return object.__getattribute__(self, name)
        local_merged_nodes_proxy = object.__getattribute__(self, 'merged_nodes_proxy')
        merged_nodes_proxy = local_merged_nodes_proxy.get(name)
        if not merged_nodes_proxy.value is None or not merged_nodes_proxy.isEmpty():
            return merged_nodes_proxy.makeProxy()
        else:
            try:
                return object.__getattribute__(self, name)
            except AttributeError as ex:
                parent_path = merged_nodes_proxy.getPath()
                path_name = '.'.join(parent_path)
                print(f'not found {path_name}')
                return merged_nodes_proxy.makeProxy('{' + path_name + '}')

    def __getitem__(self, key):
        return self.__getattribute__(key)

class InvalidOptionLineException(Exception):
    pass

OPTIONS_PARSER = re.compile(
    '(?:(?:([0-9A-Za-z_\.]*)(?:[ \t]*)=(?:[ \t]*)(.*))|(#+.*)|([ \t]*))$')

class OptionsFile:
    '''Parses an Arduino options file (boards.txt, platform.txt etc) into
    a hierarchical OptionsNode structure.'''

    def __init__(self, root=None):
        self.root = root if root else OptionsNode(None)

    def load(self, filename):
        '''Loads the contents of the given filename into this OptionsFile
        object's OptionsNode tree.'''
        
        with open(filename, "r") as fstream:
            self.loadStream(filename, fstream)
            
    def loadStream(self, logname, line_stream):
        '''Loads the contents of the given line iterable (line_stream) into this
        OptionsFile object's OptionsNode tree.'''
        line_count = 0
        for line in line_stream:
            line_count += 1
            match = OPTIONS_PARSER.match(line)
            if match:
                (pathstr, value, comment, blank) = match.groups()
                if pathstr:
                    try:
                        self.addValue(pathstr, value)
                    except MultipleAssignmentsException:
                        raise InvalidOptionLineException(
                            f'{logname}:{line_count}: multiple assignments "{line}"')
            else:
                raise InvalidOptionLineException(
                    f'{logname}:{line_count}: Failed to parse line "{line}"')
                
    def addValue(self, pathstr, value):
        path = pathstr.split('.')
        self.root.add(path, value)
        return self
    
    def addKeyValues(self, kv_pairs):
        for k, v in kv_pairs:
            path = k.split('.')
            self.root.add(path, v)
        return self
        
    def add(self, **kwds):
        return self.addKeyValues(kwds)
                    
    def traverse(self, observer):
        '''Traverse the entire tree using the provided observer.'''
        self.root.traverse(observer, ())
        
    def get(self, path):
        return self.root.get(path)
    
    def getNode(self, path):
        return self.root.getNode(path)

    def getWrapped(self, other_nodes):
        return MergedNodesProxy(
            other_nodes + (self.root,), None, None, '').makeProxy()
    

@dataclass
class ArduinoBoardOptions:
    path: tuple
    options_file: OptionsFile
    is_base: bool = False
    base_path: tuple = None
    build__board: str = None
    build__core: str = None
    build__extra_flags: str = None
    build__f_cpu: str = None
    build__mcu: str = None
    build__pid: str = None
    build__vid: str = None
    build__usb_manufacturer: str = None
    build__usb_product: str = None
    build__variant: str = None
    build__esp_ch_uart_br: str = None
    menu__cpu: str = None
    
    def getBuildNodes(self):
        node = OptionsNode.rootFor(
                self.options_file.getNode(self.path + ('build',)))
        if self.base_path:
            return (node, OptionsNode.rootFor(self.options_file.getNode(
                    self.base_path + ('build',))))
        return (node,)
    
    def getBoardName(self):
        if len(self.path) > 3:
            return self.path[0] + '_' + self.path[-1]
        return self.path[0] + '_' + self.build__mcu
        
    
def field_map(clazz, exclusion=()):
    flist = fields(clazz)
    result = dict()
    for f in flist:
        if f.name in exclusion:
            continue
        result[tuple(f.name.split('__'))] = f.name
    return result

ArduinoBoardOptions.FIELDS_MAP=field_map(
    ArduinoBoardOptions, ('path', 'is_base', 'base_path', 'options_file'))
    
@dataclass
class OptionsNodeObserverBoards(OptionsNodeObserverBase):
    arduino_boards: object = None
    tail_match: tuple = None
    
    def matched(self, path, value):
        self.arduino_boards.add_value(path, value)

@dataclass
class ArduinoBoards:
    options_file: OptionsFile
    boards: dict = field(default_factory=dict)
    menu: str = None
    
    def __post_init__(self):
        self.options_file.traverse(
            OptionsNodeObserverBoards(arduino_boards=self,
                                      tail_match=('build', PathNodeMatcher())))
        
    def getBoard(self, path):
        board = self.boards.get(path, None)
        if not board:
            base_board = None
            if len(path) > 3:
                base_board = self.boards.get(path[0:1], None)
            if base_board:
                base_board.is_base = True
                board = replace(base_board)
                board.path = path
                board.is_base = False
                board.base_path = base_board.path
            else:
                board = ArduinoBoardOptions(path, self.options_file)
            self.boards[path] = board
        return board
    
    def add_value(self, path, value):
        if not path or len(path) < 3:
            return
        
        board_path = path[0:-2]
        board = self.getBoard(board_path)
        param = path[-2:]
        field = ArduinoBoardOptions.FIELDS_MAP.get(param)
        if not field:
            sys.stderr.write(f'Field for path {".".join(path)} not found.\n')
            return
        setattr(board, field, value)

    def getBoards(self):
        return tuple(b for b in self.boards.values() if not b.is_base)


def process_macros_folders(paths):
    archs = Archs()
    
    for inpath in paths:
        for file_name in os.listdir(inpath):
            if file_name.endswith(".txt"):
                
                match = FNAME_PARSER.match(file_name)
                if not match:
                    raise FileNameErrorException(
                        f'Failed parse file {file_name}.')
                full_path = os.path.join(inpath, file_name)
                mcu_arch = match.groups()[0]
                archs.add(mcu_arch, full_path)
    
    archs.process()

    return archs

def do_archs():
    paths = ('D:\\cygwin64\\home\\gianni\\limbo\\arduino\\mcu_flags\\all',)
    archs = process_macros_folders(paths)
        
    for arch_set in archs.arch_sets:
        print(arch_set)
        
    return archs



class ArduinoParams:
    
    def __init__(self):
        self.arduino_files = ArduinoFiles.create()
        
        self.boards_options_file = OptionsFile()
        self.boards_options_file.load(self.arduino_files.boards)
        
        self.arduino_boards = ArduinoBoards(self.boards_options_file)
        
        self.platform_options_file = OptionsFile()
        self.platform_options_file.load(self.arduino_files.platform)
        
        self.default_build_options = OptionsFile()
        self.default_build_options.addValue('build.arch', 'AVR')
        
        self.default_runtime_options = OptionsFile()
        self.default_runtime_options.addValue(
            'runtime.tools.avr-gcc.path', self.arduino_files.avr_gnu_dir)
        self.default_runtime_options.addValue('runtime.ide.version', '10813')
        
    def getAllNodes(self):
        return (self.default_build_options.root,
                self.default_runtime_options.root)
        
    def getPlatformStr(self, key, board):
        return self.getPlatformStrPath(tuple(key.split('.')), board)
    
    def getIncludes(self, *additional):
        inc = (f'"-I{d}"' for d in self.arduino_files.includeDirs() + additional)
        return ' '.join(inc)
    
    def getPlatformStrPath(self, path, board, 
            add_values=(),
            **kwds):
        of = OptionsFile().addKeyValues(kwds.items())
        of.addKeyValues(add_values)
        wrapped_values = self.platform_options_file.getWrapped(
            (of.root,) + board.getBuildNodes() + self.getAllNodes())
        value = self.platform_options_file.get(path)
        if value:
            return value.format_map(wrapped_values)
        return value
    
    def getCompilerLineStr(
            self, 
            key, 
            board, 
            source_file, 
            addl_includes, 
            add_values=(), 
            **dest):
        return self.getCompilerLinePath(
            tuple(key.split('.')), 
            board, 
            source_file, 
            addl_includes, 
            add_values=add_values, 
            **dest)
        
    def getCompilerLinePath(
            self, 
            path, 
            board, 
            source_file, 
            addl_includes, 
            add_values=(), 
            **dest):
        return self.getPlatformStrPath(
            path,
            board,
            source_file=source_file,
            includes=self.getIncludes(*addl_includes),
            add_values=add_values,
            **dest)
        
    def runPreprocMacros(self, 
                         board, 
                         source_file, 
                         preprocessed_file_path,
                         env_overrides=None,
                         add_values=()
                         ):
        cmd = self.getCompilerLineStr(
            'recipe.preproc.macros',
            board,
            source_file,
            (),
            preprocessed_file_path=preprocessed_file_path,
            add_values=add_values
            )
    
        return self.runCmd(cmd, env_overrides=env_overrides)
    
    def runPreprocIncludes(self, 
                           board, 
                           source_file, 
                           env_overrides=None,
                           add_values=()):
        cmd = self.getCompilerLineStr(
            'recipe.preproc.includes',
            board,
            source_file,
            (),
            add_values=add_values
            )
    
        return self.runCmd(cmd + ' -E -dM', env_overrides=env_overrides)
    
    def runCmd(self, cmd, env_overrides=None):
        escaped_cmd = escapeCmd(cmd)
        status, output = getstatusoutput(escaped_cmd, env_overrides)
        return status, output, escaped_cmd
        
def escapeCmd(cmd):
    t = []
    state = 0 
    for c in cmd:
        if c == "'":
            if state == 0:
                state = 1
            else:
                state = 0
            t.append('"')
        elif c == '"':
            if state == 1:
                t.append('\\"')
            else:
                t.append('"')
        elif c == '\\':
            t.append('\\')
        else:
            t.append(c)
    return ''.join(t)


BOARDS_SUBDIR = 'boards'

header_macros='''
#define _UTIL_DELAY_BASIC_H_ 1
#define __MATH_H
#define __attribute__(a)
#define __asm__(a)
#define __inline__
#define __builtin_constant_p(a) 0
#define __extension__
#define __builtin_va_list int
#define __null 0
#define volatile
'''

SNIP_STRING='////---SNIP---'
INPUT_LESS_FILE_CPP=f'''// Generated file.
{SNIP_STRING}
#define ARDUINO_MAIN 1

#define __attribute__(a)
#define uint8_t Symbol
#include <pins_arduino.h>
'''

INPUT_PREPROC_FILE_CPP=f'''#define ARDUINO_MAIN 1
#include <Arduino.h>
#undef Pins_Arduino_h
#define ARDUINO_MAIN 1
{SNIP_STRING}
#include <pins_arduino.h>
'''

INPUT_DEV_SPEC_FILE_CPP='''// Get the device specific macros.
#include <avr/io.h>
'''

INPUT_CC_SPEC_FILE_CPP='''// Compiler only macros.
// Don't include #include <avr/io.h>
'''


DEVICE_SPEC_PARSER=re.compile('.*__AVR_DEVICE_NAME__=([a-zA-Z0-9_]+).*')

SUPPLEMENTAL_HEADER='''// Generated for arch {mcu_arch}.
// This file is generated from the avr-gcc compiler with the mcu
// set to {mcu_arch} from macros specific to avr/io.h.
// Any changes to this file will likely be lost next time this file
// is regenerated. Many any mcu_arch specific changes to 
// ardo_supplemental_{mcu_arch}_defs.h.

#ifndef ardo_supplemental_{mcu_arch}__h
#define ardo_supplemental_{mcu_arch}__h

#include "setlx_cstdint.h"
#include "setl_bit_fields.h"
#include "ardo_avr_bit_io_defs.h"

namespace ardo {{
namespace sys {{
namespace avr {{
namespace arch_{mcu_arch} {{

constexpr const char MCU_ARCH_NAME[] = "{mcu_arch}";
constexpr ptrdiff_t cc__SFR_OFFSET = {__SFR_OFFSET};

template <typename T, ptrdiff_t w_addr>
using IoRegisterDef = avr::nfp::IoRegisterDef<T, w_addr, cc__SFR_OFFSET>;
using avr::nfp::MemRegisterDef;

'''


SUPPLEMENTAL_TAIL = '''

}}  // arch_{mcu_arch}
}}  // namespace avr
}}  // namespace sys
}}  // namespace ardo

#endif  // ardo_supplemental_{mcu_arch}__h
'''


ADRO_AVR_HEADER='''// ArdOinus specific header for AVR {mcu_arch} MCU.
// This file will not be regenerated (unlike ardo_supplemental_{mcu_arch}.h)
// so manual changes to this file will survive regeneration of architecture
// specific definitions.

#ifndef ardo_supplemental_{mcu_arch}_defs__h
#define ardo_supplemental_{mcu_arch}_defs__h

#include "ardo_supplemental_{mcu_arch}.h"

namespace ardo {{
namespace sys {{
namespace avr {{
namespace arch_{mcu_arch} {{

// Add only {mcu_arch} specific resources here.
// Resources in this namespace will appear in the ardo::sys::avr::mcu
// namespace when compiled for the {mcu_arch} architecture.
// Any code added here should be independent of compiler provided resources
// so as to enable compiling of this code in any environment for the 
// purpose of cross platform testing.
'''

ADRO_AVR_TAIL = '''

}}  // arch_{mcu_arch}
}}  // namespace avr
}}  // namespace sys
}}  // namespace ardo

#endif  // ardo_supplemental_{mcu_arch}_defs__h
'''
# Header for the board specific definitions.
ADRO_BOARD_HEADER='''\
// ArdOinus specific header for board {board} using the {mcu_arch} MCU.

#ifndef ardo_board_{board}__h
#define ardo_board_{board}__h

#include "setl_device_map.h"
#include "setlx_type_traits.h"
#include "setlx_tuple.h"

// Include the MCU specific definitions.
#include "ardo_supplemental_{mcu_arch}_dev.h"

namespace ardo {{
namespace sys {{
namespace boards {{
namespace arduino {{
namespace board_{board} {{
    
namespace board_mcu = ardo::sys::avr::arch_{mcu_arch};

struct BoardDefinition {{
  static constexpr std::uint32_t CPU_FREQUENCY_HZ = {cpu_freq};

  using DevicePinMapping = setl::DeviceMappings<
    std::tuple<
        {pin_mappings}
    >
  >;
}};  // Board

'''

ARDO_BOARD_PIN_MAPPING = 'setl::PortMapping<board_mcu::{type}{number}, {pin_id}>'

# Tail for the board specific definitions.
ADRO_BOARD_TAIL = '''

}} // board_{board}
}} // arduino
}} // boards
}} // sys
}} // ardo

#endif  // ardo_board_{board}__h
'''

ARDO_ARDUINO_BOARDS_HEADER='''\
/**
 * Includes the header file for the Arduino board being compiled for.
 *
 * This is only specific for the Arduino boards.
 * (This file is generated, do not edit.)
 */

#ifndef ARDUINO_BOARDS__H
#define ARDUINO_BOARDS__H

namespace ardo {{
namespace sys {{

// Specialize this template for when the board is found.
template <bool found>
struct ArduinoBoard;

}}  // namespace sys
}}  // namespace ardo

'''

ARDO_ARDUINO_BOARDS_BODY='''\
#{if_elif} defined({arduino_board}) && defined({mcu_arch}) && (F_CPU == {cpu_freq})
#include "{header_file}"
namespace ardo {{ namespace sys {{

namespace board = ::ardo::sys::boards::arduino::board_{board};

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {{
    using type = board::BoardDefinition;
}};

}} }}  // namespace sys::ardo
'''

ARDO_ARDUINO_BOARDS_TAIL='''\
#elif !defined(ARDO_IGNORE_ARDUINO_BOARD_NOT_FOUND)
#error "No board definition found for the board being compiled."
#endif

#endif // ARDUINO_BOARDS__H
'''


ARDO_ARCH_MACRO_NAME_HEAD='''/**
 * Generated for AVR code. Do not edit.
 * This file is generated by using the avr-gcc compiler configuration.
 * This will include the architecture specific headers by using the
 * macro names like ARDO_MCU_ARCH_INCLUDE_{{mcu_arch}}. Multiple achitecture
 * specific header files can be included if multiple ARDO_MCU_ARCH_INCLUDE_...
 * macros are defined. The mcu_arch with the ARDO_MCU_ARCH_NAME defined
 * will cause the namespace for that architecture to be aliased to 
 * ardo::sys::avr::mcu. If the ARDO_MCU_ARCH_NAME is defined before loading
 * this file, the compiler arch setting is ignored.
 */

#ifndef ardo_mcu_avr_defs__h
#define ardo_mcu_avr_defs__h

#define ARDO_MCU_ARCH_NAMESPACE_(arch_name) arch_ ## arch_name
#define ARDO_MCU_ARCH_NAMESPACE(arch_name) ARDO_MCU_ARCH_NAMESPACE_(arch_name)

#if defined(ARDO_MCU_ARCH_NAME)
#pragma message("MCU architecture is overridden, compiler's mcu arch setting ignored.")
'''

ARDO_ARCH_MACRO_NAME_ENTRY1='''#elif defined({avr_at_macro_name})
#define ARDO_MCU_ARCH_INCLUDE_{mcu_arch} 1
#define ARDO_MCU_ARCH_NAME {mcu_arch}
'''
ARDO_ARCH_MACRO_NAME_END1='''#endif

// Architecture's defines included separately.
'''

ARDO_ARCH_MACRO_NAME_ENTRY2='''
#if defined(ARDO_MCU_ARCH_INCLUDE_{mcu_arch})
#include "ardo_supplemental_{mcu_arch}_dev.h"
#endif
'''

ARDO_ARCH_MACRO_NAME_TAIL='''

#if defined(ARDO_MCU_ARCH_NAME)
namespace ardo {{
namespace sys {{
namespace avr {{

namespace mcu = ARDO_MCU_ARCH_NAMESPACE(ARDO_MCU_ARCH_NAME);

}}  // namespace avr
}}  // namespace sys
}}  // namespace ardo
#endif

#endif  // ardo_mcu_avr_defs__h
'''

MACRO_PARSER = re.compile('#define +(.[_A-Za-z0-9]*) +(.*)$')

# Detects strings like "static const Symbol A3 = (17)"
STATIC_CONST_PARSER = re.compile(r'static\s+const\s+Symbol\s+([_A-Za-z0-9]+)\s*=\s*\(([0-9]+)\)')

# Returns a regex that matches the given mcu string and starting with __AVR.
def avr_mcu_macro_name_matcher(mcu):
    return re.compile(f'__AVR.*{mcu}__', re.IGNORECASE)

# Detects strings like __AVR_AT90PWM3B__
AVR_AT_NAME_PARSER = re.compile('__AVR_(?:AT|AVR|M)[a-zA-Z_0-9]+__')
    
IGNORE_NAMES_PARSER = re.compile(
    '(?:B[01]+)|(?:__AVR_LIBC.*)|(?:_AVR_.*_H_)|(?:INT.*_MAX)')
SUPP_MACRO_PARSER = re.compile(
    '[ \t]*(?:(?:(?:_SFR_IO *(8|16|32))'
    '|(?:_SFR_MEM *(8|16|32))'
    ')[ \t]*\\(((?:0x[0-9A-Fa-f]+)|(?:[0-9]+))\\))'
    '|(?:\\(?((?:0x[0-9A-Fa-f]+)|(?:[0-9]+))\\)?)'
    '|(?:\\(unsigned char\\)\\~_BV\\(((?:0x[0-9A-Fa-f]+)|(?:[0-9]+))\\))')

INT_VALUE_GROUP=3
SFR_MEM_GROUP=1
SFR_IO_GROUP=0
SFR_VALUE_GROUP=2
UCHAR_BV_GROUP=4

@dataclass
class IntValueType:
    macro_name: str
    value: str
    orig_value: str
    
    def render(self):
        return f'constexpr unsigned cc{self.macro_name} = {self.value};\n'

@dataclass
class RegisterType:
    macro_name: str
    value: str
    size: str
    orig_value: str
    
    def render(self):
        return (
            f'using rr{self.macro_name} = '
            f'{self.REGTYPE}RegisterDef<std::uint{self.size}_t, {self.value}>;\n')

    
class MemResisterType(RegisterType):
    '''Renderer for defines like:
        #define ADC _SFR_MEM16 (0x78)
    '''
    REGTYPE = 'Mem'
    
class IoResisterType(RegisterType):
    '''Renderer for defines like:
        #define ADCXX _SFR_IO16(0x55)
    '''
    REGTYPE = 'Io'

@dataclass
class UcharBvValueType:
    '''Renderer for #defines like:
    #define FUSE_DWEN (unsigned char)~_BV(6)
    Translates to:
    using ffFUSE_DWEN = setl::BitsRW<
        setl::SemanticType<setl::hash("FUSE_DWEN"), bool>, 1u<<6>;
    '''
    macro_name: str
    value: str
    orig_value: str
    
    def render(self):
        return (
            f'using ff{self.macro_name} = setl::BitsRW<'
            f'setl::SemanticType<setl::hash("{self.macro_name}"),'
            f' bool>, (1u << {self.value})>;\n')


@dataclass
class DefaultValueType:
    macro_name: str
    orig_value: str
    
    
    def render(self):
        return ''
    
def get_def_type(name, value, match):
    if match[INT_VALUE_GROUP]:
        return IntValueType(name, match[INT_VALUE_GROUP], value)
    
    if match[SFR_MEM_GROUP]:
        return MemResisterType(name, match[SFR_VALUE_GROUP], match[SFR_MEM_GROUP], value)
    
    if match[SFR_IO_GROUP]:
        return IoResisterType(name, match[SFR_VALUE_GROUP], match[SFR_IO_GROUP], value)
    
    if match[UCHAR_BV_GROUP]:
        return UcharBvValueType(name, match[UCHAR_BV_GROUP], value)
    
    return DefaultValueType(name, value)


class DeviceSpecCompilerErrorException(Exception):
    pass

@dataclass
class ProcessedBoard:
    board: ArduinoBoardOptions
    code_file : str
    code_less_file : str
    preproc_file : str
    preproc_less_file : str
    out_name : str
    out_less_name : str
    macros_name : str
    cmd_name : str
    deps_name : str
    preproc_less_filtered : str
    board_header_file : str
    all_boards_header_file : str
    arch_macro_name : str = field(init=False)
    cpu_freq_hz : str = field(init=False)

class CreateArduinoData:

    def __init__(self, tmp_path='ardo_data'):
        self.params = ArduinoParams()
        if not tmp_path:
            tmp_path = tempfile.TemporaryDirectory(prefix='ardogen-')
        self.top_dir = tmp_path
        self.dir_path = os.path.join(tmp_path, 'arduino_boards')
        Path(self.dir_path).mkdir(parents=True, exist_ok=True)
        self.dir_boards_path = os.path.join(tmp_path, 'arduino_boards', BOARDS_SUBDIR)
        Path(self.dir_boards_path).mkdir(parents=True, exist_ok=True)
        self.dev_spec_data = os.path.join(tmp_path, 'device_specs')
        Path(self.dev_spec_data).mkdir(parents=True, exist_ok=True)
        # AVR C++ friendly macros. 
        self.avr_supplemental = os.path.join(tmp_path, 'avr_supplemental')
        Path(self.avr_supplemental).mkdir(parents=True, exist_ok=True)
        
        self.boards = self.params.arduino_boards.getBoards()
        self.arch_macro_names = {}
        
        
    def getFileNames(self, boardname):
        return (f'ardo_{boardname}_input.cpp',
                f'ardo_{boardname}_input_less.cpp',
                f'ardo_{boardname}_preproc.h',
                f'ardo_{boardname}_preproc_less.h',
                f'ardo_{boardname}_out.h',
                f'ardo_{boardname}_out_less.h',
                f'ardo_{boardname}_macros.h',
                f'ardo_{boardname}_shell_cmd.bat',
                f'ardo_{boardname}_other_deps.d',
                f'ardo_{boardname}_preproc_less_filtered.h',
                os.path.join(BOARDS_SUBDIR, f'ardo_board_{boardname}.h'),
                os.path.join(BOARDS_SUBDIR, 'ardo_boards.h'))

    def getOutNames(self, board):
        names = self.getFileNames(board.getBoardName())
        return ProcessedBoard(board, *(
            os.path.join(self.dir_path, name) for name in names))
        
    def runAndReport(self, 
                     board, 
                     func,
                     input_file, 
                     env_overrides=None,
                     add_values=(),
                     **other_args):
        
        status, output, cmd = func(
                board,
                input_file,
                env_overrides=env_overrides,
                add_values=add_values,
                **other_args)
        
        if status:
            name = self.getFileNames(board.getBoardName())
            sys.stderr.write(f'Failed compile for board {name}\n')
            sys.stderr.write(f'{cmd}\n')
            sys.stderr.write(output)
            
        return status, output, cmd
        
    def runPreprocIncludes(self, board):
        processed_board = self.getOutNames(board)
        
        with open(processed_board.code_less_file, 'w') as cf:
            cf.write(INPUT_LESS_FILE_CPP)

        less_status, less_output, less_cmd = self.runAndReport(
                board,
                self.params.runPreprocMacros,
                processed_board.code_less_file,
                preprocessed_file_path=processed_board.preproc_less_file
            )

        with open(processed_board.code_file, 'w') as cf:
            cf.write(INPUT_PREPROC_FILE_CPP)
            
        out_status, out_output, out_cmd = self.runAndReport(
                board,
                self.params.runPreprocMacros,
                processed_board.code_file,
                preprocessed_file_path=processed_board.preproc_file
            )
            
        flags = f'-w -x c++ -MF \'{processed_board.deps_name}\''
        includes_status, includes_output, includes_cmd = self.runAndReport(
                board,
                self.params.runPreprocIncludes,
                processed_board.code_file,
                env_overrides=(('DEPENDENCIES_OUTPUT', processed_board.deps_name),),
                add_values=(('preproc.includes.flags', flags),)
            )
      
        with open(processed_board.cmd_name, 'w') as cmdf:
            cmdf.write(less_cmd)
            cmdf.write(out_cmd)
            cmdf.write(includes_cmd)
            
        if less_status or out_status or includes_status:
            return None
        
        macro_kv = self.writeMacrosOutput(
            processed_board.macros_name, includes_output)
        self.rewritePreproc(
            processed_board.preproc_file, processed_board.out_name)
        self.rewritePreproc(
            processed_board.preproc_less_file, processed_board.out_less_name)
        
        kvs = dict((k, v) for l, k, v in macro_kv.keys())
        
        board_params = {
            'cpu_freq' : kvs['F_CPU'],
            'mcu_arch' : kvs['__AVR_DEVICE_NAME__'],
            'board' : board.getBoardName()
        }
        
        avr_match = avr_mcu_macro_name_matcher(kvs['__AVR_DEVICE_NAME__'])
        
        arch_macro_name = tuple(k for k in kvs.keys() if avr_match.match(k))
        
        # avr_mactch must only match one macro name.
        processed_board.arch_macro_name = arch_macro_name[0]
        processed_board.cpu_freq_hz = kvs['F_CPU']
        
        self.filterPreprocLess(processed_board.preproc_less_file,
                               processed_board.preproc_less_filtered,
                               processed_board.board_header_file,
                               board_params)
        
        return processed_board
    
    def pullComponent(self, rx, data):
        match = re.compile(rx, re.DOTALL).match(data)
        if match:
            return match.group(1)
        return None
    
    def tokenizeArray(self, arrstr, rx):
        elems = arrstr.split(',')
        # Only use elems that are not empty and not whitespace.
        return tuple(rx.match(elem).group(1) for elem in elems if elem.strip())
    
    
    def filterPreprocLess(self, 
                          preproc_less_file, 
                          preproc_less_filtered, 
                          board_header_file,
                          board_params):
        with open(preproc_less_file) as inp, \
            open(preproc_less_filtered, 'w') as outp, \
            open(board_header_file, 'w') as board_header :
            data = inp.read()
            data = re.compile(r'#.*\n').sub('', data)
            # Remove C like comments
            data = re.compile(r'/\*.*?\*/', re.DOTALL).sub('', data)
            # Remove C++ like comments
            data = re.compile(r'//.*?\n').sub('', data)
            # Remove empty lines
            data = re.compile(r'\n\s*\n').sub('\n', data)
            
            # Find the digital_pin_to_port_PGM[] array.
            pin_to_port = self.pullComponent(
                r'.* digital_pin_to_port_PGM\[[^\]]*\] = {([^}]*)}', data)
            
            # Find the digital_pin_to_bit_mask_PGM[] array.
            pin_to_bit = self.pullComponent(
                r'.* digital_pin_to_bit_mask_PGM\[[^\]]*\] = {([^}]*)}', data)
            
            outp.write(data)
            
            if pin_to_port is None or pin_to_bit is None:
                raise Exception(
                    f'File: {preproc_less_filtered}: unable to parse pin to port/bit arrays')
                
            pin_to_port_tokens = self.tokenizeArray(pin_to_port, re.compile(r'\s*(.*)\s*'))
            pin_to_bit_tokens = self.tokenizeArray(pin_to_bit, re.compile(r'\s*\(\s*1\s*<<\s*\(\s*(\d+)\s*\)\s*\)\s*'))
            
            port_mappings = []
            
            for i, (port, bit) in enumerate(zip(pin_to_port_tokens, pin_to_bit_tokens)):
                port_mappings.append(
                    ARDO_BOARD_PIN_MAPPING.format(pin_id=i, type='ppP' + port[1], number=bit))
                
            board_header.write(
                ADRO_BOARD_HEADER.format(
                    pin_mappings=',\n        '.join(port_mappings),
                    **board_params
                ))
            
            board_header.write(ADRO_BOARD_TAIL.format(
                    **board_params))
    
    def rewritePreproc(self, preproc_file, out_name):
        snipping = True
        with open(preproc_file) as inp, open(out_name, 'w') as outp:
            for line in inp:
                if snipping:
                    if line.startswith(SNIP_STRING):
                        snipping = False
                else:
                    if line.startswith('#'):
                        outp.write('//')
                        outp.write(line)
                    else:
                        outp.write(line)
        return not snipping
        
    def writeMacrosOutput(self, macros_name, macros_output):
        kv = {}
        for line in macros_output.split('\n'):
            match = MACRO_PARSER.match(line)
            if match:
                (macro_name, macro_value) = match.groups()
                kv[(len(macro_name), macro_name, macro_value)] = line
                
        with open(macros_name, 'w') as mf:
            mf.write('\n'.join(
                kv[k] for k in sorted(kv.keys())))
            
        return kv
            

    def writeSupplementalOutput(
            self, mcu_arch, macros_name, macros_output, ignore_macros):
        ignores = set()
        avr_macro_name = None
        for line in ignore_macros.split('\n'):
            match = MACRO_PARSER.match(line)
            if match:
                (macro_name, macro_value) = match.groups()
                ignores.add(macro_name)
                if macro_name != '__AVR_MEGA__' and AVR_AT_NAME_PARSER.match(macro_name):
                    if mcu_arch in self.arch_macro_names:
                        sys.stderr.write(
                            f'Duplicate __AVT_*__ macro name for {mcu_arch}\n'
                            f'    "{macro_name}" and '
                            f'"{self.arch_macro_names[mcu_arch]} match."\n')
                    self.arch_macro_names[mcu_arch] = macro_name
                    avr_macro_name = macro_name
        
        if not avr_macro_name:
            sys.stderr.write(
                f'Could not find __AVT_*__ macro name for {mcu_arch}\n')
        
        kv = {}
        for line in macros_output.split('\n'):
            match = MACRO_PARSER.match(line)
            if match:
                (macro_name, macro_value) = match.groups()
                if IGNORE_NAMES_PARSER.match(macro_name):
                    continue
                if macro_name in ignores:
                    continue
                match = SUPP_MACRO_PARSER.match(macro_value)
                if match:
                    kv[macro_name] = get_def_type(
                        macro_name, macro_value, match.groups())
                else:
                    kv[macro_name] = DefaultValueType(macro_name, macro_value)
                
        with open(macros_name, 'w') as mf:
            mf.write(SUPPLEMENTAL_HEADER.format(
                mcu_arch=mcu_arch, __SFR_OFFSET=kv['__SFR_OFFSET'].value))
            keys = list(kv.keys()) 
            keys.remove('__SFR_OFFSET')
            mf.write(''.join(kv[k].render() for k in sorted(keys)))
            mf.write(SUPPLEMENTAL_TAIL.format(mcu_arch=mcu_arch))

    def writeSupplementalParentFile(self, parent_filename):
        
        with open(parent_filename, 'w') as mf:
            mf.write(ARDO_ARCH_MACRO_NAME_HEAD)
            
            keys = sorted(self.arch_macro_names.keys())
            for k in keys:
                mf.write(ARDO_ARCH_MACRO_NAME_ENTRY1.format(
                    avr_at_macro_name=self.arch_macro_names[k],
                    mcu_arch=k))
            
            mf.write(ARDO_ARCH_MACRO_NAME_END1)
            
            for k in keys:
                mf.write(ARDO_ARCH_MACRO_NAME_ENTRY2.format(
                    avr_at_macro_name=self.arch_macro_names[k],
                    mcu_arch=k))
            
            mf.write(ARDO_ARCH_MACRO_NAME_TAIL)
        

    def process(self, boards):
        results = []
        failed = []
        for board in boards:
            result = self.runPreprocIncludes(board)
            if result:
                results.append(result)
            else:
                failed.append(board)
        
        self.generateBoardHeaders(results)
        
        return results, failed
    
    def generateBoardHeaders(self, results):
        
        for result in results:
            print(f'{result.board.getBoardName()} {result.board.build__mcu}\n')
            
        fname = os.path.join(self.dir_path, BOARDS_SUBDIR, 'arduino_boards.h')
        with open(fname, 'w') as out:
            
            out.write(ARDO_ARDUINO_BOARDS_HEADER.format())
            
            if_elif = 'if'
            
            for result in results:
                
                vals = {
                    'if_elif': if_elif,
                    'arduino_board': 'ARDUINO_' + result.board.build__board,
                    'board': result.board.getBoardName(),
                    'mcu_arch': result.arch_macro_name,
                    'cpu_freq': result.cpu_freq_hz,
                    'header_file' : os.path.basename(result.board_header_file)
                }
                
                out.write(ARDO_ARDUINO_BOARDS_BODY.format(**vals))
                
                if_elif = 'elif'
                
            out.write(ARDO_ARDUINO_BOARDS_TAIL.format())
            
    
    def processAll(self):
        return self.process(self.boards)
    
    def processDeviceSpecs(self):
        avr_dev_cpp_file = os.path.join(self.dev_spec_data, 'gen_tmp_dev.cpp')
        with open(avr_dev_cpp_file, "w") as out:
            out.write(INPUT_DEV_SPEC_FILE_CPP)
            
        avr_cc_cpp_file = os.path.join(self.dev_spec_data, 'gen_tmp_cc.cpp')
        with open(avr_cc_cpp_file, "w") as out:
            out.write(INPUT_CC_SPEC_FILE_CPP)
        
        files = os.listdir(self.params.arduino_files.gnu_gpp_dev_specs)
        
        self.avr_archs = []
        for dev_spec in files:
            arch = self.get_arch(
                os.path.join(self.params.arduino_files.gnu_gpp_dev_specs,
                             dev_spec))
            if arch:
                self.avr_archs.append(arch)
                
        for mcu_arch in self.avr_archs:
            self.run_dev_spec(mcu_arch, avr_dev_cpp_file, avr_cc_cpp_file)
        
        # Write the include all header file.
        parent_filename = self.get_supplemental_parent_filename()
        self.writeSupplementalParentFile(parent_filename)
        
        archs = Archs()
        for mcu_arch in self.avr_archs:
            archs.add(
                mcu_arch, 
                self.get_dev_macros_filename(mcu_arch))
        
        archs.process()
        macros_file = os.path.join(
            self.dev_spec_data, 'mcu_archs_accum_macros.txt')
        with open(macros_file, "w") as mout:
            for v in archs.arch_sets:
                mout.write(str(v[-1]))
                mout.write('\n')
                mout.write(str(v[0:-1]))
                mout.write('\n')
        
        print(archs.id_sets) 
    
    
    def get_dev_macros_filename(self, mcu_arch):
        return os.path.join(self.dev_spec_data, f'dev_{mcu_arch}.h')
    
    def get_cc_macros_filename(self, mcu_arch):
        return os.path.join(self.dev_spec_data, f'cc_{mcu_arch}.h')
    
    def get_supplemental_filename(self, mcu_arch):
        return os.path.join(self.avr_supplemental, f'ardo_supplemental_{mcu_arch}.h')
    
    def get_supplemental_parent_filename(self):
        return os.path.join(self.avr_supplemental, 'ardo_sys_avr_mcu_defs.h')
    
    def get_supplemental_dev_filename(self, mcu_arch):
        return os.path.join(self.avr_supplemental, f'ardo_supplemental_{mcu_arch}_dev.h')
    
    def run_dev_spec(self, mcu_arch, avr_dev_cpp_file, avr_cc_cpp_file):
        dev_outfile = self.get_dev_macros_filename(mcu_arch)
        cc_outfile = self.get_cc_macros_filename(mcu_arch)
        
        gnu_gpp = self.params.arduino_files.gnu_gpp
        dev_cmd = f'"{gnu_gpp}" -mmcu={mcu_arch} -E -dM -c {avr_dev_cpp_file}'
        cc_cmd = f'"{gnu_gpp}" -mmcu={mcu_arch} -E -dM -c {avr_cc_cpp_file}'
        
        dev_result = getstatusoutput(dev_cmd)
        cc_result = getstatusoutput(cc_cmd)
        
        if dev_result[0]:
            raise DeviceSpecCompilerErrorException(
                'Error while attempting to run:\n'
                f'{dev_cmd}\n'
                f'Result: {dev_result[1]}\n')
            
        if cc_result[0]:
            raise DeviceSpecCompilerErrorException(
                'Error while attempting to run:\n'
                f'{cc_cmd}\n'
                f'Result: {cc_result[1]}\n')
        
        self.writeMacrosOutput(dev_outfile, dev_result[1])
        self.writeMacrosOutput(cc_outfile, cc_result[1])
        
        # Add some C++ friendly macros.
        sup_outfile = self.get_supplemental_filename(mcu_arch)
        self.writeSupplementalOutput(
            mcu_arch, sup_outfile, dev_result[1], cc_result[1])
        
        sup_def_outfile = self.get_supplemental_dev_filename(mcu_arch)
        if not os.path.exists(sup_def_outfile):
            with open(sup_def_outfile, 'w') as mf:
                mf.write(ADRO_AVR_HEADER.format(mcu_arch=mcu_arch))
                mf.write(ADRO_AVR_TAIL.format(mcu_arch=mcu_arch))
            
    def get_arch(self, filename):
        with open(filename) as inp:
            for line in inp:
                match = DEVICE_SPEC_PARSER.match(line)
                if match:
                    return match.groups()[0]
        return None

def main():
    
    params = ArduinoParams()
    boards = params.arduino_boards.getBoards()
    
    cad = CreateArduinoData()
#     result = cad.runPreprocIncludes(boards[35])
#     print(result)

    results = cad.processAll()
    
    print('Succeeded:', results[0])
    print('Failures:', results[1])
    
    archs = Archs()
    for proc_board in results[0]:
        archs.add(
            proc_board.board.getBoardName(), 
            proc_board.macros_name)
    
    archs.process()
    macros_file = os.path.join(cad.dir_path, 'archs_accum_macros.txt')
    with open(macros_file, "w") as mout:
        for v in archs.arch_sets:
            mout.write(str(v[-1]))
            mout.write('\n')
            mout.write(str(v[0:-1]))
            mout.write('\n')
    
    print(archs.id_sets)
    
    cad.processDeviceSpecs()
    

def main3():
    
    params = ArduinoParams()
    boards = params.arduino_boards.getBoards()
    for i, board in enumerate(boards):
        print(i, ':', board.getBoardName(), ':', board.path)
    board = boards[5]
    print('Using: ', board)
    
    print(params.getPlatformStr('compiler.cpp.flags', board))
    
    for i, board in enumerate(boards):
        print(i, ':', params.getPlatformStr('recipe.cpp.o.pattern', board))
        
    @dataclass
    class Observer(OptionsNodeObserverBase):
        ostream: io.TextIOWrapper = sys.stdout
    
        def matched(self, path, value):
            pathStr = '.'.join(path)
            value = f'{params.getPlatformStr(pathStr, board)}\n'
            self.ostream.write(pathStr)
            self.ostream.write('=')
            self.ostream.write(value)
            
    #params.platform_options_file.traverse(Observer())
    
    code_file = 'a_source_file.cpp'
    with open(code_file, 'w') as cf:
        cf.write('#define ARDUINO_MAIN 1\n')
        cf.write('#define __MATH_H\n')
        cf.write('#define _UTIL_DELAY_H_\n')
        cf.write('#define _UTIL_DELAY_BASIC_H_ 1\n')
        cf.write('#include <Arduino.h>\n')
        cf.write('#undef TIMER1A')
        cf.write('#include <pins_arduino.h>\n')
    
    cmd = params.getCompilerLineStr(
        'recipe.preproc.macros',
        board,
        code_file,
        (),
        preprocessed_file_path='preproc_out.cpp.i'
        )
    
    status, output, escaped_cmd = params.runPreprocMacros(
        board,
        code_file,
        preprocessed_file_path='preproc_out.cpp.i')
    
    print(escaped_cmd)
    print(status)
    print(output)
    
    
    status, output, escaped_cmd = params.runPreprocIncludes(
        board,
        code_file)
    
    print(escaped_cmd)
    print(status)
#     print(output)
        
def mainold():
    archs = do_archs()
    
    for v in archs.arch_sets:
        print(v)

#     af = ArduinoFiles.create()
#     print(af)
    
#     of = OptionsFile()
#     of.load(af.boards)

#     of.traverse(OptionsNodeObserverPrinter(ostream=sys.stdout))
#     of.traverse(OptionsNodeObserverPrinter(tail_match=('mcu',), ostream=sys.stdout))
#     of.traverse(OptionsNodeObserverPrinter(tail_match=('build', 'f_cpu'), ostream=sys.stdout))
#     of.traverse(OptionsNodeObserverPrinter(tail_match=('build', 'variant'), ostream=sys.stdout))
#     of.traverse(OptionsNodeObserverPrinter(tail_match=('build', PathNodeMatcher()), ostream=sys.stdout))
#     of.traverse(OptionsNodeObserverPrinter(
#         tail_match=('build', PathNodeMatcher(re.compile('v.*'))), ostream=sys.stdout))
    
#     ab = ArduinoBoards()
#     ab.collect(of)
#     "{a.b.c}".format_map({'a.b.c':5})
#     
#     print(ab)
#     
    return 0


if __name__ == "__main__":
    sys.exit(main())
