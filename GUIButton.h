#ifndef GUIButton_h__
#define GUIButton_h__

#include "guiobject.h"


class GUIButton : public GUIObject
{
protected:

public:
	GUIButton(int x, int y, int w, int h);
	~GUIButton(void);

	virtual void LoadContent();
	virtual void Draw(Render *render);
};


#endif // GUIButton_h__