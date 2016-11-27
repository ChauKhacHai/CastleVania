#include "CWindown.h"


CWindown::CWindown(HINSTANCE hInstance)
{
	this->hInstance = hInstance;
}

CWindown::CWindown(){
}


CWindown::~CWindown(void)
{
}
bool CWindown::initWindows(){
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = 0;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = NameClass;
	wcex.hIconSm = 0;
	RegisterClassEx(&wcex);
	hWnd = CreateWindow(NameClass,
		NameClass,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);
	if (!hWnd)
	{
		return false;
	}
	if (!SetWindowPos(hWnd, HWND_NOTOPMOST, 200, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SWP_SHOWWINDOW))
	{
		return false;
	}
	bool _show = false;
	while (!_show)
	{
		_show = ShowWindow(hWnd, SW_SHOW);
	}
	
	UpdateWindow(hWnd);
	return true;

}

HINSTANCE CWindown::gethInstance(){
	return this->hInstance;
}

HWND CWindown::getHandle(){
	return this->hWnd;
}



LRESULT CALLBACK CWindown::WndProc(HWND wnd, UINT mess, WPARAM wParam, LPARAM lParam)
{
	switch (mess)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	}
	return DefWindowProc(wnd, mess, wParam, lParam);
}


