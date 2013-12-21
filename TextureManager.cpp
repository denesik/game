#include "TextureManager.h"
#include <SDL_Image.h>
#include <SDL_opengl.h>


TextureManager::TextureManager(void)
{
}


TextureManager::~TextureManager(void)
{
}

unsigned int TextureManager::AddFromFile(std::string fileName, std::string name)
{
	auto f= textureList.find(name);
	if(f != textureList.end())
		return 0;

	SDL_Surface *surface = IMG_Load(fileName.c_str());
	if(surface == nullptr)
	{
		throw std::runtime_error("IMG_Load failed (there is probably a problem with your font file)");
		return 0;
	}

	GLuint tex;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

	SDL_FreeSurface(surface);

	textureList[name] = tex;

	return 1;
}

int TextureManager::Get( std::string fontName )
{
	auto f= textureList.find(fontName);
	if(f == textureList.end())
		return 0;

	return (*f).second;
}

void TextureManager::Cleanup()
{
	for (auto i = textureList.begin(); i != textureList.end(); i++)
	{
		glDeleteTextures(1,&((*i).second));
	}
}
