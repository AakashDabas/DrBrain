#include<windows.h>
#include"engine.h"
#include"control.h"
#include"sound.h"
#include"timer.h"

#define xStart 100
#define yStart 100
float sizeX = 1, sizeY = 1;
static keys a;
int xWid, yWid,xlen,ylen;
char max = false;
timer t1,t2;
bool timeKey = false, tmp = false;
bool play = true;
int mod(int x)
{
	if (x >= 0)
		return x;
	else
		return (x*-1);
}
LRESULT CALLBACK winProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	RECT *loc = new RECT;   //structure for the coordinates of the window
	POINT *p = new POINT;
	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}break;
	case WM_KEYDOWN:
		for (int i = 0; i < 255; i++)     //Set all keys if pressed down
			if (wParam == i)
				a.onKey(i);
		break;
	case WM_KEYUP:
		for (int i = 0; i < 255; i++)     //Set all keys off if the key is up
			if (wParam == i)
				a.offKey(i);
		break;
	case WM_RBUTTONDOWN:    //Same as keyboard just this time manually
		a.rDown();
		break;
	case WM_RBUTTONUP:
		a.rUp();
		break;
	case WM_LBUTTONDOWN:
		a.lDown();
		break;
	case WM_LBUTTONUP:
		a.lUp();
		break;
	case WM_MBUTTONDOWN:
		a.mDown();
		break;
	case WM_MBUTTONUP:
		a.mUp();
		break;
	case WM_SETFOCUS:
		play = true;
		break;
	case WM_KILLFOCUS:
		play = false;
		break;
	case WM_MOUSEMOVE:
		if (wParam == SIZE_MAXIMIZED)
			max = true;
		else if (wParam == SIZE_RESTORED)
			max = false;
		GetWindowRect(hWnd, loc);
		loc->left += xWid;
		loc->right -= xWid;
		loc->top += yWid;
		loc->bottom -= xWid;
		GetCursorPos(p);
		//a.setxy((p->x-loc->left)*xlen/(loc->right-loc->left),(p->y-loc->top)*ylen/(loc->bottom-loc->top));
		a.setxy((p->x - loc->left), (p->y - loc->top));
		break;
		if (a.getx() >= xlen || a.getx() < 0 || a.gety() > ylen || a.gety() < 0)
			a.offWin();
		else
			a.onWin();
	}
	static int xtmp, ytmp;
	if (!tmp&&a.mKeyl())
	{
		xtmp = a.getx();
		ytmp = a.gety();
	}
	if (tmp&&!a.mKeyl() && mod(xtmp - a.getx()) <= 3 && mod(ytmp - a.gety()) <= 3)
	{
		a.cx = a.getx();
		a.cy = a.gety();
		a.leftClickOn();
	}
	tmp = a.mKeyl();
	if (a.getWin())
		a.lUp();
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

#pragma warning(suppress: 28251)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	WNDCLASSEX windowClass;
	windowClass.cbClsExtra = NULL;
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.cbWndExtra = NULL;
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(103), 1, 32, 32, 0);
	windowClass.hIconSm = NULL;
	windowClass.hInstance = hInstance;
	windowClass.lpfnWndProc = winProc;
	windowClass.lpszClassName = "Engine Window Class";
	windowClass.lpszMenuName = NULL;
	windowClass.style = CS_CLASSDC;
	RegisterClassEx(&windowClass);
	RECT adj;
	adj.left = xStart;
	adj.top = yStart;
	adj.right = xStart + 1920;
	adj.bottom = yStart + 1080;
	AdjustWindowRect(&adj, WS_CAPTION, FALSE);
	xWid = xStart - adj.left;
	yWid = yStart - adj.top;
	HWND hWnd = CreateWindowEx(NULL,
		(LPCTSTR)"Engine Window Class", "D R.  B R A I N  --  A GAME BY ENTANGLER",
		WS_OVERLAPPEDWINDOW,adj.left, adj.top, adj.right-adj.left, adj.bottom-adj.top,
		NULL, NULL, windowClass.hInstance, NULL);
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	RECT rect;
	GetWindowRect(hWnd, &rect);
	xlen = rect.left + rect.right;
	ylen = rect.bottom + rect.top-24;
	engine engine(hWnd,&a,xlen,ylen,sizeX,sizeY);
	ShowCursor(false);
	timer t;
	float fCntrl=33.3, fRend=0, fWait=0;
	bool ext = false;
	timer tC;
	while (msg.message != WM_QUIT&&!ext)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		if (t.ticTic(fWait)&&play)
		{
			t.start();
			ext=engine.launch();
			fRend = t.elapsed();
			t.reset();
		}
		if (!play&&engine.playG)
		{
			engine.gfxObject.BeginFrame(1);
			engine.pauseTimer();
			engine.snd.stopa();
			engine.snd.play(11,0);
			engine.paus = -1;
			engine.paused();
			engine.gfxObject.EndFrame();
		}
		t.start();
		fWait = fCntrl - fRend;
		if (fWait <= 0)
			fWait = 0;
		tC.start();
	}
	
	UnregisterClass("Engine Window Class", windowClass.hInstance);
	return 0;
}