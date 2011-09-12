cbuffer per_frame : register( b0 )
{
    matrix world;
    matrix view;
    matrix proj;
};

float4 VS_Test( float4 pos : POSITION ) : SV_POSITION
{
    float4 v = mul( pos, world );
    v = mul( v, view );
    v = mul( v, proj );
    return v;
}

float4 PS_Test( float4 pos : SV_POSITION ) : SV_Target
{
    return float4( 1.0, 0.0, 0.0, 1.0 );
}

