//BlurShader
float2 imageSize;
int blurCount;

texture map;
sampler samp
{
    Texture = map;
};

float4 main(float2 uv : TEXCOORD0) : SV_Target
{
    return tex2D(samp, uv);
}

float4 Blur(float2 uv : TEXCOORD0) : SV_Target
{
    float u = uv.x;
    float v = uv.y;

    float4 result = tex2D(samp, uv);

    [unroll(4)]
    for (int i = 0; i < blurCount; i++)
    {
        float x = (float) (i * 2 + 1) / imageSize.x;
        float y = (float) (i * 2 + 1) / imageSize.y;

        result += tex2D(samp, float2(u - x, v));
        result += tex2D(samp, float2(u + x, v));
        result += tex2D(samp, float2(u, v + y));
        result += tex2D(samp, float2(u, v - y));
    }

    result /= blurCount * 4 + 1;

    return result;
}

float4 GaussianBlur(float2 uv : TEXCOORD0) : SV_Target
{
    const float weight[7] =
    {
        0.486f, 0.726f, 0.923f, 1, 0.923f, 0.726f, 0.486f
    };

    float4 result = float4(0, 0, 0, 0);
    float x = 1 / imageSize.x;
    float y = 1 / imageSize.y;

    for (int i = -3; i <= 3; i++)
    {
        float2 temp = float2(uv.x + i * x, uv.y);
        result += weight[3 + i] * tex2D(samp, temp);

        temp = float2(uv.x, uv.y + i * y);
        result += weight[3 + i] * tex2D(samp, temp);
    }

    //result /= 2.135f * 2 * 2 + 2;
    result /= 10.54f;
    return result;
}

technique tech
{
    pass p0
    {
        PixelShader = compile ps_2_0 main();
    }
    pass p1
    {
        PixelShader = compile ps_2_0 Blur();
    }
    pass p2
    {
        PixelShader = compile ps_2_0 GaussianBlur();
    }

}