#include "Game.h"

#ifdef _DEBUG
#include <crtdbg.h>
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#endif

	GE::Math::Vector2 windowSize = GE::Math::Vector2(1280, 720);
	GE::Math::Vector2 resolution = GE::Math::Vector2(1280, 720);

	Game game = Game(windowSize, resolution, "no title", GE::WindowMode::WINDOW);

	return game.Run();
}