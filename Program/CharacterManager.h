#pragma once
#include "body.h"
#include "player.h"
#include "playerfactory.h"
#include "enemy.h"
#include "enemyfactory.h"

// UIの安全性のため
#include "UICharaState.h"

// キャラクターマネージャー
class CharacterManager {
private:
    CharacterManager() {}
    ~CharacterManager() = default;
public:
    CharacterManager(const CharacterManager&) = delete;
    CharacterManager& operator=(const CharacterManager&) = delete;
    static CharacterManager& Instance() {
        static CharacterManager instance;
        return instance;
    }
private:
    std::vector<std::shared_ptr<CharaInterface>> players;
    std::vector<std::shared_ptr<CharaInterface>> enemies;
public:

    // プレイヤー追加
    CharaInterface* AddPlayer(std::unique_ptr<CharaInterface> player) {
        CharaInterface* ptr = player.get();
        players.push_back(std::move(player));
        return ptr;
    }

    // 敵追加
    CharaInterface* AddEnemy(std::unique_ptr<CharaInterface> Enemy) {
        CharaInterface* ptr = Enemy.get();
        enemies.push_back(std::move(Enemy));
        return ptr;
    }

    // 取得用インターフェース
    const std::vector<std::shared_ptr<CharaInterface>>& GetPlayers() const { return players; }
    std::vector<std::shared_ptr<CharaInterface>>& NCGetPlayers() { return players; }
    const std::vector<std::shared_ptr<CharaInterface>>& GetEnemies() const { return enemies; }
    std::vector<std::shared_ptr<CharaInterface>>& NCGetEnemies() { return enemies; }

    // プレイヤーとエネミーの全て
    std::vector<std::shared_ptr<CharaInterface>> GetAllBodies() {
        std::vector<std::shared_ptr<CharaInterface>> result;
        result.reserve(players.size() + enemies.size());
        for (auto& p : players) result.push_back(p);
        for (auto& e : enemies) result.push_back(e);
        return result;
    }

    // 敵の削除
    void ClearEnemies() {
        enemies.clear();
    }
    
    // 更新処理
    void Update() {
        IfDead();
        for (auto& p : players) p->Update(enemies);
        for (auto& e : enemies) e->Update(players);
    }

    // 描画処理
    void Draw() const {
        for (auto& p : players) p->Draw();
        for (auto& e : enemies) e->Draw();
    }

    template<typename T>
    void RemoveDead(std::vector<std::shared_ptr<T>>& list) {
        // 死んだ時の処理
        // remove_if	→ 「削除したい要素を後ろに寄せて、残すべき要素の新しい終端を返す」
        // erase		→ 「寄せられた不要部分を物理的に削除してコンテナを縮める」
        // vectorからの削除 erase
        list.erase(
            // remove_of 条件を満たす要素 CheckHp() == false を削除したい要素と判断
            // 引数 first 対象のコンテナの戦闘を指すイテレータ last 終端（最後の位置）を指すイテレータ
            std::remove_if(list.begin(), list.end(),
                // 単項述語 要素を判定する関数オブジェ trueをかえした要素は削除対象になる
                // []はラムダ式のキャプチャリスト
                [](const std::shared_ptr<T>& obj) { return !obj->CheckHp(); }),// trueなら削除したい
            list.end()
        );
    }
    // 削除の処理
    void IfDead() {
        RemoveDead(players);
        RemoveDead(enemies);
    }

    // 全消去系
    void ClearAll() {
        players.clear();
        enemies.clear();
    }

    CharaInterface* GetRandomEnemy() {
        if (enemies.empty()) return nullptr;
        int idx = rand() % enemies.size();
        return enemies[idx].get();
    }
    // 生きているプレイヤーの取得
    std::vector<CharaInterface*> GetAlivePlayers() {
        std::vector<CharaInterface*> result;
        for (auto& p : players)
            if (p->CheckHp()) result.push_back(p.get());
        return result;
    }
};