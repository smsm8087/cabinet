texture map;
sampler samp
{
    Texture = map;
};

float4 main(float2 uv : TEXCOORD0) : SV_Target
{
    float4 result = tex2D(samp, uv);
    if (result.a <=0.2f)
    {
        result.rgb =1.0f;
    }
    return result;
}

technique alphaShader
{
    pass p0
    {
        AlphaBlendEnable = false;
        PixelShader = compile ps_2_0 main();
    }
//¾ËÆÄºí·»µù
    pass p1
    {
        AlphaBlendEnable = true;
        BlendOp = Add;
        DestBlend = InvSrcAlpha;
        SrcBlend = SrcAlpha;
        PixelShader = compile ps_2_0 main();
    }
//´õ¹à¾ÆÁü  ADDITIVE
    pass p2
    {
        AlphaBlendEnable = true;
        BlendOp = Add;
        DestBlend = One;
        SrcBlend = SrcAlpha;
        PixelShader = compile ps_2_0 main();
    }
//Á¦°öÇÕ¼º ¼Ò¼öÁ¡Á¦°öÀÌ¶ó ´õ ÀÛ¾ÆÁ®¼­ ÁøÇØÁü
    pass p3 
    {
        AlphaBlendEnable = true;
        BlendOp = Add;
        DestBlend = InvSrcAlpha;
        SrcBlend = SrcColor ;
        PixelShader = compile ps_2_0 main();
    }
//°ö¼ÀÇÕ¼º
    pass p4
    {
        AlphaBlendEnable = true;
        BlendOp = Add;
        DestBlend = SrcColor ;
        SrcBlend = Zero;
        PixelShader = compile ps_2_0 main();
    }


}