#include "Block.h"
#include <SDL_opengl.h>


Block::Block(void)
{
}


Block::~Block(void)
{
}

void Block::Draw( Render *render )
{

	glLoadIdentity();
	glTranslatef(1.5f,0.0f,-7.0f);          // Сдвинуть вправо и вглубь экрана
	//glRotatef(rquad,1.0f,1.0f,1.0f);        // Вращение куба по X, Y & Z
	glBegin(GL_QUADS);                      // Рисуем куб

		glColor3f(0.0f,1.0f,0.0f);              // Синий
		glVertex3f( 1.0f, 1.0f,-1.0f);          // Право верх квадрата (Верх)
		glVertex3f(-1.0f, 1.0f,-1.0f);          // Лево верх
		glVertex3f(-1.0f, 1.0f, 1.0f);          // Лево низ
		glVertex3f( 1.0f, 1.0f, 1.0f);          // Право низ

		glColor3f(1.0f,0.5f,0.0f);              // Оранжевый
		glVertex3f( 1.0f,-1.0f, 1.0f);          // Верх право квадрата (Низ)
		glVertex3f(-1.0f,-1.0f, 1.0f);          // Верх лево
		glVertex3f(-1.0f,-1.0f,-1.0f);          // Низ лево
		glVertex3f( 1.0f,-1.0f,-1.0f);          // Низ право

		glColor3f(1.0f,0.0f,0.0f);              // Красный
		glVertex3f( 1.0f, 1.0f, 1.0f);          // Верх право квадрата (Перед)
		glVertex3f(-1.0f, 1.0f, 1.0f);          // Верх лево
		glVertex3f(-1.0f,-1.0f, 1.0f);          // Низ лево
		glVertex3f( 1.0f,-1.0f, 1.0f);          // Низ право

		glColor3f(1.0f,1.0f,0.0f);              // Желтый
		glVertex3f( 1.0f,-1.0f,-1.0f);          // Верх право квадрата (Зад)
		glVertex3f(-1.0f,-1.0f,-1.0f);          // Верх лево
		glVertex3f(-1.0f, 1.0f,-1.0f);          // Низ лево
		glVertex3f( 1.0f, 1.0f,-1.0f);          // Низ право

		glColor3f(0.0f,0.0f,1.0f);              // Синий
		glVertex3f(-1.0f, 1.0f, 1.0f);          // Верх право квадрата (Лево)
		glVertex3f(-1.0f, 1.0f,-1.0f);          // Верх лево
		glVertex3f(-1.0f,-1.0f,-1.0f);          // Низ лево
		glVertex3f(-1.0f,-1.0f, 1.0f);          // Низ право

		glColor3f(1.0f,0.0f,1.0f);              // Фиолетовый
		glVertex3f( 1.0f, 1.0f,-1.0f);          // Верх право квадрата (Право)
		glVertex3f( 1.0f, 1.0f, 1.0f);          // Верх лево
		glVertex3f( 1.0f,-1.0f, 1.0f);          // Низ лево
		glVertex3f( 1.0f,-1.0f,-1.0f);          // Низ право

	glEnd();   

}
