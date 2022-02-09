#include "Game.h"
#include "Header/Util/Random.h"
#include "Header/Util/Utility.h"

Game::Game()
	: Application()
{
}

Game::Game(const GE::Math::Vector2& size, const std::string& title)
	: Application(size,title)
{
}

Game::~Game()
{
}

bool Game::LoadContents()
{
	Application::LoadContents();
	return true;
}

bool Game::Initialize()
{
	Application::Initialize();
	return true;
}

bool Game::Update()
{
	return true;
}

bool Game::Draw()
{
	return true;
}
