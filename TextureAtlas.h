#ifndef TextureAtlas_h__
#define TextureAtlas_h__

#include <SDL.h>



class TextureAtlas
{
private:
	struct ElasticBox
	{
		int surfaceWidth, surfaceHeight;		// Ўирина и высота "€щика"
		int x, y, width, height;				// √абариты "контейнера"
		ElasticBox *childrenBoxSmall;
		ElasticBox *childrenBoxBig;
	};

	SDL_Surface *surface;
	ElasticBox *box;

	SDL_Surface *surfaceTmp;
	ElasticBox *boxTmp;

	unsigned int xTmp;
	unsigned int yTmp;

public:
	TextureAtlas(void);
	~TextureAtlas(void);

	bool Create(unsigned int width, unsigned int height);
	void Remove();
	SDL_Surface *GetAtlas();

	bool InsertSurface(SDL_Surface *surface, unsigned int &x, unsigned int &y);

private:
	bool InsertSurface();

};


#endif // TextureAtlas_h__