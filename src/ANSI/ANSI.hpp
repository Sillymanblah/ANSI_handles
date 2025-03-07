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

        constexpr inline auto DEFAULT           = COMMAND<>();
        constexpr inline auto RESET             = COMMAND< EFFECT::RESET_ALL >();

        namespace FOREGROUND
        {
            constexpr inline auto DEFAULT           = COMMAND< EFFECT::FOREGROUND + 1 >();

            constexpr inline auto BLACK             = COMMAND< EFFECT::FOREGROUND - 8 >();
            constexpr inline auto RED               = COMMAND< EFFECT::FOREGROUND - 7 >();
            constexpr inline auto GREEN             = COMMAND< EFFECT::FOREGROUND - 6 >();
            constexpr inline auto BLUE              = COMMAND< EFFECT::FOREGROUND - 4 >();
            constexpr inline auto YELLOW            = COMMAND< EFFECT::FOREGROUND - 5 >();
            constexpr inline auto MAGENTA           = COMMAND< EFFECT::FOREGROUND - 3 >();
            constexpr inline auto CYAN              = COMMAND< EFFECT::FOREGROUND - 2 >();
            constexpr inline auto WHITE             = COMMAND< EFFECT::FOREGROUND - 1 >();
    
            // NOTE: Bright colors can also usually be achieved via layering BOLD with the text color.
            constexpr inline auto BRIGHT_BLACK      = COMMAND< EFFECT::FOREGROUND - 8 + 60 >();
            constexpr inline auto BRIGHT_RED        = COMMAND< EFFECT::FOREGROUND - 7 + 60 >();
            constexpr inline auto BRIGHT_GREEN      = COMMAND< EFFECT::FOREGROUND - 6 + 60 >();
            constexpr inline auto BRIGHT_BLUE       = COMMAND< EFFECT::FOREGROUND - 4 + 60 >();
            constexpr inline auto BRIGHT_YELLOW     = COMMAND< EFFECT::FOREGROUND - 5 + 60 >();
            constexpr inline auto BRIGHT_MAGENTA    = COMMAND< EFFECT::FOREGROUND - 3 + 60 >();
            constexpr inline auto BRIGHT_CYAN       = COMMAND< EFFECT::FOREGROUND - 2 + 60 >();
            constexpr inline auto BRIGHT_WHITE      = COMMAND< EFFECT::FOREGROUND - 1 + 60 >();
        }
        // namespace FOREGROUND

        namespace EFFECTS
        {
            constexpr inline auto UNDERLINE_ON      = COMMAND< EFFECT::UNDERLINE >();
            constexpr inline auto UNDERLINE_X2      = COMMAND< EFFECT::DOUBLE_UNDERLINE >();
            constexpr inline auto UNDERLINE_OFF     = COMMAND< EFFECT::RESET_UNDERLINE >();
            
            constexpr inline auto OVERLINE_ON       = COMMAND< EFFECT::OVERLINE >();
            constexpr inline auto OVERLINE_OFF      = COMMAND< EFFECT::RESET_OVERLINE >();

            constexpr inline auto BLINKING_ON       = COMMAND< EFFECT::BLINKING >();
            constexpr inline auto BLINKING_OFF      = COMMAND< EFFECT::RESET_BLINKING >();

            constexpr inline auto BOLD_ON           = COMMAND< EFFECT::BOLD >();
            constexpr inline auto BOLD_OFF          = COMMAND< EFFECT::RESET_BOLD >();

            constexpr inline auto DIM_ON            = COMMAND< EFFECT::DIM >();
            constexpr inline auto DIM_OFF           = COMMAND< EFFECT::RESET_DIM >();

            constexpr inline auto ITALIC_ON         = COMMAND< EFFECT::ITALIC >();
            constexpr inline auto ITALIC_OFF        = COMMAND< EFFECT::RESET_ITALIC >();

            constexpr inline auto OPEN_FRAME        = COMMAND< EFFECT::FRAME_OPEN >();
            constexpr inline auto CLOSE_FRAME       = COMMAND< EFFECT::FRAME_CLOSE >();

            constexpr inline auto HIDE              = COMMAND< EFFECT::HIDDEN >();
            constexpr inline auto UNHIDE            = COMMAND< EFFECT::RESET_HIDDEN >();
            
            constexpr inline auto INVERT_ON         = COMMAND< EFFECT::INVERSE >();
            constexpr inline auto INVERT_OFF        = COMMAND< EFFECT::RESET_INVERSE >();
            
            constexpr inline auto STRIKE_ON         = COMMAND< EFFECT::STRIKETHROUGH >();
            constexpr inline auto STRIKE_OFF        = COMMAND< EFFECT::RESET_STRIKETHROUGH >();
            
            constexpr inline auto SUB_ON            = COMMAND< EFFECT::SUBSCRIPT >();
            constexpr inline auto SUPER_ON          = COMMAND< EFFECT::SUPERSCRIPT >();
            constexpr inline auto SCRIPTS_OFF       = COMMAND< EFFECT::RESET_SCRIPT >();
        }
        // namespace EFFECTS

        namespace BACKGROUND
        {
            constexpr inline auto DEFAULT           = COMMAND< EFFECT::BACKGROUND + 1 >();

            constexpr inline auto BLACK             = COMMAND< EFFECT::BACKGROUND - 8 >();
            constexpr inline auto RED               = COMMAND< EFFECT::BACKGROUND - 7 >();
            constexpr inline auto GREEN             = COMMAND< EFFECT::BACKGROUND - 6 >();
            constexpr inline auto BLUE              = COMMAND< EFFECT::BACKGROUND - 4 >();
            constexpr inline auto YELLOW            = COMMAND< EFFECT::BACKGROUND - 5 >();
            constexpr inline auto MAGENTA           = COMMAND< EFFECT::BACKGROUND - 3 >();
            constexpr inline auto CYAN              = COMMAND< EFFECT::BACKGROUND - 2 >();
            constexpr inline auto WHITE             = COMMAND< EFFECT::BACKGROUND - 1 >();

            // NOTE: Bright colors can also usually be achieved via layering BOLD with the text color.
            constexpr inline auto BRIGHT_BLACK      = COMMAND< EFFECT::BACKGROUND - 8 + 60 >();
            constexpr inline auto BRIGHT_RED        = COMMAND< EFFECT::BACKGROUND - 7 + 60 >();
            constexpr inline auto BRIGHT_GREEN      = COMMAND< EFFECT::BACKGROUND - 6 + 60 >();
            constexpr inline auto BRIGHT_BLUE       = COMMAND< EFFECT::BACKGROUND - 4 + 60 >();
            constexpr inline auto BRIGHT_YELLOW     = COMMAND< EFFECT::BACKGROUND - 5 + 60 >();
            constexpr inline auto BRIGHT_MAGENTA    = COMMAND< EFFECT::BACKGROUND - 3 + 60 >();
            constexpr inline auto BRIGHT_CYAN       = COMMAND< EFFECT::BACKGROUND - 2 + 60 >();
            constexpr inline auto BRIGHT_WHITE      = COMMAND< EFFECT::BACKGROUND - 1 + 60 >();
        }
        // namespace BACKGROUND
    }
    // namespace TEXT
}
// namespace ANSI


#endif // ANSI_HPP