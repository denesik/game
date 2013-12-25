#ifndef GUIObject_h__
#define GUIObject_h__

#include "GameMath.h"
#include "Render.h"
#include "Font.h"

class GUIManager;

struct WindowTexture
{
	Texture *borderTop;
	Texture *borderBot;
	Texture *borderLeft;
	Texture *borderRight;
	Texture *borderTopLeft;
	Texture *borderTopRight;
	Texture *borderBotRight;
	Texture *borderBotLeft;
	Texture *body;
};

class GUIObject
{
protected:
	GUIManager *guiManager;

	std::string fontName;
	Font *font;

	Rect boundBoxOriginal;
	Rect boundBox;
	WindowTexture windowTexture;

	virtual void SetFont(Font *font);
	virtual Font *GetFont();

public:
	bool isVisible;
	bool isActive;

public:
	GUIObject(void);
	~GUIObject(void);

	friend GUIManager;

	virtual void OnMouseMove(int x, int y){};
	virtual void OnMouseClick(int button, int x, int y){};

	virtual void Resize(int width, int height);
	virtual void LoadContent();
	virtual void Update(){};
	virtual void Draw(Render *render);

	virtual void SetFont(std::string fontName);
};


#endif // GUIObject_h__