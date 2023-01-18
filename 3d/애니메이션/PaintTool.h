#pragma once

class PaintTool : public Test
{
private:
	struct Vertex
	{
		D3DXVECTOR4 position;
		DWORD color;

		static DWORD fvf;

		Vertex() {}
		Vertex(float x, float y, DWORD color)
		{
			position = { x, y, 0, 1 };
			this->color = color;
		}
	};

	enum State
	{
		LINE,
		RECTANGLE
	};
	State state;

	DWORD selectColor;

	vector<Vertex> lineVertex;
	vector<Vertex> rectVertex;

public:
	PaintTool();
	~PaintTool();

	void Update();
	void Render();
};

