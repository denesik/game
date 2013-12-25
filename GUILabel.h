#ifndef GUILabel_h__
#define GUILabel_h__

#include "guiobject.h"

class GUILabel : public GUIObject
{
protected:
	int textX;
	int textY;
	std::string text;

public:
	GUILabel();
	GUILabel(int x, int y, std::string text);
	~GUILabel(void);

	virtual void LoadContent();
	virtual void Resize(int width, int height);
	virtual void Draw(Render *render);
	virtual void SetText(std::string text);
protected:

	void ResizeText();
};


#endif // GUILabel_h__