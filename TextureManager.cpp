#include "TextureManager.h"
#include <SDL_Image.h>
#include <SDL_opengl.h>
#include "Logger.h"


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
		LOG(LOG_WARNING, "TextureManager. IMG_Load. Файл " + fileName + " не загружен.");
		return nullptr;
	}
	return surface;
}


void TextureManager::UnloadContent()
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
		LOG(LOG_WARNING, "TextureManager. Surface отсутствует.");
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
		LOG(LOG_WARNING, "TextureManager. Изображение отсутствует в видео памяти.");
		return nullptr;
	}
	Texture *texture = new Texture;
	texture->textureId = image;
	texture->u1 = float(x1) / float(imageList[image].width - 1);
	texture->v1 = float(y1) / float(imageList[image].height - 1);
	texture->u2 = float(x2) / float(imageList[image].width - 1);
	texture->v2 = float(y2) / float(imageList[image].height - 1);
	if(x2 > x1)
		texture->width = x2 - x1 + 1;
	else
		texture->width = x1 - x2 + 1;
	if(y2 > y1)
		texture->height = y2 - y1 + 1;
	else
		texture->height = y1 - y2 + 1;

	imageList[image].refCount++;
	return texture;
}

bool TextureManager::AddTexture(Texture *texture, std::string name)
{
	auto f= textureList.find(name);
	if(f != textureList.end())
	{
		LOG(LOG_WARNING, "TextureManager. Текстура " + name + " уже существует.");
		return false;
	}

	textureList[name] = texture;

	return true;
}

bool TextureManager::RemoveTexture(std::string name)
{
	auto f= textureList.find(name);
	if(f == textureList.end())
	{
		LOG(LOG_WARNING, "TextureManager. Невозможно удалить текстуру. Текстура не найдена.");
		return false;
	}

	auto t = imageList.find(textureList[name]->textureId);
	if(t == imageList.end())
	{
		LOG(LOG_WARNING, "TextureManager. Невозможно удалить текстуру. Текстура не найдена.");
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
	auto f = textureList.find(name);
	if(f == textureList.end())
	{
		LOG(LOG_WARNING, "TextureManager. Текстура " + name + " не найдена.");
		Texture *errorTexture = GetTexture("ERROR_TEXTURE");
		if(errorTexture == nullptr)
		{
			LOG(LOG_ERROR, "TextureManager. Текстура ERROR_TEXTURE не найдена");
			return nullptr;
		}
		else
			return errorTexture;
	}
	return (*f).second;
}

bool TextureManager::LoadTextureFromFile( std::string fileName, std::string name )
{
	SDL_Surface *s = LoadSurfaceFromFile(fileName);
	if(!s) 
	{
		return false;
	}

	Texture *t = GetTextureFromImage(LoadImageFromSurface(s, true), 0, 0, s->w, s->h);
	SDL_FreeSurface(s);
	if(!t)
	{
		return false;
	}

	return AddTexture(t, name);
}

void TextureManager::SetErrorTexture( std::string fileName )
{

	SDL_Surface *s = LoadSurfaceFromFile(fileName);
	if(!s) 
	{
		LOG(LOG_ERROR, "TextureManager. Текстура ERROR_TEXTURE не загружена. Файл: " + fileName);
		return ;
	}

	Texture *t = GetTextureFromImage(LoadImageFromSurface(s, true), 0, 0, s->w, s->h);
	SDL_FreeSurface(s);
	if(!t)
	{
		LOG(LOG_ERROR, "TextureManager. Текстура ERROR_TEXTURE не загружена. Файл: " + fileName);
		return;
	}

	if(!AddTexture(t, "ERROR_TEXTURE"))
	{
		LOG(LOG_ERROR, "TextureManager. Текстура ERROR_TEXTURE не загружена. Файл: " + fileName);
		return;
	}

}
