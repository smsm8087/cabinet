// .hlsl 옵션에서 설정
// Shader 2.0, PixelShader

// 채도 
// Shader : Shade + er 
//  소프트웨어 명령의 집합
// 그래픽 하드웨어의 렌더링 효과를 계산하는데 쓰임

float4 color;
texture map;
sampler samp
{
	Texture = map;
};

float4 main() : COLOR0
{
	//r      g     b   a
return float4(1.0f, 1.0f, 1.0f, 1.0f);
}
// 콜디네이션
float4 ColorShader(float2 uv : TEXCOORD0) : COLOR0
{
    float4 result = tex2D(samp, uv);
    result *= color;

    return result;
}

technique colorShader
{
	pass p
	{
		PixelShader = compile ps_2_0 main();
	}
	pass p1
	{
		PixelShader = compile ps_2_0 ColorShader();
	}
}