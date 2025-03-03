#pragma once
#ifndef ANSI_COMMAND_HPP
#define ANSI_COMMAND_HPP

#include <ostream>

typedef unsigned char BYTE;

namespace ANSI
{
    enum class EFFECT : BYTE
    {
        BOLD = 1,
        DIM,
        ITALIC,
        UNDERLINE,
        BLINKING,
        INVERSE,
        HIDDEN,
        STRIKETHROUGH,
        DOUBLE_UNDERLINE = 21,
        FOREGROUND = 38,
        BACKGROUND = 48,
        OVERLINE = 53,
        SUPERSCRIPT = 73,
        SUBSCRIPT = 74,
        
        RESET_ALL = 0,
        RESET_BOLD = 22, // Resetting bold or dim colors is the same code, so they are both set to 22.
        RESET_DIM = 22, // Resetting bold or dim colors is the same code, so they are both set to 22.
        RESET_ITALIC,
        RESET_UNDERLINE, // Turns off underlines, including single and double, plus any colored underlines
        RESET_BLINKING,
        RESET_INVERSE,
        RESET_HIDDEN,
        RESET_STRIKETHROUGH,
        RESET_OVERLINE = 55,
        RESET_SCRIPT = 75, // Turns off subscript AND superscript

        FRAME_OPEN = 51,
        FRAME_CLOSE = 54,
    };
    // enum class EFFECT

    enum class FUNCTION : char
    {
        CURSOR_UP               = 'A',
        CURSOR_DOWN             = 'B',
        CURSOR_RIGHT            = 'C',
        CURSOR_LEFT             = 'D',
        CURSOR_DOWN_START       = 'E',
        CURSOR_UP_START         = 'F',
        CURSOR_SET_COLUMN       = 'G',
        CURSOR_SET_POSITION     = 'H',
        CURSOR_GET_POSITION     = 'n',
        ERASE_SCREEN            = 'J',
        ERASE_LINES             = 'K',
        CURSOR_SAVE_POSITION    = '7',
        CURSOR_RESTORE_POSITION = '8',
        TEXT_EFFECT             = 'm',
        SCREEN_SETTING          = 'h',
        RESET_SCREEN            = 'l',
        KEY_STRING              = 'p',
    };
    // enum class FUNCTION

    struct COMMAND_BASE
    {
        static inline constexpr char DELIMITER      = ';';      // Delimiter for if commands have multiple parts.
        static inline constexpr char ESCAPE_CHAR    = 27;       // Escape key to start a command or sequence.
        static inline constexpr char SEQUENCE_INTRO = '[';      // Control Sequence Introducer - almost always follows ESCAPE in ANSI codes.
        static inline constexpr char CSI            = '\x9B';   // Is considered to be able to do the job of both, but is not as consistent.

        static inline constexpr char BEGIN_CODE[2] = { ESCAPE_CHAR, SEQUENCE_INTRO };
    };
    // struct COMMAND_BASE

    // Command is the base for ANSI still, but should NOT be used by itself, as other functions have better type safety.
    template < FUNCTION _Type, BYTE... _Data >
    class COMMAND : protected COMMAND_BASE
    {
    public:
        COMMAND() = default;
        COMMAND( const COMMAND& ) = default; // There is not really a reason to use this constructor, since everything is compile-time constants now.
        COMMAND( COMMAND&& ) = default; // There is not really a reason to use this constructor, since everything is compile-time constants now.
        COMMAND& operator = ( const COMMAND& ) = default; // There is not really a reason to use this assignment operator, since everything is compile-time constants now.
        COMMAND& operator = ( COMMAND&& ) = default; // There is not really a reason to use this assignment operator, since everything is compile-time constants now.
        
        // Same command template args means same command.
        bool operator == ( const COMMAND& )
        { return true; }
        bool operator == ( COMMAND&& )
        { return true; }
        bool operator != ( const COMMAND& )
        { return false; }
        bool operator != ( COMMAND&& )
        { return false; }
        
        // Different command template args means different command.
        template < FUNCTION _Type, BYTE... _Data >
        bool operator == ( const COMMAND< _Type, _Data >& )
        { return true; }
        template < FUNCTION _Type, BYTE... _Data >
        bool operator == ( COMMAND< _Type, _Data >&& )
        { return true; }
        template < FUNCTION _Type, BYTE... _Data >
        bool operator != ( const COMMAND< _Type, _Data >& )
        { return true; }
        template < FUNCTION _Type, BYTE... _Data >
        bool operator != ( COMMAND< _Type, _Data >&& )
        { return true; }

    protected:
        template < FUNCTION _Type, BYTE... _Data >
        static void print_data( std::ostream& output, const COMMAND ) {} // Do nothing, no data to print...

        template < FUNCTION _Type, BYTE _First, BYTE... _Rest >
        static void print_data( std::ostream& output, const COMMAND ) // One part of data to print, print it...
        { output << (int)_First; }
        template < FUNCTION _Type, BYTE _First, BYTE _Second, BYTE... _Rest >
        static void print_data( std::ostream& output, const COMMAND ) // Multiple parts of data, print the first with a delimiter and recurse.
        {
            output << (int)_First << COMMAND::DELIMITER;
            print_data( output, COMMAND< _Type, _Second, _Rest... >() );
        }

    public:
        // Base case, no data to print.
        template < FUNCTION _Type, BYTE... _Data >
        virtual inline friend std::ostream& operator << ( std::ostream& output, const COMMAND< _Type, _Data... > )
        {
            output << COMMAND::BEGIN_CODE;
            COMMAND::print_data( output, COMMAND< _Types, _Data... >() );
            output << _Type;
            return output;
        }
    };
    // class COMMAND
}
// namespace ANSI

#endif // ANSI_COLORS_HPP