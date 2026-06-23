#pragma once
#include "CharaState.h"
#include "hp.h"
/// <summary>
/// インターフェイス
/// </summary>
class CharaInterface {
public:
    virtual ~CharaInterface() = default;

    // ------------------------
    // アクセッサ
    // ------------------------
    virtual int GetLevel() const = 0;
    virtual const BaseState& GetBaseState() const = 0;
    virtual const LevelState& GetLevelState() const = 0;
    virtual CurrentState& GetCurrentState() = 0;

    virtual Pos& GetPos() = 0;
    virtual const Pos& GetPos() const = 0;
    virtual void SetPos(const Pos& newPos) = 0;

    // HP関連
    virtual HP& GetHP() = 0;
    virtual const HP& GetHP() const = 0;

    virtual void Damage(int amount) = 0;
    virtual void Heal(int amount) = 0;
    virtual void AddShield(int amount, float durationSec) = 0;
    virtual bool CheckHp() const = 0;
    virtual int  GetCHp() const = 0;
    virtual int  GetMaxHp() const = 0;

    // バフ
    virtual void AddState(CurrentState addState, float duration) = 0;

    // 描画・更新・移動系を追加
    virtual void Update(const std::vector<std::shared_ptr<CharaInterface>>& enemies) = 0;
    virtual void Draw() = 0;
    virtual void Move(const std::vector<std::shared_ptr<CharaInterface>>& enemies) = 0;

    // スキル発動
    virtual void ActivateSkill(const std::vector<std::shared_ptr<CharaInterface>>& enemies, const std::vector<std::shared_ptr<CharaInterface>>& players) = 0;
    // スキル名前取得
    virtual const char* GetSkillName() = 0;

    // パッシブ発動
    virtual void ActivatePassive(const std::vector<std::shared_ptr<CharaInterface>>& enemies, const std::vector<std::shared_ptr<CharaInterface>>& players) = 0;
    // パッシブ名前取得
    virtual const char* GetPassiveName() = 0;
    /// <summary>
    /// リザルト表示用のゲッター
    /// </summary>
    virtual const int GetDamageDealtTotal() = 0;
    virtual const int GetDamageTakenTotal() = 0;
    virtual const int GetSkillUsedCount() = 0;

    virtual void EnemyToDamage(int amount) = 0;
};