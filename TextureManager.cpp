#include "TextureManager.h"
#include <SDL_Image.h>
#include <SDL_opengl.h>


TextureManager::TextureManager(void)
{
}

TextureManager::~TextureManager(void)
{
}


SDL_Surface *TextureManager::LoadSurfaceFromFile(std::string fileName)
{
	SDL_Surface *surface = IMG_Load(fileName.c_str());
	if(surface == nullptr)
	{
		throw std::runtime_error("IMG_Load failed (there is probably a problem with your font file)");
		return nullptr;
	}
	return surface;
}


void TextureManager::Cleanup()
{
	for (auto i =  textureList.begin(); i != textureList.end(); ++i)
	{
		delete (*i).second;
	}
	textureList.clear();
	for (auto i = imageList.begin(); i != imageList.end(); i++)
	{
		glDeleteTextures(1,&((*i).first));
	}
}

unsigned int TextureManager::LoadImageFromSurface( SDL_Surface *surface, bool smoothing)
{

	if(surface == nullptr)
	{
		throw std::runtime_error("LoadImageFromSurface failed");
		return 0;
	}

	GLuint tex;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	GLint param = GL_LINEAR;
	if(!smoothing) param = GL_NEAREST;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);

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

bool TextureManager::AddTexture(Texture *texture, std::string name)
{
	auto f= textureList.find(name);
	if(f != textureList.end())
		return false;

	textureList[name] = texture;

	return true;
}

bool TextureManager::RemoveTexture(std::string name)
{
	auto f= textureList.find(name);
	if(f == textureList.end())
		return false;

	auto t = imageList.find(textureList[name]->textureId);
	if(t == imageList.end())
	{
		throw std::runtime_error("RemoveTexture failed");
		return false;
	}
	else
	{
		(*t).second.refCount--;
		if((*t).second.refCount <= 0)
		{
			glDeleteTextures(1,&((*t).first));
			imageList.erase(t);
		}
	}
	delete (*f).second;
	textureList.erase(f);
	return true;
}

Texture * TextureManager::GetTexture( std::string name )
{
	auto f= textureList.find(name);
	if(f == textureList.end())
	{
		throw std::runtime_error("GetTexture failed. Texture not found.");
		return nullptr;
	}
	return (*f).second;
}

bool TextureManager::LoadTextureFromFile( std::string fileName, std::string name )
{
	SDL_Surface *s = LoadSurfaceFromFile(fileName);
	if(!s) return false;

	Texture *t = GetTextureFromImage(LoadImageFromSurface(s, true), 0, 0, s->w, s->h);
	SDL_FreeSurface(s);
	if(!t) return false;

	return AddTexture(t, name);
}
