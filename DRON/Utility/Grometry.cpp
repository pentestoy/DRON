/**
 *  Utility/Geometry.cpp
 *  (c) Jonathan Capps
 *  Created 20 Sept. 2011
 */

#include "Geometry.hpp"
#include <aiScene.h>
#include "DXUtil.hpp"

XMMATRIX AIMatrixToXMMatrix( const aiMatrix4x4& in )
{
	return XMMATRIX( in.a1, in.a2, in.a3, in.a4,
					 in.b1, in.b2, in.b3, in.b4,
					 in.c1, in.c2, in.c3, in.c4,
					 in.d1, in.d2, in.d3, in.d4 );
}

Mesh::~Mesh()
{
	DXRelease( _vertex_buffer );
	DXRelease( _index_buffer );
}
