/**
 *  Utility/Rotations.cpp
 *  (c) Jonathan Capps
 *  Created 11 Oct. 2011
 */

#include <Windows.h>
#include <xnamath.h>

extern const XMVECTOR IDENTITY_QUAT = XMQuaternionIdentity();

extern const XMVECTOR QUARTER_TURN = XMQuaternionRotationAxis(
	XMVectorSet( 0.0f, 0.0f, -1.0f, 0.0f ),
	XM_PIDIV2 );

extern const XMVECTOR HALF_TURN = XMQuaternionRotationAxis(
	XMVectorSet( 0.0f, 0.0f, -1.0f, 0.0f ),
	XM_PI );

extern const XMVECTOR THREE_QUARTER_TURN = XMQuaternionRotationAxis(
	XMVectorSet( 0.0f, 0.0f, -1.0f, 0.0f ),
	3.0f * XM_PIDIV2 );

extern const XMVECTOR TOP_JOIN = XMQuaternionRotationRollPitchYaw(
	0.0f, -XM_PIDIV2, 0.0f );

extern const XMVECTOR SIDE_JOIN = XMQuaternionRotationRollPitchYaw(
	-XM_PIDIV2, -XM_PIDIV2, 0.0f );
