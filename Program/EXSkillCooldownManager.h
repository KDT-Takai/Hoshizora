#pragma once

/// <summary>
/// EXスキル共通クールダウン管理
/// </summary>
class EXSkillCooldownManager {
private:
    float currentTime = 0.0f;  // 現在の経過時間
    float maxTime = 0.0f;      // 必要時間（発動したスキルによって決まる）
    bool onCooldown = false;

public:
    static EXSkillCooldownManager& Instance() {
        static EXSkillCooldownManager instance;
        return instance;
    }

    void Update(float deltaTime) {
        if (onCooldown) {
            currentTime += deltaTime;
            if (currentTime >= maxTime) {
                onCooldown = false;
                currentTime = 0.0f;
            }
        }
    }

    bool CanUse() const { return !onCooldown; }

    void ResetCooldown() {
        onCooldown = false;
        maxTime = 0.0f;
        currentTime = 0.0f;
    }

    void StartCooldown(float cooldownTime) {
        onCooldown = true;
        maxTime = cooldownTime;
        currentTime = 0.0f;
    }

    float GetProgress() const {
        return onCooldown ? currentTime / maxTime : 1.0f;
    }
};
