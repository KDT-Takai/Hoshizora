#pragma once
#include "DxLib.h"
#include "define.h"
#include "ScreenBase.h"
#include "MapManager.h"

class StageSelect : public ScreenBase
{
public:
	int stageCount = MapManager::Instance().GetStageCount();
	int boxWidth = 200;
	int boxHeight = 300;
	int margin = 20;
	int startX = 50;
	int y = 200;

	int scrollX = 0;       // スクロール位置
	int targetScrollX = 0; // バウンド後に戻す位置
	bool isDragging = false;
	int lastMouseX = 0;
	int dragMoved = 0;

	StageSelect() = default;
	virtual ~StageSelect() = default;

	void Update() override;
	void Draw() override;
};