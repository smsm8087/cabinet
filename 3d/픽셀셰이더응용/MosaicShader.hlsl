//MosaicShader

texture map;
sampler samp
{
    Texture = map;

    MinFilter = Point;//��������� �����ϴ� ����
    MagFilter = Point; //Ȯ�������� �����ϴ� ����
};
sampler linearSamp
{
    Texture = map;

    MinFilter = Linear; //��������� �����ϴ� ����
    MagFilter = Linear; //Ȯ�������� �����ϴ� ����
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
}