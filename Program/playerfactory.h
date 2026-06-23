#pragma once
#include "player.h"

class Player;

// プレイヤーの生成を担当するファクトリークラス
class PlayerFactory
{
private:
	// プレイヤーのデータを格納するテーブル
	static const Player::PlayerData  PlayerTable[];
	// プレイヤーのスキルを格納するテーブル

	// テーブルサイズを入れる用の変数
	static const int PlayerTableSize;

public:

	// プレイヤー生成
	static std::unique_ptr<CharaBody> CreatePlayer(int ID, int level, Pos pos);


	static int GetPlayerCount() { return PlayerTableSize; }
	static const Player::PlayerData& GetPlayerData(int id) {
		return PlayerTable[id];
	}
};