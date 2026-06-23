#pragma once
#include <cmath>
#include <vector>

#include "Pos.h"
#include "body.h"

/// <summary>
/// キャラクター共通のユーティリティ関数群
/// 計算や判定ロジックをまとめておく
/// </summary>
class CharaUtil
{
private:
    CharaUtil() {}
    ~CharaUtil() = default;
public:
    CharaUtil(const CharaUtil&) = delete;
    CharaUtil& operator=(const CharaUtil&) = delete;
    static CharaUtil& Instance() {
        static CharaUtil instance;
        return instance;
    }
public:

    /// <summary>
    /// 2点間の距離を返す
    /// </summary>
    inline float Distance(const Pos& a, const Pos& b) {
        float dx = a.GetX() - b.GetX();
        float dy = a.GetY() - b.GetY();
        return std::sqrt(dx * dx + dy * dy);
    }

    /// <summary>
    /// 2点間の角度（ラジアン）を返す
    /// </summary>
    inline float Angle(const Pos& from, const Pos& to) {
        float dx = to.GetX() - from.GetX();
        float dy = to.GetY() - from.GetY();
        return std::atan2(dy, dx);
    }

    /// <summary>
    /// 2点が一定距離以内なら true
    /// </summary>
    inline bool IsInRange(const Pos& a, const Pos& b, float range) {
        return Distance(a, b) <= range;
    }

    /// <summary>
    /// 値を min～max の範囲に収める
    /// </summary>
    template<typename T>
    inline T Clamp(T value, T minVal, T maxVal) {
        if (value < minVal) return minVal;
        if (value > maxVal) return maxVal;
        return value;
    }

    // 全 CharaBody を分離する処理
    // お互いが重ならないようにする
    inline void SeparateAllBodies(const std::vector<std::shared_ptr<CharaInterface>>& allBodies, float minDistance) {
        for (size_t i = 0; i < allBodies.size(); ++i) {
            for (size_t j = i + 1; j < allBodies.size(); ++j) {
                Pos posA = allBodies[i]->GetPos();
                Pos posB = allBodies[j]->GetPos();

                float dx = posB.GetX() - posA.GetX();
                float dy = posB.GetY() - posA.GetY();
                float distSq = dx * dx + dy * dy;

                if (distSq < minDistance * minDistance && distSq > 0.0001f) {
                    float dist = std::sqrt(distSq);
                    float overlap = (minDistance - dist) / 2.0f;

                    float nx = dx / dist;
                    float ny = dy / dist;

                    allBodies[i]->SetPos(Pos(
                        posA.GetX() - nx * overlap,
                        posA.GetY() - ny * overlap
                    ));
                    allBodies[j]->SetPos(Pos(
                        posB.GetX() + nx * overlap,
                        posB.GetY() + ny * overlap
                    ));
                }
            }
        }
    }
};