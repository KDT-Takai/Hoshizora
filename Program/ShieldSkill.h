#pragma once
#include <vector>
#include <memory>
#include "Skill.h"

class ShieldSkill : public EXSkillBase {
public:
    ShieldSkill(CharaInterface* owner)
        : EXSkillBase(owner, 8.5f) {} // 3.5秒クールタイム

    void Activate(const std::vector<std::shared_ptr<CharaInterface>>& enemies, const std::vector<std::shared_ptr<CharaInterface>>& players) override {
        for (auto& e : players) {
            e->AddShield(e->GetMaxHp()/2, 5);
        }
    }

    const char* GetName() const override { return "シールド"; }
};