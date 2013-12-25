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

	FT_Library library;

	if (FT_Init_FreeType( &library )) 
	{
		throw std::runtime_error("FT_Init_FreeType failed");
		return false;
	}

	FT_Face face;
	if (FT_New_Face( library, filename, 0, &face )) 
	{
		throw std::runtime_error("FT_New_Face failed (there is probably a problem with your font file)");
		return false;
	}
	// По некоторым причинам FreeType измеряет размер шрифта в терминах 1/64 пикселя.
	// Таким образом, для того чтобы сделать шрифт выстой size пикселей, мы запрашиваем размер size*64.
	// (size << 6 тоже самое что и size*64)
	FT_Set_Char_Size( face, int(size) << 6, int(size) << 6, 96, 96);

	textureAtlas.Create(textureAtlasSizeX,textureAtlasSizeY);

	for(short i=0;i<GLYPHCOUNT;i++)
		MakeFontAtlas(face,i);

	FT_Done_Face(face);
	FT_Done_FreeType(library);

	TextureManager tm;
	glyphs->textureId = tm.LoadImageFromSurface(textureAtlas.GetAtlas(), false);

	return true;
}

void Font::Cleanup()
{
	textureAtlas.Remove();
}

void Font::MakeFontAtlas ( FT_Face face, unsigned char ch) 
{
	if(FT_Load_Glyph( face, FT_Get_Char_Index( face, ch ), FT_LOAD_DEFAULT ))
		throw std::runtime_error("FT_Load_Glyph failed");

	FT_Glyph glyph;
	if(FT_Get_Glyph( face->glyph, &glyph ))
		throw std::runtime_error("FT_Get_Glyph failed");

	FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
	FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

	FT_Bitmap &bitmap=bitmap_glyph->bitmap;

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
	glyphs[ch].width = bitmap.width;
	glyphs[ch].height = bitmap.rows;
	glyphs[ch].offsetDown = bitmap_glyph->top-bitmap.rows;
	glyphs[ch].texture.u1 = double(x1) / textureAtlasSizeX;
	glyphs[ch].texture.v1 = double(y1 + bitmap.rows) / textureAtlasSizeY;
	glyphs[ch].texture.u2 = double(x1 + bitmap.width) / textureAtlasSizeX;
	glyphs[ch].texture.v2 = double(y1) / textureAtlasSizeY;

	SDL_FreeSurface(surface);
}

void Font::Print(float x, float y, string str)  
{			
	// Сделаем высоту немного больше, что бы оставить место между линиями.
	float fsize=this->size/.63f;		

	vector<string> lines;
	string allow; //переменная, для выделения слов из прописи
	int i=0; //позиция в прописи
	int length = str.length();
	while( i < length ) //пока есть символы в прописи
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

	glBindTexture(GL_TEXTURE_2D, glyphs->textureId);

	float modelview_matrix[16];	
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);

	glTranslatef(0.5, 0.5, 0.0);

	for(int i=0;i<lines.size();i++) 
	{
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(x,y-fsize*i,0);
		glMultMatrixf(modelview_matrix);
		const unsigned char *s1 = reinterpret_cast<const unsigned char *> (lines[i].c_str());

		for (int j = 0; j < lines[i].length(); j++)
		{
			if(s1[j] == ' ')
			{
				glTranslatef(glyphs['8'].width,0,0);
			}
			double u1 = glyphs[s1[j]].texture.u1;
			double v1 = glyphs[s1[j]].texture.v1;
			double u2 = glyphs[s1[j]].texture.u2;
			double v2 = glyphs[s1[j]].texture.v2;

			int x1 = 0;
			int y1 = glyphs[s1[j]].offsetDown;
			int x2 = glyphs[s1[j]].width;
			int y2 = glyphs[s1[j]].height + glyphs[s1[j]].offsetDown;

			glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2d(u1,v1); glVertex2f(x1, y1);
				glTexCoord2d(u1,v2); glVertex2f(x1, y2);
				glTexCoord2d(u2,v1); glVertex2f(x2, y1);
				glTexCoord2d(u2,v2); glVertex2f(x2, y2);
			glEnd();

			glTranslatef(x2,0,0);
		}

		glPopMatrix();
	}
	glTranslatef(-0.5, -0.5, 0.0);
	glPopAttrib();		
}

Rect &Font::GetBoundBox(string str)
{
	float fsize=size/.63f;

	Rect rect;
	rect.w = 0;
	rect.h = 0;
	rect.x = 0;
	rect.y = 0;	

	int stringLenght = 0;
	int stringOffsetUp = 0;
	int stringOffsetDown = 0;
	for(int i=0; i < str.length(); i++) 
	{
		unsigned char glyph = (unsigned char)(str[i]);

		if(glyph == '\n')
		{
			if(rect.w < stringLenght)
				rect.w = stringLenght;

			rect.h += fsize;
			stringLenght = 0;
			stringOffsetDown = 0;
			break;
		}

		if(glyph == ' ')
			stringLenght += glyphs['8'].width;
		else
			stringLenght += glyphs[glyph].width;

		if(rect.h == 0)
		{
			if(stringOffsetUp < glyphs[glyph].height)
				stringOffsetUp = glyphs[glyph].height;
		}

		if(stringOffsetDown > glyphs[glyph].offsetDown)
			stringOffsetDown = glyphs[glyph].offsetDown;
	}
	if(rect.w < stringLenght)
		rect.w = stringLenght;
	rect.h -= stringOffsetDown;
	rect.y = -rect.h;
	rect.h += stringOffsetUp;
	rect.w++;
	rect.h++;
	rect.x--;
	rect.y--;
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
