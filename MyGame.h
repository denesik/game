#ifndef MyGame_h__
#define MyGame_h__

#include "game.h"
#include "GUIManager.h"
#include "GUIFontManager.h"

class MyGame : public Game
{
private:
	GUIManager *guiManager;
	GUIFontManager *fontManager;

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