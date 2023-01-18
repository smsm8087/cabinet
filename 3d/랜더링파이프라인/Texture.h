#pragma once
class Texture : public Test
{
private:
	Vertex* vertex;

	LPDIRECT3DTEXTURE9 texture;
public:
	Texture();
	Texture(wstring _imageName,Vertex* _vertex , LPDIRECT3DTEXTURE9 _texture);
	~Texture();

	void Update();
	void Render();
};

