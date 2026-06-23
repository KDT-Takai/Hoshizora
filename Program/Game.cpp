#include "Game.h"
#include "PlayerFactory.h"
#include "CharacterManager.h"
#include "UISkillBox.h"
#include <algorithm>
#include <iostream>
#include <filesystem> // C++17: 存在確認用（プロジェクト設定で有効なら）
// マップ
#include "MapManager.h"

// staticなので
float Game::GameTimer = 0.0f;

namespace {
    // ファイルから (id,level,exp) を読み込む（存在しなければ空を返す）
    std::vector<Party::PlayerSaveData> LoadPlayerSaveData(const std::string& filename) {
        std::vector<Party::PlayerSaveData> out;
        std::ifstream ifs(filename);
        if (!ifs) return out;
        int id, lv, exp;
        while (ifs >> id >> lv >> exp) {
            out.push_back({ id, lv, exp });
        }
        return out;
    }

    // ファイルから編成（ID 列）を読み込む（存在しなければ空を返す）
    std::vector<int> LoadPartyFile(const std::string& filename) {
        std::vector<int> out;
        std::ifstream ifs(filename);
        if (!ifs) return out;
        int id;
        while (ifs >> id) {
            out.push_back(id);
        }
        return out;
    }
}

Game::Game() {
    GameTimer = 0;

    // 1) 育成データと編成データを読み込む
    auto playerDataList = LoadPlayerSaveData(Party::PLAYER_SAVE_FILE);
    auto partyList = LoadPartyFile(Party::PARTY_SAVE_FILE);

    // 2) partyList が空ならデフォルトを作る
    if (partyList.empty()) {
        int available = PlayerFactory::GetPlayerCount();
        int take = (std::min)(4, available);
        for (int i = 0; i < take; ++i) partyList.push_back(i);
    }

    // 3) partyList のサイズを最大4に制限
    if (partyList.size() > 4) partyList.resize(4);

    // 4) プレイヤー生成
    const int startX = 300;
    const int startY = 100;
    const int yStep = 100;

    for (size_t i = 0; i < partyList.size(); ++i) {
        int id = partyList[i];

        // 育成データから該当キャラのレベルを探す（無ければ level = 1）
        int spawnLevel = 1;
        auto it = std::find_if(playerDataList.begin(), playerDataList.end(),
            [id](const Party::PlayerSaveData& d) { return d.id == id; });
        if (it != playerDataList.end()) spawnLevel = it->level;

        Pos spawnPos(startX, startY + static_cast<int>(i) * yStep);

        auto player = PlayerFactory::CreatePlayer(id, spawnLevel, spawnPos);
        if (player) {
            CharacterManager::Instance().AddPlayer(std::move(player));
        }
        else {
            std::string msg = "Failed to create player ID: " + std::to_string(id);
            std::cerr << msg << std::endl;
        }
    }

    // 5) 敵生成（現在のステージ・マップに基づいて）
    MapManager::Instance().SpawnEnemies();

    // 6) UI 初期化（プレイヤー配列が揃っていることを前提）
    UISkillBox::Instance().Init(CharacterManager::Instance().GetPlayers()); // スキルボックス初期化

    // 7) その他初期化
    GameSpeedManager::Instance().ResetGameSpeed();
}

void Game::Update() {
    GameTimer += Time::Instance().GetDeltaScale();
    // ------ game system ------
    GameSpeedManager::Instance().Update();                                                           // ゲームスピード調整
    MapManager::Instance().UpdateProgress(Time::Instance().GetDeltaScale());                        // ステージ進行管理
    CharaUtil::Instance().SeparateAllBodies(CharacterManager::Instance().GetAllBodies(), 40.0f);      // 衝突回避
    CharacterManager::Instance().Update();                                                           // キャラクターアップデート

    // ------ game skill ------
    EXSkillCooldownManager::Instance().Update(Time::Instance().GetDeltaScale());                     // EXスキルのクールダウン

    // ------ game ui ------
    UICharaStatus::Instance().Update(CharacterManager::Instance().GetAllBodies());                   // キャラクターステータス
    UISkillBox::Instance().Update();                                                                  // スキルボックス

    // ------ passive activation ------
    auto& players = CharacterManager::Instance().GetPlayers();
    for (auto& p : players) p->ActivatePassive(CharacterManager::Instance().GetEnemies(), players);

    auto& enemies = CharacterManager::Instance().GetEnemies();
    for (auto& e : enemies) e->ActivatePassive(CharacterManager::Instance().GetEnemies(), players);
}

void Game::Draw() {
    DrawFormatString(10,10,GetColor(WHITE),"Timer:%.2f",GameTimer);
    // ------ system ------
    GameSpeedManager::Instance().Draw();     // ゲームスピード表示

    // ------ game ------
    CharacterManager::Instance().Draw();     // キャラクター描画

    // ------ ui ------
    UICharaStatus::Instance().Draw();        // キャラクターステータス
    UISkillBox::Instance().Draw();           // スキルボックス
    MapManager::Instance().Draw();           // ステージ/マップ表示
}
