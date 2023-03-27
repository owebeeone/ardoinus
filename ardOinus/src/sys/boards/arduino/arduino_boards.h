/**
 * Includes the header file for the Arduino board being compiled for.
 *
 * This is only specific for the Arduino boards.
 * (This file is generated, do not edit.)
 */

#ifndef ARDUINO_BOARDS__H
#define ARDUINO_BOARDS__H

namespace ardo {
namespace sys {

// Specialize this template for when the board is found.
template <bool found>
struct ArduinoBoard;

}  // namespace sys
}  // namespace ardo

#if defined(ARDUINO_AVR_LILYPAD_USB) && defined(__AVR_ATmega32U4__) && (F_CPU == 8000000L)
#include "ardo_board_LilyPadUSB_atmega32u4.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_LilyPadUSB_atmega32u4;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_NG) && defined(__AVR_ATmega168__) && (F_CPU == 16000000L)
#include "ardo_board_atmegang_atmega168.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_atmegang_atmega168;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_NG) && defined(__AVR_ATmega8__) && (F_CPU == 16000000L)
#include "ardo_board_atmegang_atmega8.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_atmegang_atmega8;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_BT) && defined(__AVR_ATmega168__) && (F_CPU == 16000000L)
#include "ardo_board_bt_atmega168.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_bt_atmega168;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_BT) && defined(__AVR_ATmega328P__) && (F_CPU == 16000000L)
#include "ardo_board_bt_atmega328.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_bt_atmega328;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_INDUSTRIAL101) && defined(__AVR_ATmega32U4__) && (F_CPU == 16000000L)
#include "ardo_board_chiwawa_atmega32u4.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_chiwawa_atmega32u4;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_CIRCUITPLAY) && defined(__AVR_ATmega32U4__) && (F_CPU == 8000000L)
#include "ardo_board_circuitplay32u4cat_atmega32u4.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_circuitplay32u4cat_atmega32u4;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_DUEMILANOVE) && defined(__AVR_ATmega168__) && (F_CPU == 16000000L)
#include "ardo_board_diecimila_atmega168.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_diecimila_atmega168;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_DUEMILANOVE) && defined(__AVR_ATmega328P__) && (F_CPU == 16000000L)
#include "ardo_board_diecimila_atmega328.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_diecimila_atmega328;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_ESPLORA) && defined(__AVR_ATmega32U4__) && (F_CPU == 16000000L)
#include "ardo_board_esplora_atmega32u4.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_esplora_atmega32u4;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_ETHERNET) && defined(__AVR_ATmega328P__) && (F_CPU == 16000000L)
#include "ardo_board_ethernet_atmega328p.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_ethernet_atmega328p;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_FIO) && defined(__AVR_ATmega328P__) && (F_CPU == 8000000L)
#include "ardo_board_fio_atmega328p.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_fio_atmega328p;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_GEMMA) && defined(__AVR_ATtiny85__) && (F_CPU == 8000000L)
#include "ardo_board_gemma_attiny85.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_gemma_attiny85;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_LEONARDO) && defined(__AVR_ATmega32U4__) && (F_CPU == 16000000L)
#include "ardo_board_leonardo_atmega32u4.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_leonardo_atmega32u4;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_LEONARDO_ETH) && defined(__AVR_ATmega32U4__) && (F_CPU == 16000000L)
#include "ardo_board_leonardoeth_atmega32u4.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_leonardoeth_atmega32u4;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_LILYPAD) && defined(__AVR_ATmega168__) && (F_CPU == 8000000L)
#include "ardo_board_lilypad_atmega168.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_lilypad_atmega168;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_LILYPAD) && defined(__AVR_ATmega328P__) && (F_CPU == 8000000L)
#include "ardo_board_lilypad_atmega328.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_lilypad_atmega328;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_MEGA) && defined(__AVR_ATmega1280__) && (F_CPU == 16000000L)
#include "ardo_board_mega_atmega1280.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_mega_atmega1280;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_MEGA2560) && defined(__AVR_ATmega2560__) && (F_CPU == 16000000L)
#include "ardo_board_mega_atmega2560.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_mega_atmega2560;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_ADK) && defined(__AVR_ATmega2560__) && (F_CPU == 16000000L)
#include "ardo_board_megaADK_atmega2560.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_megaADK_atmega2560;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_MICRO) && defined(__AVR_ATmega32U4__) && (F_CPU == 16000000L)
#include "ardo_board_micro_atmega32u4.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_micro_atmega32u4;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_MINI) && defined(__AVR_ATmega168__) && (F_CPU == 16000000L)
#include "ardo_board_mini_atmega168.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_mini_atmega168;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_MINI) && defined(__AVR_ATmega328P__) && (F_CPU == 16000000L)
#include "ardo_board_mini_atmega328.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_mini_atmega328;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_NANO) && defined(__AVR_ATmega168__) && (F_CPU == 16000000L)
#include "ardo_board_nano_atmega168.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_nano_atmega168;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_NANO) && defined(__AVR_ATmega328P__) && (F_CPU == 16000000L)
#include "ardo_board_nano_atmega328.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_nano_atmega328;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_NANO) && defined(__AVR_ATmega328P__) && (F_CPU == 16000000L)
#include "ardo_board_nano_atmega328old.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_nano_atmega328old;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_LININO_ONE) && defined(__AVR_ATmega32U4__) && (F_CPU == 16000000L)
#include "ardo_board_one_atmega32u4.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_one_atmega32u4;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_PRO) && defined(__AVR_ATmega168__) && (F_CPU == 16000000L)
#include "ardo_board_pro_16MHzatmega168.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_pro_16MHzatmega168;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_PRO) && defined(__AVR_ATmega328P__) && (F_CPU == 16000000L)
#include "ardo_board_pro_16MHzatmega328.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_pro_16MHzatmega328;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_PRO) && defined(__AVR_ATmega168__) && (F_CPU == 8000000L)
#include "ardo_board_pro_8MHzatmega168.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_pro_8MHzatmega168;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_PRO) && defined(__AVR_ATmega328P__) && (F_CPU == 8000000L)
#include "ardo_board_pro_8MHzatmega328.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_pro_8MHzatmega328;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_ROBOT_CONTROL) && defined(__AVR_ATmega32U4__) && (F_CPU == 16000000L)
#include "ardo_board_robotControl_atmega32u4.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_robotControl_atmega32u4;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_ROBOT_MOTOR) && defined(__AVR_ATmega32U4__) && (F_CPU == 16000000L)
#include "ardo_board_robotMotor_atmega32u4.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_robotMotor_atmega32u4;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_UNO) && defined(__AVR_ATmega328P__) && (F_CPU == 16000000L)
#include "ardo_board_uno_atmega328p.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_uno_atmega328p;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_UNO) && defined(__AVR_ATmega328P__) && (F_CPU == 16000000L)
#include "ardo_board_unomini_atmega328p.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_unomini_atmega328p;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_UNO_WIFI_DEV_ED) && defined(__AVR_ATmega328P__) && (F_CPU == 16000000L)
#include "ardo_board_unowifi_atmega328p.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_unowifi_atmega328p;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_YUN) && defined(__AVR_ATmega32U4__) && (F_CPU == 16000000L)
#include "ardo_board_yun_atmega32u4.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_yun_atmega32u4;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif defined(ARDUINO_AVR_YUNMINI) && defined(__AVR_ATmega32U4__) && (F_CPU == 16000000L)
#include "ardo_board_yunmini_atmega32u4.h"
namespace ardo { namespace sys {

namespace board = ::ardo::sys::boards::arduino::board_yunmini_atmega32u4;

// Specialize this template for when the board is found.
template <>
struct ArduinoBoard<true> {
    using type = board::BoardDefinition;
};

} }  // namespace sys::ardo
#elif !defined(ARDO_IGNORE_ARDUINO_BOARD_NOT_FOUND)
#error "No board definition found for the board being compiled."
#endif

#endif // ARDUINO_BOARDS__H
