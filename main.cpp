


#include "RenderWindow.h"

#include <iostream>

void main() 
{
	RenderWindow Renderer;

	if (!(Renderer.Create(1024, 768, "Hello World")))
		printf("&: Error Creating the window");	

	MSG msg = { 0 }; 

	while (TRUE)
	{
		Renderer.GetWindowMessage(&msg);

		if ((msg.message == WM_QUIT) || (msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE))
			break;
	}
}