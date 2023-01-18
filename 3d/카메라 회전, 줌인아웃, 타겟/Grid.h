#pragma once
class Grid
{
private:
	vector<ColorVertex> vertex;
	D3DXMATRIX world;
public:
	Grid();
	~Grid();

	void Render();
};

