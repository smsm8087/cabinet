// .hlsl �ɼǿ��� ����
// Shader 2.0, PixelShader

// ä�� 
// Shader : Shade + er 
//  ����Ʈ���� ����� ����
// �׷��� �ϵ������ ������ ȿ���� ����ϴµ� ����

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
// �ݵ���̼�
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