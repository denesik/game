#include "GameComponentManager.h"


GameComponentManager::GameComponentManager(void)
{
}


GameComponentManager::~GameComponentManager(void)
{
}

int GameComponentManager::Add(GameComponent *gameComponent)
{
	gameComponents.push_back(gameComponent);
	return 0;
}

int GameComponentManager::Remove(GameComponent *gameComponent)
{
	gameComponents.remove(gameComponent);
	return 0;
}

bool GameComponentManager::Initialize()
{
	for (auto i =  gameComponents.begin(); i != gameComponents.end(); ++i)
	{
		(*i)->Initialize();
	}
	return true;
}

void GameComponentManager::Update()
{
	for (auto i =  gameComponents.begin(); i != gameComponents.end(); ++i)
	{
		(*i)->Update();
	}
}

void GameComponentManager::Draw(Render *render)
{
	for (auto i =  gameComponents.begin(); i != gameComponents.end(); ++i)
	{
		(*i)->Draw(render);
	}
}

void GameComponentManager::UnloadContent()
{
	for (auto i =  gameComponents.begin(); i != gameComponents.end(); ++i)
	{
		(*i)->UnloadContent();
	}
}

void GameComponentManager::LoadContent()
{
	for (auto i =  gameComponents.begin(); i != gameComponents.end(); ++i)
	{
		(*i)->LoadContent();
	}
}

