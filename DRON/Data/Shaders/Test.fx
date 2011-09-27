cbuffer per_frame : register( b0 )
{
    matrix world;
    matrix view;
    matrix proj;
};

struct VS_OUT
{
    float4 _wpos : NORMAL;
    float4 _pos  : SV_POSITION;
};

VS_OUT VS_Test( float4 pos : POSITION )
{
    VS_OUT v2;
    v2._wpos = pos;
    v2._pos = mul( pos, world );
    v2._pos = mul( v2._pos, view );
    v2._pos = mul( v2._pos, proj );
    
    return v2;
}

float4 PS_Test( VS_OUT input ) : SV_Target
{
    return float4( 0.5, 0.5, 1.0, 1.0);
}
