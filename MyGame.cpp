#include "MyGame.h"
#include "GUIButton.h"
#include "GUIFont.h"
#include "TextureAtlas.h"
#include <SDL_Image.h>


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
	/*
	TextureAtlas *t = new TextureAtlas();
	t->Create(32,32);
	unsigned int x,y;
	bool b;
	b = t->InsertSurface(IMG_Load("a1.png"), x, y);
	b = t->InsertSurface(IMG_Load("a2.png"), x, y);
	b = t->InsertSurface(IMG_Load("a1.png"), x, y);
	b = t->InsertSurface(IMG_Load("a2.png"), x, y);
	b = t->InsertSurface(IMG_Load("a2.png"), x, y);
	b = t->InsertSurface(IMG_Load("a2.png"), x, y);
	b = t->InsertSurface(IMG_Load("a2.png"), x, y);
	b = t->InsertSurface(IMG_Load("a2.png"), x, y);
	b = t->InsertSurface(IMG_Load("a2.png"), x, y);
	b = t->InsertSurface(IMG_Load("a2.png"), x, y);
	IMG_SavePNG(t->GetAtlas(), "a12.png");
	*/

	textureManager->LoadTextureFromFile("gui2.png", "gui");
	textureManager->LoadTextureFromFile("glyph.png", "glyph");
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
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);			

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
