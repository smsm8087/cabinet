#pragma once
class cMaingame
{
private:
	struct Vertex
	{
		D3DXVECTOR4 position;
		DWORD color;
		int m_nState;
	};
	vector<Vertex*> m_vecVertex;
	vector<Vertex*>::iterator m_itervertex;
	POINT m_ptstart, m_ptfinish;
	int m_ndrawstate;
	DWORD drawcolor;
public:
	cMaingame();
	~cMaingame();

	void Init();
	void Update();
	void Render(LPDIRECT3DDEVICE9 device);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

