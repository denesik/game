#ifndef GUIManager_h__
#define GUIManager_h__

#include "gamecomponent.h"
#include "GUIObject.h"
#include "Font.h"


class GUIManager : public GameComponent
{
protected:
	std::list<GUIObject *const> guiObjectLists;
	TextureManager *textureManager;

	int width;
	int height;

	IFont *fontDefault;
	std::vector<IFont*> fontsVector;

public:
	GUIManager(int width, int height);
	~GUIManager(void);

	virtual bool Initialize();
	virtual void Update();
	virtual void LoadContent();
	virtual void Draw(Render *render);
	virtual void Cleanup(){};

	virtual void Resize(int width, int height);

	virtual void OnMouseButtonDown(int button, int x, int y){};
	virtual void OnMouseButtonUp(int button, int x, int y){};
	virtual void OnMouseButtonClick(int button, int x, int y);

	void SetTextureManager(TextureManager *textureManager);
	TextureManager *GetTextureManager();

	void SetDefaultFont(IFont *font);
	IFont *GetDefaultFont();

	int RemoveGUIObject(GUIObject *guiObject);
	int AddGUIObject(GUIObject *guiObject);

	bool AddFont(IFont *font);
	bool RemoveFont(IFont *font);

private:
	bool HittingArea(int x, int y, Rectangle2i area);

	bool GenerateFonts(int width, int height);

};


#endif // GUIManager_h__