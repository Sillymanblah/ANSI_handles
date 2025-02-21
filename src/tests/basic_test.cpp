
#include "../ANSI.hpp"

#include <iostream>

int main()
{
    std::cout << "\nTesting text coloring...\n";
    std::cout << ANSI::TEXT::GREEN << "Hello World!" << ANSI::TEXT::RESET;

    std::cout << "\nReset...\n\nNow testing background coloring...\n";
    std::cout << ANSI::BACKGROUND::RED << "REDDDDDDD RUMMM" << ANSI::BACKGROUND::RESET;

    std::cout << "\nReset...\n\nNow testing text effects...\n";
    std::cout << ANSI::TEXT::EFFECTS::BOLD_ON << "Who let the dogs out?" << ANSI::TEXT::EFFECTS::RESET;

    std::cout << "\nReset...\n\nNow testing text all at once and reset...\n";
    std::cout << ANSI::TEXT::BLUE << ANSI::BACKGROUND::BRIGHT_WHITE << ANSI::TEXT::EFFECTS::UNDERLINE_ON << "America!" << ANSI::RESET;

    std::cout << "\nReset...\n\nNow testing custom command creation...\n";
    std::cout << ANSI::COMMAND( ANSI::LAYER::BACKGROUND, ANSI::RGB_COLOR( 50, 80, 10 ) ) << "Some kind of gross green, maybe..." << ANSI::RESET;

    std::cout << "\nReset...\n\nTests complete!\n" << std::endl;

    return 0;
}