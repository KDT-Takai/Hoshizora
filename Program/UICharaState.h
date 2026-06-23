#pragma once
#include "DxLib.h"
#include <vector>
#include <memory>
#include "body.h"

class UICharaStatus {
private:
    UICharaStatus() {}
    ~UICharaStatus() = default;
public:
    UICharaStatus(const UICharaStatus&) = delete;
    UICharaStatus& operator=(const UICharaStatus&) = delete;
    static UICharaStatus& Instance() {
        static UICharaStatus instance;
        return instance;
    }
private:
    std::weak_ptr<CharaInterface> selected; // 選択中キャラ（弱参照）

    // 当たり判定（矩形）
    bool IsHitChara(const CharaInterface& chara, int mx, int my, int size = 40) {
        const Pos& p = chara.GetPos();  // ISkillOwner に GetPos() がある前提
        return (
            mx >= p.GetX() - size / 2 &&
            mx <= p.GetX() + size / 2 &&
            my >= p.GetY() - size / 2 &&
            my <= p.GetY() + size / 2
            );
    }


public:
    // 更新処理
    void Update(const std::vector<std::shared_ptr<CharaInterface>>& allBodies) {
        int mx, my;
        GetMousePoint(&mx, &my);

        if (InputManager::Instance().IsGetMouse(MOUSE_INPUT_LEFT)) {
            selected.reset(); // 選択解除
            for (auto& c : allBodies) {
                if (IsHitChara(*c, mx, my)) {
                    selected = c; // weak_ptr に代入
                    break;
                }
            }
        }
    }

    void Draw() const {
        // 選択中キャラをロック
        auto sel = selected.lock();
        if (!sel || !sel->CheckHp()) return; // 生存チェック

        const auto& level = sel->GetLevel();
        const auto& base = sel->GetBaseState();
        const auto& curr = sel->GetCurrentState();
        const auto& lvl = sel->GetLevelState();

        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
        DrawFillBox(20, 30, 250, 290, GetColor(0, 0, 0));
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        DrawFormatString(50, 50, GetColor(WHITE), "LV: %d", level);
        DrawFormatString(50, 70, GetColor(YELLOW), "Name: %s", base.name.c_str());
        DrawFormatString(50, 90, GetColor(WHITE), "HP: %d / %d", sel->GetCHp(), sel->GetMaxHp());
        DrawFormatString(50, 110, GetColor(LIGHT_BLUE), "Shield: %d", sel->GetHP().GetShield());
        DrawFormatString(50, 130, GetColor(WHITE), "Skill: %s", sel->GetSkillName());
        DrawFormatString(50, 150, GetColor(WHITE), "Passive: %s", sel->GetPassiveName());
        DrawFormatString(50, 170, GetColor(WHITE), "Atk: %d", curr.atk);
        DrawFormatString(50, 190, GetColor(WHITE), "Def: %d", curr.def);
        DrawFormatString(50, 210, GetColor(WHITE), "crit_rate: %d", curr.crit_rate);
        DrawFormatString(50, 230, GetColor(WHITE), "crit_dmg: %d", curr.crit_dmg);
        DrawFormatString(50, 250, GetColor(WHITE), "atk_spd: %d", curr.atk_spd);
    }
};