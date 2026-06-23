#pragma once
#include <vector>
#include <memory>
#include "Skill.h"

class AllHealSkill : public EXSkillBase {
public:
    AllHealSkill(CharaInterface* owner)
        : EXSkillBase(owner, 5.0f) {
    } // クールタイム

    void Activate(const std::vector<std::shared_ptr<CharaInterface>>& enemies, const std::vector<std::shared_ptr<CharaInterface>>& players) override {
        for (auto& p : players) {
            p->Heal(20);
        }
    }

    const char* GetName() const override { return "全体回復"; }
};