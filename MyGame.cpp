#include "MyGame.h"
#include "GUIButton.h"
#include "GUIFont.h"
#include "TextureAtlas.h"
#include <SDL_Image.h>
#include "GUILabel.h"
#include "GUIFPS.h"


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
	fontManager->Add("FontDefault", new GUIFont("fonts/ACADEITA.TTF",12));

	guiManager = new GUIManager(width, height);
	AddGameComponent(guiManager);
	GetEventHandler()->Add(guiManager);
	guiManager->SetFontManager(fontManager);
	guiManager->SetTextureManager(textureManager);

	GUIButton *g1 = new GUIButton(350,250,100,30, "Button 1");
	GUIButton *g2 = new GUIButton(350,230,100,30, "Button 2");
	guiManager->AddGUIObject(g1);
	guiManager->AddGUIObject(g2);

	GUILabel *gl1 = new GUILabel(500,250,"new test text\nnew line!");
	guiManager->AddGUIObject(gl1);

	guiManager->AddGUIObject(new GUIFPS(5, 580));

	Game::Initialize();

	//textureManager->LoadTextureFromFile("gui2.png", "gui");

	SDL_Surface *guiTexture = textureManager->LoadSurfaceFromFile("gui4.png");
	unsigned int tertureId = textureManager->LoadImageFromSurface(guiTexture, true);
	textureManager->AddTexture(textureManager->GetTextureFromImage(tertureId, 15, 9, 16, 0), "GUI_borderTop");
	textureManager->AddTexture(textureManager->GetTextureFromImage(tertureId, 15, 31, 16, 22), "GUI_borderBot");
	textureManager->AddTexture(textureManager->GetTextureFromImage(tertureId, 0, 15, 9, 16), "GUI_borderLeft");
	textureManager->AddTexture(textureManager->GetTextureFromImage(tertureId, 22, 15, 31, 16), "GUI_borderRight");

	textureManager->AddTexture(textureManager->GetTextureFromImage(tertureId, 0, 9, 9, 0), "GUI_borderTopLeft");
	textureManager->AddTexture(textureManager->GetTextureFromImage(tertureId, 22, 9, 31, 0), "GUI_borderTopRight");
	textureManager->AddTexture(textureManager->GetTextureFromImage(tertureId, 22, 31, 31, 22), "GUI_borderBotRight");
	textureManager->AddTexture(textureManager->GetTextureFromImage(tertureId, 0, 31, 9, 22), "GUI_borderBotLeft");
	textureManager->AddTexture(textureManager->GetTextureFromImage(tertureId, 15, 15, 16, 16), "GUI_body");


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
