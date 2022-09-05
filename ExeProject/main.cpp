#include "Game.h"
#include "resource.h"

#ifdef _DEBUG
#include <crtdbg.h>
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#endif
	GE::Math::Vector2 windowSize = GE::Math::Vector2(1920, 1080);
	GE::Math::Vector2 resolution = GE::Math::Vector2(1920, 1080);

	GE::WindowData windowData;
	windowData.title = "no title";
	windowData.windowSize = windowSize;
	windowData.windowMode = GE::WindowMode::WINDOW;
	windowData.iconHandle = IDI_ICON1;

	Game game = Game(windowData,resolution);

	return game.Run();
}