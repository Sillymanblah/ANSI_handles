#pragma once
#ifndef META_STRING_HPP
#define META_STRING_HPP

#include <cstddef>
#include <utility>

namespace meta
{
	template < class _Char, _Char... _Elems >
	struct string
	{
		using char_type		= _Char;
		using type			= string< _Char, _Elems... >;
		using value_type	= const char_type*;
		static constexpr char value[] = { _Elems..., 0 };
	};
	
	// Used to get the value type of the string, usually called without the _Elems.
	template < class _Char, _Char... _Elems >
	using string_t = typename string< _Char, _Elems... >::value_type;
	
	template < class _Char, _Char... _Elems >
	constexpr string_t< _Char, _Elems... > meta_string_v = string< _Char, _Elems... >::value;

	template < size_t _Index, class _Char, const _Char* _Cstr, _Char... _Elems >
	struct string_builder : std::conditional_t< _Cstr[ _Index ] != 0, string_builder< _Index + 1, _Char, _Cstr, _Elems..., _Cstr[ _Index ] >, string< _Char, _Elems... > >
	{ using type = typename std::conditional_t< _Cstr[ _Index ] != 0, string_builder< _Index + 1, _Char, _Cstr, _Elems..., _Cstr[ _Index ] >, string< _Char, _Elems... > >::type; };
	
	template < class _Char, const _Char* _Cstr, typename >
	struct build_string {};

	template < class _Char, const _Char* _Cstr, size_t... _Indices >
	struct build_string< _Char, _Cstr, std::index_sequence< _Indices... > > : string< _Char, _Cstr[ _Indices ]... >
	{ using type = typename string< _Char, _Cstr[ _Indices ]... >::type; };

	// Conditionally builds a string using either string_builder if we don't know the size, or std::index_sequence if we do.
	template < class _Char, const _Char* _Cstr, size_t _Size = 0 >
	struct make_string : std::conditional_t< _Size == 0, string_builder< 0, _Char, _Cstr >, build_string< _Char, _Cstr, std::make_index_sequence< _Size > > >
	{ using type = typename std::conditional_t< _Size == 0, string_builder< 0, _Char, _Cstr >, build_string< _Char, _Cstr, std::make_index_sequence< _Size > > >::type; };
	
	template < class _Char, const _Char* _Cstr, size_t _Size = 0 >
	using make_string_t = typename make_string< _Char, _Cstr, _Size >::type;

	template < class _Char, const _Char* _Cstr, size_t _Size = 0 >
	constexpr typename make_string_t< _Char, _Cstr, _Size >::value_type make_string_v = make_string< _Char, _Cstr, _Size >::value;
	
	template < class _String_1, class _String_2 >
	struct string_concat {};
	
	template < class _Char, _Char... _Elems_1, _Char... _Elems_2 >
	struct string_concat< string< _Char, _Elems_1... >, string< _Char, _Elems_2... > > : string< _Char, _Elems_1..., _Elems_2... >
	{ using type = string< _Char, _Elems_1..., _Elems_2... >; };

	template < class _String_1, class _String_2 >
	using string_concat_t = typename string_concat< _String_1, _String_2 >::type;
	
	template < class _String_1, class _String_2 >
	constexpr typename string_concat_t< _String_1, _String_2 >::value_type string_concat_v = string_concat< _String_1, _String_2 >::value;

	template < class... _Strings >
	struct string_concat_many;

	template < class _First, class _Second, class... _Rest >
	struct string_concat_many< _First, _Second, _Rest... > : string_concat_many< string_concat_t< _First, _Second >, _Rest... >
	{ using type = typename string_concat_many< string_concat_t< _First, _Second >, _Rest... >::type; };

	template < class _First, class _Second >
	struct string_concat_many< _First, _Second > : string_concat_t< _First, _Second >
	{ using type = typename string_concat_t< _First, _Second >::type; };

	template < class... _Strings >
	using string_concat_many_t = typename string_concat_many< _Strings... >::type;

	template < class... _Strings >
	constexpr typename string_concat_many_t< _Strings... >::value_type string_concat_many_v = string_concat_many< _Strings... >::value;

	template < class _Char, const _Char* _String_1, const _Char* _String_2 >
	struct cstring_concat : string_concat< make_string_t< _Char, _String_1 >, make_string_t< _Char, _String_2 > >
	{ using type = typename string_concat< make_string_t< _Char, _String_1 >, make_string_t< _Char, _String_2 > >::type; };

	template < class _Char, const _Char* _String_1, const _Char* _String_2 >
	using cstring_concat_t = typename cstring_concat< _Char, _String_1, _String_2 >::type;
	
	template < class _Char, const _Char* _String_1, const _Char* _String_2 >
	constexpr typename cstring_concat_t< _Char, _String_1, _String_2 >::value_type cstring_concat_v = cstring_concat< _Char, _String_1, _String_2 >::value;

	template < class _Char, typename, _Char... _Elems >
	struct append {};
	
	template < class _Char, _Char... _String_elems, _Char... _Elems >
	struct append< _Char, string< _Char, _String_elems... >, _Elems... > : string< _Char, _String_elems..., _Elems... >
	{ using type = typename string< _Char, _String_elems..., _Elems... >::type; };
	
	template < class _Char, class _String, _Char... _Elems >
	using append_t = typename append< _Char, _String, _Elems... >::type;

	template < class _Char, class _String, _Char... _Elems >
	constexpr typename append_t< _Char, _String, _Elems... >::value_type append_v = append< _Char, _String, _Elems... >::value;
}
// namespace meta

#endif // META_STRING_HPP