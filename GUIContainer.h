#ifndef GUIManager_h__
#define GUIManager_h__

#include "GUIObject.h"
#include "Font.h"
#include <list>
//#include "EventHandler.h"
#include "Keyboard.h"
#include "Mouse.h"


class GUIContainer
{
protected:
	
	TextureManager *textureManager;
	IFont *fontDefault;

	int width;
	int height;

	std::list<GUIObject *const> guiObjectLists;

public:
	GUIContainer(int width, int height);
	~GUIContainer(void);

	virtual void LoadContent();
	virtual void Update();
	virtual void Draw(Render *render);
	virtual void UnloadContent(){};

	virtual void Resize(int width, int height);

	//virtual void OnMouseButtonDown(int button, int x, int y){};
	//virtual void OnMouseButtonUp(int button, int x, int y){};
	//virtual void OnMouseButtonClick(int button, int x, int y);

	void SetTextureManager(TextureManager *textureManager);
	TextureManager *GetTextureManager();

	void SetDefaultFont(IFont *font);
	IFont *GetDefaultFont();

	int RemoveGUIObject(GUIObject *guiObject);
	int AddGUIObject(GUIObject *guiObject);


private:
	bool HittingArea(int x, int y, Rectangle2i area);

};


#endif // GUIManager_h__