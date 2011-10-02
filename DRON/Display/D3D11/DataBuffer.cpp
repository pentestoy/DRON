/**
 *  Display/D3D11/DataBuffer.cpp
 *  (c) Jonathan Capps
 *  Created 02 Oct. 2011
 */

#include "DataBuffer.hpp"
#include <cassert>
#include <cstring>
#include "DeviceContext.hpp"
#include "GFXDevice.hpp"
#include "../../Utility/DXUtil.hpp"

template< typename T >
DataBuffer< T >::DataBuffer(
	GFXDevice& device,
	DataBufferFlags flags,
	size_t size )
	: _buffer( 0 ), _data( 0 ), _size( size )
{
    D3D11_BUFFER_DESC bd;
    bd.ByteWidth = sizeof( T ) * size;
    bd.Usage = ( D3D11_USAGE )flags._usage;
    bd.BindFlags = ( D3D11_BIND_FLAG )flags._binding;
    bd.CPUAccessFlags = ( D3D11_CPU_ACCESS_FLAG )flags._access;
    bd.MiscFlags = 0;
	bd.StructureByteStride = 0;

	HR( device.GetRawDevicePtr()->CreateBuffer( &bd, 0, &_buffer ) );
}

template< typename T >
DataBuffer< T >::~DataBuffer()
{
	DXRelease( _buffer );
}

template< typename T >
void DataBuffer< T >::CopyDataToBuffer(
	DeviceContext& context,
	const std::vector< T >& data )
{
#if defined( DEBUG ) || defined( _DEBUG )  
	cassert( data.size() <= _size );
#endif
	context.GetRawPtr()->Map( _buffer_ptr, 0, map_flag, 0, &_data );
	std::memcpy( _data, &data[ 0 ], data.size() );
	context.GetRawPtr()->Unmap( _buffer_ptr, 0 );
}
