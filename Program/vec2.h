#pragma once
#include <cmath>

// 2Dベクトル構造体
// 座標・速度・加速度・方向など、あらゆる2D演算に使用できる
struct Vec2{
    float x;
    float y;

    // コンストラクタ（デフォルト引数あり）
    Vec2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

    // ベクトル同士の加算
    Vec2 operator+(const Vec2& other) const {
        return Vec2(x + other.x, y + other.y);
    }

    // ベクトル同士の減算
    Vec2 operator-(const Vec2& other) const {
        return Vec2(x - other.x, y - other.y);
    }

    // スカラー乗算（ベクトルの拡大・縮小）
    Vec2 operator*(float scalar) const {
        return Vec2(x * scalar, y * scalar);
    }

    // 加算代入（+=）
    Vec2& operator+=(const Vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    // 減算代入（-=）
    Vec2& operator-=(const Vec2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    // ベクトルの長さ（大きさ）を返す
    float Length() const {
        return std::sqrt(x * x + y * y);
    }

    // 正規化（単位ベクトル化）して方向だけを取り出す
    Vec2 Normalized() const {
        float len = Length();
        return (len == 0.0f) ? Vec2(0, 0) : Vec2(x / len, y / len);
    }

    // 他のベクトルとの距離を計算する
    float DistanceTo(const Vec2& other) const {
        return (*this - other).Length();
    }
};
