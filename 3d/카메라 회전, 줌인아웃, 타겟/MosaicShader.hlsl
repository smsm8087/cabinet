//MosaicShader

texture map;
sampler samp
{
    Texture = map;

    MinFilter = Point;//축소했을 때 관여하는 필터
    MagFilter = Point;//확대했을 때 관여하는 필터
};

sampler linearSamp
{
    Texture = map;

    MinFilter = Linear; //축소했을 때 관여하는 필터
    MagFilter = Linear; //확대했을 때 관여하는 필터
};

sampler mirrorSamp
{
    Texture = map;

    AddressU = Mirror;
    AddressV = Mirror;
};

sampler clampSamp
{
    Texture = map;

    AddressU = Clamp;
    AddressV = Clamp;
};

sampler borderSamp
{
    Texture = map;

    AddressU = Border;
    AddressV = Border;
    BorderColor = 0xffffff00;
};

float mosaicSize;

float4 main(float2 uv : TEXCOORD0) : SV_Target
{
    float u = uv.x;
    float v = uv.y;

    int x = (int) (u * mosaicSize);
    int y = (int) (v * mosaicSize);

    float2 result = float2(x / mosaicSize, y / mosaicSize);

    return tex2D(samp, result);
}

float4 color;

float4 Tone(float2 uv : TEXCOORD0) : SV_Target
{
    float4 result = tex2D(samp, uv);
    float pixel = (result.r + result.g + result.b) / 3.0f;

    result.rgb = pixel * color.rgb;

    return result;
}

float4 Filtering(float2 uv : TEXCOORD0) : SV_Target
{
    return tex2D(samp, uv);
}

float4 Filtering2(float2 uv : TEXCOORD0) : SV_Target
{
    return tex2D(linearSamp, uv);
}

float4 AdressMirror(float2 uv : TEXCOORD0) : SV_Target
{
    return tex2D(mirrorSamp, uv);
}

float4 AdressClamp(float2 uv : TEXCOORD0) : SV_Target
{
    return tex2D(clampSamp, uv);
}

float4 AdressBorder(float2 uv : TEXCOORD0) : SV_Target
{
    return tex2D(borderSamp, uv);
}

technique tech
{
    pass p0
    {
        PixelShader = compile ps_2_0 main();
    }
    pass p1
    {
        PixelShader = compile ps_2_0 Tone();
    }
    pass p2
    {
        PixelShader = compile ps_2_0 Filtering();
    }
    pass p3
    {
        PixelShader = compile ps_2_0 Filtering2();
    }
    pass p4
    {
        PixelShader = compile ps_2_0 AdressMirror();
    }
    pass p5
    {
        PixelShader = compile ps_2_0 AdressClamp();
    }
    pass p6
    {
        PixelShader = compile ps_2_0 AdressBorder();
    }
}