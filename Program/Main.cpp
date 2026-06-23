#include "Main.h"

gameManager* gameManager::gameManagerPtr = nullptr; // 定義

// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ゲームオブジェクトの取得
	gameManager* gamePtr = gameManager::GetGameObject();

	// ゲーム初期化
	if (!gamePtr->GameInit()) {
		return -1; // DxLibの初期化に失敗したら直ちに終了
	}

	// 参照を使ってゲームループ起動
	gamePtr->GameLoop();

	// ゲームオブジェクト破棄
	if (gamePtr != nullptr)
	{
		gamePtr->GameEnd();
		// オブジェクトの破棄
		delete gamePtr;
		// ポインター変数の初期化
		gamePtr = nullptr;
	}

	// ソフトの終了
	return 0;
}