#pragma once
#include <vector>
#include <memory>
#include "Passive.h"
class PassiveHeal : public PassiveBase
{
public:
    PassiveHeal(CharaInterface* owner)
        : PassiveBase(owner, 10.0f) {
    }

    void Activate(const std::vector<std::shared_ptr<CharaInterface>>& enemies,
        const std::vector<std::shared_ptr<CharaInterface>>& players) override {
        owner->Heal(2);
    }

    const char* GetName() const override { return "í‰ñ•œ"; }
};
