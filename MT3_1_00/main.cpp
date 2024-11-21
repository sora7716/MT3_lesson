#include "scene/GameLoop.h"
#include <memory>
using namespace std;
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	std::unique_ptr<GameLoop>gameLoop = std::make_unique<GameLoop>();
	
	gameLoop->Loop();
	
	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
