#ifndef Render_h__
#define Render_h__

#include "GameMath.h"
#include <SDL_render.h>

class Render
{
protected:
	SDL_Renderer *render;
	SDL_Window *window;
	SDL_GLContext context;

	const char* title;
	int width;
	int height;
	bool fullScreen;

public:
	Render(void);
	~Render(void);

	bool CreateGameWindow();
	bool ResizeWindow(int width, int height);

	bool Initialize(const char* title, int width, int height, bool fullScreen);
	void Cleanup();
	bool InitGL();

	void SwapBuffers();

	void PushProjectionMatrix(); 
	void PopProjectionMatrix(); 
};

#endif // Render_h__

