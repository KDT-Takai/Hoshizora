#include "playerfactory.h"
#include "player.h"
#include "SkillFactory.h"
#include "PassiveFactory.h"

/// <summary>
/// プレイヤーデータ
/// </summary>
/// ID、名前、ヒットポイント、攻撃力、防御力、治癒力、会心率、会心ダメージ、射程距離、攻撃速度、画像ハンドル、タイプ、経験値の量
const Player::PlayerData PlayerFactory::PlayerTable[] = {
	{BaseState{0,"OrangeSlime" , 300, 45, 10, 20, 50, 130, 80,  1, "Data/Handle/OrangeSlime.png", TYPE::FORM::FIGHTER}},
	{BaseState{1,"YellowSlime" , 300, 42, 10, 20, 50, 130, 80,  1, "Data/Handle/YellowSlime.png", TYPE::FORM::FIGHTER}},
	{BaseState{2,"BlueSlime" , 300, 20, 12, 20, 50, 130, 360, 2, "Data/Handle/BlueSlime.png", TYPE::FORM::FIGHTER}},
	{BaseState{3,"GreenSlime" , 300, 28, 12, 20, 50, 130, 300, 2, "Data/Handle/GreenSlime.png", TYPE::FORM::FIGHTER}},
	{BaseState{4,"SkyBlueSlime" , 300, 25, 12, 20, 50, 130, 100, 2, "Data/Handle/SkyBlueSlime.png", TYPE::FORM::FIGHTER}},
	{BaseState{5,"PupleSlime" , 300, 25, 12, 20, 50, 130, 60,  2, "Data/Handle/PupleSlime.png", TYPE::FORM::FIGHTER}},
	{BaseState{6,"Redlime" , 300, 25, 12, 20, 50, 130, 60,  2, "Data/Handle/Redlime.png", TYPE::FORM::FIGHTER}},
	{BaseState{7,"OrangeSlime" , 300, 25, 12, 20, 50, 130, 100, 2, "Data/Handle/OrangeSlime.png", TYPE::FORM::FIGHTER}},
};

const int PlayerFactory::PlayerTableSize = sizeof(PlayerTable) / sizeof(Player::PlayerData);

// プレイヤーキャラクター生成
std::unique_ptr<CharaBody> PlayerFactory::CreatePlayer(int ID, int level, Pos pos) {
    for (int i = 0; i < PlayerFactory::PlayerTableSize; ++i) {
        if (PlayerFactory::PlayerTable[i].baseState.id == ID) {
            auto player = std::make_unique<Player>(
                PlayerFactory::PlayerTable[i].baseState,
                level,
                pos
            );

            // スキルをセット
            switch (ID) {
            case 0: player->SetEXSkill(SkillFactory::CreateSkill("Bomb", player.get())); break;
            case 1: player->SetEXSkill(SkillFactory::CreateSkill("AllHeal", player.get())); break;
            case 2: player->SetEXSkill(SkillFactory::CreateSkill("Shield", player.get())); break;
            case 3: player->SetEXSkill(SkillFactory::CreateSkill("AtkSpeed", player.get())); break;
            case 4: player->SetEXSkill(SkillFactory::CreateSkill("Heal", player.get())); break;
            case 6: player->SetEXSkill(SkillFactory::CreateSkill("AtkSpeed", player.get())); break;
            case 7: player->SetEXSkill(SkillFactory::CreateSkill("Shield", player.get())); break;
            default: break;
            }
            // パッシブをセット
            switch (ID) {
            case 0: player->SetPassive(PassiveFactory::CreatePassive("Berserker", player.get())); break;
            case 1: player->SetPassive(PassiveFactory::CreatePassive("HalfShield", player.get())); break;
            case 2: player->SetPassive(PassiveFactory::CreatePassive("Heal", player.get())); break;
            case 3: player->SetPassive(PassiveFactory::CreatePassive("HalfShield", player.get())); break;
            case 4: player->SetPassive(PassiveFactory::CreatePassive("Berserker", player.get())); break;
            case 5: player->SetPassive(PassiveFactory::CreatePassive("Berserker", player.get())); break;
            case 6: player->SetPassive(PassiveFactory::CreatePassive("Heal", player.get())); break;
            case 7: player->SetPassive(PassiveFactory::CreatePassive("HalfShield", player.get())); break;
            default: break;
            }

            return player;
        }
    }
    return nullptr;
}