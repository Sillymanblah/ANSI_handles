#include "../ANSI/ANSI.hpp"

#include <iostream>

int main()
{
	using namespace ANSI;

	std::cout << TEXT::FOREGROUND::BLUE << "Blue text?";
}