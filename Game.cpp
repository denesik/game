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

	render->SetTextureManager(textureManager);
}


Game::~Game(void)
{
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
	
	EventManager::Init();

	render->Initialize(title, width, height, fullscreen);

	return true;
}

void Game::LoadContent()
{
}

int Game::Run()
{
	if(!Initialize()) 
	{
		LOG(LOG_ERROR, "Инициализация завершилась с ошибками.");
		return -1;
	}

	LoadContent();

	SDL_Event event;

	while(Running) 
	{
		while(SDL_PollEvent(&event)) 
		{
			if(event.type == SDL_QUIT)
				Running=false;
			if(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				ResizeWindow(event.window.data1, event.window.data2);
			}
			
			EventManager::OnEvent(&event);
		}

		EventManager::Update();
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

}

void Game::Draw()
{

}

void Game::UnloadContent()
{
	textureManager->UnloadContent();
}

void Game::ResizeWindow( unsigned int _width, unsigned int _height )
{
	width = _width;
	height = _height;
	render->ResizeWindow(width, height);
}
