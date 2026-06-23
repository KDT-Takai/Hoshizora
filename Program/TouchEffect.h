#pragma once
#include <math.h>
#include <DxLib.h>

class ExpandingCircleEffect {
private:
    int x, y;             // 円の中心座標
    float radius;         // 半径
    float maxRadius;      // 最大半径
    int color;            // 円の色
    float growthSpeed;    // 半径の成長速度
    bool isActive;        // エフェクトのアクティブ状態

public:
    // コンストラクタ
    ExpandingCircleEffect(int startX, int startY, int maxRadius, int color, float growthSpeed)
        : x(startX), y(startY), maxRadius(maxRadius), color(color), growthSpeed(growthSpeed), radius(0), isActive(false) {
    }

    // マウスクリック時にエフェクトを開始
    void StartEffect(int mouseX, int mouseY) {
        x = mouseX;
        y = mouseY;
        radius = 0;          // 初期半径
        isActive = true;     // エフェクトをアクティブに
    }

    // エフェクトの更新
    void Update() {
        if (!isActive) return;

        radius += growthSpeed;  // 半径を増加させる
        if (radius > maxRadius) {
            isActive = false;  // 最大半径に達したらエフェクトを終了
        }
    }

    // エフェクトの描画
    void Draw() {
        if (isActive) {
            DrawOvalAA(x - radius, y - radius, x + radius, y + radius, 64, color, false, 2);
        }
    }

    // エフェクトがアクティブかどうか
    bool IsActive() const {
        return isActive;
    }
};