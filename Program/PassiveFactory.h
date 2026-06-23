#pragma once
#include <memory>
#include "Passive.h"
#include "CharaInterface.h"
#include "PassiveHeal.h"
#include "PassiveShield.h"
#include "PassiveBerserker.h"

class PassiveFactory {
public:
    static std::unique_ptr<PassiveBase> CreatePassive(const std::string& passiveName, CharaInterface* owner) {
        if (passiveName == "Heal") return std::make_unique<PassiveHeal>(owner);
        if (passiveName == "HalfShield") return std::make_unique<PassiveShield>(owner);
        if (passiveName == "Berserker") return std::make_unique<PassiveBerserker>(owner);

    //    if (passiveName == "Bomb") return std::make_unique<BombSkill>(owner);
    //    if (passiveName == "AtkSpeed") return std::make_unique<BuffAtkSpeedSkill>(owner);
    //    if (passiveName == "Shield") return std::make_unique<ShieldSkill>(owner);
        return nullptr;
    }
};