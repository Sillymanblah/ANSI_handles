#pragma once
#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <ostream>
#include "../numeric_string.hpp"

typedef unsigned char BYTE;

namespace ANSI
{
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

    // Base class to derive commands from, do not use this class by itself!
    class COMMAND_BASE
    {
    protected:
        static inline constexpr char DELIMITER      = ';';      // Delimiter for if commands have multiple parts.
        static inline constexpr char ESCAPE_CHAR    = 27;       // Escape key to start a command or sequence.
        static inline constexpr char SEQUENCE_INTRO = '[';      // Control Sequence Introducer - almost always follows ESCAPE in ANSI codes.
        static inline constexpr char CSI            = '\x9B';   // Is considered to be able to do the job of both, but is not as consistent.

        static inline constexpr char BEGIN_CODE[2] = { ESCAPE_CHAR, SEQUENCE_INTRO };

    private:
        // No byte data to print, so append the closing tag.
        template < class _String, FUNCTION _Tag, BYTE... _Data >
        struct command_string_builder : meta::append_t< char, _String, (char) _Tag >
        { using type = typename meta::append_t< char, _String, (char) _Tag >::type; };

        // Only one byte of data to print, so we need to just convert it.
        template < class _String, FUNCTION _Tag, BYTE _First >
        struct command_string_builder< _String, _Tag, _First > :
            command_string_builder< meta::string_concat_t< _String, meta::numeric_string_t< BYTE, _First > >, _Tag >
        { using type = typename command_string_builder< meta::string_concat_t< _String, meta::numeric_string_t< BYTE, _First > >, _Tag >::type; };

        // At least two bytes of data to print, so we need to append a semi-colon.
        template < class _String, FUNCTION _Tag, BYTE _First, BYTE _Second, BYTE... _Rest >
        struct command_string_builder< _String, _Tag, _First, _Second, _Rest... > :
            command_string_builder< meta::string_concat_t< _String, meta::append_t< char, meta::numeric_string_t< BYTE, _First >, DELIMITER > >, _Tag, _Second, _Rest... >
        { using type = typename command_string_builder< meta::string_concat_t< _String, meta::append_t< char, meta::numeric_string_t< BYTE, _First >, DELIMITER > >, _Tag, _Second, _Rest... >::type; };

    protected:
        template < FUNCTION _Tag, BYTE... _Data >
        struct command_string : command_string_builder< meta::make_string_t< char, BEGIN_CODE, 2 >, _Tag, _Data... >
        { using type = command_string_builder< meta::make_string_t< char, BEGIN_CODE, 2 >, _Tag, _Data... >::type; };

        template < FUNCTION _Tag, BYTE... _Data >
        using command_string_t = typename command_string< _Tag, _Data... >::type;

        template < FUNCTION _Tag, BYTE... _Data >
        static constexpr typename command_string_t< _Tag, _Data... >::value_type command_string_v = command_string< _Tag, _Data... >::value; 

    public:
        static inline constexpr const char* cstr()
        { return "invalid use of COMMAND_BASE::cstr()"; };
        inline friend std::ostream& operator << ( std::ostream& output, const COMMAND_BASE command )
        { return ( output << command.cstr() ); }
    };
    // struct COMMAND_BASE

    // Command class can be used to build ANSI commands from scratch, but it is not recommended, instead use one of the supported classes that layers on top of ANSI::COMMAND.
    template < FUNCTION _Type, BYTE... _Data >
    class COMMAND : public COMMAND_BASE
    {
    public:
        COMMAND() = default;
        COMMAND( const COMMAND& ) = default; // There is not really a reason to use this constructor, since everything is compile-time constants now.
        COMMAND( COMMAND&& ) = default; // There is not really a reason to use this constructor, since everything is compile-time constants now.
        COMMAND& operator = ( const COMMAND& ) = default; // There is not really a reason to use this assignment operator, since everything is compile-time constants now.
        COMMAND& operator = ( COMMAND&& ) = default; // There is not really a reason to use this assignment operator, since everything is compile-time constants now.
        
        // Same command template args means same command.
        bool operator == ( const COMMAND ) const
        { return true; }
        bool operator != ( const COMMAND ) const
        { return false; }
        
        // Different command template args means different command.
        template < FUNCTION _Other_type, BYTE... _Other_data >
        bool operator == ( const COMMAND< _Other_type, _Other_data... > ) const
        { return true; }
        template < FUNCTION _Other_type, BYTE... _Other_data >
        bool operator != ( const COMMAND< _Other_type, _Other_data... > ) const
        { return false; }

    public:
        static inline constexpr const char* cstr() const
        { return command_string_v< _Type, _Data... >; }

        inline friend std::ostream& operator << ( std::ostream& output, const COMMAND command )
        { return ( output << command.cstr() ); }
    };
    // class COMMAND

}
// namespace ANSI

#endif // COMMAND_HPP