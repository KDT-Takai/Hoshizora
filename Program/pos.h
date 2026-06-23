#pragma once
#include "Vec2.h"

/// <summary>
/// 位置を表すクラス（2D）
/// プレイヤーや敵などの座標管理に使用
/// 内部的には Vec2 を用いて演算を処理
/// </summary>
class Pos {
private:

    Vec2 position;  // 実際の座標（内部ベクトル）

public:
    /// <summary>
    /// コンストラクタ（初期座標を指定）
    /// </summary>
    /// <param name="x">X座標</param>
    /// <param name="y">Y座標</param>
    Pos(float x = 0.0f, float y = 0.0f) : position(x, y) {}

    /// <summary>
    /// 座標を設定する（x, y を直接指定）
    /// </summary>
    /// <param name="x">X座標</param>
    /// <param name="y">Y座標</param>
    void Set(float x, float y) {
        position = Vec2(x, y);
    }

    /// <summary>
    /// 座標を設定する（Vec2型で指定）
    /// </summary>
    /// <param name="vec">Vec2型の座標</param>
    void Set(const Vec2& vec) {
        position = vec;
    }

    /// <summary>
    /// 現在のx座標を取得
    /// </summary>
    /// <returns>x座標</returns>
    float GetX() const {
        return position.x;
    }

    /// <summary>
    /// 現在のy座標を取得
    /// </summary>
    /// <returns>y座標</returns>
    float GetY() const {
        return position.y;
    }

    /// <summary>
    /// 現在の座標を取得
    /// </summary>
    /// <returns>Vec2型の座標</returns>
    Vec2 Get() const {
        return position;
    }

    /// <summary>
    /// 指定したベクトル分だけ移動する
    /// </summary>
    /// <param name="delta">移動量のベクトル</param>
    void Move(const Vec2& delta) {
        position += delta;
    }
    
    /// <summary>
    /// 
    /// </summary>
    void Add(const Vec2& arg) {
        position.x += arg.x;
        position.y += arg.y;
    }

    /// <summary>
    /// 他の Pos との距離を取得する
    /// </summary>
    /// <param name="other">もう一方の座標</param>
    /// <returns>距離（float）</returns>
    float DistanceTo(const Pos& other) const {
        return position.DistanceTo(other.position);
    }

    /// <summary>
    /// 指定範囲内に座標を制限する（Clamp）
    /// </summary>
    /// <param name="minX">最小X</param>
    /// <param name="maxX">最大X</param>
    /// <param name="minY">最小Y</param>
    /// <param name="maxY">最大Y</param>
    void Clamp(float minX, float maxX, float minY, float maxY) {
        if (position.x < minX) position.x = minX;
        if (position.x > maxX) position.x = maxX;
        if (position.y < minY) position.y = minY;
        if (position.y > maxY) position.y = maxY;
    }

};
