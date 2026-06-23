#include "Home.h"
#include "ScreenManager.h"
#include "StageSelect.h"
#include "Party.h"

void Home::Update() {
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);

    // ボタン領域（中央寄せ）
    RECT stageBtn = { WINDOW_W / 2 - 150, 300, WINDOW_W / 2 + 150, 370 };
    RECT partyBtn = { WINDOW_W / 2 - 150, 420, WINDOW_W / 2 + 150, 490 };

    if (InputManager::Instance().IsGetMouse(MOUSE_INPUT_LEFT)) {
        if (mouseX >= stageBtn.left && mouseX <= stageBtn.right &&
            mouseY >= stageBtn.top && mouseY <= stageBtn.bottom) {
            ScreenManager::Instance().ChangeScreen<StageSelect>();
        }
        else if (mouseX >= partyBtn.left && mouseX <= partyBtn.right &&
            mouseY >= partyBtn.top && mouseY <= partyBtn.bottom) {
            ScreenManager::Instance().ChangeScreen<Party>();
        }
    }

}

void Home::Draw() {

    // タイトル
    //const char* title = "星空課外活動";  // ゲームタイトル
    //int titleX = WINDOW_W / 2 - 200;
    //int titleY = 150;
    //DrawString(titleX, titleY, title, GetColor(255, 255, 200));
    DrawRotaGraph(WINDOW_W / 2 - 25, WINDOW_H / 2 - 200, 0.1, 0, tittle, 1);

    // ボタン描画関数
    auto drawButton = [](int x1, int y1, int x2, int y2, const char* label, int mouseX, int mouseY) {
        bool hover = (mouseX >= x1 && mouseX <= x2 && mouseY >= y1 && mouseY <= y2);
        int boxColor = hover ? GetColor(100, 180, 255) : GetColor(80, 80, 120);
        int textColor = hover ? GetColor(255, 255, 255) : GetColor(200, 200, 200);

        DrawBox(x1, y1, x2, y2, boxColor, TRUE);
        DrawBox(x1, y1, x2, y2, GetColor(255, 255, 255), FALSE);

        int textW = GetDrawStringWidth(label, strlen(label));
        int textX = (x1 + x2) / 2 - textW / 2;
        int textY = (y1 + y2) / 2 - 8;
        DrawString(textX, textY, label, textColor);
        };

    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);

    drawButton(WINDOW_W / 2 - 150, 300, WINDOW_W / 2 + 150, 370, "Stage Select", mouseX, mouseY);
    drawButton(WINDOW_W / 2 - 150, 420, WINDOW_W / 2 + 150, 490, "Party Edit", mouseX, mouseY);

    // フッターテキスト
    DrawFormatString(WINDOW_W / 2 - 80, WINDOW_H - 50, GetColor(180, 180, 180), "Left Mouse Click");
}
