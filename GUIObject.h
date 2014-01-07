#ifndef GUIObject_h__
#define GUIObject_h__

#include "GameMath.h"
#include "Render.h"
#include "Font.h"

class GUIContainer;

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
	GUIContainer *guiContainer;

	IFont *font;

	Rectangle2i boundBoxOriginal;
	Rectangle2i boundBox;
	WindowTexture windowTexture;

public:
	bool isVisible;
	bool isActive;

public:
	GUIObject(void);
	~GUIObject(void);

	virtual void OnMouseMove(int x, int y){};
	virtual void OnMouseClick(int button, int x, int y){};

	virtual void Resize(int width, int height);

	virtual void LoadContent();
	virtual void Update(){};
	virtual void Draw(Render *render);
	virtual void UnloadContent(){};

	virtual void SetFont(IFont *font);
	virtual IFont *GetFont();

	virtual void SetContainer(GUIContainer *guiContainerParent);
	virtual GUIContainer *GetContainer();

	virtual Rectangle2i GetBoundBox();
};


#endif // GUIObject_h__