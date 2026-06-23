#pragma once
#pragma once
#include <vector>   // 配列
#include <cmath>    // ← std::sqrt を使うならこれが必要
#include <unordered_map>
#include "body.h"   // CharaBody
#include "HitCheck.h"   // 当たり判定

class BattleSystem {
private:
    BattleSystem() {}
    ~BattleSystem() = default;
public:
    BattleSystem(const BattleSystem&) = delete;
    BattleSystem& operator=(const BattleSystem&) = delete;
    static BattleSystem& Instance() {
        static BattleSystem instance;
        return instance;
    }
public:
    // 指定された target に向かって移動させる（一定距離以内は近づかない）
    void MoveToTarget(CharaInterface* mover, CharaInterface* target, float minDistance) {
        // 無効なポインタやターゲットがHPなしなら終了
        if (!mover || !target || !target->GetHP().IsAlive()) return;
        // 差分ベクトル
        float dx = target->GetPos().GetX() - mover->GetPos().GetX();
        float dy = target->GetPos().GetY() - mover->GetPos().GetY();
        float len = std::sqrt(dx * dx + dy * dy);
        // もし距離が minDistance 以下なら移動しない
        if (len <= minDistance) return;
        // 移動速度（仮）
        float speed = 100.0f * Time::Instance().GetDeltaScale();
        // 移動方向の正規化＆速度適用
        Vec2 moveVec((dx / len) * speed, (dy / len) * speed);
        // 移動（PosのMove関数）
        mover->GetPos().Move(moveVec);
    }

    // マウスクリックされた敵をターゲットとして取得
    CharaInterface* GetClickedEnemy(const std::vector<std::shared_ptr<CharaInterface>>& enemies) {
        int mouseX, mouseY;
        GetMousePoint(&mouseX, &mouseY);

        for (const auto& enemy : enemies) {
            if (!enemy->GetHP().IsAlive()) continue;

            Vec2 pos = enemy->GetPos().Get();
            if (DotCircleHit(static_cast<float>(mouseX), static_cast<float>(mouseY), pos.x, pos.y, 20.0f)) {
                return enemy.get();
            }
        }
        return nullptr;
    }

    // 指定された距離内だったら一番近い敵に攻撃する
    CharaInterface* AttackNearestEnemy(
        CharaInterface* attacker,
        const std::vector<std::shared_ptr<CharaInterface>>& enemies,
        float attackRange,
        float attackInterval // 攻撃間隔
    ) {
        static std::unordered_map<CharaInterface*, float> nextAttackTime;
        float now = Time::Instance().GetTotalTime();
        if (!attacker || !attacker->GetHP().IsAlive()) return nullptr;

        if (nextAttackTime[attacker] > now) return nullptr;

        CharaInterface* nearestEnemy = nullptr;
        float nearestDist = attackRange;

        for (const auto& enemy : enemies) {
            if (!enemy->GetHP().IsAlive()) continue;

            float dx = enemy->GetPos().GetX() - attacker->GetPos().GetX();
            float dy = enemy->GetPos().GetY() - attacker->GetPos().GetY();
            float dist = std::sqrt(dx * dx + dy * dy);

            if (dist <= nearestDist) {
                nearestDist = dist;
                nearestEnemy = enemy.get();
            }
        }

        if (nearestEnemy) {
            int damage = CalculateDamage(attacker, nearestEnemy);
            attacker->EnemyToDamage(damage);
            nearestEnemy->Damage(damage);
            nextAttackTime[attacker] = now + attackInterval;
        }

        return nearestEnemy;
    }

    // --------------------------------------------------
    // ダメージ計算
    // --------------------------------------------------
    int CalculateDamage(CharaInterface* attacker, CharaInterface* target) {
        const auto& atkState = attacker->GetCurrentState();
        const auto& defState = target->GetCurrentState();

        int baseDamage = atkState.atk - defState.def / 2;
        if (baseDamage < 1) baseDamage = 1;

        double damage = baseDamage;

        bool isCritical = (rand() % 100) < atkState.crit_rate;
        if (isCritical) {
            damage *= (100 + atkState.crit_dmg) / 100.0;
        }
        attacker->EnemyToDamage(damage);
        return static_cast<int>((damage < 1) ? 1 : damage);
    }
    int CalculateDamage(CharaInterface* attacker, const std::shared_ptr<CharaInterface>& target) {
        const auto& atkState = attacker->GetCurrentState();
        const auto& defState = target->GetCurrentState();

        int baseDamage = atkState.atk - defState.def / 2;
        if (baseDamage < 1) baseDamage = 1;

        double damage = baseDamage;

        bool isCritical = (rand() % 100) < atkState.crit_rate;
        if (isCritical) {
            damage *= (100 + atkState.crit_dmg) / 100.0;
        }
        attacker->EnemyToDamage(damage);
        return static_cast<int>((damage < 1) ? 1 : damage);
    }

};