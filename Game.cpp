#include "Game.h"
#include <iostream>

Game::Game(void)
{
	Running = true;
	
	title = "Game";
	width = 800;
	height = 600;
	fullscreen = false;

	render = new Render();
	eventHandler = new EventHandler();
	gameComponentHandler = new GameComponentManager();
}


Game::~Game(void)
{
	delete render;
	delete eventHandler;
	delete gameComponentHandler;
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
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

	UnLoadContent();

	Cleanup();

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

void Game::UnLoadContent()
{
	gameComponentHandler->UnLoadContent();
}

void Game::Cleanup()
{

	gameComponentHandler->Cleanup();

	render->Cleanup();

	SDL_Quit();
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
