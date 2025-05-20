#pragma once
#ifndef ANSI_HPP
#define ANSI_HPP

#include "COMMAND.hpp"

namespace ANSI
{
    namespace TEXT
    {
        namespace EFFECT
        {
            enum : BYTE
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
        }
        // namespace EFFECT

        template < BYTE... _Data >
        using COMMAND = ::ANSI::COMMAND< FUNCTION::TEXT_EFFECT, _Data... >;

        constexpr inline COMMAND<>                                     DEFAULT;
        constexpr inline COMMAND< EFFECT::RESET_ALL >                  RESET;

        namespace FOREGROUND
        {
            constexpr inline COMMAND< EFFECT::FOREGROUND + 1 >         DEFAULT;

            constexpr inline COMMAND< EFFECT::FOREGROUND - 8 >         BLACK;
            constexpr inline COMMAND< EFFECT::FOREGROUND - 7 >         RED;
            constexpr inline COMMAND< EFFECT::FOREGROUND - 6 >         GREEN;
            constexpr inline COMMAND< EFFECT::FOREGROUND - 4 >         BLUE;
            constexpr inline COMMAND< EFFECT::FOREGROUND - 5 >         YELLOW;
            constexpr inline COMMAND< EFFECT::FOREGROUND - 3 >         MAGENTA;
            constexpr inline COMMAND< EFFECT::FOREGROUND - 2 >         CYAN;
            constexpr inline COMMAND< EFFECT::FOREGROUND - 1 >         WHITE;
    
            // NOTE: Bright colors can also usually be achieved via layering BOLD with the text color.
            constexpr inline COMMAND< EFFECT::FOREGROUND - 8 + 60 >    BRIGHT_BLACK;
            constexpr inline COMMAND< EFFECT::FOREGROUND - 7 + 60 >    BRIGHT_RED;
            constexpr inline COMMAND< EFFECT::FOREGROUND - 6 + 60 >    BRIGHT_GREEN;
            constexpr inline COMMAND< EFFECT::FOREGROUND - 4 + 60 >    BRIGHT_BLUE;
            constexpr inline COMMAND< EFFECT::FOREGROUND - 5 + 60 >    BRIGHT_YELLOW;
            constexpr inline COMMAND< EFFECT::FOREGROUND - 3 + 60 >    BRIGHT_MAGENTA;
            constexpr inline COMMAND< EFFECT::FOREGROUND - 2 + 60 >    BRIGHT_CYAN;
            constexpr inline COMMAND< EFFECT::FOREGROUND - 1 + 60 >    BRIGHT_WHITE;
        }
        // namespace FOREGROUND

        namespace EFFECTS
        {
            constexpr inline COMMAND< EFFECT::UNDERLINE >              UNDERLINE_ON;
            constexpr inline COMMAND< EFFECT::DOUBLE_UNDERLINE >       UNDERLINE_X2;
            constexpr inline COMMAND< EFFECT::RESET_UNDERLINE >        UNDERLINE_OFF;
            
            constexpr inline COMMAND< EFFECT::OVERLINE >               OVERLINE_ON;
            constexpr inline COMMAND< EFFECT::RESET_OVERLINE >         OVERLINE_OFF;

            constexpr inline COMMAND< EFFECT::BLINKING >               BLINKING_ON;
            constexpr inline COMMAND< EFFECT::RESET_BLINKING >         BLINKING_OFF;

            constexpr inline COMMAND< EFFECT::BOLD >                   BOLD_ON;
            constexpr inline COMMAND< EFFECT::RESET_BOLD >             BOLD_OFF;

            constexpr inline COMMAND< EFFECT::DIM >                    DIM_ON;
            constexpr inline COMMAND< EFFECT::RESET_DIM >              DIM_OFF;

            constexpr inline COMMAND< EFFECT::ITALIC >                 ITALIC_ON;
            constexpr inline COMMAND< EFFECT::RESET_ITALIC >           ITALIC_OFF;

            constexpr inline COMMAND< EFFECT::FRAME_OPEN >             OPEN_FRAME;
            constexpr inline COMMAND< EFFECT::FRAME_CLOSE >            CLOSE_FRAME;

            constexpr inline COMMAND< EFFECT::HIDDEN >                 HIDE;
            constexpr inline COMMAND< EFFECT::RESET_HIDDEN >           UNHIDE;
            
            constexpr inline COMMAND< EFFECT::INVERSE >                INVERT_ON;
            constexpr inline COMMAND< EFFECT::RESET_INVERSE >          INVERT_OFF;
            
            constexpr inline COMMAND< EFFECT::STRIKETHROUGH >          STRIKE_ON;
            constexpr inline COMMAND< EFFECT::RESET_STRIKETHROUGH >    STRIKE_OFF;
            
            constexpr inline COMMAND< EFFECT::SUBSCRIPT >              SUB_ON;
            constexpr inline COMMAND< EFFECT::SUPERSCRIPT >            SUPER_ON;
            constexpr inline COMMAND< EFFECT::RESET_SCRIPT >           SCRIPTS_OFF;
        }
        // namespace EFFECTS

