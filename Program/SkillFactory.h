#pragma once
#include <memory>
#include "Skill.h"
#include "CharaInterface.h"
#include "BombSkill.h"
#include "HealSkill.h"
#include "BuffAtkSpeedSkill.h"
#include "ShieldSkill.h"
#include "AllHealSkill.h"

class SkillFactory {
public:
    static std::unique_ptr<EXSkillBase> CreateSkill(const std::string& skillName, CharaInterface* owner) {
        if (skillName == "Bomb") return std::make_unique<BombSkill>(owner);
        if (skillName == "Heal") return std::make_unique<HealSkill>(owner);
        if (skillName == "AtkSpeed") return std::make_unique<BuffAtkSpeedSkill>(owner);
        if (skillName == "Shield") return std::make_unique<ShieldSkill>(owner);
        if (skillName == "AllHeal") return std::make_unique<AllHealSkill>(owner);
        return nullptr;
    }
};