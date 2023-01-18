//MultiShader

float value;

float4x4 rotMat;
float2 imageSize;

texture map1;
sampler samp1
{
    Texture = map1;
};

texture map2;
sampler samp2
{
    Texture = map2;
};

float4 main(float2 uv : TEXCOORD0) : SV_Target
{
    float4 tex1 = tex2D(samp1, uv);
    //float4 tex2 = tex2D(samp2, uv);
    float y = uv.y;

    y -= value;
    if(y < 0)
    {
        y += 1.0f;
    }else if(y > 1.0f)
    {
        y -= 1.0f;
    }
    float4 tex2 = tex2D(samp2, float2(uv.x, y));
    
    if(tex1.a == 1)
        tex1.rgb = tex2.rgb;

    return tex1;
}

float4 main1(float2 uv : TEXCOORD0) : SV_Target
{
    float4 tex1 = tex2D(samp1, uv);
    float4 tex2 = tex2D(samp2, uv);
        
    return tex1 * tex2; //modulate
}

float4 main2(float2 uv : TEXCOORD0) : SV_Target
{
    float4 tex1 = tex2D(samp1, uv);
    float4 tex2 = tex2D(samp2, uv);
        
    //return tex1 * tex2 * 2; //modulate2X
    return tex1 * tex2 * 4; //modulate4X
}

float4 main3(float2 uv : TEXCOORD0) : SV_Target
{
    float4 tex1 = tex2D(samp1, uv);
    float4 tex2 = tex2D(samp2, uv);
    
    float4 result = tex1 + tex2;
    result.a = tex1.a;
    return result; //add
}

float4 main4(float2 uv : TEXCOORD0) : SV_Target
{
    float4 tex1 = tex2D(samp1, uv);
    float4 tex2 = tex2D(samp2, uv);
    
    float4 result = tex1 + tex2 - tex1*tex2;//addsmooth
    result.a = tex1.a;
    return result;
}

float4 main5(float2 uv : TEXCOORD0) : SV_Target
{
    float4 tex1 = tex2D(samp1, uv);
    float4 tex2 = tex2D(samp2, uv);
    
    float4 result = tex1 + tex2 - 0.5f; //addsigned
    result.a = tex1.a;
    return result;
}

float4 main6(float2 uv : TEXCOORD0) : SV_Target
{
    float4 tex1 = tex2D(samp1, uv);
    float4 tex2 = tex2D(samp2, uv);
    
    float4 result = (tex1 + tex2 - 0.5f) * 2.0f; //addsigned2x
    result.a = tex1.a;
    return result;
}

float4 main7(float2 uv : TEXCOORD0) : SV_Target
{
    float4 tex1 = tex2D(samp1, uv);
    float4 tex2 = tex2D(samp2, uv);
    
    float4 result = tex1 - tex2; //subtract
    result.a = tex1.a;
    return result;
}

float4 main8(float2 uv : TEXCOORD0) : SV_Target
{
    float4 tex1 = tex2D(samp1, uv);
    float4 tex2 = tex2D(samp2, uv);
    
    float4 result = tex2 - tex1; //invsubtract
    result.a = tex1.a;
    return result;
}

float4 main9(float2 uv : TEXCOORD0) : SV_Target
{
    float4 tex1 = tex2D(samp1, uv);
    float4 tex2 = tex2D(samp2, uv);
    
    float4 result = 1.0f - tex2;
    result.a = tex1.a;
    return result;
}

float4 main10(float2 uv : TEXCOORD0) : SV_Target
{
    float4 tex1 = tex2D(samp1, uv);
    float4 tex2 = tex2D(samp2, uv);
    
    float4 result = 1.0f - (tex1 * tex2);
    result.a = tex1.a;
    return result;
}

technique tech
{
    pass p0
    {
        AlphaBlendEnable = true;
        BlendOp = Add;
        DestBlend = InvSrcAlpha;
        SrcBlend = SrcAlpha;
        PixelShader = compile ps_2_0 main();
    }
    pass p1
    {
        AlphaBlendEnable = true;
        BlendOp = Add;
        DestBlend = InvSrcAlpha;
        SrcBlend = SrcAlpha;
        PixelShader = compile ps_2_0 main1();
    }
    pass p2
    {
        AlphaBlendEnable = true;
        BlendOp = Add;
        DestBlend = InvSrcAlpha;
        SrcBlend = SrcAlpha;
        PixelShader = compile ps_2_0 main2();
    }
    pass p3
    {
        AlphaBlendEnable = true;
        BlendOp = Add;
        DestBlend = InvSrcAlpha;
        SrcBlend = SrcAlpha;
        PixelShader = compile ps_2_0 main3();
    }
    pass p4
    {
        AlphaBlendEnable = true;
        BlendOp = Add;
        DestBlend = InvSrcAlpha;
        SrcBlend = SrcAlpha;
        PixelShader = compile ps_2_0 main4();
    }
    pass p5
    {
        AlphaBlendEnable = true;
        BlendOp = Add;
        DestBlend = InvSrcAlpha;
        SrcBlend = SrcAlpha;
        PixelShader = compile ps_2_0 main5();
    }

    pass p6
    {
        AlphaBlendEnable = true;
        BlendOp = Add;
        DestBlend = InvSrcAlpha;
        SrcBlend = SrcAlpha;
        PixelShader = compile ps_2_0 main6();
    }
    pass p7
    {
        AlphaBlendEnable = true;
        BlendOp = Add;
        DestBlend = InvSrcAlpha;
        SrcBlend = SrcAlpha;
        PixelShader = compile ps_2_0 main7();
    }
    pass p8
    {
        AlphaBlendEnable = true;
        BlendOp = Add;
        DestBlend = InvSrcAlpha;
        SrcBlend = SrcAlpha;
        PixelShader = compile ps_2_0 main8();
    }
    pass p9
    {
        AlphaBlendEnable = true;
        BlendOp = Add;
        DestBlend = InvSrcAlpha;
        SrcBlend = SrcAlpha;
        PixelShader = compile ps_2_0 main9();
    }
    pass p10
    {
        AlphaBlendEnable = true;
        BlendOp = Add;
        DestBlend = InvSrcAlpha;
        SrcBlend = SrcAlpha;
        PixelShader = compile ps_2_0 main10();
    }
}