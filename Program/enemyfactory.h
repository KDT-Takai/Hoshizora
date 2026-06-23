#pragma once
#include "enemy.h"

class Enemy;

// 敵の生成を担当するファクトリークラス
class EnemyFactory
{
private:
	// エネミーのデータの格納するテーブル
	static const Enemy::EnemyData EnemyTable[];
	// テーブルサイズを入れる用の変数
	static const int EnemyTableSize;

public:
	
	// エネミー作成
	static std::unique_ptr<CharaBody> CreateEnemy(int ID, int level, Pos pos);
};