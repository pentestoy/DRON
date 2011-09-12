/**
 *  Resource/ResourceManager.hpp
 *  (c) Jonathan Capps
 *  Created 11 Sept. 2011
 */

#ifndef _RESOURCE_MANAGER_HPP_
#define _RESOURCE_MANAGER_HPP_

#include <map>
#include <string>

template< class T >
class Resource
{
	public:
		virtual ~Resource() { _data; }
		T& Data() { return *_data; }

	protected:
		T* _data;
};

template< class T >
class ResourceManager
{
	public:
		ResourceManager() : _id_count( 0 ) {}
		virtual ~ResourceManager() {}

		virtual unsigned int LoadResource( const std::string& filename ) = 0;
		T& RequestResource( unsigned int resource_id )
		{
			return *( *_resources.find( resource_id ) ).second;
		}

	protected:
		unsigned int	_id_count;
		std::map< unsigned int, T* >	_resources;
};

#endif //_RESOURCE_MANAGER_HPP_