        namespace BACKGROUND
        {
            constexpr inline COMMAND< EFFECT::BACKGROUND + 1 >         DEFAULT;

            constexpr inline COMMAND< EFFECT::BACKGROUND - 8 >         BLACK;
            constexpr inline COMMAND< EFFECT::BACKGROUND - 7 >         RED;
            constexpr inline COMMAND< EFFECT::BACKGROUND - 6 >         GREEN;
            constexpr inline COMMAND< EFFECT::BACKGROUND - 4 >         BLUE;
            constexpr inline COMMAND< EFFECT::BACKGROUND - 5 >         YELLOW;
            constexpr inline COMMAND< EFFECT::BACKGROUND - 3 >         MAGENTA;
            constexpr inline COMMAND< EFFECT::BACKGROUND - 2 >         CYAN;
            constexpr inline COMMAND< EFFECT::BACKGROUND - 1 >         WHITE;

            // NOTE: Bright colors can also usually be achieved via layering BOLD with the text color.
            constexpr inline COMMAND< EFFECT::BACKGROUND - 8 + 60 >    BRIGHT_BLACK;
            constexpr inline COMMAND< EFFECT::BACKGROUND - 7 + 60 >    BRIGHT_RED;
            constexpr inline COMMAND< EFFECT::BACKGROUND - 6 + 60 >    BRIGHT_GREEN;
            constexpr inline COMMAND< EFFECT::BACKGROUND - 4 + 60 >    BRIGHT_BLUE;
            constexpr inline COMMAND< EFFECT::BACKGROUND - 5 + 60 >    BRIGHT_YELLOW;
            constexpr inline COMMAND< EFFECT::BACKGROUND - 3 + 60 >    BRIGHT_MAGENTA;
            constexpr inline COMMAND< EFFECT::BACKGROUND - 2 + 60 >    BRIGHT_CYAN;
            constexpr inline COMMAND< EFFECT::BACKGROUND - 1 + 60 >    BRIGHT_WHITE;
        }
        // namespace BACKGROUND
    }
    // namespace TEXT

    namespace ERASE
    {
        namespace SCREEN
        {
            template < BYTE _Value >
            using COMMAND = ::ANSI::COMMAND< FUNCTION::ERASE_SCREEN, _Value >;

            constexpr inline COMMAND< 0 > CURSOR_TO_END;
            constexpr inline COMMAND< 1 > CURSOR_TO_BEGIN;
            constexpr inline COMMAND< 2 > CLEAR_SCREEN;
            constexpr inline COMMAND< 3 > SAVED_LINES;
        }
        // namespace SCREEN

        namespace LINE
        {
            template < BYTE _Value >
            using COMMAND = ::ANSI::COMMAND< FUNCTION::ERASE_LINES, _Value >;
    
            constexpr inline COMMAND< 0 > CURSOR_TO_END;
            constexpr inline COMMAND< 1 > CURSOR_TO_BEGIN;
            constexpr inline COMMAND< 2 > DELETE_LINE;
        }
        // namespace LINE
    }
    // namespace ERASE

    namespace CURSOR_POSITION
    {
        using HOME = ::ANSI::COMMAND< FUNCTION::CURSOR_SET_POSITION >;

        template < BYTE _Line, BYTE _Column >
        using SET = ::ANSI::COMMAND< FUNCTION::CURSOR_SET_POSITION, _Line, _Column >;

        template < BYTE _Column >
        using SET_COLUMN = ::ANSI::COMMAND< FUNCTION::CURSOR_SET_COLUMN, _Column >;

        template < BYTE _Distance >
        using UP = ::ANSI::COMMAND< FUNCTION::CURSOR_UP, _Distance >;

        template < BYTE _Distance >
        using UP_RESET = ::ANSI::COMMAND< FUNCTION::CURSOR_UP_START, _Distance >;

        template < BYTE _Distance >
        using DOWN = ::ANSI::COMMAND< FUNCTION::CURSOR_DOWN, _Distance >;

        template < BYTE _Distance >
        using DOWN_RESET = ::ANSI::COMMAND< FUNCTION::CURSOR_DOWN_START, _Distance >;

        template < BYTE _Distance >
        using LEFT = ::ANSI::COMMAND< FUNCTION::CURSOR_LEFT, _Distance >;

        template < BYTE _Distance >
        using RIGHT = ::ANSI::COMMAND< FUNCTION::CURSOR_RIGHT, _Distance >;

        // Saves a position to restore to with `ANSI::CURSOR_POSITION::RESTORE`.
        using SAVE = ::ANSI::COMMAND< FUNCTION::CURSOR_SAVE_POSITION >;
        
        // Restores the last saved position by `ANSI::CURSOR_POSITION::SAVE`.
        using RESTORE = ::ANSI::COMMAND< FUNCTION::CURSOR_RESTORE_POSITION >;
    }
    // namespace CURSOR_POSITION
    
}
// namespace ANSI


#endif // ANSI_HPP