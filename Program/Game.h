#pragma once
#include "ScreenBase.h"

// キャラクターマネージャー
#include "CharacterManager.h"

// デルタタイム
#include "deltatime.h"
// ゲームスピード
#include "GameSpeedManager.h"

// スキル
#include "Skill.h"
// UI
#include "UICharaState.h"
#include "UISkillBox.h"
// ユーティリティ関数群
#include "CharaUtil.h"

// パーティー
#include "Party.h"

class Game : public ScreenBase
{
public:

	static float GameTimer;
	Game();
	virtual ~Game() = default;

	void Update() override;
	void Draw() override;

	static float GetGameTimer() { return GameTimer; }

};