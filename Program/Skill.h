#pragma once
#include <vector>
#include <memory>
#include "CharaInterface.h"
#include "EXSkillCooldownManager.h"
#include "battlesystem.h"

/// <summary>
/// パッシブスキル基底（プレイヤーのみ）
/// </summary>
class EXSkillBase {
protected:
    CharaInterface* owner;
    float cooldown;  // 必要時間（秒）
public:
    EXSkillBase(CharaInterface* owner, float cooldown)
        : owner(owner), cooldown(cooldown) {
        EXSkillCooldownManager::Instance().ResetCooldown();
    }
    virtual ~EXSkillBase() = default;

    virtual void Activate(const std::vector<std::shared_ptr<CharaInterface>>& enemies, const std::vector<std::shared_ptr<CharaInterface>>& players) = 0;
    virtual const char* GetName() const = 0;

    float GetCooldown() const { return cooldown; }

    bool CanActivate() const {
        return EXSkillCooldownManager::Instance().CanUse();
    }

    bool TryActivate(const std::vector<std::shared_ptr<CharaInterface>>& enemies, const std::vector<std::shared_ptr<CharaInterface>>& players) {
        if (CanActivate()) {
            Activate(enemies, players);
            EXSkillCooldownManager::Instance().StartCooldown(cooldown);
            return true;
        }
        return false;
    }
};
