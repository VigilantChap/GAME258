
#include "Game/Game1.h"

int main(int argc, char* argv[]) {

	CoreEngine::GetInstance()->SetGameInterface(new Game1);

	if (!CoreEngine::GetInstance()->OnCreate("GAME258 Engine", 800, 600)) {
		return 0;
	}

	CoreEngine::GetInstance()->Run();

	return 0;
}