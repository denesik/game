#ifndef MyGame_h__
#define MyGame_h__

#include "game.h"
#include "TextureManager.h"
#include "GUIContainer.h"
#include "Block.h"

class MyGame : public Game
{
private:
	GUIContainer *gui;
	GUIObject *fps;

	void test(int x1, int x2);

	Block *testBlock;

public:
	MyGame(void);
	~MyGame(void);

	virtual bool Initialize();
	virtual void LoadContent();
	virtual void Update();
	virtual void Draw();
	virtual void ResizeWindow(unsigned int width, unsigned int height);
	virtual void UnloadContent();

};


#endif // MyGame_h__