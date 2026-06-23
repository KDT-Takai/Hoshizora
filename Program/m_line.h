#pragma once
#include "dxlib.h"
#include <memory>
#include <vector>

class LineEffect{
private:
    LineEffect(int lifeTime = 8)  // デフォルトで8フレーム
        : prevX(-1), prevY(-1), maxLifeTime(lifeTime), isFirstUpdate(true) {    // 初期化処理
        GetMousePoint(&mouseX, &mouseY);
    }
    ~LineEffect() = default;
public:
    LineEffect(const LineEffect&) = delete;
    LineEffect& operator=(const LineEffect&) = delete;
    static LineEffect& Instance() {
        static LineEffect instance;
        return instance;
    }
private:
    // マウス座標
    int mouseX;
    int mouseY;
    // 各線の構造体を定義（線の始点、終点、描画時間）
    struct Line {
        int startX, startY; // 始点座標
        int endX, endY;     // 終点座標
        int lifeTime;       // 残り時間（フレーム数で管理）
    };
    std::vector<Line> lines;    // 描画された線を保存するベクター
    int maxLifeTime;            // 線が残る最大時間（フレーム数）
    int prevX, prevY;           // 前回のマウス座標
    bool isFirstUpdate;         // 初回更新フラグ
public:

    void Update() {
        // マウス座標に合わせる
        GetMousePoint(&mouseX, &mouseY);

        // 前回の座標と現在の座標を結ぶ線を保存
        if (prevX != -1 && prevY != -1) {
            Line newLine = { prevX, prevY, mouseX, mouseY, maxLifeTime };
            lines.push_back(newLine);  // 新しい線を追加
        }

        // 線の寿命を減らし、寿命が切れた線を削除
        for (auto it = lines.begin(); it != lines.end();) {
            if (it->lifeTime > 0) {
                it->lifeTime--;  // 寿命を減らす
                ++it;
            } else {
                it = lines.erase(it);  // 寿命が切れた線を削除
            }
        }

        // 現在のマウス位置を前回座標として保存
        prevX = mouseX;
        prevY = mouseY;
    }

    void Draw() {
        // 線を描画
        for (auto& line : lines) {
            // 線を描画（残り時間があれば）
            if (line.lifeTime > 0) {
                float distToMouseEnd = sqrt(pow(line.endX - mouseX, 2) + pow(line.endY - mouseY, 2));
                // 始点と終点の距離がマウスに近いほど白、遠いほどシアン
                int colorEnd = 255 - static_cast<int>(distToMouseEnd / 2);
                // 始点と終点の色のグラデーション
                if (colorEnd < 0) colorEnd = 0;
                // 始点と終点の距離がマウスに近いほど線を太くする
                int thickness = 5 - static_cast<int>(distToMouseEnd / 2);
                // 太さの変化
                if (thickness < 3) thickness = 3;
                // 色を白からシアンへ変化させる
                int colorEndRGB = GetColor(0, colorEnd, 255); // シアンに近づける（青）
                // 描画ブレンドモードをアルファブレンドにする
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, 125);
                DrawLine(line.startX, line.startY, line.endX, line.endY, colorEndRGB, thickness); // 線を描画
                // 描画ブレンドモードをノーブレンドに戻す。
                SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            }
        }
    }
};
