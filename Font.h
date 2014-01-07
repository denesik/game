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
#include "TextureAtlas.h"
#include "TextureManager.h"

class IFont
{
protected:

	std::string filename;
	std::string fontName;

public:
	IFont(){};
	~IFont(void){};

	virtual std::string GetFontName();

	virtual bool Initialize() = 0;
	virtual bool Generate() = 0;
	virtual void UnloadContent() = 0;

	virtual void Print(float x, float y, std::string str) = 0;

	virtual Rectangle2i GetBoundBox(std::string str) = 0;

};

class FontTTF : public IFont
{
protected:

	FT_Library library;

	TextureAtlas textureAtlas;

	static const short GLYPHCOUNT = 256;
	static const short textureAtlasSizeX = 512;
	static const short textureAtlasSizeY = 512;

	struct FontTexture
	{
		unsigned int textureId;
		Texture texture;
		int width;
		int height;
		int offsetDown;
	};

	FontTexture glyphs[GLYPHCOUNT];

	unsigned int size;
	float fsize;

public:
	FontTTF(){};
	FontTTF(std::string filename, std::string fontName, unsigned int size);
	~FontTTF(void);

	virtual bool Initialize();
	virtual bool Generate();
	virtual void UnloadContent();

	virtual void Print(float x, float y, std::string str);

	virtual Rectangle2i GetBoundBox(std::string str);

protected:
	void MakeFontAtlas ( FT_Face face, unsigned char ch);

};

#endif // GameFont_h__