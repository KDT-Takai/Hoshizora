#pragma once
#include <vector>
#include <memory>
#include "CharaInterface.h"
#include "PassiveCooldownManager.h"

/// <summary>
/// パッシブスキル基底（プレイヤー・敵両方）
/// </summary>
class PassiveBase {
protected:
    CharaInterface* owner;
    float cooldown;
    std::unique_ptr<PassiveSkillCooldownManager> cooldownManager;  // ← スキルごとに独立管理

public:
    /// <summary>
    /// パッシブベース
    /// </summary>
    /// <param name="owner"></param>
    /// <param name="cooldown"></param>
    PassiveBase(CharaInterface* owner, float cooldown)
        : owner(owner), cooldown(cooldown),
        cooldownManager(std::make_unique<PassiveSkillCooldownManager>()) {
    }

    virtual ~PassiveBase() = default;

    virtual void Activate(const std::vector<std::shared_ptr<CharaInterface>>& enemies,
        const std::vector<std::shared_ptr<CharaInterface>>& players) = 0;

    virtual const char* GetName() const = 0;

    float GetCooldown() const { return cooldown; }

    void Update(float deltaTime) {
        cooldownManager->Update(deltaTime);
    }

    bool CanActivate() const {
        return cooldownManager->CanUse();
    }

    bool TryActivate(const std::vector<std::shared_ptr<CharaInterface>>& enemies,
        const std::vector<std::shared_ptr<CharaInterface>>& players) {
        if (CanActivate()) {
            Activate(enemies, players);
            cooldownManager->StartCooldown(cooldown);
            return true;
        }
        return false;
    }
};
