#pragma once
#include <vector>
#include <memory>
#include "Passive.h"

class PassiveShield : public PassiveBase
{
private:
    bool flag = false;
public:
    PassiveShield(CharaInterface* owner)
        : PassiveBase(owner, 0) {
    }

    void Activate(const std::vector<std::shared_ptr<CharaInterface>>& enemies,
        const std::vector<std::shared_ptr<CharaInterface>>& players) override {
        if (owner->GetMaxHp() / 2 > owner->GetCHp() && flag == false) {
            flag = true;
            owner->AddShield(owner->GetMaxHp() / 2, 5.0f);
        }
    }

    const char* GetName() const override { return "シールド付与"; }
};