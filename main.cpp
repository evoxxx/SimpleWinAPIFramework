#include "RenderWindow.h" /* including header */

#include <iostream> /* for printf */

void main() 
{
	/* Creating Renderer */
	RenderWindow Renderer;

	if (!(Renderer.Create(1024, 768, "Hello World")))
		printf("&: Error Creating the window");	

	MSG msg = { 0 }; 

	while (TRUE)
	{
		/* Getting the message */
		Renderer.GetWindowMessage(&msg);

		/* If the message recevie the "Closing Window" or Pressing ESC , destroy loop */
		if ((msg.message == WM_QUIT) || (msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE))
			break;
	}
}
