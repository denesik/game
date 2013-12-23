#include "Font.h"
#include <gl/GLU.h>
#include <algorithm>
#include <SDL_surface.h>
#include <SDL_Image.h>
using namespace std;

Font::Font(const char *_filename, unsigned int _size)
{
	filename = _filename;
	size = _size;
}

Font::~Font(void)
{
}

bool Font::Generate()
{
	for(int i=0;i<GLYPHCOUNT;i++)
		glyphSize[i][0] = glyphSize[i][1] = glyphSize[i][2] = 0; 

	FT_Library library;
	textures = new GLuint[GLYPHCOUNT];

	if (FT_Init_FreeType( &library )) 
	{
		throw std::runtime_error("FT_Init_FreeType failed");
		return false;
	}
	FT_Face face;
	// �������� ����� �� �����. ���� ����� ������ �� ���������� ��� ����� �����,
	// �� ��������� ����� �������.
	if (FT_New_Face( library, filename, 0, &face )) 
	{
		throw std::runtime_error("FT_New_Face failed (there is probably a problem with your font file)");
		return false;
	}
	// �� ��������� �������� FreeType �������� ������ ������ � �������� 1/64 �������.
	// ����� �������, ��� ���� ����� ������� ����� ������ size ��������, �� ����������� ������ size*64.
	// (size << 6 ���� ����� ��� � size*64)
	FT_Set_Char_Size( face, int(size) << 6, int(size) << 6, 96, 96);

	listBase=glGenLists(GLYPHCOUNT);
	if(glGetError() == GL_INVALID_OPERATION)
	{
		throw std::runtime_error("glGenLists");
		return false;
	}
	glGenTextures( GLYPHCOUNT, textures );
	if(glGetError() == GL_INVALID_OPERATION)
	{
		throw std::runtime_error("glGenTextures");
		return false;
	}

	textureAtlas.Create(128,256);

	for(short i=0;i<GLYPHCOUNT;i++)
		MakeDlist(face,i);

	FT_Done_Face(face);
	FT_Done_FreeType(library);

	IMG_SavePNG(textureAtlas.GetAtlas(), "fontAtlas.png");

	return true;
}

void Font::Cleanup()
{
	glDeleteLists(listBase,GLYPHCOUNT);
	glDeleteTextures(GLYPHCOUNT,textures);
	delete [] textures;
}

//��� ������� ���������� ����� � ������� ���, �������, ��� ����� a
inline int Font::NextP2 ( int a )
{
	int rval=1;
	while(rval<a) rval<<=1;
	return rval;
}

