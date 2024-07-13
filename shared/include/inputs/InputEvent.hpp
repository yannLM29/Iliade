/**
 * @file inputs.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-05-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <cstdint>
#include <array>
#include <string>

// #include <SFML/Graphics.hpp>

namespace Iliade::Inputs
{
    
    enum eInputCode : uint16_t
    {
        kUnknown = 0, ///< Unhandled key
        kAnalogOpt1,
        kAnalogOpt2,
        kAnalogOpt3,
        kAnalogOpt4,
        kAnalogOpt5,
        kAnalogOpt6,
        kAnalogOpt7,
        kAnalogOpt8,
        kDigitalOpt1,
        kDigitalOpt2,
        kDigitalOpt3,
        kDigitalOpt4,
        kDigitalOpt5,
        kDigitalOpt6,
        kDigitalOpt7,
        kDigitalOpt8,
        kJoystick1,
        kJoystick2,
        kR1,
        kL1,
        kR2,
        kL2,
        kCrossLeft,
        kCrossRight,
        kCrossUp,
        kCrossDown,
        kPadA,
        kPadB,
        kPadX,
        kPadY,
        kPadStart,
        kPadSelect,
        kMouseLeft,
        kMouseRight,
        kMouseMiddle,
        kMousePosX,
        kMousePosY,
        kGlobalMousePosX,
        kGlobalMousePosY,
        kA,            ///< The A key
        kB,            ///< The B key
        kC,            ///< The C key
        kD,            ///< The D key
        kE,            ///< The E key
        kF,            ///< The F key
        kG,            ///< The G key
        kH,            ///< The H key
        kI,            ///< The I key
        kJ,            ///< The J key
        kK,            ///< The K key
        kL,            ///< The L key
        kM,            ///< The M key
        kN,            ///< The N key
        kO,            ///< The O key
        kP,            ///< The P key
        kQ,            ///< The Q key
        kR,            ///< The R key
        kS,            ///< The S key
        kT,            ///< The T key
        kU,            ///< The U key
        kV,            ///< The V key
        kW,            ///< The W key
        kX,            ///< The X key
        kY,            ///< The Y key
        kZ,            ///< The Z key
        kNum0,         ///< The 0 key
        kNum1,         ///< The 1 key
        kNum2,         ///< The 2 key
        kNum3,         ///< The 3 key
        kNum4,         ///< The 4 key
        kNum5,         ///< The 5 key
        kNum6,         ///< The 6 key
        kNum7,         ///< The 7 key
        kNum8,         ///< The 8 key
        kNum9,         ///< The 9 key
        kEscape,       ///< The Escape key
        kLControl,     ///< The left Control key
        kLShift,       ///< The left Shift key
        kLAlt,         ///< The left Alt key
        kLSystem,      ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
        kRControl,     ///< The right Control key
        kRShift,       ///< The right Shift key
        kRAlt,         ///< The right Alt key
        kRSystem,      ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
        kMenu,         ///< The Menu key
        kLBracket,     ///< The [ key
        kRBracket,     ///< The ] key
        kSemicolon,    ///< The ; key
        kComma,        ///< The , key
        kPeriod,       ///< The . key
        kQuote,        ///< The ' key
        kSlash,        ///< The / key
        kBackslash,    ///< The \ key
        kTilde,        ///< The ~ key
        kEqual,        ///< The = key
        kHyphen,       ///< The - key (hyphen)
        kSpace,        ///< The Space key
        kEnter,        ///< The Enter/Return keys
        kBackspace,    ///< The Backspace key
        kTab,          ///< The Tabulation key
        kPageUp,       ///< The Page up key
        kPageDown,     ///< The Page down key
        kEnd,          ///< The End key
        kHome,         ///< The Home key
        kInsert,       ///< The Insert key
        kDelete,       ///< The Delete key
        kAdd,          ///< The + key
        kSubtract,     ///< The - key (minus, usually from numpad)
        kMultiply,     ///< The * key
        kDivide,       ///< The / key
        kLeft,         ///< Left arrow
        kRight,        ///< Right arrow
        kUp,           ///< Up arrow
        kDown,         ///< Down arrow
        kNumpad0,      ///< The numpad 0 key
        kNumpad1,      ///< The numpad 1 key
        kNumpad2,      ///< The numpad 2 key
        kNumpad3,      ///< The numpad 3 key
        kNumpad4,      ///< The numpad 4 key
        kNumpad5,      ///< The numpad 5 key
        kNumpad6,      ///< The numpad 6 key
        kNumpad7,      ///< The numpad 7 key
        kNumpad8,      ///< The numpad 8 key
        kNumpad9,      ///< The numpad 9 key
        kF1,           ///< The F1 key
        kF2,           ///< The F2 key
        kF3,           ///< The F3 key
        kF4,           ///< The F4 key
        kF5,           ///< The F5 key
        kF6,           ///< The F6 key
        kF7,           ///< The F7 key
        kF8,           ///< The F8 key
        kF9,           ///< The F9 key
        kF10,          ///< The F10 key
        kF11,          ///< The F11 key
        kF12,          ///< The F12 key
        kF13,          ///< The F13 key
        kF14,          ///< The F14 key
        kF15,          ///< The F15 key
        kPause,         ///< The Pause key
        length
    };

    extern std::array<std::string, length + 1> inputCodeNames;

    enum eInputStatus : uint16_t 
    {
        kPressed = 0,
        kStillPressed,
        kReleased,
        kValueChanged
    };

    struct InputEvent
    {
        eInputStatus status;
        eInputCode code;
        uint16_t value;
    };

    union InputData
    {
        uint32_t data;
        struct ParsedData
        {
            uint16_t code;
            uint16_t value;
        };
        
    };
    
} // namespace Iliade::Inputs
