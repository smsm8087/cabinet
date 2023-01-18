// dxprograming.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "dxprograming.h"
#include"cMaingame.h"
#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWnd;
cMaingame*	g_Maingame;
// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DXPROGRAMING, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DXPROGRAMING));

    MSG msg;

	//시스템의 물리적 하드웨어 장치에 대한 정보를 얻는 객체
	LPDIRECT3D9 d3d;
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	
	//3D 그래픽을 디스플레이하는데 이용될 물리 하드웨어 장치를 
	//나타내는 c++ 객체
	LPDIRECT3DDEVICE9 device;
	//Device 객체의 성격을 결정하는데 이용
	D3DPRESENT_PARAMETERS param = {  };
	//윈도우 창크기 설정 트루는 창모드
	param.Windowed = TRUE;
	
	//더블버퍼링
	param.SwapEffect  = D3DSWAPEFFECT_DISCARD;
	//플리핑 체인의 버퍼가 교환되는 방법을 지정하는 
	//D3DWSWAPEFFECT열거형 멤버, DISCARD를 지정하는것이 가장 효과적이다.

	param.AutoDepthStencilFormat = D3DFMT_D16;
	//깊이 ,스텐실 버퍼의 포맷
	param.EnableAutoDepthStencil = TRUE;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		g_hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&param,
		&device
	);
	

	DWORD fvf = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;

	//VerTex(정점) : 3D공간에서의 점
	//fvf (Flexible Vertex Format) - 유연한 정점의 형식
	//정점의 포맷중 자신이 제작하는 프로그램에 알맞은 것들로
	//모아 새로운 포맷을 만드는 것

	//D3DFVF_XYZ : 3차원 좌표계의 정점 정보
	//D3DFVF_XYZRHW : 2차원 공간에서의 정점 좌표

	//동치변환 : 렌더링 파이프라인을 통해서 화면상의 뿌려지는 좌표로
	//변환하는 과정

	//w : 동치좌표의 네번째 성분
	//RHW :W 의 역수(1/w)
	
	//폴리곤(POLYGON) : 3D상에서 정점 세개가 모여 이루어진 단면
	//폴리곤은 앞면과 뒷면이 존재한다.
	//시계방향으로 정점의 순서에 따라서 앞면만 출력한다.


	
    // 기본 메시지 루프입니다.

	g_Maingame = new cMaingame();
	g_Maingame->Init();

    while (true)
    {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				if (g_Maingame)
				{
					delete g_Maingame;
					g_Maingame = nullptr;
					break;
				}
			}
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			//업데이트,렌더하는곳메인
			g_Maingame->Update();
			//device를 초기화하는 함수

			device->Clear(
				0,
				NULL,
				D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
				//소거할 대상 지정
				//target : 후면버퍼, zbuffer : 깊이
				0xffffffff,
				1.0f,
				0
			);
			device->BeginScene();//장면의 시작
			device->SetFVF(fvf);

			//RENDER()
			//점찍기
			//device->DrawPrimitiveUP(D3DPT_POINTLIST,1,vertex,sizeof(Vertex));
			//선그리기
			//device->DrawPrimitiveUP(D3DPT_LINESTRIP,3,vertex,sizeof(Vertex));
			//면그리기(삼각형)
			g_Maingame->Render(device);

			//device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(Vertex));


			device->EndScene();
			device->Present(NULL, NULL, NULL, NULL);
			//후면버퍼를 시연한다.

		}
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DXPROGRAMING));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DXPROGRAMING);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (g_Maingame)
		g_Maingame->WndProc(hWnd, message, wParam, lParam);
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
