/**
 *  Utility/StringHelper.cpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */
#include "StringHelper.hpp"
#include <vector>

std::string WStringToString( const std::wstring& source )
{
    std::vector< char > ascii_chars( source.length() ); 
    const wchar_t* next_w_char; 
    char* next_ascii_char;   
 
    mbstate_t state; 
    int res = std::use_facet
		< std::codecvt< wchar_t, char, mbstate_t> >( std::locale( "C" ) ).out(
			state,
			source.c_str(),
			&source.c_str()[source.length()], 
			next_w_char,
			&ascii_chars[0],
			&ascii_chars[0] + source.length(), 
			next_ascii_char ); 
        
	if(res == std::codecvt_base::error) 
		throw std::runtime_error( "Wide to ASCII conversion failed" ); 
 
    return std::string(&ascii_chars[0], next_ascii_char - &ascii_chars[0]); 
}

std::wstring StringToWString( const std::string& source )
{
	std::wstring result( source.length(), L' ' );
	std::copy( source.begin(), source.end(), result.begin() );

	return result;
}
