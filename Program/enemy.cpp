#include "enemyfactory.h"
#include "enemy.h"
#include "PassiveFactory.h"

/// <summary>
/// 敵データ
/// </summary>
/// ID、名前、ヒットポイント、攻撃力、防御力、治癒力、会心率、会心ダメージ、射程距離、攻撃速度、画像ハンドル、タイプ、経験値の量
const Enemy::EnemyData EnemyFactory::EnemyTable[] = {
	{BaseState{0,"YellowSlime" , 300, 40, 10, 20, 50, 130, 100, 1, "Data/Handle/YellowSlime.png",TYPE::FORM::FIGHTER}},
	{BaseState{1,"RedSlime" , 300, 40, 10, 20, 50, 130, 300, 1, "Data/Handle/RedSlime.png",TYPE::FORM::HEALER}},
	{BaseState{2,"SkyBlueSlime" , 300, 20, 10, 20, 50, 130, 100, 1, "Data/Handle/SkyBlueSlime.png",TYPE::FORM::FIGHTER}},
	{BaseState{3,"BlueSlime" , 300, 20, 10, 20, 50, 130, 360, 2, "Data/Handle/BlueSlime.png",TYPE::FORM::RANGE}},
	{BaseState{4,"PinkSlime" , 300, 20, 10, 20, 50, 130, 360, 2, "Data/Handle/PinkSlime.png",TYPE::FORM::RANGE}},
	{BaseState{5,"OrangeSlime" , 300, 20, 10, 20, 50, 130, 360, 2, "Data/Handle/OrangeSlime.png",TYPE::FORM::RANGE}},
};

const int EnemyFactory::EnemyTableSize = sizeof(EnemyTable) / sizeof(Enemy::EnemyData);

// エネミーキャラクター生成
std::unique_ptr<CharaBody> EnemyFactory::CreateEnemy(int ID, int level, Pos pos) {
	//　繰り返してIDの一致があるか調べる
	for (int i = 0; i < EnemyFactory::EnemyTableSize; ++i) {
		// IDが同じ場合生成する
		if (EnemyFactory::EnemyTable[i].baseState.id == ID) {
			// インスタンス生成
			auto enemy = std::make_unique<Enemy>(EnemyTable[i].baseState, level, pos);

			// パッシブをセット
			switch (ID) {
			case 0: enemy->SetPassive(PassiveFactory::CreatePassive("Heal", enemy.get())); break;
			case 1: enemy->SetPassive(PassiveFactory::CreatePassive("HalfShield", enemy.get())); break;
			case 2: enemy->SetPassive(PassiveFactory::CreatePassive("Heal", enemy.get())); break;
			case 3: enemy->SetPassive(PassiveFactory::CreatePassive("HalfShield", enemy.get())); break;
			case 4: enemy->SetPassive(PassiveFactory::CreatePassive("Heal", enemy.get())); break;
			case 5: enemy->SetPassive(PassiveFactory::CreatePassive("Heal", enemy.get())); break;
			default: break;
			}

			return enemy;
		}
		// ID が見つからなかった場合は nullptr を返す
	}
	return nullptr;
}