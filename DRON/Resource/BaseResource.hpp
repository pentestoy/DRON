/**
 *  Resource/BaseResource.hpp
 *  (c) Jonathan Capps
 *  Created 19 Sept. 2011
 */

#ifndef BASE_RESOURCE_HPP
#define BASE_RESOURCE_HPP

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

#endif //BASE_RESOURCE_HPP
