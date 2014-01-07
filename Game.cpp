#include "Game.h"
#include <iostream>
#include "Logger.h"

Game::Game(void)
{
	Running = true;
	
	title = "Game";
	width = 800;
	height = 600;
	fullscreen = false;

	render = new Render();
	textureManager = new TextureManager();
	eventHandler = new EventHandler();
	gameComponentHandler = new GameComponentManager();

	render->SetTextureManager(textureManager);
}


Game::~Game(void)
{
	delete gameComponentHandler;
	delete eventHandler;
	delete textureManager;
	delete render;
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		LOG(LOG_ERROR, "SDL не инициализирован.");
		Running = false;
	}
	
	render->Initialize(title, width, height, fullscreen);

	gameComponentHandler->Initialize();

	return true;
}

void Game::LoadContent()
{
	gameComponentHandler->LoadContent();
}

int Game::Run()
{
	if(!Initialize()) 
	{
		LOG(LOG_ERROR, "Инициализация завершилась с ошибками.");
		return -1;
	}

	LoadContent();

	SDL_Event Event;

	while(Running) 
	{
		while(SDL_PollEvent(&Event)) 
		{
			if(Event.type == SDL_QUIT)
				Running=false;
			if(Event.type == SDL_WINDOWEVENT && Event.window.event == SDL_WINDOWEVENT_RESIZED)
				render->ResizeWindow(Event.window.data1, Event.window.data2);

			eventHandler->OnEvent(&Event);
		}

		Update();
		Draw();
		render->SwapBuffers();
	}

	UnloadContent();

	render->Finalize();
	SDL_Quit();

	return 0;
}

void Game::Update()
{

	gameComponentHandler->Update();
}

void Game::Draw()
{

	gameComponentHandler->Draw(render);
}

void Game::UnloadContent()
{
	gameComponentHandler->UnloadContent();
	textureManager->UnloadContent();
}

IEventHandler *Game::GetEventHandler()
{
	return eventHandler;
}

int Game::AddGameComponent(GameComponent *gameComponent)
{
	gameComponentHandler->Add(gameComponent);
	return 0;
}
