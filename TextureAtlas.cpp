#include "TextureAtlas.h"
#include <stdexcept>
#include <SDL_Image.h>
#include <math.h>
#include "Logger.h"


TextureAtlas::TextureAtlas(void)
{
	surface = nullptr;
	box = new ElasticBox;
	box->x = 0;
	box->y = 0;
	box->width = 0;
	box->height = 0;
	box->surfaceHeight = 0;
	box->surfaceWidth = 0;
	box->childrenBoxBig = nullptr;
	box->childrenBoxSmall = nullptr;
}


TextureAtlas::~TextureAtlas(void)
{
}

bool TextureAtlas::Create(unsigned int width, unsigned int height)
{
	Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	surface = SDL_CreateRGBSurface(0,width,height,32,rmask, gmask, bmask, amask);
	SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_NONE);
	//surface = IMG_Load("a1.png");
	box->x = 0;
	box->y = 0;
	box->width = width;
	box->height = height;
	box->surfaceHeight = 0;
	box->surfaceWidth = 0;
	box->childrenBoxBig = nullptr;
	box->childrenBoxSmall = nullptr;
	return true;
}

SDL_Surface * TextureAtlas::GetAtlas()
{
	return surface;
}

void TextureAtlas::Remove()
{
	SDL_FreeSurface(surface);
}

bool TextureAtlas::InsertSurface( SDL_Surface *_surface, unsigned int &x, unsigned int &y )
{
	boxTmp = box;
	surfaceTmp = _surface;
	bool result = InsertSurface();

	x = xTmp;
	y = yTmp;

	return result;
}

bool TextureAtlas::InsertSurface()
{
	ElasticBox *boxTmpParent = boxTmp;

	if(boxTmp->surfaceHeight == 0 && boxTmp->surfaceWidth == 0)
	{
		SDL_Rect dstrect;
		xTmp = dstrect.x = boxTmp->x;
		yTmp = dstrect.y = boxTmp->y;
		// Копируем всю поверхность
		SDL_SetSurfaceBlendMode(surfaceTmp, SDL_BLENDMODE_NONE);
		int r = SDL_BlitSurface(surfaceTmp, nullptr, surface, &dstrect);
		if(r != 0)
		{
			LOG(LOG_ERROR, "TextureAtlas. Surfase не создана.");
			return false;
		}

		unsigned int w1 = boxTmp->surfaceWidth = surfaceTmp->w;
		unsigned int h1 = boxTmp->surfaceHeight = surfaceTmp->h;

		boxTmp->childrenBoxSmall = new ElasticBox;
		boxTmp->childrenBoxSmall->surfaceHeight = 0;
		boxTmp->childrenBoxSmall->surfaceWidth = 0;
		boxTmp->childrenBoxSmall->childrenBoxBig = nullptr;
		boxTmp->childrenBoxSmall->childrenBoxSmall = nullptr;
		boxTmp->childrenBoxBig = new ElasticBox;
		boxTmp->childrenBoxBig->surfaceHeight = 0;
		boxTmp->childrenBoxBig->surfaceWidth = 0;
		boxTmp->childrenBoxBig->childrenBoxBig = nullptr;
		boxTmp->childrenBoxBig->childrenBoxSmall = nullptr;
		// Правый верхний прямоугольник
		double d1 = sqrt(double(h1 * h1) + double((boxTmp->width - w1) * (boxTmp->width - w1)));
		// Левый нижний прямоугольник
		double d2 = sqrt(double((boxTmp->height - h1) * (boxTmp->height - h1)) + double(w1 * w1));

		if(d1 < d2)
		{
			// Правый верхний прямоугольник - маленький
			boxTmp->childrenBoxSmall->height = h1;
			boxTmp->childrenBoxSmall->width = boxTmp->width - w1 - indent;
			boxTmp->childrenBoxSmall->x = boxTmp->x + w1 + indent;
			boxTmp->childrenBoxSmall->y = boxTmp->y;

			boxTmp->childrenBoxBig->x = boxTmp->x;
			boxTmp->childrenBoxBig->y = boxTmp->y + h1 + indent;
			boxTmp->childrenBoxBig->width = boxTmp->width;
			boxTmp->childrenBoxBig->height = boxTmp->height - h1 - indent;
		}
		else
		{
			// Левый нижний прямоугольник - маленький
			boxTmp->childrenBoxSmall->height = boxTmp->height - h1 - indent;
			boxTmp->childrenBoxSmall->width = w1;
			boxTmp->childrenBoxSmall->x = boxTmp->x;
			boxTmp->childrenBoxSmall->y = boxTmp->y + h1 + indent;

			boxTmp->childrenBoxBig->x = boxTmp->x + w1 + indent;
			boxTmp->childrenBoxBig->y = boxTmp->y;
			boxTmp->childrenBoxBig->width = boxTmp->width - w1 - indent;
			boxTmp->childrenBoxBig->height = boxTmp->height;
		}
	}
	else
	{
		// Попытаемся уместиться в маленькую площадь.
		if(boxTmp->childrenBoxSmall->height >= surfaceTmp->h && boxTmp->childrenBoxSmall->width >= surfaceTmp->w)
		{
			boxTmp = boxTmp->childrenBoxSmall;
			if(InsertSurface())
			{
				return true;
			}
			else
				boxTmp = boxTmpParent;
		}
		
		if(boxTmp->childrenBoxBig->height >= surfaceTmp->h && boxTmp->childrenBoxBig->width >= surfaceTmp->w)
		{
			boxTmp = boxTmp->childrenBoxBig;
			return InsertSurface();
		}
		return false;
	}

	return true;
}
