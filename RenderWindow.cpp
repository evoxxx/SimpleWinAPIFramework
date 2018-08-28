#include "RenderWindow.h"

void RenderWindow::SetWindowSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void RenderWindow::SetWindowPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

LRESULT CALLBACK RenderWindow::WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT Rect;

	switch (msg)
	{
	case WM_MOVE:
		GetWindowRect(hwnd, &Rect);
		SetWindowPosition(Rect.left, Rect.top);
		break;

	case WM_SIZE:
		GetClientRect(hwnd, &Rect);
		SetWindowSize(Rect.right - Rect.left, Rect.bottom - Rect.top);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, msg, wp, lp);
	}
	return 0;
}

LRESULT CALLBACK RenderWindow::WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	RenderWindow* Window = (RenderWindow*)(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	if (Window)
		return Window->WindowProc(hwnd, msg, wp, lp);

	return DefWindowProc(hwnd, msg, wp, lp);
}

RenderWindow::RenderWindow(LPCSTR classname)
{	
	m_instance = NULL;
	w_classname = classname;

	WNDCLASSEX w_class;
	w_class.cbSize = sizeof(WNDCLASSEX);
	w_class.cbClsExtra = 0;
	w_class.cbWndExtra = 0;
	w_class.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	w_class.hCursor = LoadCursor(NULL, IDC_ARROW);
	w_class.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	w_class.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	w_class.hInstance = m_instance;
	w_class.lpfnWndProc = (WNDPROC)WndProc;
	w_class.lpszClassName = w_classname;
	w_class.lpszMenuName = NULL;
	w_class.style = CS_VREDRAW | CS_HREDRAW;

	if (RegisterClassEx(&w_class))
		w_created = true;
}

RenderWindow::~RenderWindow()
{
	if (w_created)
	{
		if (m_window)
		{
			DestroyWindow(m_window);
			m_window = NULL;
		}
		UnregisterClass(w_classname, m_instance);
		m_instance = NULL;
		w_created = false;
	}
}

bool RenderWindow::Create(int width, int height, const char*title)
{
	if (!w_created)
		return false;

	this->width = width;
	this->height = height;
	this->title = title;

	RECT wr = { 0, 0, width, height };
	RECT sr = { 0 };

	GetWindowRect(GetDesktopWindow(), &sr);
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    

	x = sr.right / 2 - (width / 2);
	y = sr.bottom / 2 - (height / 2);

	m_window = CreateWindow(w_classname, title, WS_OVERLAPPEDWINDOW,x, y, wr.right - wr.left, wr.bottom - wr.top, NULL, NULL, m_instance, NULL);

	if (!m_window)
		return false;

	ShowWindow(m_window, SW_SHOW);
	SetWindowLongPtr(m_window, GWLP_USERDATA, (LONG)this);

	return true;
}

void RenderWindow::GetWindowMessage(MSG *message)
{
	if (PeekMessage(message, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(message);
		DispatchMessage(message);
	}
}

HWND RenderWindow::GetWindowHandler()
{
	return m_window;
}

HINSTANCE RenderWindow::GetHandleInstance()
{
	return m_instance;
}

bool RenderWindow::SetPos(int x, int y)
{
	this->x = x;
	this->y = y;

	if (!(SetWindowPos(m_window, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE)))
		return false;

	return true;
}

bool RenderWindow::SetSize(int width, int height)
{
	RECT wr = { 0, 0, width, height };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

	if (!(MoveWindow(m_window, x, y, wr.right - wr.left, wr.bottom - wr.top, true)))
		return false;

	return true;
}
