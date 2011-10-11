/**
 *  Utility/AlignedPtr.hpp
 *  (c) Jonathan Capps
 *  Created 09 Oct. 2011
 */

#ifndef UTILITY_ALIGNED_PTR_HPP
#define UTILITY_ALIGNED_PTR_HPP

template< typename T >
class AlignedPtr
{
	public:
		AlignedPtr();
		~AlignedPtr();

		bool ResetWithDefault();
		bool IsValid() const;
		void Release();
		void Reset( T* ptr = 0 );
		void Reset( const T& value );

		T& operator*() const;
		T* operator->() const;

	private:
		T* _ptr;
};

template< typename T >
AlignedPtr< T >::AlignedPtr()
	: _ptr( 0 ) { }

template< typename T >
AlignedPtr< T >::~AlignedPtr()
{
	Release();
}

template< typename T >
bool AlignedPtr< T >::IsValid() const
{
	return _ptr != 0;
}

template< typename T >
bool AlignedPtr< T >::ResetWithDefault()
{
	void* buffer = _aligned_malloc( sizeof( T ), 16 );
	_ptr = new( buffer ) T;

	return _ptr != 0;
}

template< typename T >
void AlignedPtr< T >::Release()
{
	if( _ptr )
	{
		_ptr->~T();
		_aligned_free( _ptr );
		_ptr = 0;
	}
}

template< typename T >
void AlignedPtr< T >::Reset( T* ptr = 0 )
{
	Release();
	_ptr = ptr;
}

template< typename T >
void AlignedPtr< T >::Reset( const T& value )
{
	if( !_ptr )
	{
	void* buffer = _aligned_malloc( sizeof( T ), 16 );
	_ptr = new( buffer ) T;
	}

	*_ptr = value;/*XMVectorSet(
		XMVectorGetX( value ),
		XMVectorGetY( value ),
		XMVectorGetZ( value ),
		XMVectorGetW( value )
	);*/
}

template< typename T >
T& AlignedPtr< T >::operator*() const
{
	return *_ptr;
}

template< typename T >
T* AlignedPtr< T >::operator->() const
{
	return _ptr;
}

#endif ///UTILITY_ALIGNED_PTR_HPP
