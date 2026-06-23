#include "GameSpeedManager.h"
#include "dxlib.h"
#include "define.h"
#include "HitCheck.h"

void GameSpeedManager::Update() {
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    if (InputManager::Instance().IsGetMouse(MOUSE_INPUT_LEFT)) {
        if (CheckPointBoxHit<float>(mouseX, mouseY, buttonX, buttonY, buttonX + buttonW, buttonY + buttonH)) {
            // î{ó¶Çêÿë÷
            currentIndex = (currentIndex + 1) % speedOptions.size();
        }
    }
    float newScale = speedOptions[currentIndex];
    Time::Instance().SetTimeScale(newScale);
}

void GameSpeedManager::Draw() const {
    // É{É^Éìòg
    DrawBox(buttonX, buttonY, buttonX + buttonW, buttonY + buttonH, GetColor(150, 150, 150), true);
    DrawBox(buttonX, buttonY, buttonX + buttonW, buttonY + buttonH, GetColor(50, 50, 50), false);

    DrawFormatString(buttonX + buttonW/2 - 10, buttonY + buttonH/2 - 5,GetColor(BLACK),"%.1f",Time::Instance().GetTimeScale());
}