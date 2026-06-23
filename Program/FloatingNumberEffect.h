#pragma once
#include <iostream>
#include <vector>
#include "define.h"
#include "DxLib.h"

struct HealOrShieldNumber {
    int amount;
    float x, y;
    float lifetime;
    Color color;  // —Î or Â
    bool plus; // true: +, false: -
};

class FloatingNumberEffect {
private:
    std::vector<HealOrShieldNumber> numbers;
public:
    void Add(int amount, float x, float y, Color color, bool plus = true, float duration = 1.0f) {
        numbers.push_back({ amount, x, y, duration, color, plus });
    }

    void Update(float deltaTime) {
        for (auto it = numbers.begin(); it != numbers.end(); ) {
            it->y -= 50.0f * deltaTime; // ã‚ÉˆÚ“®
            it->lifetime -= deltaTime;
            if (it->lifetime <= 0)
                it = numbers.erase(it);
            else
                ++it;
        }
    }

    void Draw() {
        for (auto& num : numbers) {
            DrawFormatString((int)num.x, (int)num.y, GetColor(num.color), "%c%d", num.plus ? '+' : '-', num.amount);
        }
    }
};