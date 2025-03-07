#include "../numeric_string.hpp"
#include <iostream>

template < class _Ty, const _Ty _Value >
void print_number_as_string()
{ std::cout << "\nNumber " << _Value << " as a string: " << meta::numeric_string_v< int, _Value >; }

template < class _Ty, const _Ty* _Values, size_t _First, size_t... _Rest >
void print_numbers_as_strings_recurse()
{
	print_number_as_string< _Ty, _Values[ _First ] >();
	if constexpr ( sizeof... ( _Rest ) > 0 ) print_numbers_as_strings_recurse< _Ty, _Values, _Rest... >();
}

template < class _Ty, const _Ty* _Values, size_t... _Indices >
void print_numbers_as_strings( std::index_sequence< _Indices... > )
{ print_numbers_as_strings_recurse< _Ty, _Values, _Indices... >(); }

template < class _Ty, const _Ty* _Values, size_t _Count >
void print_numbers_as_strings()
{ print_numbers_as_strings< _Ty, _Values >( std::make_index_sequence< _Count >() ); }

template < class _Ty, const _Ty* _Values, typename >
struct concat_number_strings;

template < class _Ty, const _Ty* _Values, size_t... _Indices >
struct concat_number_strings< _Ty, _Values, std::index_sequence< _Indices... > > :
	meta::string_concat_many< meta::numeric_string_t< _Ty, _Values[ _Indices ] >... >
{ using type = meta::string_concat_many< meta::numeric_string_t< _Ty, _Values[ _Indices ] >... >::type; };

template < class _Ty, const _Ty* _Values, size_t _Count >
struct concat_number_array_strings :
	concat_number_strings< _Ty, _Values, typename std::make_index_sequence< _Count > >
{ using type = concat_number_strings< _Ty, _Values, typename std::make_index_sequence< _Count > >::type; };

template < class _Ty, const _Ty* _Values, size_t _Count >
using concat_number_array_strings_t = concat_number_array_strings< _Ty, _Values, _Count >::type;

template < class _Ty, const _Ty* _Values, size_t _Count >
constexpr typename concat_number_array_strings_t< _Ty, _Values, _Count >::value_type concat_number_array_strings_v = concat_number_array_strings< _Ty, _Values, _Count >::value;

using integer_type = long long; // For consistency, and to make it easy to change.

static constexpr integer_type x[] =
{
	-12236, 10012, -8535, 15651, 9352, -4275, 12239, -7994, 14230, -3463, 
	-12664, -3033, -2533, -2246, 150, 6470, -8161, 2885, 13165, 1052,
	9421, -19, 5794, -1223, 12418, 4073, 15008, -13396, -7900, 4694,
	1949, 13347, -11083, -8448, 8396, 2899, 1576, -14371, 2004, 9626,
	11379, -13350, 5250, 15843, 4069, -6438, 5306, -6709, -13894, 8956,
	10420, -16126, 8685, -12515, 12133, 4083, -179, -353, -10438, -12889,
	7635, 13928, 9996, -6938, -205, -5331, 4945, -16224, -13903, 13552,
	-3185, 15244, 2358, -9273, -5097, 13071, 1699, 8672, 8175, -16033,
	10597, -4414, 16144, -7448, 5962, 16341, -15151, 2799, 1682, 549,
	-1372, -5259, -2486, 14691, 4864, -2978, -16171, 6189, -3938, -12846
};
constexpr size_t NUM_INTS = sizeof( x ) / sizeof( integer_type );

int main()
{
	print_numbers_as_strings< integer_type, x, NUM_INTS >();
	std::cout << "\nConcat: {" << concat_number_array_strings_v< integer_type, x, NUM_INTS > << '}';
}