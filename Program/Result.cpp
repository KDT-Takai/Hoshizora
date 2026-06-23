#include "Result.h"
#include "ScreenManager.h"
#include "Home.h"
#include "body.h"
#include "playerfactory.h"

void Result::Update() {
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    bool hoverBack = (mouseX >= backX && mouseX <= backX + backW && mouseY >= backY && mouseY <= backY + backH);

    if (hoverBack && InputManager::Instance().IsGetMouse(MOUSE_INPUT_LEFT)) {
        ScreenManager::Instance().ChangeScreen<Home>();
    }
}

void Result::Draw() {

    // フォントの初期化（最初の1回だけ）
    if (titleFont == -1) {
        titleFont = CreateFontToHandle(NULL, 60, 3, DX_FONTTYPE_EDGE);
        normalFont = CreateFontToHandle(NULL, 24, 3, DX_FONTTYPE_EDGE);
        smallFont = CreateFontToHandle(NULL, 22, 3, DX_FONTTYPE_EDGE);
        bigFont = CreateFontToHandle(NULL, 28, 3, DX_FONTTYPE_EDGE);
    }

     // タイトル
    DrawStringToHandle(100, 50, "観測結果", GetColor(255, 215, 0), titleFont);

    if (result) {
        DrawFormatStringToHandle(100, 120, GetColor(255, 255, 255),
            normalFont,
            "クリア: %s", result->isClear ? "観測成功" : "観測失敗");

        DrawFormatStringToHandle(100, 160, GetColor(255, 255, 255),
            normalFont,
            "クリアタイム: %.1f秒", result->clearTime);

        DrawFormatStringToHandle(100, 200, GetColor(255, 255, 255),
            normalFont,
            "総与ダメージ: %d", result->totalDamageDealt);

        DrawFormatStringToHandle(100, 240, GetColor(255, 255, 255),
            normalFont,
            "総被ダメージ: %d", result->totalDamageTaken);
    }

    // プレイヤー情報カード
    int y = 300;
    int cardH = 60;
    for (auto& p : result->players) {
        DrawBox(80, y - 10, 930, y - 10 + cardH, GetColor(30, 30, 60), TRUE); // カード背景
        DrawBox(80, y - 10, 930, y - 10 + cardH, GetColor(200, 200, 200), FALSE); // 枠線

        DrawFormatStringToHandle(100, y, GetColor(255, 255, 255),
            smallFont,
            "キャラクター:%d番 与えたダメージ:%d 受けたダメージ:%d 生:%s", p.charaId+1, p.damageDealt, p.damageTaken, p.isAlive ? "観測成功" : "観測失敗");

        y += cardH + 20;
    }

    // ホームに戻るボタン（角丸風に）
//    DrawRoundBox(backX, backY, backX + backW, backY + backH, 20, GetColor(200, 200, 200), TRUE); // 角丸
//    DrawRoundBox(backX, backY, backX + backW, backY + backH, 20, GetColor(100, 100, 100), FALSE); // 枠線
//    DrawFormatStringToHandle(backX + 50, backY + 20, GetColor(0, 0, 0),
//        bigFont,
//        "ホームへ戻る");
    DrawBox(backX, backY, backX + backW, backY + backH, GetColor(150, 150, 150), TRUE);
    DrawFormatString(backX + 50, backY + 20, GetColor(0, 0, 0), "ホームへ戻る");
}