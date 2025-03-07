#include "../meta_string.hpp"
#include <iostream>

int main()
{
	static constexpr char HELLO[] = "Hello ";
	static constexpr char WORLD[] = "World!";

	using hello_world = meta::cstring_concat_t< char, HELLO, WORLD >;
	std::cout << "As an alias: " << hello_world::value << '\n';
	std::cout << "Direct function: " << meta::cstring_concat_v< char, HELLO, WORLD > << '\n';

	using hello_jake = meta::append_t< char, meta::make_string_t< char, HELLO, sizeof( HELLO ) - 1 >, 'J', 'a', 'k', 'e' >;
	std::cout << "As an alias: " << hello_jake::value << '\n';
	std::cout << "Direct function: " << meta::append_v< char, meta::make_string_t< char, HELLO, sizeof( HELLO ) - 1 >, 'J', 'a', 'k', 'e' > << '\n';

	using nasty = meta::string< char, 'T', 'h', 'i', 's', ' ', 'm', 'a', 'y', ' ', 'b', 'e', ' ', 'n', 'a', 's', 't', 'y', ':', ' ' >;
	std::cout << "As an alias: " << nasty::value << sizeof( nasty ) << '\n';
	std::cout << "Direct function: " << meta::string< char, 'T', 'h', 'i', 's', ' ', 'm', 'a', 'y', ' ', 'b', 'e', ' ', 'n', 'a', 's', 't', 'y', ':', ' ' >::value << sizeof( nasty ) << '\n';

	static constexpr char TOGETHER[] = "ALL TOGETHER NOW...";
	using together = meta::make_string_t< char, TOGETHER >;
	std::cout << "As an alias: " << together::value << '\n';
	std::cout << "Direct function: " << meta::make_string_v< char, TOGETHER > << '\n';

	using all_together = meta::string_concat_many_t< meta::append_t< char, together, ' ' >, meta::append_t< char, hello_world, ' ' >, meta::append_t< char, hello_jake, '.', ' ' >, nasty >;
	std::cout << "As an alias: " << all_together::value << '\n';
	std::cout << "Direct function: " << meta::string_concat_many_v< meta::append_t< char, together, ' ' >, meta::append_t< char, hello_world, ' ' >, meta::append_t< char, hello_jake, '.', ' ' >, nasty > << '\n';

	std::cout << "Total memory usage in variables: " << sizeof( HELLO ) + sizeof( WORLD ) + sizeof( TOGETHER );
}