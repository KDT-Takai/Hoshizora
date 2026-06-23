#pragma once
#include <Vector>
#include <Ctime>
#include <string>
#include <cassert>	// アサート
#include <iostream>

#include "DxLib.h"
#include "define.h"
// スクリーン管理
#include "ScreenManager.h"
// デルタタイムクラス
#include "deltatime.h"
// エフェクト
#include "m_line.h"
#include "ShapeEffect.h"
#include "ShootingStar.h"


class gameManager final
{
private:

	/// <summary>
	/// シングルトンオブジェクト保持
	/// </summary>
	static gameManager* gameManagerPtr;

	std::vector<std::unique_ptr<CShapeEf>> mEffects;

	// エフェクト発生
	void SpawnEffect(Pos spawnPos) {
		mEffects.push_back(std::make_unique<CShapeEf>(spawnPos));
	};

	/// <summary>
	/// 隠蔽コンストラクタ
	/// </summary>
	gameManager() {}
	
	bool CheckAssertion;	// アサート確認
	std::unique_ptr<ShootingStarSystem> g_stars;

public:
	
	/// <summary>
	/// ゲームオブジェクト取得
	/// </summary>
	/// <returns>オブジェクト</returns>
	static gameManager* GetGameObject() {
		//　シングルトンオブジェクトの存在チェック
		if (gameManager::gameManagerPtr == nullptr) {
			//　オブジェクト生成
			gameManager::gameManagerPtr = new gameManager();
		}
		//　シングルトンオブジェクトをリターン
		return gameManager::gameManagerPtr;
	}

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~gameManager() {
		//　終了処理
		DxLib_End();

		//　シングルトン保持変数のリセット
		gameManager::gameManagerPtr = nullptr;
		;
	}

	/// <summary>
	/// 初期化メソッド
	/// </summary>
	/// <returns>結果</returns>
	bool GameInit()
	{
		// オブジェクトチェック
		if (this == nullptr)
		{
			return false;
		}

		// =======================================
		//  初期化処理
		// =======================================
		// ログの書き出しを無効化
		SetOutApplicationLogValidFlag(FALSE);	// ログの書き出しを無効化

		// ウィンドウモードの設定
		ChangeWindowMode(TRUE);					// ウインドウモードを有効化

		// ウィンドウサイズとカラービットの設定
		SetGraphMode(WINDOW_W, WINDOW_H, COLOR_DEPTH);

		// ウィンドウのタイトル
		SetMainWindowText("DxLib Template");

		// 背景色の設定
		SetBackgroundColor(128, 128, 128);

		// ＤＸライブラリの初期化
		if (DxLib_Init() < 0) return -1;

		// ウィンドウ描画モード設定
		SetDrawScreen(DX_SCREEN_BACK);			// 裏画面に描画する

		this->Init();

		return true;

	}

	/// <summary>
	/// Gameループメソッド
	/// </summary>
	void GameLoop() {

		// アサート確認
		assert(CheckAssertion == 0);

		// オブジェクトチェック
		if (this == nullptr)
		{
			return;
		}

		// ------------------------------
		//  ゲームループ
		// ------------------------------
		while (ProcessMessage() == 0)
		{
			// リフレッシュレートを設定するための処理
			clock_t check_fps = clock() + CLOCKS_PER_SEC / 60;

			// マウスカーソル表示設定
			SetMouseDispFlag(TRUE);

			// printfDxの初期化
			clsDx();

			// 画面上の描画を初期化（画面を消去）
			ClearDrawScreen();

			// 画面描画処理
			this->Update();

			// 描画処理
			this->Draw();

			// リフレッシュレートが一定になるまで待つ処理
			while (clock() < check_fps) {}

			// 裏画面の描画を表に反映
			ScreenFlip();


			// ESCキーでループから抜ける
			if (CheckHitKey(KEY_INPUT_ESCAPE)) {
				break;
			}
		}
	}

	/// <summary>
	/// Game終了処理
	/// </summary>
	void GameEnd() {
		this->End();
	}

protected:

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() {
		g_stars = std::make_unique<ShootingStarSystem>(1280, 720);
	};

	/// <summary>
	/// 画面更新処理
	/// </summary>
	void Update() {
		g_stars->Update();
		// ------ system ------ 
		Time::Instance().Update();				// デルタタイムの更新
		InputManager::Instance().Update();		// 入力処理のアップデート
		// ------ effect ------
		LineEffect::Instance().Update();		// ラインエフェクト
		// エフェクトの更新
		for (auto it = mEffects.begin(); it != mEffects.end();) {
			(*it)->Updata();
			// 終わったエフェクトは削除
			if (!(*it)->CheckEnable()) { it = mEffects.erase(it); }
			else { ++it; }
		}
		if (InputManager::Instance().IsGetMouse(MOUSE_INPUT_LEFT) || InputManager::Instance().IsGetMouse(MOUSE_INPUT_RIGHT)) {
			// エフェクト生成してリストに追加
			SpawnEffect(Pos(InputManager::Instance().GetMouseX(), InputManager::Instance().GetMouseY()));
		};
		ScreenManager::Instance().Update(); 
	};

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() {
		// 背景
		for (int i = 0; i < WINDOW_H; i++) {
			int col = GetColor(20, 20, 40 + i / 10);
			DrawLine(0, i, WINDOW_W, i, col);
		}
		g_stars->Draw();

		ScreenManager::Instance().Draw(); 
		// ------ effect ------
		LineEffect::Instance().Draw();					// ラインエフェクト
		for (const auto& ef : mEffects) { ef->Draw(); }	// クリックエフェクト
	};

	/// <summary>
	/// 終了処理
	/// </summary>
	void End() {};
};
