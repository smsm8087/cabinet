//ºŒ¿Ã¥ı(Shader - Shade + er)

float4 main() : COLOR0
{
	return float4(1.0f,1.0f,1.0f,1.0f);//rgba
}
technique colorShader
{
	pass p
	{
		PixelShader = compile ps_2_0 main();
	}
}