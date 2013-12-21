#ifndef GUIObject_h__
#define GUIObject_h__

#include "GameMath.h"
#include "Render.h"
#include "Font.h"

class GUIManager;

class GUIObject
{
protected:
	GUIManager *guiManager;

	std::string fontName;
	Font *font;

	bool isVisible;
	bool isEnable;

	Rect boundBox;

	virtual void SetFont(Font *font);
	virtual Font *GetFont();

public:
	GUIObject(void);
	~GUIObject(void);

	friend GUIManager;

	virtual void OnClick(){};
	virtual void OnRelease(){};
	virtual void OnMove(){};

	virtual void Update(){};
	virtual void Draw(Render *render){};

	virtual void SetFont(std::string fontName);
};


#endif // GUIObject_h__