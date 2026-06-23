#pragma once
#include "DxLib.h"
#include "body.h"
#include "define.h"
// バトルシステム
#include "battlesystem.h"

// ステータスファイル
#include "CharaState.h"

class Enemy : public CharaBody {
public:
	struct EnemyData
	{
		// ベースステータス
		BaseState baseState;
	};
protected:

public:
	Enemy(const BaseState& data, int level, Pos pos) : CharaBody(data, level, pos) {}

	~Enemy() {}

	void Move(const std::vector<std::shared_ptr<CharaInterface>>& enemies) override {
		if (enemies.empty()) return;
		// BattleSystem で移動処理
//		CharaBody* target = battle.GetClickedEnemy(enemies);
//		if (!target) return;

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
		// 基底クラスの更新処理
	//	CharaBody::Update(enemies);
	}

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override {
#ifndef	 DEBUG
		switch (basestate.handle) {
		case -1:
			ResourceManager::Instance().ShowImageLoadError("enemy.png", "Enemy");
			break;
		default:
			break;
		}
#endif // DEBUG

		CharaBody::Draw();
	}
};