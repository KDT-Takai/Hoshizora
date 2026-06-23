#pragma once
#include "DxLib.h"
#include <vector>
#include <memory>
#include "body.h"
#include "CharacterManager.h"

class UISkillBox {
private:
    UISkillBox() {}
    ~UISkillBox() = default;
public:
    UISkillBox(const UISkillBox&) = delete;
    UISkillBox& operator=(const UISkillBox&) = delete;
    static UISkillBox& Instance() {
        static UISkillBox instance;
        return instance;
    }
public:
    struct Box {
        int x, y, width, height;
        std::shared_ptr<CharaInterface> owner;
    };

private:
    std::vector<Box> boxes;
public:
    // プレイヤーキャラを受け取りボックスを生成
    void Init(const std::vector<std::shared_ptr<CharaInterface>>& players,
        int startX = 900, int startY = 600, int boxWidth = 80, int boxHeight = 80, int gap = 10)
    {
        boxes.clear();
        for (size_t i = 0; i < players.size(); i++) {
            boxes.push_back({
                startX + (boxWidth + gap) * (int)i,
                startY,
                boxWidth,
                boxHeight,
                players[i]
                });
        }
    }

    // 更新処理（クリック判定）
    void Update() {
        int mx, my;
        GetMousePoint(&mx, &my);
        if (InputManager::Instance().IsGetMouse(MOUSE_INPUT_LEFT)) {
            for (auto& box : boxes) {
                if (mx >= box.x && mx <= box.x + box.width &&
                    my >= box.y && my <= box.y + box.height)
                {
                    if (auto owner = box.owner) {
                        if (box.owner && box.owner->CheckHp()) {
                            owner->ActivateSkill(CharacterManager::Instance().GetEnemies(), CharacterManager::Instance().GetPlayers());
                        }
                    }
                }
            }
        }
    }

    // 描画処理
    void Draw() const {
        // EXスキルゲージをUIに表示
        float progress = EXSkillCooldownManager::Instance().GetProgress();
        for (auto& box : boxes) {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
            DrawBox(box.x, box.y, box.x + box.width, box.y + box.height, GetColor(GRAY), true);
            if (box.owner && box.owner->CheckHp()) {
                DrawBox(box.x, box.y + box.height, box.x + box.width, box.y + box.height - (int)(box.height * progress), GetColor(GREEN), true);
            }
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

            if (box.owner) {
                DrawFormatString(box.x + 5, box.y + 5, GetColor(0, 0, 0), "%s", box.owner->GetSkillName());
            }
        }
    }
};
