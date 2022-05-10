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
	Game game = Game({ 1280,720 }, "no title", GE::WindowMode::WINDOW);

	return game.Run();
}