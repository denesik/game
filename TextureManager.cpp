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

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

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

unsigned int TextureManager::LoadImageFromSurface( SDL_Surface *surface )
{
	if(surface == nullptr)
	{
		throw std::runtime_error("LoadImageFromSurface failed");
		return 0;
	}

	GLuint tex;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

	imageList[tex].width = surface->w;
	imageList[tex].height = surface->h;
	imageList[tex].refCount = 0;
	return tex;
}

Texture * TextureManager::GetTextureFromImage( unsigned int image, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2 )
{
	auto t = imageList.find(image);
	if(t == imageList.end())
	{
		throw std::runtime_error("GetTextureFromImage failed");
		return nullptr;
	}
	Texture *texture = new Texture;
	texture->textureId = image;
	texture->u1 = float(x1) / float(imageList[image].width);
	texture->v1 = float(y1) / float(imageList[image].height);
	texture->u2 = float(x2) / float(imageList[image].width);
	texture->v2 = float(y2) / float(imageList[image].height);
	imageList[image].refCount++;
	return texture;
}

bool TextureManager::AddTexture( Texture *texture )
{

	return true;
}
