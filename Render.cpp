#include "Render.h"
#include <SDL_opengl.h>
#include <GL\glu.h>
#include <iostream>

Render::Render()
{
	render = nullptr;
	window = nullptr;
	context = nullptr;
}


Render::~Render(void)
{
}

bool Render::Initialize(const char* _title, int _width, int _height, bool _fullScreen)
{
	title = _title;
	width = _width;
	height = _height;
	fullScreen = _fullScreen;

	if(!CreateGameWindow())
		return false;

	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (render == nullptr)
	{
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return false;
	}

	context = SDL_GL_CreateContext(window);

	return true;
}

bool Render::InitGL()
{
	GLfloat ratio;

	if ( height == 0 ) 
	{
		height = 1;
	}

	ratio = ( GLfloat )width / ( GLfloat )height;

	glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );

	gluPerspective( 45.0f, ratio, 0.1f, 100.0f );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	glShadeModel(GL_SMOOTH);							
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				
	glClearDepth(1.0f);									
	glEnable(GL_DEPTH_TEST);							
	glDepthFunc(GL_LEQUAL);								
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	return true;
}

void Render::Cleanup()
{
	SDL_GL_DeleteContext(context); 
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
}

bool Render::CreateGameWindow()
{
	Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
	if(fullScreen)
		flags |= SDL_WINDOW_FULLSCREEN;

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);

	if (window == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

bool Render::ResizeWindow(int _width, int _height)
{
	width = _width;
	height = _height;

	SDL_SetWindowSize(window, width, height);

	if(!InitGL())
		return false;

	return true;
}

void Render::SwapBuffers()
{
	SDL_GL_SwapWindow(window);
}

void Render::PushProjectionMatrix() 
{
	glPushAttrib(GL_TRANSFORM_BIT);
	GLint	viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(viewport[0],viewport[2],viewport[1],viewport[3]);
	glPopAttrib();
}

// Восстановить координаты матрицы проекции.
void Render::PopProjectionMatrix() 
{
	glPushAttrib(GL_TRANSFORM_BIT);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPopAttrib();
}