#ifndef Render_h__
#define Render_h__

#include "GameMath.h"
#include <SDL_render.h>
#include "TextureManager.h"

class Render
{
private:
	SDL_Renderer *render;
	SDL_Window *window;
	SDL_GLContext context;

	const char* title;
	int width;
	int height;
	bool fullScreen;

	TextureManager *textureManager;

public:
	Render(void);
	~Render(void);

	bool CreateGameWindow();
	bool ResizeWindow(int width, int height);

	bool Initialize(const char* title, int width, int height, bool fullScreen);
	void Cleanup();
	bool InitGL();

	void SetTextureManager(TextureManager *textureManager);
	TextureManager *GetTextureManager();

	void SwapBuffers();

	void PushProjectionMatrix(); 
	void PopProjectionMatrix(); 

	void DrawRectangle(Rectangle2i rectangle);
	void DrawQuad2D(Rectangle2i rectangle);
	void DrawQuad2D(int x1, int y1, int x2, int y2);
	void DrawQuad2D(Rectangle2i rectangle, Texture tex);
	void BindTexture(unsigned int textureId);
};

#endif // Render_h__

