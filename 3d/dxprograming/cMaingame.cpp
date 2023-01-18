#include "stdafx.h"
#include "cMaingame.h"


cMaingame::cMaingame()
{
}


cMaingame::~cMaingame()
{
}

void cMaingame::Init()
{
	m_ndrawstate = E_NONE;
}

void cMaingame::Update()
{
	if (GetAsyncKeyState(VK_F1) & 0X8000)
	{
		drawcolor = 0xffff0000;
	}
	if (GetAsyncKeyState(VK_F2) & 0X8000)
	{
		drawcolor = 0xff0000ff;
	}
	if (GetAsyncKeyState(VK_F3) & 0X8000)
	{
		drawcolor = 0xff00ffff;
	}
	if (GetAsyncKeyState(0x31) & 0X8000)//1누를때
	{
		m_ndrawstate = E_LINE;
	}
	if (GetAsyncKeyState(0x32) & 0X8000)//2누를때
	{
		m_ndrawstate = E_TRIANGLE;
	}
	if (GetAsyncKeyState(0x33) & 0X8000)//3누를때
	{
		m_ndrawstate = E_RECTANGLE;
	}
}

void cMaingame::Render(LPDIRECT3DDEVICE9 device)
{
	for (int i = 1; i < m_vecVertex.size(); i+=2)
	{
		if (m_vecVertex[i]->m_nState == E_LINE)
		{
			Vertex* temp = new Vertex[2];
			temp[0].position = m_vecVertex[i - 1]->position;
			temp[0].color = m_vecVertex[i - 1]->color;
			temp[1].position = m_vecVertex[i]->position;
			temp[1].color = m_vecVertex[i]->color;
			device->DrawPrimitiveUP(D3DPT_LINELIST, 1, temp/*&m_vecVertex[0]*/, sizeof(Vertex));
		}
		if (m_vecVertex[i]->m_nState == E_TRIANGLE)
		{
			Vertex* temp = new Vertex[3];
			if (m_vecVertex[i - 1]->position.x < m_vecVertex[i]->position.x)//오른쪽아래 드래그
			{
				if (m_vecVertex[i - 1]->position.y < m_vecVertex[i]->position.y)
				{
					temp[0].position = m_vecVertex[i - 1]->position;
					temp[0].color = m_vecVertex[i - 1]->color;
					temp[1].position = m_vecVertex[i]->position;
					temp[1].color = m_vecVertex[i]->color;
					temp[2].position = { m_vecVertex[i - 1]->position.x,m_vecVertex[i]->position.y,0,1 };
					temp[2].color = m_vecVertex[i]->color;
					device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, temp, sizeof(Vertex));
				}
				//오른쪽 위
				else
				{
					temp[0].position = m_vecVertex[i - 1]->position;
					temp[0].color = m_vecVertex[i - 1]->color;
					temp[2].position = m_vecVertex[i]->position;
					temp[2].color = m_vecVertex[i]->color;
					temp[1].position = { m_vecVertex[i - 1]->position.x,m_vecVertex[i]->position.y,0,1 };
					temp[1].color = m_vecVertex[i]->color;
					device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, temp, sizeof(Vertex));
				}
			}
			else
			{
				//왼쪽아래로 드래그
				if (m_vecVertex[i - 1]->position.y < m_vecVertex[i]->position.y)
				{
					temp[0].position = m_vecVertex[i - 1]->position;
					temp[0].color = m_vecVertex[i - 1]->color;
					temp[1].position = { m_vecVertex[i - 1]->position.x,m_vecVertex[i]->position.y,0,1 };
					temp[1].color = m_vecVertex[i]->color;
					temp[2].position = m_vecVertex[i]->position;
					temp[2].color = m_vecVertex[i]->color;
					device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, temp, sizeof(Vertex));
				}
				//왼쪽위로 드래그
				else
				{
					temp[0].position = m_vecVertex[i - 1]->position;
					temp[0].color = m_vecVertex[i - 1]->color;
					temp[2].position = { m_vecVertex[i - 1]->position.x,m_vecVertex[i]->position.y,0,1 };
					temp[2].color = m_vecVertex[i]->color;
					temp[1].position = m_vecVertex[i]->position;
					temp[1].color = m_vecVertex[i]->color;
					device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, temp, sizeof(Vertex));
				}
				
			}
		}
		if (m_vecVertex[i]->m_nState == E_RECTANGLE)
		{
			Vertex* temp = new Vertex[4];
			//오른쪽드래그
			if (m_vecVertex[i - 1]->position.x < m_vecVertex[i]->position.x)
			{
				//오른쪽아래
				if (m_vecVertex[i - 1]->position.y < m_vecVertex[i]->position.y)
				{
					temp[0].position = m_vecVertex[i - 1]->position;
					temp[0].color = m_vecVertex[i - 1]->color;
					temp[1].position = m_vecVertex[i]->position;
					temp[1].color = m_vecVertex[i]->color;
					temp[2].position = { m_vecVertex[i - 1]->position.x,m_vecVertex[i]->position.y,0,1 };
					temp[2].color = m_vecVertex[i]->color;
					device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, temp, sizeof(Vertex));

					Vertex* temp2 = new Vertex[4];
					temp2[0] = temp[0];
					temp2[1].position = { m_vecVertex[i]->position.x, m_vecVertex[i - 1]->position.y,0,1 };
					temp2[1].color = m_vecVertex[i]->color;
					temp2[2] = temp[1];
					device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, temp2, sizeof(Vertex));
				}
				//오른쪽위
				else
				{
					temp[0].position = m_vecVertex[i - 1]->position;
					temp[0].color = m_vecVertex[i - 1]->color;
					temp[1].position = m_vecVertex[i]->position;
					temp[1].color = m_vecVertex[i]->color;
					temp[2].position = { m_vecVertex[i]->position.x,m_vecVertex[i-1]->position.y,0,1 };
					temp[2].color = m_vecVertex[i]->color;
					device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, temp, sizeof(Vertex));

					Vertex* temp2 = new Vertex[4];
					temp2[0] = temp[0];
					temp2[1].position = { m_vecVertex[i-1]->position.x, m_vecVertex[i]->position.y,0,1 };
					temp2[1].color = m_vecVertex[i]->color;
					temp2[2] = temp[1];
					device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, temp2, sizeof(Vertex));
				}
				
			}
			//왼쪽드래그
			else
			{
				//왼쪽아래
				if (m_vecVertex[i - 1]->position.y < m_vecVertex[i]->position.y)
				{
					temp[0].position = m_vecVertex[i - 1]->position;
					temp[0].color = m_vecVertex[i - 1]->color;
					temp[1].position = { m_vecVertex[i - 1]->position.x,m_vecVertex[i]->position.y,0,1 };
					temp[1].color = m_vecVertex[i]->color;
					temp[2].position = m_vecVertex[i]->position;
					temp[2].color = m_vecVertex[i]->color;
					device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, temp, sizeof(Vertex));

					Vertex* temp2 = new Vertex[4];
					temp2[0] = temp[0];
					temp2[1] = temp[2];
					temp2[2].position = { m_vecVertex[i]->position.x, m_vecVertex[i - 1]->position.y,0,1 };
					temp2[2].color = m_vecVertex[i]->color;
					device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, temp2, sizeof(Vertex));
				}
				//왼쪽위
				else
				{
					temp[0].position = m_vecVertex[i - 1]->position;
					temp[0].color = m_vecVertex[i - 1]->color;
					temp[1].position = { m_vecVertex[i]->position.x,m_vecVertex[i-1]->position.y,0,1 };
					temp[1].color = m_vecVertex[i]->color;
					temp[2].position = m_vecVertex[i]->position;
					temp[2].color = m_vecVertex[i]->color;
					device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, temp, sizeof(Vertex));

					Vertex* temp2 = new Vertex[4];
					temp2[0] = temp[0];
					temp2[1] = temp[2];
					temp2[2].position = { m_vecVertex[i-1]->position.x, m_vecVertex[i]->position.y,0,1 };
					temp2[2].color = m_vecVertex[i]->color;
					device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, temp2, sizeof(Vertex));
				}
			}
		}
	}
}

void cMaingame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		m_ptstart.x = LOWORD(lParam);
		m_ptstart.y = HIWORD(lParam);
		float x, y;
		x = (float)m_ptstart.x;
		y = (float)m_ptstart.y;

		Vertex* vertex = new Vertex;

		vertex->position = {x,y,0,1 };
		vertex->m_nState = m_ndrawstate;
		vertex->color = drawcolor;
		m_vecVertex.push_back(vertex);
		
	}break;
	case WM_MOUSEMOVE:
	{
		m_ptfinish.x = LOWORD(lParam);
		m_ptfinish.y = HIWORD(lParam);
		
	}break;
	case WM_LBUTTONUP:
	{
		float x, y;
		x = (float)m_ptfinish.x;
		y = (float)m_ptfinish.y;

		Vertex* vertex = new Vertex;
		vertex->position = { x,y,0,1 };
		vertex->m_nState = m_ndrawstate;
		vertex->color = drawcolor;
		m_vecVertex.push_back(vertex);
	}break;
	default:
		break;
	}
}
