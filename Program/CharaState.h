#pragma once
#include "type.h"
#include <string>

// 基礎ステータス
struct BaseState {
	int id;				// キャラクターID
	std::string name;	// 名前
	int hp;				// ヒットポイント
	int atk;			// 攻撃力
	int def;			// 防御力
	int hel;			// 治癒力 受ける側
	int crit_rate;		// 会心率
	int crit_dmg;		// 会心ダメージ
	int rg;				// 射程距離
	int atk_spd;		// 攻撃速度
	std::string handle;			// 画像ハンドル
	TYPE type;			// タイプ
};
// レベル反映後のステータス（保存用）
struct LevelState {
	int hp;				// ヒットポイント
	int atk;			// 攻撃力
	int def;			// 防御力
	int hel;			// 治癒力 受ける側
	int crit_rate;		// 会心率
	int crit_dmg;		// 会心ダメージ
	int rg;				// 射程距離
	int atk_spd;		// 攻撃速度
};
// 実際にゲーム内で変動する値たち
struct CurrentState {
	int atk;			// バフ・デバフ適用後の攻撃力
	int def;			// バフ・デバフ適用後の防御力
	int crit_rate;		// 会心率
	int crit_dmg;		// 会心ダメージ
	int atk_spd;		// 攻撃速度
};