#pragma once
#include <vector>
#include <memory>
#include "Skill.h"

class HealSkill : public EXSkillBase {
public:
    HealSkill(CharaInterface* owner)
        : EXSkillBase(owner, 5.0f) {} // クールタイム

    void Activate(const std::vector<std::shared_ptr<CharaInterface>>& enemies, const std::vector<std::shared_ptr<CharaInterface>>& players) override {
        owner->Heal(50);
    }

    const char* GetName() const override { return "回復"; }
};