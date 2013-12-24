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

class Font
{
protected:
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

	float size;
	const char *filename;

public:
	Font(){};
	Font(const char *filename, unsigned int size);
	~Font(void);

	virtual void SetSize(unsigned int size);
	virtual bool Generate();
	virtual void Cleanup();

	virtual void print(float x, float y, std::string str);

	virtual int GetSize();

	virtual Rect &GetRect(std::string str);

private:
	virtual void MakeFontAtlas ( FT_Face face, unsigned char ch);

};


#endif // GameFont_h__