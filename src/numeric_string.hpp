#pragma once
#ifndef NUMERIC_STRING_HPP
#define NUMERIC_STRING_HPP

#include <type_traits>
#include <cstddef>
#include "meta_string.hpp"

#define CONVERT_STRING( VALUE ) #VALUE
#define CREATE_STRING( MACRO ) CONVERT_STRING( MACRO )
#define SUPPORTED_MAX_BASE 10

namespace meta
{
	template < class _Ty, class... _Types >
	struct is_any_of : std::disjunction< std::is_same< _Ty, _Types >... > {};

	template < class _Ty, class... _Types >
	constexpr bool is_any_of_v = is_any_of< _Ty, _Types... >::value;

	template < class _Ty >
	struct is_char : is_any_of< _Ty, char, wchar_t, char16_t, char32_t > {};

	template < class _Ty >
	constexpr bool is_char_v = is_char< _Ty >::value;

	template < bool _Trait, class _Ty, _Ty _Value >
	struct use_if {};

	template < class _Ty, _Ty _Value >
	struct use_if< true, _Ty, _Value >
	{ static constexpr _Ty value = _Value; };

	template < bool _Trait, class _Ty, _Ty _Value >
	constexpr _Ty use_if_v = use_if< _Trait, _Ty, _Value >::value;

	template < class _Ty >
	constexpr _Ty is_negative( _Ty value )
	{
		static_assert( std::is_integral_v< _Ty >, "The function is_negative() requires an integral type!" );
		return value < 0;
	}

	template < class _Ty >
	constexpr _Ty negate( _Ty value )
	{
		static_assert( std::is_integral_v< _Ty > && std::is_signed_v< _Ty >, "The function negate() requires a signed integral type!" );
		return -value;
	}

	template < class _Ty >
	constexpr _Ty abs( std::enable_if_t< std::is_signed_v< _Ty >, _Ty > value )
	{
		static_assert( std::is_integral_v< _Ty >, "The function abs() requires an integral type!" );
		return is_negative( value ) ? negate( value ) : value;
	}

	template < class _Ty >
	constexpr _Ty abs( std::enable_if_t< std::is_unsigned_v< _Ty >, _Ty > value )
	{
		static_assert( std::is_integral_v< _Ty >, "The function abs() requires an integral type!" );
		return value;
	}

	template < class _Ty, _Ty _Base >
	constexpr _Ty remove_digit( _Ty value )
	{
		static_assert( std::is_integral_v< _Ty >, "The function first_digit() requires an integral type!" );
		static_assert( _Base <= SUPPORTED_MAX_BASE, "The function first_digit() only supports a base up to base " CREATE_STRING( SUPPORTED_MAX_BASE ) "!" );
		return value / _Base;
	}

	template < class _Ty, _Ty _Base >
	constexpr _Ty first_digit( _Ty value )
	{
		static_assert( std::is_integral_v< _Ty >, "The function first_digit() requires an integral type!" );
		static_assert( _Base > 1 && _Base <= SUPPORTED_MAX_BASE, "The function first_digit() only supports a bases from base 2 up to base " CREATE_STRING( SUPPORTED_MAX_BASE ) "!" );
		return abs< _Ty >( value ) % _Base;
	}

	template < class _Ty, _Ty _Base >
	constexpr size_t digits( _Ty value )
	{
		static_assert( std::is_integral_v< _Ty >, "The function digits() requires an integral type!" );
		return value < _Base ? 1 : 1 + digits< _Ty, _Base >( remove_digit< _Ty, _Base >( value ) );
	}

	// Helper class to remove errors with unsigned integer types:
	template < bool _Signed, class _Ty, _Ty _Value, _Ty _Base, class _Char, _Char... _Elems >
	struct numeric_string_finisher;
	
	template < class _Ty, _Ty _Value, _Ty _Base, class _Char, _Char... _Elems >
	struct numeric_string_finisher< true, _Ty, _Value, _Base, _Char, _Elems... > :
		std::conditional_t< is_negative( _Value ), string< _Char, '-' , '0' + negate( _Value ), _Elems... >, string< _Char, '0' + _Value, _Elems... > > 
	{ using type = typename std::conditional_t< is_negative( _Value ), string< _Char, '-' , '0' + negate( _Value ), _Elems... >, string< _Char, '0' + _Value, _Elems... > >::type; };
	
	template < class _Ty, _Ty _Value, _Ty _Base, class _Char, _Char... _Elems >
	struct numeric_string_finisher< false, _Ty, _Value, _Base, _Char, _Elems... > : string< _Char, '0' + _Value, _Elems... >
	{ using type = string< _Char, '0' + _Value, _Elems... >::type; };

	template < size_t _Digits, class _Ty, _Ty _Value, _Ty _Base, class _Char, _Char... _Elems >
	struct numeric_string_builder :
		numeric_string_builder< _Digits - 1, _Ty, remove_digit< _Ty, _Base >( _Value ), _Base, _Char, '0' + first_digit< _Ty, _Base >( _Value ), _Elems... >
	{ using type = typename numeric_string_builder< _Digits - 1, _Ty, remove_digit< _Ty, _Base >( _Value ), _Base, _Char, '0' + first_digit< _Ty, _Base >( _Value ), _Elems... >::type; };

	template < class _Ty, _Ty _Value, _Ty _Base, class _Char, _Char... _Elems >
	struct numeric_string_builder< 1, _Ty, _Value, _Base, _Char, _Elems... > : numeric_string_finisher< std::is_signed_v< _Ty >, _Ty, _Value, _Base, _Char, _Elems... >
	{ using type = typename numeric_string_finisher< std::is_signed_v< _Ty >, _Ty, _Value, _Base, _Char, _Elems... >::type; };

	template < class _Ty, _Ty _Value, _Ty _Base = 10, class _Char = char >
	struct numeric_string : numeric_string_builder< digits< _Ty, _Base >( abs< _Ty >( _Value ) ), _Ty, _Value, _Base, _Char >
	{ using type = numeric_string_builder< digits< _Ty, _Base >( abs< _Ty >( _Value ) ), _Ty, _Value, _Base, _Char >::type; };

	// Gets the base type (the meta::string) from the call to numeric_string.
	template < class _Ty, _Ty _Value, _Ty _Base = 10, class _Char = char >
	using numeric_string_t = numeric_string< _Ty, _Value, _Base, _Char >::type;

	template < class _Ty, _Ty _Value, _Ty _Base = 10, class _Char = char >
	constexpr numeric_string_t< _Ty, _Value, _Base, _Char>::value_type numeric_string_v = numeric_string< _Ty, _Value, _Base, _Char >::value;
}
// namespace meta

#endif // NUMERIC_STRING_HPP