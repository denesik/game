#ifndef MyGame_h__
#define MyGame_h__

#include "game.h"
#include "GUIManager.h"
#include "GUIFontManager.h"
#include "TextureManager.h"

class MyGame : public Game
{
private:
	GUIManager *guiManager;
	GUIFontManager *fontManager;
	GUIObject *fps;

	void test(int x1, int x2);

public:
	MyGame(void);
	~MyGame(void);

	virtual bool Initialize();
	virtual void LoadContent();
	virtual void Update();
	virtual void Draw();
	virtual void UnLoadContent();
	virtual void Cleanup();
};


#endif // MyGame_h__