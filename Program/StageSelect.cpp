#include "StageSelect.h"
#include "ScreenManager.h"
#include "Game.h"
#include "MapManager.h"
#include "Home.h"

void StageSelect::Update() {
    int stageCount = MapManager::Instance().GetStageCount();
    int maxUnlocked = MapManager::Instance().GetClearedStage() + 1;
    if (maxUnlocked > stageCount) maxUnlocked = stageCount;

    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);

    int totalWidth = stageCount * (boxWidth + margin);
    int maxScroll = 0;
    int minScroll = -(totalWidth - (WINDOW_W - startX - margin));

    // --- ドラッグ処理 ---
    if (InputManager::Instance().GetMouseRepeat(MOUSE_INPUT_LEFT)) {
        if (!isDragging) {
            isDragging = true;
            lastMouseX = mouseX;
            dragMoved = 0;
        }
        else {
            int dx = mouseX - lastMouseX;
            scrollX += dx;
            dragMoved += abs(dx);
            lastMouseX = mouseX;
        }
    }
    else {
        if (isDragging) {
            // ドラッグ終了時
            if (dragMoved < 5) {
                // --- クリック処理 ---
                for (int i = 0; i < stageCount; i++) {
                    int x = startX + i * (boxWidth + margin) + scrollX;
                    int stageNumber = i + 1;

                    bool isHover = (mouseX >= x && mouseX <= x + boxWidth &&
                        mouseY >= y && mouseY <= y + boxHeight);

                    if (stageNumber <= maxUnlocked && isHover) {
                        MapManager::Instance().SetStage(stageNumber);
                        ScreenManager::Instance().ChangeScreen<Game>();
                        break;
                    }
                }
            }
            // バウンド戻りのターゲットを決定
            if (scrollX > maxScroll) targetScrollX = maxScroll;
            else if (scrollX < minScroll) targetScrollX = minScroll;
            else targetScrollX = scrollX;
        }
        isDragging = false;
    }

    // --- バウンドアニメーション（ドラッグしてない時だけ） ---
    if (!isDragging) {
        // 補間でゆっくり戻す
        scrollX += static_cast<int>((targetScrollX - scrollX) * 0.2f);
    }
    // ホームに戻るボタン
    int backX = 1000;
    int backY = 600;
    int backW = 200;
    int backH = 60;
    bool hoverBack = (mouseX >= backX && mouseX <= backX + backW && mouseY >= backY && mouseY <= backY + backH);

    if (hoverBack && InputManager::Instance().IsGetMouse(MOUSE_INPUT_LEFT)) {
        ScreenManager::Instance().ChangeScreen<Home>();
    }
}

void StageSelect::Draw() {
    int stageCount = MapManager::Instance().GetStageCount();
    int maxUnlocked = MapManager::Instance().GetClearedStage() + 1;
    if (maxUnlocked > stageCount) maxUnlocked = stageCount;

    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);

    for (int i = 0; i < stageCount; i++) {
        int x = startX + i * (boxWidth + margin) + scrollX;
        int stageNumber = i + 1;

        bool isHover = (mouseX >= x && mouseX <= x + boxWidth &&
            mouseY >= y && mouseY <= y + boxHeight);

        int color;
        if (stageNumber > maxUnlocked) {
            color = GetColor(LIGHT_GRAY);
        }
        else {
            color = isHover ? GetColor(RED) : GetColor(WHITE);
        }

        //SetDrawBlendMode(DX_BLENDMODE_ADD, 0);
        //DrawFillBox(x, y, x + boxWidth, y + boxHeight, GetColor(BLUE));
        //SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        DrawBox(x, y, x + boxWidth, y + boxHeight, color, FALSE);

        DrawFormatString(x + 10, y + 20, GetColor(WHITE), "Stage %d", stageNumber);

        if (MapManager::Instance().IsStageCleared(stageNumber)) {
            DrawFormatString(x + 10, y + 60, GetColor(WHITE), "観測完了");
        }
    }

    // 戻るボタン
    int backX = 1000;
    int backY = 600;
    int backW = 200;
    int backH = 60;
    DrawBox(backX, backY, backX + backW, backY + backH, GetColor(150, 150, 150), TRUE);
    DrawFormatString(backX + 50, backY + 20, GetColor(0, 0, 0), "ホームへ戻る");
}