// ������� ������ ����������� �� ���� ������� �������
void Font::MakeDlist ( FT_Face face, unsigned char ch) 
{
	//��������� ����� ��� ������� �������.
	if(FT_Load_Glyph( face, FT_Get_Char_Index( face, ch ), FT_LOAD_DEFAULT ))
		throw std::runtime_error("FT_Load_Glyph failed");

	//��������� ���� � ������.
	FT_Glyph glyph;
	if(FT_Get_Glyph( face->glyph, &glyph ))
		throw std::runtime_error("FT_Get_Glyph failed");

	//�������������� ���� � �����.
	FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
	FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

	FT_Bitmap &bitmap=bitmap_glyph->bitmap;

	int width = NextP2( bitmap.width );
	int height = NextP2( bitmap.rows );

	GLubyte* expanded_data = new GLubyte[ 2 * width * height];

	//����������� ������������� ����� (���� ��� ������ ������� � ���� ��� �����)
	for(int j=0; j <height;j++) 
	{
		for(int i=0; i < width; i++)
		{
			expanded_data[2 * (i + j * width)] = 255;
			expanded_data[2 * (i + j * width) + 1] = 
				(i >= bitmap.width || j >= bitmap.rows) ? 0 : bitmap.buffer[i + bitmap.width * j];
		}
	}

	Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	SDL_Surface *surface = SDL_CreateRGBSurface(0,bitmap.width,bitmap.rows,32,rmask,gmask,bmask,amask);
	for(int j=0; j <bitmap.rows;j++) 
	{
		for(int i=0; i < bitmap.width; i++)
		{
			((GLubyte*)(surface->pixels))[4 * (i + j * bitmap.width) + 0] = 255;
			((GLubyte*)(surface->pixels))[4 * (i + j * bitmap.width) + 1] = 255;
			((GLubyte*)(surface->pixels))[4 * (i + j * bitmap.width) + 2] = 255;
			((GLubyte*)(surface->pixels))[4 * (i + j * bitmap.width) + 3] = bitmap.buffer[i + bitmap.width * j];
		}
	}
	unsigned int x1, y1;
	textureAtlas.InsertSurface(surface, x1, y1);
	SDL_FreeSurface(surface);

	glBindTexture( GL_TEXTURE_2D, textures[ch]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height,
		0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expanded_data );
	delete [] expanded_data;

	glNewList(listBase+ch,GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D,textures[ch]);

	glPushMatrix();

	// ������� �� ������� ������ ������ �� ���������� ����� ��� � �������� �� ����.
	glTranslatef(bitmap_glyph->left,0,0);

	// ������� ���� � ��� ������, ���� ����� ������ ���� ������.
	// ��� ������� ������ ��� ��������, ����� ��� 'g' ��� 'y'.
	glTranslatef(0,bitmap_glyph->top-bitmap.rows,0);

	// �������� ����� ����� ����� �������� ����� ��������� ������ �������������.
	// �� ������ ������ �� ����� ��������, � ������� ��������� ������, � ���������
	// ���������� � ���������� x � y, �����, ����� �� ������ ���������������,
	// �� ����� ������ ��������� �� �� ����� ��������, � ������� ���������������
	// ���������� ������.
	float	x=(float)bitmap.width / (float)width,
		y=(float)bitmap.rows / (float)height;

	glBegin(GL_QUADS);
		glTexCoord2d(0,0); glVertex2f(0,bitmap.rows);
		glTexCoord2d(0,y); glVertex2f(0,0);
		glTexCoord2d(x,y); glVertex2f(bitmap.width,0);
		glTexCoord2d(x,0); glVertex2f(bitmap.width,bitmap.rows);
	glEnd();
	glPopMatrix();
	glTranslatef(face->glyph->advance.x >> 6 ,0,0);

	// ��������� ������� �������.
	glyphSize[ch][0] = bitmap_glyph->left + face->glyph->advance.x >> 6;	// �������� ������
	glyphSize[ch][1] = bitmap_glyph->top-bitmap.rows;						// �������� ����
	glyphSize[ch][2] = bitmap.rows;
	// ����������� ������� ������, ��� ���� �� ��� ��� ��������� �����.
	// (���������� ������, ���� �� ������ ��������� ����� ������)
	//glBitmap(0,0,0,0,face->glyph->advance.x >> 6,0,NULL);

	glEndList();
}

/*
void Font::print(float x, float y, const char *fmt, ...)  
{
	// �� ����� ������� ���������, � ������� ���������� ���������� � ��������.
	PushScreenCoordinateMatrix();					

	float fsize=this->size/.63f;						// ������� ������ ������� ������, ��� �� �������� ����� ����� �������.

	char		text[256];								
	va_list		ap;										// ��������� �� ���� ����������

	if (fmt == NULL)									
		*text=0;										
	else 
	{					// ������ ������, ���������� � std::string
		va_start(ap, fmt);								// Parses The String For Variables
		vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
		va_end(ap);										// Results Are Stored In Text
	}
	// �������� ����� �� ������.
	const char *start_line=text;
	vector<string> lines;
	const char *c;
	for(c=text;*c;c++) 
	{
		if(*c=='\n') 
		{
			string line;
			for(const char *n=start_line;n<c;n++) line.append(1,*n);
			lines.push_back(line);
			start_line=c+1;
		}
	}
	if(start_line) 
	{
		string line;
		for(const char *n=start_line;n<c;n++) line.append(1,*n);
		lines.push_back(line);
	}

	glPushAttrib(GL_LIST_BIT | GL_CURRENT_BIT  | GL_ENABLE_BIT | GL_TRANSFORM_BIT);	
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	

	glListBase(listBase);

	float modelview_matrix[16];	
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);

	// �� ������ ������� �� ���������� ������� ���� ������
	// ������� ������ ����� ���������� � ���������� �������.
	// ������, ��� ����� ���� ������ �� ������ ���� �� size, ��������� ����� ������
	// ������ �������� � ��� ������������ ������� �������, ������� ���������
	// ������ ����� ��������� ����� ����� ����. 
	for(int i=0;i<lines.size();i++) 
	{
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(x,y-fsize*i,0);
		glMultMatrixf(modelview_matrix);
		glCallLists(lines[i].length(), GL_UNSIGNED_BYTE, lines[i].c_str());
		glPopMatrix();
	}

	glPopAttrib();		
	Pop_projection_matrix();
}
*/

