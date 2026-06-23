#pragma once
#include "deltatime.h"
#include <vector>

class GameSpeedManager
{
private:
	GameSpeedManager() {}
	~GameSpeedManager() = default;
public:
	GameSpeedManager(const GameSpeedManager&) = delete;
	GameSpeedManager& operator=(const GameSpeedManager&) = delete;
	static GameSpeedManager& Instance() {
		static GameSpeedManager instance;
		return instance;
	}
private:
	std::vector<float> speedOptions{ 1.0f, 1.5f, 2.0f};
	
	int currentIndex = 0;

	// ボタンの矩形情報
	int buttonX = 1150;
	int	buttonY = 30;
	int	buttonW = 80;
	int	buttonH = 32;

	// ボタン画像（未使用なら -1）
	int buttonHandle = -1;

public:

	void Update();   // マウス入力を検出して切替
	void Draw() const; // ボタンと現在倍率を描画

	
	void ResetGameSpeed() { currentIndex = 0; }

	float GetSpeed() const { return speedOptions[currentIndex]; }
};