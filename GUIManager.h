#ifndef GUIManager_h__
#define GUIManager_h__

#include "gamecomponent.h"
#include "GUIObject.h"
#include "Font.h"
#include "GUIFontManager.h"


class GUIManager : public GameComponent
{
protected:
	std::list<GUIObject *const> guiObjectLists;
	GUIFontManager *fontManager;
	TextureManager *textureManager;

	int width;
	int height;

	GUIFont *fontDefault;
	std::string NameDefaultFont;

public:
	GUIManager(int width, int height);
	~GUIManager(void);

	virtual bool Initialize();
	virtual void Update();
	virtual void LoadContent();
	virtual void Draw(Render *render);
	virtual void Cleanup(){};

	virtual int RemoveGUIObject(GUIObject *guiObject);
	virtual int AddGUIObject(GUIObject *guiObject);

	virtual void SetTextureManager(TextureManager *textureManager);
	virtual TextureManager *GetTextureManager();

	virtual void SetFontManager(GUIFontManager *_fontManager);
	virtual GUIFontManager *GetFontManager();

	virtual void Resize(int width, int height);

	virtual void OnMouseButtonDown(int button, int x, int y){};
	virtual void OnMouseButtonUp(int button, int x, int y){};
	virtual void OnMouseButtonClick(int button, int x, int y);

private:
	bool HittingArea(int x, int y, Rectangle2i area);
};


#endif // GUIManager_h__