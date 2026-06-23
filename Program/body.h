#pragma once
#include <memory>
#include <vector>
#include <string>
#include <iostream>
// ------ system ------ 
#include "DxLib.h"
#include "define.h"
#include "ResourceManager.h"
#include "deltatime.h"
#include "pos.h"
#include "type.h"
// ------ game skill ------
#include "Skill.h"
#include "BombSkill.h"
#include "HealSkill.h"
#include "BuffAtkSpeedSkill.h"
// ------ passive ------
#include "Passive.h"

// ------ game system ------
#include "CharaState.h"
// ------ InterFace ------
#include "CharaInterface.h"
// ------ Effect ------
#include "FloatingNumberEffect.h"

/// <summary>
/// キャラクター基底クラス
/// </summary>
class CharaBody : public CharaInterface
{
private:
    struct TimedBuff {
        CurrentState buff;   // 追加ステート
        float duration;      // 効果時間（秒）
        float elapsed;       // 経過時間
    };
protected:
    Pos pos;             // 座標
    int level;           // レベル

    BaseState basestate;        // ベースステータス
    LevelState levelstate;      // レベル反映後ステータス
    CurrentState currentstate;  // 攻撃力や防御力など可変系

    HP hp;                          // HP管理クラス

    std::unique_ptr<EXSkillBase> EXSkill;   // スキル
    std::unique_ptr<PassiveBase> Passive;  // パッシブ

    std::vector<TimedBuff> activeBuffs;     // バフ
    FloatingNumberEffect floatingEffect;    // HPエフェクト

    /// <summary>
    /// 戦闘中の累積データ
    /// </summary>
    int damageDealtTotal = 0;       // 与えた総ダメージ
    int damageTakenTotal = 0;       // 受けた総ダメージ
    int skillUsedCountTotal = 0;    // スキル使用回数

    int handcount;
    int handx, handy;

public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    CharaBody(const BaseState& data, int level, Pos pos)
        : basestate(data), level(level), pos(pos), hp(data.hp) {
        ApplyLevel();
        ResetCurrent();
    }

    /// <summary>
    /// レベル補正を反映
    /// </summary>
    void ApplyLevel() {
        levelstate.hp = basestate.hp + (level - 1) * 10;
        levelstate.atk = basestate.atk + (level - 1) * 5;
        levelstate.def = basestate.def + (level - 1) * 3;
        levelstate.hel = basestate.hel + (level - 1) * 3;
        levelstate.crit_rate = basestate.crit_rate + (level - 1) * 3;
        levelstate.crit_dmg = basestate.crit_dmg + (level - 1) * 3;
        levelstate.rg = basestate.rg + (level - 1) * 3;
        levelstate.atk_spd = basestate.atk_spd + (level - 1) * 3;

        hp.Reset(levelstate.hp); // HPを更新
    }

    /// <summary>
    /// 可変ステータスを初期化
    /// </summary>
    void ResetCurrent() {
        currentstate.atk = levelstate.atk;
        currentstate.def = levelstate.def;
        currentstate.crit_rate = levelstate.crit_rate;
        currentstate.crit_dmg = levelstate.crit_dmg;
        currentstate.atk_spd = levelstate.atk_spd;
    }

