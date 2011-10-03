/**
 *  Utility/Geometry.hpp
 *  (c) Jonathan Capps
 *  Created 19 Sept. 2011
 */

#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <vector>
#include <Windows.h>
#include <d3d11.h>
#include <xnamath.h>

struct aiMatrix4x4;
XMMATRIX AIMatrixToXMMatrix( const aiMatrix4x4& in );

struct Vertex
{
	Vertex( const XMFLOAT3& f ) : _position( f ) {}
	Vertex( float x, float y, float z ) : _position( x, y, z ) {}
	XMFLOAT3 _position;
};

struct InstanceData
{
	XMFLOAT4X4 _xform;
	XMFLOAT4   _color;
};

struct TexCoord
{
	XMFLOAT2 _coord;
};

struct Triangle
{
	unsigned int _indices[3];
	TexCoord     _coords;
};

struct Mesh
{
	Mesh() : _vertex_buffer( 0 ), _index_buffer( 0 ) { }
	~Mesh();

	//std::vector< unsigned int > _indices;
	//std::vector< Triangle >		_triangles;
	unsigned int				_num_vertices;
	unsigned int				_num_indices;
	ID3D11Buffer*				_vertex_buffer;
	ID3D11Buffer*				_index_buffer;
};

#endif //GEOMETRY_HPP