void Font::print(float x, float y, string str)  
{				

	// ������� ������ ������� ������, ��� �� �������� ����� ����� �������.
	float fsize=this->size/.63f;		

	vector<string> lines;
	string allow; //����������, ��� ��������� ���� �� �������
	int i=0; //������� � �������
	int length = str.length();
	while( i < length ) //���� ���� ������� � �������
	{ 
		while(i < length && str[i] != '\n')
		{
			allow+=str[i];
			i++;
		}
		i++;
		lines.push_back(allow);
		allow.clear();
	}

	glPushAttrib(GL_LIST_BIT | GL_CURRENT_BIT  | GL_ENABLE_BIT | GL_TRANSFORM_BIT);	
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	

	glListBase(listBase);

	float modelview_matrix[16];	
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);

	// �� ������ ������� �� ���������� ������� ���� ������
	// ������� ������ ����� ���������� � ���������� �������.
	// ������, ��� ����� ���� ������ �� ������ ���� �� size, ��������� ����� ������
	// ������ �������� � ��� ������������ ������� �������, ������� ���������
	// ������ ����� ��������� ����� ����� ����. 
	for(int i=0;i<lines.size();i++) 
	{
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(x,y-fsize*i,0);
		glMultMatrixf(modelview_matrix);
		const unsigned char *s1 = reinterpret_cast<const unsigned char *> (lines[i].c_str());
		glCallLists(lines[i].length(), GL_UNSIGNED_BYTE, s1);
		glPopMatrix();
	}

	glPopAttrib();		
}

Rect &Font::GetRect(string str)
{
	float fsize=this->size/.63f;

	Rect rect;
	rect.w = 0;
	rect.h = 0;
	rect.x = 0;
	rect.y = 0;

	int lineSize;
	int lineCount = 0;

	int lineWidth = 0;
	int lineDown = 0;

	int i=0;
	int length = str.length();
	const unsigned char *str_c = reinterpret_cast<const unsigned char *> (str.c_str());
	while( i < length )
	{ 
		lineSize = 0;
		lineDown = 0;
		lineCount++;
		while(i < length && str_c[i] != '\n')
		{
			lineSize += glyphSize[str_c[i]][0];

			if(lineCount == 1)
			{
				//������ ������ ������ ������
				if(lineWidth < glyphSize[str_c[i]][2])
					lineWidth = glyphSize[str_c[i]][2];
			}
			// ������ �������� ����
			if(lineDown > glyphSize[str_c[i]][1])
				lineDown = glyphSize[str_c[i]][1];

			i++;
		}

		if (rect.w < lineSize)	// ����� ������������ ����� ������
			rect.w = lineSize;
		i++;
	}

	if(lineCount <= 0)
		return rect;
	lineCount -= 1;

	rect.y += lineDown;	// ��������� ������
	rect.h -= lineDown; // 

	rect.y -= lineCount*fsize;
	rect.h += lineCount*fsize;

	rect.h += lineWidth; // ���������� ������ ������ ������

	rect.y -= 2;
	rect.h += 3;
	rect.x -= 1;
	rect.w += 3;

	return rect;
}

int Font::GetSize()
{
	return size;
}

void Font::SetSize( unsigned int _size )
{
	size = _size;
}
