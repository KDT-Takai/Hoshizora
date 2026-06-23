#pragma once
#include "shapeEffect.h"
#include <vector>
#include <memory>

class EffectManager {
private:
    std::vector<std::unique_ptr<CShapeEf>> effects;

public:
    void AddEffect(const Pos& pos) {
        effects.push_back(std::make_unique<CShapeEf>(pos));
    }

    void Update() {
        for (int i = 0; i < effects.size();) {
            effects[i]->Updata();
            if (!effects[i]->CheckEnable()) {
                effects.erase(effects.begin() + i);
            }
            else {
                i++;
            }
        }
    }

    void Draw() {
        for (auto& ef : effects) {
            ef->Draw();
        }
    }
};
