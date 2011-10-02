cbuffer per_frame : register( b0 )
{
    matrix world;
    matrix view;
    matrix proj;
};

struct VS_IN
{
    float4 _pos       : POSITION;
    float3 _posoffset : Translation;
    float4 _rotation  : Rotation;
    float3 _scale     : Scale;
    float4 _color     : COLOR;
};

struct VS_OUT
{
    float4 _wpos : NORMAL;
    float4 _pos  : SV_POSITION;
    float4 _color : COLOR;
};

VS_OUT VS_Test( VS_IN v_in )
{
    VS_OUT v_out;
    v_out._wpos = v_in._pos;
    v_out._pos = mul( v_in._pos + float4( v_in._posoffset, 0.0 ), world );
    v_out._pos = mul( v_out._pos, view );
    v_out._pos = mul( v_out._pos, proj );
    v_out._color = v_in._color;
    
    return v_out;
}

float4 PS_Test( VS_OUT input ) : SV_Target
{
    return input._color;
}
