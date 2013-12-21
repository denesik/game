#include "MyGame.h"
#include "GUIButton.h"
#include "GUIFont.h"


MyGame::MyGame(void)
{

	title = "New Game";
	width = 800;
	height = 600;
	fullscreen = false;

}


MyGame::~MyGame(void)
{

}

//PRN35__C.TTF
//REVERNCE.TTF

bool MyGame::Initialize()
{
	fontManager = new GUIFontManager();
	fontManager->Add("FontDefault", new GUIFont("fonts/ACADEITA.TTF",14));
	fontManager->Add("Font1", new GUIFont("fonts/REVERNCE.TTF",14));
	fontManager->Add("Font2", new GUIFont("fonts/PRN55__C.TTF",14));

	guiManager = new GUIManager(width, height);
	AddGameComponent(guiManager);
	GetEventHandler()->Add(guiManager);
	guiManager->SetFontManager(fontManager);

	GUIObject *g = new GUIButton(10,20,30,40);
	guiManager->AddGUIObject(g);
	g->SetFont("Font2");

	Game::Initialize();
	
	return true;
}

void MyGame::Update()
{

	Game::Update();
}

void MyGame::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	

	glColor3ub(0xff,0,0xff);			

	Game::Draw();
}

void MyGame::Cleanup()
{

	Game::Cleanup();
}

void MyGame::LoadContent()
{

	Game::LoadContent();
}

void MyGame::UnLoadContent()
{

	Game::UnLoadContent();
}
