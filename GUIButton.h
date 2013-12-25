#ifndef GUIButton_h__
#define GUIButton_h__

#include "guiobject.h"


class GUIButton : public GUIObject
{
protected:
	int textX;
	int textY;
	std::string text;

public:
	GUIButton(int x, int y, int w, int h, std::string _text);
	~GUIButton(void);

	virtual void LoadContent();
	virtual void Draw(Render *render);
	virtual void SetText(std::string text);
	virtual void Resize(int width, int height);

protected:
	void ResizeText();
};


#endif // GUIButton_h__