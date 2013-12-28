#ifndef TextureManager_h__
#define TextureManager_h__

#include <string>
#include <map>
#include <sdl.h>

struct Texture
{
	unsigned int textureId;
	double u1;
	double v1;
	double u2;
	double v2;
	unsigned int width;
	unsigned int height;
};

class TextureManager
{
protected:
	struct image
	{
		unsigned int refCount;
		unsigned int width;
		unsigned int height;
	};
	std::map<unsigned int, image> imageList;
	std::map<std::string, Texture *> textureList;

public:
	TextureManager(void);
	~TextureManager(void);

	void Cleanup();

	SDL_Surface *LoadSurfaceFromFile(std::string fileName);
	unsigned int LoadImageFromSurface(SDL_Surface *surface, bool smoothing);
	Texture *GetTextureFromImage(unsigned int image, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
	
	void SetErrorTexture(std::string fileName);

	bool AddTexture(Texture *texture, std::string name);
	bool RemoveTexture(std::string name);
	Texture *GetTexture(std::string name);

	bool LoadTextureFromFile(std::string fileName, std::string name);

};

#endif // TextureManager_h__