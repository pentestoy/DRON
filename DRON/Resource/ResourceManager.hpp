/**
 *  Resource/ResourceManager.hpp
 *  (c) Jonathan Capps
 *  Created 11 Sept. 2011
 */

#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <map>
#include <string>

template< class T >
class Resource
{
	public:
		Resource() : _data( 0 ), _valid( false ) { }
		virtual ~Resource() { }
		T& Data() const { return *_data; }

	protected:
		void SetValid( bool validity ) { _valid = validity; }

		T* _data;
		bool _valid;
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

#endif //RESOURCE_MANAGER_HPP
