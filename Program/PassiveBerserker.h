#pragma once
#include <vector>
#include <memory>
#include "Passive.h"

class PassiveBerserker : public PassiveBase
{
private:
    bool flag = false;
public:
    PassiveBerserker(CharaInterface* owner)
        : PassiveBase(owner, 0) {
    }

    void Activate(const std::vector<std::shared_ptr<CharaInterface>>& enemies,
        const std::vector<std::shared_ptr<CharaInterface>>& players) override {
        if (owner->GetHP().GetCurrent() < owner->GetMaxHp() * 0.3f && flag == false) {
            flag = true;
            // 火力を上げる
            owner->AddState(CurrentState{ 200,200,0,0,10 }, 5.0f);
        }
    }
    const char* GetName() const override { return "バーサーカー"; }
};