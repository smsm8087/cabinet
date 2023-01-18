#pragma once
class CubeTexture
{
private:
	vector<Texture*> cube;
	World* world;

public:
	CubeTexture();
	~CubeTexture();

	void Update();
	void Render();

	void LoadTexture(wstring fileName);
	World* GetWorld() { return world; }
};

