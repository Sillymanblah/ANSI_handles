#include "../ANSI/ANSI.hpp"

#include <iostream>

int main()
{
	using namespace ANSI;

	std::cout << TEXT::FOREGROUND::BLUE + TEXT::BACKGROUND::BRIGHT_RED + TEXT::EFFECTS::UNDERLINE_ON << "Blue text, red background, and underline..." << TEXT::DEFAULT << '\n';
	std::cout << "Text has been defaulted...\n";
	std::cout << ANSI::merge_v< TEXT::COMMAND< 34 >, TEXT::COMMAND< 101 >, TEXT::COMMAND< 4 > > << "Same thing done with ANSI::merge..." << TEXT::RESET << '\n';
	std::cout << "Text has been reset..." << std::endl;
}