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
	glTranslatef(1.5f,0.0f,-7.0f);          // �������� ������ � ������ ������
	//glRotatef(rquad,1.0f,1.0f,1.0f);        // �������� ���� �� X, Y & Z
	glBegin(GL_QUADS);                      // ������ ���

		glColor3f(0.0f,1.0f,0.0f);              // �����
		glVertex3f( 1.0f, 1.0f,-1.0f);          // ����� ���� �������� (����)
		glVertex3f(-1.0f, 1.0f,-1.0f);          // ���� ����
		glVertex3f(-1.0f, 1.0f, 1.0f);          // ���� ���
		glVertex3f( 1.0f, 1.0f, 1.0f);          // ����� ���

		glColor3f(1.0f,0.5f,0.0f);              // ���������
		glVertex3f( 1.0f,-1.0f, 1.0f);          // ���� ����� �������� (���)
		glVertex3f(-1.0f,-1.0f, 1.0f);          // ���� ����
		glVertex3f(-1.0f,-1.0f,-1.0f);          // ��� ����
		glVertex3f( 1.0f,-1.0f,-1.0f);          // ��� �����

		glColor3f(1.0f,0.0f,0.0f);              // �������
		glVertex3f( 1.0f, 1.0f, 1.0f);          // ���� ����� �������� (�����)
		glVertex3f(-1.0f, 1.0f, 1.0f);          // ���� ����
		glVertex3f(-1.0f,-1.0f, 1.0f);          // ��� ����
		glVertex3f( 1.0f,-1.0f, 1.0f);          // ��� �����

		glColor3f(1.0f,1.0f,0.0f);              // ������
		glVertex3f( 1.0f,-1.0f,-1.0f);          // ���� ����� �������� (���)
		glVertex3f(-1.0f,-1.0f,-1.0f);          // ���� ����
		glVertex3f(-1.0f, 1.0f,-1.0f);          // ��� ����
		glVertex3f( 1.0f, 1.0f,-1.0f);          // ��� �����

		glColor3f(0.0f,0.0f,1.0f);              // �����
		glVertex3f(-1.0f, 1.0f, 1.0f);          // ���� ����� �������� (����)
		glVertex3f(-1.0f, 1.0f,-1.0f);          // ���� ����
		glVertex3f(-1.0f,-1.0f,-1.0f);          // ��� ����
		glVertex3f(-1.0f,-1.0f, 1.0f);          // ��� �����

		glColor3f(1.0f,0.0f,1.0f);              // ����������
		glVertex3f( 1.0f, 1.0f,-1.0f);          // ���� ����� �������� (�����)
		glVertex3f( 1.0f, 1.0f, 1.0f);          // ���� ����
		glVertex3f( 1.0f,-1.0f, 1.0f);          // ��� ����
		glVertex3f( 1.0f,-1.0f,-1.0f);          // ��� �����

	glEnd();   

}
