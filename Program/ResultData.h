#pragma once
#include <vector>

// リザルトデータ
struct ResultData {
	// 必要なステータス
	bool isClear = false;		// 勝利判定
	float clearTime = 0;		// クリアタイム
	int totalDamageDealt = 0;	// パーティ全体が与えた総ダメージ
	int totalDamageTaken = 0;	// パーティ全体が受けた総ダメージ
	// プレイヤー個別の戦績
	struct PlayerResult {
		int charaId = -1;		// キャラクターID
		int damageDealt = 0;	// 与えたダメージ
		int damageTaken = 0;	// 受けたダメージ
		int skillUsedCount = 0;	// スキル使用回数
		bool isAlive = false;	// 生存しているか
	};
	std::vector<PlayerResult> players; // パーティ全員分の結果
};
