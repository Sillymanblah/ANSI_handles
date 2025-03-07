#pragma once
#ifndef ANSI_HPP
#define ANSI_HPP

#include "COMMAND.hpp"

namespace ANSI
{
    namespace TEXT
    {
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
}
// namespace ANSI


#endif // ANSI_HPP