/**
 *  Utility/DXutil.hpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#ifndef DXUTIL_HPP
#define DXUTIL_HPP

#include <D3DX10.h>
#include <DXerr.h>

#if defined(DEBUG) | defined(_DEBUG)
	#ifndef HR
	#define HR(x)                                                  \
	{                                                              \
		HRESULT hr = ( x );                                        \
		if( FAILED( hr ) )                                         \
		{                                                          \
			DXTrace( __FILE__, ( DWORD )__LINE__, hr, L#x, true ); \
		}                                                          \
	}
	#endif

#else
	#ifndef HR
	#define HR(x) (x)
	#endif
#endif 

#define DXRelease(x) { if(x){ x->Release();x = 0; } }

/*
float DistanceXY( D3DXVECTOR2, D3DXVECTOR2 );
float DistanceXY( D3DXVECTOR2, D3DXVECTOR3 );
float DistanceXY( D3DXVECTOR3, D3DXVECTOR2 );

bool AreParallel( const D3DXVECTOR3&, const D3DXVECTOR3& );
*/
#endif  DXUTIL_HPP
