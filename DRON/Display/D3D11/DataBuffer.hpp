/**
 *  Display/D3D11/DataBuffer.hpp
 *  (c) Jonathan Capps
 *  Created 02 Oct. 2011
 */

#ifndef DISPLAY_D3D11_DATA_BUFFER_HPP
#define DISPLAY_D3D11_DATA_BUFFER_HPP

#include <cassert>
#include <cstring>
#include <vector>
#include <D3D11.h>
#include "GFXDevice.hpp"
#include "../../Utility/DXUtil.hpp"

enum DATA_BUFFER_ACCESS
{
	DATA_BUFFER_ACCESS_READ  = D3D11_CPU_ACCESS_READ,
	DATA_BUFFER_ACCESS_WRITE = D3D11_CPU_ACCESS_WRITE
};

enum DATA_BUFFER_BINDING
{
  DATA_BUFFER_BIND_VERTEX_BUFFER    = D3D11_BIND_VERTEX_BUFFER,
  DATA_BUFFER_BIND_INDEX_BUFFER     = D3D11_BIND_INDEX_BUFFER,
  DATA_BUFFER_BIND_CONSTANT_BUFFER  = D3D11_BIND_CONSTANT_BUFFER,
  DATA_BUFFER_BIND_SHADER_RESOURCE  = D3D11_BIND_SHADER_RESOURCE,
  DATA_BUFFER_BIND_STREAM_OUTPUT    = D3D11_BIND_STREAM_OUTPUT,
  DATA_BUFFER_BIND_RENDER_TARGET    = D3D11_BIND_RENDER_TARGET,
  DATA_BUFFER_BIND_DEPTH_STENCIL    = D3D11_BIND_DEPTH_STENCIL,
  DATA_BUFFER_BIND_UNORDERED_ACCESS = D3D11_BIND_UNORDERED_ACCESS
};

enum DATA_BUFFER_MAP
{
  DATA_BUFFER_MAP_READ               = D3D11_MAP_READ,
  DATA_BUFFER_MAP_WRITE              = D3D11_MAP_WRITE,
  DATA_BUFFER_MAP_READ_WRITE         = D3D11_MAP_READ_WRITE,
  DATA_BUFFER_MAP_WRITE_DISCARD      = D3D11_MAP_WRITE_DISCARD,
  DATA_BUFFER_MAP_WRITE_NO_OVERWRITE = D3D11_MAP_WRITE_NO_OVERWRITE
};

enum DATA_BUFFER_USAGE
{
  DATA_BUFFER_USAGE_DEFAULT   = D3D11_USAGE_DEFAULT,
  DATA_BUFFER_USAGE_IMMUTABLE = D3D11_USAGE_IMMUTABLE,
  DATA_BUFFER_USAGE_DYNAMIC   = D3D11_USAGE_DYNAMIC,
  DATA_BUFFER_USAGE_STAGING   = D3D11_USAGE_STAGING
};

struct DataBufferFlags
{
	DATA_BUFFER_ACCESS  _access;
	DATA_BUFFER_BINDING _binding;
	DATA_BUFFER_USAGE   _usage;
};

class GFXDevice;
template< typename T >
class DataBuffer
{
	public:
		DataBuffer( GFXDevice& device, DataBufferFlags flags, size_t size );
		~DataBuffer();

		ID3D11Buffer* GetBuffer() const { return _buffer; }

		void CopyDataToBuffer(
			GFXDevice& device,
			const std::vector< T >& data,
			DATA_BUFFER_MAP map_flag );
		void Unmap();

	private:
		ID3D11Buffer* _buffer;
		T*            _data;
		size_t		  _size;
};

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
	GFXDevice& device,
	const std::vector< T >& data,
	DATA_BUFFER_MAP map_flag )
{
#if defined( DEBUG ) || defined( _DEBUG )  
	assert( data.size() <= _size );
#endif
	D3D11_MAPPED_SUBRESOURCE msr;
	device.GetRawContextPtr()->Map(
		_buffer,
		0,
		( D3D11_MAP )map_flag,
		0,
		&msr );
	_data = static_cast< T* >( msr.pData );
	std::memcpy( _data, &data[ 0 ], sizeof( T ) * data.size() );
	device.GetRawContextPtr()->Unmap( _buffer, 0 );
}

#endif //DISPLAY_D3D11_DATA_BUFFER_HPP
