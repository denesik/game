#ifndef MyGame_h__
#define MyGame_h__

#include "game.h"
#include "TextureManager.h"
#include "GUIComponent.h"

class MyGame : public Game
{
private:

	GUIComponent *guiComponent;

	GUIObject *fps;

	void test(int x1, int x2);

public:
	MyGame(void);
	~MyGame(void);

	virtual bool Initialize();
	virtual void LoadContent();
	virtual void Update();
	virtual void Draw();
	virtual void UnloadContent();
};


#endif // MyGame_h__