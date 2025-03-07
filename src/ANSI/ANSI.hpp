#pragma once
#ifndef ANSI_HPP
#define ANSI_HPP

#include "COMMAND.hpp"

namespace ANSI
{
    namespace TEXT
    {
        constexpr inline auto DEFAULT           = COMMAND< FUNCTION::TEXT_EFFECT >();
        constexpr inline auto RESET             = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::RESET_ALL >();

        namespace FOREGROUND
        {
            constexpr inline auto DEFAULT           = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::FOREGROUND + 1 >();

            constexpr inline auto BLACK             = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::FOREGROUND - 8 >();
            constexpr inline auto RED               = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::FOREGROUND - 7 >();
            constexpr inline auto GREEN             = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::FOREGROUND - 6 >();
            constexpr inline auto BLUE              = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::FOREGROUND - 4 >();
            constexpr inline auto YELLOW            = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::FOREGROUND - 5 >();
            constexpr inline auto MAGENTA           = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::FOREGROUND - 3 >();
            constexpr inline auto CYAN              = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::FOREGROUND - 2 >();
            constexpr inline auto WHITE             = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::FOREGROUND - 1 >();
    
            // NOTE: Bright colors can also usually be achieved via layering BOLD with the text color.
            constexpr inline auto BRIGHT_BLACK      = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::FOREGROUND - 8 + 60 >();
            constexpr inline auto BRIGHT_RED        = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::FOREGROUND - 7 + 60 >();
            constexpr inline auto BRIGHT_GREEN      = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::FOREGROUND - 6 + 60 >();
            constexpr inline auto BRIGHT_BLUE       = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::FOREGROUND - 4 + 60 >();
            constexpr inline auto BRIGHT_YELLOW     = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::FOREGROUND - 5 + 60 >();
            constexpr inline auto BRIGHT_MAGENTA    = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::FOREGROUND - 3 + 60 >();
            constexpr inline auto BRIGHT_CYAN       = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::FOREGROUND - 2 + 60 >();
            constexpr inline auto BRIGHT_WHITE      = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::FOREGROUND - 1 + 60 >();
        }
        // namespace FOREGROUND

        namespace EFFECTS
        {
            constexpr inline auto UNDERLINE_ON      = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::UNDERLINE >();
            constexpr inline auto UNDERLINE_X2      = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::DOUBLE_UNDERLINE >();
            constexpr inline auto UNDERLINE_OFF     = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::RESET_UNDERLINE >();
            
            constexpr inline auto OVERLINE_ON       = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::OVERLINE >();
            constexpr inline auto OVERLINE_OFF      = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::RESET_OVERLINE >();

            constexpr inline auto BLINKING_ON       = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::BLINKING >();
            constexpr inline auto BLINKING_OFF      = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::RESET_BLINKING >();

            constexpr inline auto BOLD_ON           = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::BOLD >();
            constexpr inline auto BOLD_OFF          = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::RESET_BOLD >();

            constexpr inline auto DIM_ON            = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::DIM >();
            constexpr inline auto DIM_OFF           = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::RESET_DIM >();

            constexpr inline auto ITALIC_ON         = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::ITALIC >();
            constexpr inline auto ITALIC_OFF        = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::RESET_ITALIC >();

            constexpr inline auto OPEN_FRAME        = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::FRAME_OPEN >();
            constexpr inline auto CLOSE_FRAME       = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::FRAME_CLOSE >();

            constexpr inline auto HIDE              = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::HIDDEN >();
            constexpr inline auto UNHIDE            = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::RESET_HIDDEN >();
            
            constexpr inline auto INVERT_ON         = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::INVERSE >();
            constexpr inline auto INVERT_OFF        = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::RESET_INVERSE >();
            
            constexpr inline auto STRIKE_ON         = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::STRIKETHROUGH >();
            constexpr inline auto STRIKE_OFF        = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::RESET_STRIKETHROUGH >();
            
            constexpr inline auto SUB_ON            = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::SUBSCRIPT >();
            constexpr inline auto SUPER_ON          = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::SUPERSCRIPT >();
            constexpr inline auto SCRIPTS_OFF       = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::RESET_SCRIPT >();
        }
        // namespace EFFECTS

        namespace BACKGROUND
        {
            constexpr inline auto DEFAULT           = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::BACKGROUND + 1 >();

            constexpr inline auto BLACK             = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::BACKGROUND - 8 >();
            constexpr inline auto RED               = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::BACKGROUND - 7 >();
            constexpr inline auto GREEN             = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::BACKGROUND - 6 >();
            constexpr inline auto BLUE              = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::BACKGROUND - 4 >();
            constexpr inline auto YELLOW            = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::BACKGROUND - 5 >();
            constexpr inline auto MAGENTA           = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::BACKGROUND - 3 >();
            constexpr inline auto CYAN              = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::BACKGROUND - 2 >();
            constexpr inline auto WHITE             = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::BACKGROUND - 1 >();

            // NOTE: Bright colors can also usually be achieved via layering BOLD with the text color.
            constexpr inline auto BRIGHT_BLACK      = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::BACKGROUND - 8 + 60 >();
            constexpr inline auto BRIGHT_RED        = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::BACKGROUND - 7 + 60 >();
            constexpr inline auto BRIGHT_GREEN      = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::BACKGROUND - 6 + 60 >();
            constexpr inline auto BRIGHT_BLUE       = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::BACKGROUND - 4 + 60 >();
            constexpr inline auto BRIGHT_YELLOW     = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::BACKGROUND - 5 + 60 >();
            constexpr inline auto BRIGHT_MAGENTA    = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::BACKGROUND - 3 + 60 >();
            constexpr inline auto BRIGHT_CYAN       = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::BACKGROUND - 2 + 60 >();
            constexpr inline auto BRIGHT_WHITE      = COMMAND< FUNCTION::TEXT_EFFECT, EFFECT::BACKGROUND - 1 + 60 >();
        }
        // namespace BACKGROUND
    }
    // namespace TEXT
}
// namespace ANSI


#endif // ANSI_HPP