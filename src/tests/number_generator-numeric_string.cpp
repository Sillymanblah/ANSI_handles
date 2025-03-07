#include <random>
#include <iostream>

int main()
{
	srand( time( NULL ) );

	int count;
	
	std::cout << "Please type the number of random numbers you want: ";
	std::cin >> count;
	
	for ( int i = 0; i < count; ++i )
	{
		std::cout << ( rand() % RAND_MAX ) - ( RAND_MAX / 2 ) << ", ";
		if ( i % 10 == 9 ) std::cout << '\n';
	}
}