#pragma once
#include <memory>
#include <vector>
#include "Skill.h"

class BuffAtkSpeedSkill : public EXSkillBase {
public:
    BuffAtkSpeedSkill(CharaInterface* owner)
        : EXSkillBase(owner, 3.0f) {} // 2秒クールタイム

    void Activate(const std::vector<std::shared_ptr<CharaInterface>>& enemies, const std::vector<std::shared_ptr<CharaInterface>>& players) override {
        owner->AddState(CurrentState{ 0,0,0,0,100 }, 5.0f);
    }

    const char* GetName() const override { return "攻撃速度UP"; }
};