#include "stdafx.h"
#include "PaintTool.h"

DWORD PaintTool::Vertex::fvf = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;

PaintTool::PaintTool()
{
	state = LINE;
	selectColor = 0xffff0000;
}


PaintTool::~PaintTool()
{
}

void PaintTool::Update()
{
	if (KEYBOARD->KeyDown(VK_F1))
		selectColor = 0xffff0000;
	if (KEYBOARD->KeyDown(VK_F2))
		selectColor = 0xff00ff00;
	if (KEYBOARD->KeyDown(VK_F3))
		selectColor = 0xff0000ff;
	if (KEYBOARD->KeyDown('1'))
		state = LINE;
	if (KEYBOARD->KeyDown('2'))
		state = RECTANGLE;

	if (KEYBOARD->KeyDown(VK_LBUTTON))
	{
		Vertex startVertex = Vertex(mousePos.x, mousePos.y, selectColor);
		
		switch (state)
		{
		case PaintTool::LINE:
			lineVertex.push_back(startVertex);
			break;
		case PaintTool::RECTANGLE:
			rectVertex.push_back(startVertex);
			break;
		default:
			break;
		}
	}

	if (KEYBOARD->KeyUp(VK_LBUTTON))
	{
		Vertex endVertex = Vertex(mousePos.x, mousePos.y, selectColor);

		switch (state)
		{
		case PaintTool::LINE:
			lineVertex.push_back(endVertex);
			break;
		case PaintTool::RECTANGLE:
		{
			//Vertex startVertex = rectVertex[rectVertex.size() - 1];
			Vertex startVertex = rectVertex.back();

			Vertex v1, v2, v3, v4;
			v1 = Vertex(mousePos.x, startVertex.position.y, selectColor);
			v2 = Vertex(startVertex.position.x, mousePos.y, selectColor);
			v3 = Vertex(startVertex.position.x, mousePos.y, selectColor);
			v4 = Vertex(mousePos.x, startVertex.position.y, selectColor);

			rectVertex.push_back(v1);
			rectVertex.push_back(v2);
			rectVertex.push_back(v3);
			rectVertex.push_back(v4);
			rectVertex.push_back(endVertex);
		}
			break;
		default:
			break;
		}
	}
}

void PaintTool::Render()
{
	DEVICE->SetFVF(Vertex::fvf);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	if (lineVertex.size() > 0)
	{
		DEVICE->DrawPrimitiveUP(D3DPT_LINELIST, lineVertex.size()*0.5f,
			&lineVertex[0], sizeof(Vertex));
	}

	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, rectVertex.size() / 3,
		rectVertex.begin()._Ptr, sizeof(Vertex));
}
