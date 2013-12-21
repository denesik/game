#ifndef Font_h__
#define Font_h__

#include <SDL_opengl.h>

#include <ft2build.h>
#include <freetype.h>
#include <ftglyph.h>
#include <ftoutln.h>
#include <fttrigon.h>

#include <vector>
#include <string>

#include "GameMath.h"

class Font
{
protected:

	static const short GLYPHCOUNT = 256;

	float size;
	const char *filename;

	GLuint *textures;
	GLuint listBase;

	int glyphSize[GLYPHCOUNT][3];

public:
	Font(){};
	Font(const char *filename, unsigned int size);
	~Font(void);

	virtual void SetSize(unsigned int size);
	virtual bool Generate();
	virtual void Cleanup();

//	void print(float x, float y, const char *fmt, ...);
	virtual void print(float x, float y, std::string str);

	virtual int GetSize();

	virtual Rect &GetRect(std::string str);

private:
	virtual inline int NextP2 ( int a );
	virtual void MakeDlist ( FT_Face face, unsigned char ch);

};


#endif // GameFont_h__