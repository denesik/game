#include "Render.h"
#include <SDL_opengl.h>
#include <GL\glu.h>
#include <iostream>
#include "Logger.h"

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
	{
		return false;
	}

	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (render == nullptr)
	{
		LOG(LOG_ERROR, "Render. SDL. ������ �������� �������.");
		return false;
	}

	context = SDL_GL_CreateContext(window);

	InitGL();

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

	glEnable(GL_TEXTURE_2D);

	return true;
}

void Render::Finalize()
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
		LOG(LOG_ERROR, "Render. SDL. ���� �� �������");
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

// ������������ ���������� ������� ��������.
void Render::PopProjectionMatrix() 
{
	
	glPushAttrib(GL_TRANSFORM_BIT);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPopAttrib();
}

void Render::DrawRectangle(Rectangle2i rectangle)
{
	glBegin(GL_LINES);
		glVertex2i(rectangle.x, rectangle.y);						//��� ����
		glVertex2i(rectangle.x + rectangle.w, rectangle.y);			//��� �����

		glVertex2i(rectangle.x + rectangle.w, rectangle.y);		 
		glVertex2i(rectangle.x + rectangle.w, rectangle.y + rectangle.h);//����� ����

		glVertex2i(rectangle.x + rectangle.w, rectangle.y + rectangle.h);//����� ����
		glVertex2i(rectangle.x, rectangle.y + rectangle.h);			//���� ����

		glVertex2i(rectangle.x, rectangle.y + rectangle.h);			//���� ����
		glVertex2i(rectangle.x, rectangle.y);						//��� ����
	glEnd();
}

void Render::SetTextureManager( TextureManager *_textureManager )
{
	textureManager = _textureManager;
}

TextureManager * Render::GetTextureManager()
{
	return textureManager;
}

void Render::DrawQuad2D(Rectangle2i rectangle )
{
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2i(0,0); glVertex2i(rectangle.x,rectangle.y);
		glTexCoord2i(0,1); glVertex2i(rectangle.x,rectangle.y + rectangle.h);
		glTexCoord2i(1,0); glVertex2i(rectangle.x + rectangle.w,rectangle.y);
		glTexCoord2i(1,1); glVertex2i(rectangle.x + rectangle.w,rectangle.y + rectangle.h);
	glEnd();
}

void Render::DrawQuad2D(int x1, int y1, int x2, int y2)
{
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2i(0,0); glVertex2i(x1,y1);
		glTexCoord2i(0,1); glVertex2i(x1,y2);
		glTexCoord2i(1,0); glVertex2i(x2,y1);
		glTexCoord2i(1,1); glVertex2i(x2,y2);
	glEnd();
}

void Render::DrawQuad2D(Rectangle2i rectangle, Texture tex)
{
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2d(tex.u1,tex.v1); glVertex2i(rectangle.x,rectangle.y);
		glTexCoord2d(tex.u1,tex.v2); glVertex2i(rectangle.x,rectangle.y + rectangle.h);
		glTexCoord2d(tex.u2,tex.v1); glVertex2i(rectangle.x + rectangle.w,rectangle.y);
		glTexCoord2d(tex.u2,tex.v2); glVertex2i(rectangle.x + rectangle.w,rectangle.y + rectangle.h);
	glEnd();
}

void Render::BindTexture( unsigned int textureId )
{
	glBindTexture(GL_TEXTURE_2D, textureId);
}
