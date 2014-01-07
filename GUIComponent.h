#ifndef GUIComponent_h__
#define GUIComponent_h__


#include "gamecomponent.h"
#include "GUIContainer.h"

class GUIComponent : public GameComponent
{
private:
	GUIContainer *guiComponent;
	int width;
	int height;

public:
	GUIComponent(int width, int height);
	~GUIComponent(void);


	virtual bool Initialize();
	virtual void LoadContent();
	virtual void Update();
	virtual void Draw(Render *render);
	virtual void UnloadContent();


	virtual void Resize(int width, int height);

	virtual void OnMouseButtonDown(int button, int x, int y);
	virtual void OnMouseButtonUp(int button, int x, int y);
	virtual void OnMouseButtonClick(int button, int x, int y);

	void SetTextureManager(TextureManager *textureManager);
	TextureManager *GetTextureManager();

	void SetDefaultFont(IFont *font);
	IFont *GetDefaultFont();

	int RemoveGUIObject(GUIObject *guiObject);
	int AddGUIObject(GUIObject *guiObject);
};


#endif // GUIComponent_h__