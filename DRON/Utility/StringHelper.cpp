/**
 *  Utility/StringHelper.cpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */
#include "StringHelper.hpp"

std::string WStringToString( const std::wstring& source )
{
	std::string result( source.length(), ' ' );
	std::copy( source.begin(), source.end(), result.begin() );

	return result;
}

std::wstring StringToWString( const std::string& source )
{
	std::wstring result( source.length(), L' ' );
	std::copy( source.begin(), source.end(), result.begin() );

	return result;
}
