#pragma once
#include <vector>
#include <memory>
#include "Skill.h"

class BombSkill : public EXSkillBase {
public:
    BombSkill(CharaInterface* owner)
        : EXSkillBase(owner, 4.0f) {} // 3.5•bƒN[ƒ‹ƒ^ƒCƒ€

    void Activate(const std::vector<std::shared_ptr<CharaInterface>>& enemies, const std::vector<std::shared_ptr<CharaInterface>>& players) override {
        for (auto& e : enemies) {
            int damage = BattleSystem::Instance().CalculateDamage(owner, e);
            damage = static_cast<int>(damage * 0.8f); // ‘S‘ÌUŒ‚‚È‚Ì‚Å80%‚É
            e->Damage(damage);
        }
    }

    const char* GetName() const override { return "”š’e"; }
};