#pragma once
#include <vector>
#include <set>      // 自動でソートする
#include "Game.h"
#include "EnemyFactory.h"
#include "CharacterManager.h"
#include "ScreenManager.h"
#include "Result.h"
#include "MapLoader.h"
#include "body.h"

class MapManager {
private:
    int currentStage;              // 現在プレイ中のステージ番号
    int currentMap;                // 現在プレイ中のマップ番号
    std::vector<MapData> mapDataList; // 全マップデータ
    //int count;                          // カウント 敵を倒してから少しして次に行きたい
    MapManager() : currentStage(1), currentMap(1) {
        // 起動時に全マップデータをロード
        mapDataList = MapLoader::LoadFromFile("Data/Map/map_data.txt");
        // 起動時にセーブデータを読み込み
        LoadProgress();
    }

    int clearedStage;   // 最後にクリアしたステージ
    const std::string saveFile = "Data/Save/progress.txt"; // セーブファイルのパス

public:
    MapManager(const MapManager&) = delete;
    MapManager& operator=(const MapManager&) = delete;

    static MapManager& Instance() {
        static MapManager instance;
        return instance;
    }

    // マップ数/ステージ数が動的でも表示OK
    void Draw() {
        DrawFormatString(1120, 10, GetColor(WHITE), "Stage %d / Map %d", GetStage(), GetMap());
    }

    // StageSelectで選んだステージ番号をセット
    void SetStage(int stage) {
        currentStage = stage;
        currentMap = 1;   // 必ず最初のマップから開始
    }

    int GetStage() const { return currentStage; }
    int GetMap() const { return currentMap; }

    // 敵を生成
    void SpawnEnemies() {
        CharacterManager::Instance().ClearEnemies();
        for (const auto& data : mapDataList) {
            if (data.stage == currentStage && data.map == currentMap) {
                for (const auto& e : data.enemies) {
                    CharacterManager::Instance().AddEnemy(
                        EnemyFactory::CreateEnemy(e.id, e.level, e.pos)
                    );
                }
                return;
            }
        }
    }

    // ステージ進行管理
    //void UpdateProgress(float deltaTime) {
    //    if (AllEnemiesDefeated()) {
    //        currentMap++;
    //        if (!HasMap(currentStage, currentMap)) {
    //            // ステージをクリアしたので保存
    //            MapManager::Instance().SetStageCleared(currentStage);
    //            currentMap = 1;
    //            CharacterManager::Instance().ClearAll();
    //            ScreenManager::Instance().ChangeScreen<Result>();
    //            return;
    //        }
    //        SpawnEnemies();
    //    }
    //    // プレイヤーが全員死んだとき
    //    else if (AllPlayersDefeated()) {
    //        currentMap = 1;
    //        CharacterManager::Instance().ClearAll();
    //        ScreenManager::Instance().ChangeScreen<Result>();
    //    }
    //}
    
    void UpdateProgress(float deltaTime) {
        if (AllEnemiesDefeated()) {
            currentMap++;
            // リザルト用データ作成
            if (!HasMap(currentStage, currentMap)) {
                // プレイヤーの結果の情報
                ResultData data;
                data.isClear = true;
                data.clearTime = Game::GetGameTimer();
                data.totalDamageDealt = 0;
                data.totalDamageTaken = 0;

                for (auto& p : CharacterManager::Instance().GetPlayers()) {
                    ResultData::PlayerResult pr;
                    pr.charaId = p->GetBaseState().id;
                    pr.damageDealt = p->GetDamageDealtTotal();
                    pr.damageTaken = p->GetDamageTakenTotal();
                    pr.skillUsedCount = p->GetSkillUsedCount();
                    pr.isAlive = p->CheckHp();

                    data.players.push_back(pr);
                    data.totalDamageDealt += pr.damageDealt;
                    data.totalDamageTaken += pr.damageTaken;
                }
                //count++;
                //if (count >= 30) {
                //    count = 0;
                    // ステージクリア処理
                    MapManager::Instance().SetStageCleared(currentStage);
                    currentMap = 1;
                    CharacterManager::Instance().ClearAll();

                    // リザルト画面へ
                    auto dataPtr = std::make_unique<ResultData>();
                    *dataPtr = data; // コピー
                    ScreenManager::Instance().ChangeScreen<Result>(std::move(dataPtr));
                //}
            }
            SpawnEnemies();
        }
        else if (AllPlayersDefeated()) {
            // リザルト用データ作成
            ResultData data;
            data.isClear = false;
            data.clearTime = Game::GetGameTimer();

            for (auto& p : CharacterManager::Instance().GetPlayers()) {
                ResultData::PlayerResult pr;
                pr.charaId = p->GetBaseState().id;
                pr.damageDealt = p->GetDamageDealtTotal();
                pr.damageTaken = p->GetDamageTakenTotal();
                pr.skillUsedCount = p->GetSkillUsedCount();
                pr.isAlive = p->CheckHp();

                data.players.push_back(pr);
                data.totalDamageDealt += pr.damageDealt;
                data.totalDamageTaken += pr.damageTaken;
            }

            //if (count >= 30) {
            //    count = 0;
                currentMap = 1;

                CharacterManager::Instance().ClearAll();
                auto dataPtr = std::make_unique<ResultData>();
                *dataPtr = data; // コピー
                ScreenManager::Instance().ChangeScreen<Result>(std::move(dataPtr));
            //}
            return;
        }
    }

    // ステージをクリアしたときに呼び出す
    void SetStageCleared(int stage) {
        if (stage > clearedStage) {
            clearedStage = stage;  // より大きいステージ番号なら更新
            SaveProgress();
        }
    }

    // 指定ステージがクリア済みかどうか
    bool IsStageCleared(int stage) const {
        return stage <= clearedStage;
    }

    // 最大クリア済みステージ番号
    int GetClearedStage() const {
        return clearedStage;
    }

    // 総ステージ数
    int GetStageCount() const {
        std::set<int> stages;
        for (const auto& data : mapDataList) {
            stages.insert(data.stage);
        }
        return static_cast<int>(stages.size());
    }

private:
    // 敵が全員死んでいるか
    bool AllEnemiesDefeated() {
        const auto& enemies = CharacterManager::Instance().GetEnemies();
        for (const auto& e : enemies) {
            if (e->CheckHp()) return false;
        }
        return true;
    }
    // プレイヤーが全員死んでいるか
    bool AllPlayersDefeated() {
        const auto& players = CharacterManager::Instance().GetPlayers();
        for (const auto& p : players) {
            if (p->CheckHp()) return false;
        }
        return true;
    }

    // そのステージにマップが存在するか？
    bool HasMap(int stage, int map) const {
        for (const auto& data : mapDataList) {
            if (data.stage == stage && data.map == map) return true;
        }
        return false;
    }

    // そのステージが存在するか？
    bool HasStage(int stage) const {
        for (const auto& data : mapDataList) {
            if (data.stage == stage) return true;
        }
        return false;
    }

    // セーブデータ保存
    void SaveProgress() {
        std::ofstream ofs(saveFile);
        if (!ofs) return;
        ofs << "ClearedStage " << clearedStage << std::endl;
    }

    // セーブデータ読み込み
    void LoadProgress() {
        std::ifstream ifs(saveFile);
        if (!ifs) return;
        std::string label;
        ifs >> label >> clearedStage;
        if (label != "ClearedStage") {
            clearedStage = 0; // ファイル形式が違ったらリセット
        }
    }
};
