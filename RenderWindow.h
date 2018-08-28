#pragma once

#ifdef _WIN32 || _WIN64
#include <Windows.h>
#endif

class RenderWindow
{
	private:

		/* WinApi Handles */

		HWND			m_window;
		HINSTANCE		m_instance;
		LPCSTR			w_classname;

		/* Check Creating Window */

		bool			w_created;

		/* Window Settings */

		int				width, height;
		const char*		title;

		/* WNDPROC In Class */

		static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
		LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

		void SetWindowSize(int width, int height);
		void SetWindowPosition(int x, int y);

	public:

		int				x, y;

		RenderWindow(LPCSTR			classname ="WindowClass");
		~RenderWindow();

		bool Create(int width, int height, const char*title);
		bool SetPos(int x, int y);
		bool SetSize(int width, int height);

		void GetWindowMessage(MSG *message);

		HWND GetWindowHandler();
		HINSTANCE GetHandleInstance();
};

