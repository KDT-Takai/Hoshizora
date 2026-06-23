#pragma once
#include "DxLib.h"

/// <summary>
/// HP管理クラス（ダメージ演出 + シールド対応 + 減衰）
/// </summary>
class HP {
private:
    int current;   // 現在HP
    int maxHp;     // 最大HP
    int prev;      // ダメージ演出用のHP（前のHPを保持）

    float shield;           // 現在のシールド
    float initialShield;    // シールド付与時の値を保持
    float shieldDuration;   // シールドが持続する秒数
    float shieldTimer;      // 経過時間

public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    HP(int maxHp = 100)
        : current(maxHp), maxHp(maxHp), prev(maxHp),
        shield(0), shieldDuration(0), shieldTimer(0) {}

    /// <summary>
    /// 最大HPを変更してリセット
    /// </summary>
    void Reset(int newMaxHp) {
        maxHp = newMaxHp;
        current = maxHp;
        prev = maxHp;
        shield = 0;
        shieldDuration = 0;
        shieldTimer = 0;
    }

    /// <summary>
    /// シールドを追加する（持続時間付き）
    /// </summary>
    /// <param name="amount">追加したいシールド量</param>
    /// <param name="durationSec">シールドの持続時間（秒）</param>
    int AddShield(int amount, float durationSec) {
        shield += amount;
        initialShield = shield;
        shieldDuration = durationSec;
        shieldTimer = 0.0f;
        return amount;
    }
    
    /// <summary>
    /// シールドの確認
    /// </summary>
    /// <returns>true:シールドあり false:シールドなし</returns>
    bool ShieldNon() { return shield > 0; }

    /// <summary>
    /// ダメージ処理（まずシールドが削れる）
    /// </summary>
    void Damage(int amount) {
        if (shield > 0) {
            int absorbed = (amount <= shield) ? amount : shield;
            shield -= absorbed;
            amount -= absorbed;
        }

        if (amount > 0) {
            current -= amount;
            if (current < 0) current = 0;
        }
        // prev はすぐには減らさず、演出で後から追いつかせる
    }

    /// <summary>
    /// 回復処理（シールドは回復しない）
    /// </summary>
    void Heal(int amount) {
        current += amount;
        if (current > maxHp) current = maxHp;
        prev = current; // 回復は即反映
    }

    /// <summary>
    /// シールド減衰更新（毎フレーム呼ぶ）
    /// </summary>
    void UpdateShield(float deltaTime) {
        if (shield > 0 && shieldDuration > 0) {
            shieldTimer += deltaTime;

            if (shieldTimer >= shieldDuration) {
                // 時間切れ後は徐々に減衰させる
                const float decaySpeed = 200.0f; // 1秒あたりの減少量（調整可）
                shield -= (decaySpeed * deltaTime);

                if (shield <= 0) {
                    shield = 0;
                    shieldDuration = 0.0f;
                    shieldTimer = 0.0f;
                }
            }
        }
    }

    /// <summary>
    /// 生存確認
    /// </summary>
    bool IsAlive() const { return current > 0; }

    /// <summary>
    /// Getter
    /// </summary>
    inline int GetCurrent() const { return current; }
    inline int GetMax() const { return maxHp; }
    inline int GetShield() const { return static_cast<int>(shield); }

    /// <summary>
    /// 演出更新（1フレームごとに呼ぶ）
    /// </summary>
    void Update() {
        if (prev > current) {
            prev -= 10;
            if (prev < current) prev = current;
        }
    }

    /// <summary>
    /// HPバー描画（シールド対応）
    /// </summary>
    void Draw(float x, float y, int barWidth = 100, int barHeight = 10, int tickInterval = 200) const {

        int halfWidth = barWidth / 2;
        float unitWidth = static_cast<float>(barWidth) / static_cast<float>(maxHp);

        // HP比率
        float ratioCurr = static_cast<float>(current) / static_cast<float>(maxHp);
        float ratioPrev = static_cast<float>(prev) / static_cast<float>(maxHp);

        int drawCurr = static_cast<int>(ratioCurr * barWidth);
        int drawPrev = static_cast<int>(ratioPrev * barWidth);

        // --- 1. 減少演出（灰色） ---
        DrawDecreaseEffect(x, y, barWidth, barHeight, drawCurr, drawPrev);

        // --- 2. 現在HP（グラデーション） ---
        DrawHPBar(x, y, barHeight, drawCurr, halfWidth, ratioCurr);

        // --- 3. 枠線 ---
        DrawFrame(x, y, halfWidth, barHeight, barWidth);

        // --- 4. シールド描画 ---
        DrawShield(x, y, barHeight, halfWidth, barWidth);

        // --- 5. メモリ線 ---
        DrawTicks(x, y, halfWidth, barHeight, barWidth, unitWidth, tickInterval);
    }

    // 減少演出
    void DrawDecreaseEffect(float x, float y, int barWidth, int barHeight, int drawCurr, int drawPrev) const {
        if (drawPrev > drawCurr) {
            DrawBox(
                static_cast<int>(x) - barWidth / 2 + drawCurr,
                static_cast<int>(y) - barHeight,
                static_cast<int>(x) - barWidth / 2 + drawPrev,
                static_cast<int>(y),
                GetColor(GRAY),
                TRUE
            );
        }
    }

    // 現在HP（グラデーション）
    void DrawHPBar(float x, float y, int barHeight, int drawCurr, int halfWidth, float ratioCurr) const {
        int r = 0, g = 0, b = 0;
        if (ratioCurr > 0.5f) {
            float t = (ratioCurr - 0.5f) / 0.5f;
            r = static_cast<int>(255 * (1.0f - t));
            g = 255;
        }
        else {
            float t = ratioCurr / 0.5f;
            r = 255;
            g = static_cast<int>(255 * t);
        }

        DrawBox(
            static_cast<int>(x) - halfWidth,
            static_cast<int>(y) - barHeight,
            static_cast<int>(x) - halfWidth + drawCurr,
            static_cast<int>(y),
            GetColor(r, g, b),
            TRUE
        );
    }

    // 枠線
    void DrawFrame(float x, float y, int halfWidth, int barHeight, int barWidth) const {
        DrawLineBox(
            static_cast<int>(x) - halfWidth,
            static_cast<int>(y) - barHeight,
            static_cast<int>(x) + halfWidth,
            static_cast<int>(y),
            GetColor(255, 255, 255)
        );
    }

    // シールド描画（HPバーの上に半透明で重ねる）
    void DrawShield(float x, float y, int barHeight, int halfWidth, int barWidth) const {
        if (shield > 0) {
            float shieldRatio = static_cast<float>(shield) / static_cast<float>(maxHp);
            int drawShield = static_cast<int>(shieldRatio * barWidth);

            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128); // 半透明
            DrawBox(
                static_cast<int>(x) - halfWidth,
                static_cast<int>(y) - barHeight,
                static_cast<int>(x) - halfWidth + drawShield,
                static_cast<int>(y),
                GetColor(0, 128, 255),
                TRUE
            );
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
    }

    // メモリ線
    void DrawTicks(float x, float y, int halfWidth, int barHeight, int barWidth, float unitWidth, int tickInterval) const {
        int numTicks = maxHp / tickInterval;
        for (int i = 1; i < numTicks; i++) {
            int tickX = static_cast<int>(x) - halfWidth + static_cast<int>(i * tickInterval * unitWidth);
            DrawLine(
                tickX, static_cast<int>(y) - barHeight,
                tickX, static_cast<int>(y),
                GetColor(200, 200, 200)
            );
        }
    }
};