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
	std::map<std::string, unsigned int> textureList;

public:
	TextureManager(void);
	~TextureManager(void);

	void Cleanup();

	unsigned int AddFromFile(std::string fileName, std::string name);
	int Get(std::string name);

	unsigned int LoadImageFromSurface(SDL_Surface *surface);
	Texture *GetTextureFromImage(unsigned int image, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
	
	bool AddTexture(Texture *texture);
};

#endif // TextureManager_h__