    /// <summary>
    /// 更新処理（純粋仮想）
    /// </summary>
    void Update(const std::vector<std::shared_ptr<CharaInterface>>& enemies) override {
        hp.UpdateShield(static_cast<float>(Time::Instance().GetDeltaScale()));
        hp.Update();
        // 移動処理
        Move(enemies);
        // バフアップデート
        UpdateBuffs(static_cast<float>(Time::Instance().GetDeltaScale()));
        // effect
        floatingEffect.Update(static_cast<float>(Time::Instance().GetDeltaScale()));
        // パッシブ
        if (Passive) Passive->Update(static_cast<float>(Time::Instance().GetDeltaScale()));
        // ハンドル用
        handcount += 1;
    }
    void Move(const std::vector<std::shared_ptr<CharaInterface>>& enemies) override {}

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw() override {
        // 画像ハンドル
        CharaDraw(basestate.handle);

        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 60);
        if (hp.ShieldNon()) DrawCircleAA(pos.GetX(), pos.GetY(), 30, C_POSNUM, GetColor(LIGHT_BLUE));   // シールドの可視化
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 128);

        hp.Draw(pos.GetX(), pos.GetY() - 40);       // HPバー
        floatingEffect.Draw();                      // HPエフェクト 上に上がっていく
    }

    // キャラの画像表示
    void CharaDraw(const std::string& handle) {
        if (handle == "null") {
            DrawCircleAA(pos.GetX(), pos.GetY(), 20, C_POSNUM, GetColor(RED));
            DrawFormatString(static_cast<int>(pos.GetX()), static_cast<int>(pos.GetY()), GetColor(WHITE), "%d", basestate.id);
        }
        else {
            int hand = LoadGraph(handle.c_str());
            if (handcount >= 30) {
                handcount = 0;
                if (handx == 0 && handy == 0) {
                    handx = 16;
                    handy = 0;
                } else if(handx == 16 && handy == 0) {
                    handx = 0;
                    handy = 16;
                }
                else if (handx == 0 && handy == 16) {
                    handx = 16;
                    handy = 16;
                }
                else if (handx == 16 && handy == 16) {
                    handx = 0;
                    handy = 0;
                }
            }
            DrawRectRotaGraph(pos.GetX(), pos.GetY(),handx, handy,16, 16,3.0,0.0,hand,TRUE);
        }
    }

    // ------------------------
    // アクセッサ
    // ------------------------
    int GetLevel() const override { return level; }                  
    const BaseState& GetBaseState() const override { return basestate; }    
    const LevelState& GetLevelState() const override { return levelstate; } 
    CurrentState& GetCurrentState() override { return currentstate; }       

    // HP関連
    HP& GetHP() override { return hp; }                                   
    const HP& GetHP() const override { return hp; }                    

    void Damage(int amount) override { 
        hp.Damage(amount);
        damageTakenTotal += amount;
        floatingEffect.Add(amount, pos.GetX(), pos.GetY() - 30, RED, false);
    }      
    void Heal(int amount) override {
        hp.Heal(amount * basestate.hel);
        floatingEffect.Add(amount * basestate.hel, pos.GetX(), pos.GetY() - 30, GREEN, true);
    }
    void AddShield(int amount, float duration) override {
        hp.AddShield(amount, duration);
        floatingEffect.Add(amount, pos.GetX(), pos.GetY() - 30, BLUE, true);
    }

    bool CheckHp() const override { return hp.IsAlive(); }                  
    int  GetCHp() const override { return hp.GetCurrent(); }                
    int  GetMaxHp() const override { return hp.GetMax(); }                  

    // バフ管理
    void AddState(CurrentState addState, float duration) override {
        // 即座に加算
        currentstate.atk += addState.atk;
        currentstate.def += addState.def;
        currentstate.crit_rate += addState.crit_rate;
        currentstate.crit_dmg += addState.crit_dmg;
        currentstate.atk_spd += addState.atk_spd;

        // バフを管理リストに追加
        activeBuffs.push_back({ addState, duration, 0.0f });
    }
    // バフアップデート
    void UpdateBuffs(float deltaTime) {
        for (auto it = activeBuffs.begin(); it != activeBuffs.end(); ) {
            it->elapsed += deltaTime;
            if (it->elapsed >= it->duration) {
                // 効果終了 → ステートを戻す
                currentstate.atk -= it->buff.atk;
                currentstate.def -= it->buff.def;
                currentstate.crit_rate -= it->buff.crit_rate;
                currentstate.crit_dmg -= it->buff.crit_dmg;
                currentstate.atk_spd -= it->buff.atk_spd;

                it = activeBuffs.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    // 座標
    Pos& GetPos() override { return pos; }                                  
    const Pos& GetPos() const override { return pos; }                      

    void SetPos(const Pos& newPos) override { pos = newPos; }               

    // スキル関係
    void SetEXSkill(std::unique_ptr<EXSkillBase> skill) {
        EXSkill = std::move(skill);
    }
    // スキル発動
    void ActivateSkill(const std::vector<std::shared_ptr<CharaInterface>>& enemies, const std::vector<std::shared_ptr<CharaInterface>>& players) override {
        if (EXSkill) {
            EXSkill->TryActivate(enemies, players);
            skillUsedCountTotal++;
        }
    }
    // スキル名前取得
    const char* GetSkillName() override { if (!EXSkill) return "false"; return EXSkill->GetName(); }

    // パッシブ関係
    void SetPassive(std::unique_ptr<PassiveBase> passive) {
        Passive = std::move(passive);
    }
    // パッシブ発動
    void ActivatePassive(const std::vector<std::shared_ptr<CharaInterface>>& enemies, const std::vector<std::shared_ptr<CharaInterface>>& players) override {
        if (Passive) Passive->TryActivate(enemies, players);
    }
    // パッシブ名前取得
    const char* GetPassiveName() override { if (!Passive) return "false"; return Passive->GetName(); }

    /// <summary>
    /// リザルト表示用のゲッター
    /// </summary>
    const int GetDamageDealtTotal() override { return damageDealtTotal; }
    const int GetDamageTakenTotal() override { return damageTakenTotal; }
    const int GetSkillUsedCount() override { return skillUsedCountTotal; }

    void EnemyToDamage(int amount) override {
        damageDealtTotal += amount;
    }
};