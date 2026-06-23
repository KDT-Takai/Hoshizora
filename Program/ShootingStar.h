// ShootingStar.h
#pragma once
#include <deque>
#include <vector>
#include <memory>
#include <random>
#include <cmath>
#include "DxLib.h"
#include "define.h"
#include "deltatime.h"

struct StarVec2 {
    float x{}, y{};
    StarVec2() = default;
    StarVec2(float X, float Y) : x(X), y(Y) {}
    StarVec2 operator+(const StarVec2& o) const { return { x + o.x, y + o.y }; }
    StarVec2 operator-(const StarVec2& o) const { return { x - o.x, y - o.y }; }
    StarVec2 operator*(float s) const { return { x * s, y * s }; }
};


class FrameDelta {
    // Update()に引数を渡さずにΔtを取る用の簡易タイマ
    int prev = 0;
    float dt = 1.0f / 60.0f;
public:
    FrameDelta() { prev = GetNowCount(); }
    void Tick() {
        int now = GetNowCount();
        int diff = now - prev;
        prev = now;
        if (diff < 0) diff += 24 * 60 * 60 * 1000; // 一応
        dt = diff > 0 ? diff / 1000.0f : (1.0f / 60.0f);
        if (dt > 0.05f) dt = 0.05f; // フリーズ保険
    }
    float Get() const { return dt; }
};

// 単体の流れ星
class ShootingStar {
    StarVec2 pos;
    StarVec2 vel;
    float life = 0.0f;      // 現在生存時間
    float lifeMax = 10.0f;   // 寿命（秒）
    float headRadius = 3.0f;
    std::deque<StarVec2> trail; // 軌跡（古い→新しい）
    size_t trailMax = 16;

public:
    ShootingStar(const StarVec2& start, const StarVec2& velocity,
        float life_seconds = 1.2f, float head_radius = 3.0f, size_t trail_len = 16)
        : pos(start), vel(velocity), lifeMax(life_seconds), headRadius(head_radius), trailMax(trail_len)
    {
        trail.clear();
        trail.push_back(pos);
    }

    bool IsDead() const { return life >= lifeMax; }

    void Update(float dt) {
        life += dt;
        pos = pos + vel * dt;
        // 尾の更新
        if (trail.empty() || std::hypot(pos.x - trail.back().x, pos.y - trail.back().y) > 1.0f) {
            trail.push_back(pos);
            if (trail.size() > trailMax) trail.pop_front();
        }
    }

    void Draw() const {
        // 加算合成で光を表現
        SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

        // 尾：古い点→新しい点でフェード
        for (size_t i = 1; i < trail.size(); ++i) {
            float t0 = static_cast<float>(i - 1) / static_cast<float>(trail.size());
            float t1 = static_cast<float>(i) / static_cast<float>(trail.size());
            int alpha = static_cast<int>(180 * t1); // 後ろほど薄い
            int thick = 1 + static_cast<int>(2 * (1.0f - t1)); // 先端ほど太い

            // 線の代わりに短い帯を重ねる：DrawLineAAでOK
            SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);
            DrawLineAA(trail[i - 1].x, trail[i - 1].y, trail[i].x, trail[i].y, GetColor(LIGHT_BLUE), (float)thick);
        }

        // 先端の光（小さなグロー）
        {
            float age01 = life / lifeMax;
            int a = static_cast<int>(220 * (1.0f - age01 * 0.3f)); // 少しずつ減衰
            SetDrawBlendMode(DX_BLENDMODE_ADD, a);
            DrawCircleAA(pos.x, pos.y, headRadius, 5, GetColor(YELLOW), TRUE);
        }

        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
    }
};

// 複数管理＋ランダム発生
class ShootingStarSystem {
    std::vector<std::unique_ptr<ShootingStar>> stars;
    FrameDelta timer;

    // 乱数
    std::mt19937 rng{ std::random_device{}() };
    std::uniform_real_distribution<float> spawnIntervalDist{ 0.2f, 0.6f };
    std::uniform_real_distribution<float> speedDist{ 350.0f, 700.0f };
    std::uniform_real_distribution<float> angleDist{ -10.0f * 3.1415926f / 180.0f, 15.0f * 3.1415926f / 180.0f };
    std::uniform_real_distribution<float> yDist{ 50.0f, 300.0f };
    std::uniform_real_distribution<float> lifeDist{ 2.0f, 4.5f };

    float spawnCooldown = 0.0f;

    int screenW = 1280;
    int screenH = 720;

public:
    ShootingStarSystem(int w, int h) : screenW(w), screenH(h) {}

    void SetScreenSize(int w, int h) { screenW = w; screenH = h; }

    void Update() {
        float dt = Time::Instance().GetDeltaScale();

        // 生成
        spawnCooldown -= dt;
        if (spawnCooldown <= 0.0f) {
            spawnCooldown = spawnIntervalDist(rng);

            // 画面の左上～左端の上の方から右下へ流れる
            //StarVec2 start{ -50.0f, yDist(rng) };
            //float baseAngle = -45.0f * 3.1415926f / 180.0f; // 右下方向
            //float ang = baseAngle + angleDist(rng);
            //float spd = speedDist(rng);
            //StarVec2 vel{ std::cos(ang) * spd, std::sin(ang) * spd };
            
            // 画面の右上～右端の上の方から左下へ流れる
            StarVec2 start{ screenW + 50.0f, yDist(rng) };   // 右端の外から出現
            float baseAngle = RADIAN(160.0f);
            // ランダムで少し左右にブレるようにする
            float ang = baseAngle + angleDist(rng);
            // 速度
            float spd = speedDist(rng);
            StarVec2 vel{ std::cos(ang) * spd, std::sin(ang) * spd };
            // ライフや見た目はそのまま
            float life = lifeDist(rng);
            float headR = 2.5f;
            size_t trailLen = 18;

            stars.emplace_back(std::make_unique<ShootingStar>(start, vel, life, headR, trailLen));
        }

        // 更新＆破棄
        for (auto& s : stars) {
            s->Update(dt);
        }
        stars.erase(std::remove_if(stars.begin(), stars.end(),
            [&](const std::unique_ptr<ShootingStar>& s) {
                // 画面外長く出た or 寿命
                return s->IsDead();
            }),
            stars.end());
    }

    void Draw() const {
        for (auto& s : stars) s->Draw();
    }

    // 任意の場所・方向に撃ちたいとき
    void Emit(const StarVec2& start, const StarVec2& velocity, float lifeSec = 1.2f) {
        stars.emplace_back(std::make_unique<ShootingStar>(start, velocity, lifeSec, 3.0f, 18));
    }
};
