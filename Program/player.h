#pragma once
#include "DxLib.h"
#include "body.h"
#include "define.h"
// バトルシステム
#include "battlesystem.h"
// ステータスファイル
#include "CharaState.h"

class Player : public CharaBody {
public:

	struct PlayerData
	{
		// ベースステータス
		BaseState baseState;
	};

protected:

//	int expPoint;

public:
	Player(const BaseState& data, int level, Pos pos) : CharaBody(data, level, pos){}
	~Player() {}

	void Move(const std::vector<std::shared_ptr<CharaInterface>>& enemies) override {
		if (enemies.empty()) return;
		// 敵の中からターゲットを選ぶ処理（例: 最初の敵）
		CharaInterface* target = enemies[0].get();

		BattleSystem::Instance().MoveToTarget(this, target, basestate.rg);
		BattleSystem::Instance().AttackNearestEnemy(this, enemies, basestate.rg, basestate.atk_spd); // basestate.rg以内なら攻撃
	}

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(const std::vector<std::shared_ptr<CharaInterface>>& enemies) override {
		CharaBody::Update(enemies);
	}

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override {
#ifndef	 DEBUG
		switch (basestate.handle) {
		case -1:
			ResourceManager::Instance().ShowImageLoadError("player.png", "Player");
			
			break;
		default:
			break;
		}
#endif // DEBUG
		CharaBody::Draw();
	}
};