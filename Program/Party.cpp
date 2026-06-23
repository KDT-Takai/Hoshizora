#include "Party.h"
#include "ScreenManager.h"
#include "Home.h"
#include <fstream>
#include <algorithm>
#include "playerfactory.h"

Party::Party() {
    LoadParty();
    LoadPlayerData(PLAYER_SAVE_FILE);
}

void Party::Update() {
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);

    // --- スクロール処理（所持キャラリスト用） ---
    if (InputManager::Instance().GetMouseRepeat(MOUSE_INPUT_LEFT)) {
        if (!isDragging) {
            isDragging = true;
            lastMouseY = mouseY;
        }
        else {
            int dy = mouseY - lastMouseY;
            scrollY += dy;
            lastMouseY = mouseY;
        }
    }
    else {
        isDragging = false;
    }

    // スクロール範囲制限
    if (scrollY > 0) scrollY = 0;
    int maxScrollY = -(((PlayerFactory::GetPlayerCount() / colsPerRow + 1) * (boxH + margin)) - visibleHeight);
    if (scrollY < maxScrollY) scrollY = maxScrollY;

    // --- 編成解除処理 ---
    for (int i = 0; i < selectedParty.size(); i++) {
        int x = (WINDOW_W / 2 - (partyBoxW * 2 + margin * 1.5f)) + i * (partyBoxW + margin);
        int y = partyY;
        if (mouseX >= x && mouseX <= x + partyBoxW &&
            mouseY >= y && mouseY <= y + partyBoxH) {
            if (InputManager::Instance().IsGetMouse(MOUSE_INPUT_LEFT)) {
                selectedParty.erase(selectedParty.begin() + i);
                SaveParty();
                return;
            }
        }
    }

    // --- 所持キャラクリック処理 ---
    for (int i = 0; i < PlayerFactory::GetPlayerCount(); i++) {
        int row = i / colsPerRow;
        int col = i % colsPerRow;

        int x = startX + col * (boxW + margin);
        int y = startY + row * (boxH + margin) + scrollY;

        if (mouseX >= x && mouseX <= x + boxW &&
            mouseY >= y && mouseY <= y + boxH) {
            if (InputManager::Instance().IsGetMouse(MOUSE_INPUT_LEFT)) {
                if (selectedParty.size() < 4 &&
                    std::find(selectedParty.begin(), selectedParty.end(), i) == selectedParty.end()) {
                    selectedParty.push_back(i);
                    SaveParty();
                }
                return;
            }
            else if (InputManager::Instance().IsGetMouse(MOUSE_INPUT_RIGHT)) {
                // 右クリックで経験値を加算してレベルアップ
                AddExpToPlayer(i, 50);
            }
        }
    }

    // --- ホームに戻る ---
    int backX = 1000, backY = 600, backW = 200, backH = 60;
    if (mouseX >= backX && mouseX <= backX + backW &&
        mouseY >= backY && mouseY <= backY + backH) {
        if (InputManager::Instance().IsGetMouse(MOUSE_INPUT_LEFT)) {
            ScreenManager::Instance().ChangeScreen<Home>();
        }
    }

    hoveredPlayerId = -1; // 初期化

    // --- 所持キャラクリック処理 & ホバー判定 ---
    for (int i = 0; i < PlayerFactory::GetPlayerCount(); i++) {
        int row = i / colsPerRow;
        int col = i % colsPerRow;

        int x = startX + col * (boxW + margin);
        int y = startY + row * (boxH + margin) + scrollY;

        if (mouseX >= x && mouseX <= x + boxW &&
            mouseY >= y && mouseY <= y + boxH) {
            hoveredPlayerId = i; // マウスが乗っているキャラを記録

            if (InputManager::Instance().IsGetMouse(MOUSE_INPUT_LEFT)) {
                if (selectedParty.size() < 4 &&
                    std::find(selectedParty.begin(), selectedParty.end(), i) == selectedParty.end()) {
                    selectedParty.push_back(i);
                    SaveParty();
                }
                return;
            }
            else if (InputManager::Instance().IsGetMouse(MOUSE_INPUT_RIGHT)) {
                // 右クリックで経験値を加算してレベルアップ
                AddExpToPlayer(i, 50);
            }
        }
    }
}

void Party::Draw() {
    // タイトル（白文字＋縁取り＋中央寄せ）
    DrawStringToHandle(WINDOW_W / 2 - GetDrawStringWidthToHandle("Party 編成", strlen("Party 編成"), gTitleFont) / 2,
        20,
        "Party 編成",
        GetColor(255, 255, 255),
        gTitleFont);
    // --- 編成パーティ枠 ---
    for (int i = 0; i < 4; i++) {
        int x = (WINDOW_W / 2 - (partyBoxW * 2 + margin * 1.5f)) + i * (partyBoxW + margin);
        int y = partyY;
        DrawBox(x, y, x + partyBoxW, y + partyBoxH, GetColor(200, 200, 200), FALSE);

        if (i < selectedParty.size()) {
            int id = selectedParty[i];
            DrawFormatString(x + 10, y + 10, GetColor(0, 255, 0),
                "%s\n(Lv.%d)",
                PlayerFactory::GetPlayerData(id).baseState.name.c_str(),
                GetPlayerLevel(id)
            );
        }
    }

    // --- 所持キャラ --- （少し小さめ、影付き風）
    int x = 50;
    int y = startY - 30;
    DrawStringToHandle(x + 2, y + 2, "所持キャラ", GetColor(50, 50, 50), gSubFont);  // 影
    DrawStringToHandle(x, y, "所持キャラ", GetColor(200, 200, 255), gSubFont);      // 本体
    for (int i = 0; i < PlayerFactory::GetPlayerCount(); i++) {
        int row = i / colsPerRow;
        int col = i % colsPerRow;

        int x = startX + col * (boxW + margin);
        int y = startY + row * (boxH + margin) + scrollY;

        if (y + boxH < startY || y > WINDOW_H) continue; // 画面外はスキップ

        DrawBox(x, y, x + boxW, y + boxH, GetColor(100, 100, 100), FALSE);

        DrawFormatString(x + 10, y + 10, GetColor(255, 255, 0),
            "%s\nLv.%d EXP:%d",
            PlayerFactory::GetPlayerData(i).baseState.name.c_str(),
            GetPlayerLevel(i),
            GetPlayerExp(i)
        );
    }

    // --- 戻るボタン ---
    int backX = 1000, backY = 600, backW = 200, backH = 60;
    DrawBox(backX, backY, backX + backW, backY + backH, GetColor(150, 150, 150), TRUE);
    DrawFormatString(backX + 50, backY + 20, GetColor(0, 0, 0), "ホームへ戻る");

    // --- ホバー中キャラの詳細ステータス ---
    if (hoveredPlayerId >= 0) {
        auto& base = PlayerFactory::GetPlayerData(hoveredPlayerId).baseState;
        int lv = GetPlayerLevel(hoveredPlayerId);
        int exp = GetPlayerExp(hoveredPlayerId);
        
        // ← ここで補正後のステータスを算出
        LevelState ls = CalcLevelState(base, lv);

        int infoX = 900, infoY = 300;
        DrawBox(infoX, infoY, infoX + 250, infoY + 250, GetColor(30, 30, 30), TRUE);
        DrawBox(infoX, infoY, infoX + 250, infoY + 250, GetColor(200, 200, 200), FALSE);

        DrawFormatString(infoX + 10, infoY + 10, GetColor(255, 255, 255),
            "名前：%s", base.name.c_str());
        DrawFormatString(infoX + 10, infoY + 30, GetColor(255, 255, 255),
            "レベル：%d (Exp:%d)", lv, exp);
        DrawFormatString(infoX + 10, infoY + 50, GetColor(255, 255, 255),
            "HP：%d", ls.hp);
        int i = hoveredPlayerId;  // 0～partyMembers.size()-1 の範囲であること
        if (i >= 0 && i < partyMembers.size()) {
            DrawFormatString(infoX + 10, infoY + 70, GetColor(255, 255, 255),
                "スキル：%s", partyMembers[i]->GetSkillName());

            DrawFormatString(infoX + 10, infoY + 90, GetColor(255, 255, 255),
                "パッシブ：%s", partyMembers[i]->GetPassiveName());
        }
        DrawFormatString(infoX + 10, infoY + 110, GetColor(255, 255, 255),
            "攻撃力：%d", ls.atk);
        DrawFormatString(infoX + 10, infoY + 130, GetColor(255, 255, 255),
            "防御力：%d", ls.def);
        DrawFormatString(infoX + 10, infoY + 150, GetColor(255, 255, 255),
            "回復力：%d", ls.hel);
        DrawFormatString(infoX + 10, infoY + 170, GetColor(255, 255, 255),
            "会心率：%d", ls.crit_rate);
        DrawFormatString(infoX + 10, infoY + 190, GetColor(255, 255, 255),
            "会心ダメージ：%d", ls.crit_dmg);
        DrawFormatString(infoX + 10, infoY + 210, GetColor(255, 255, 255),
            "射程距離：%d", ls.rg);
        DrawFormatString(infoX + 10, infoY + 230, GetColor(255, 255, 255),
            "攻撃速度：%d", ls.atk_spd);
    }
    // フッターテキスト
    DrawFormatString(WINDOW_W / 2 - 130, WINDOW_H - 50, GetColor(180, 180, 180), "Right Mouse Click : GetExp");
}

// --- 補助関数 ---
int Party::GetPlayerLevel(int id) {
    for (auto& d : playerSaveData) {
        if (d.id == id) return d.level;
    }
    return 1;
}
int Party::GetPlayerExp(int id) {
    for (auto& d : playerSaveData) {
        if (d.id == id) return d.exp;
    }
    return 0; // 見つからなかったら0EXP
}
void Party::SaveParty() {
    std::ofstream ofs(PARTY_SAVE_FILE);
    if (!ofs) return;

    for (int i = 0; i < 4; i++) {
        if (i < selectedParty.size())
            ofs << selectedParty[i] << " ";
        else
            ofs << -1 << " ";
    }
    ofs << std::endl;
}

void Party::LoadParty() {
    for (int i = 0; i < PlayerFactory::GetPlayerCount(); i++) {
        partyMembers.push_back(PlayerFactory::CreatePlayer(i, 1, Pos(100, 100)));
    }

    std::ifstream ifs(PARTY_SAVE_FILE);
    selectedParty.clear();

    if (!ifs) return;

    for (int i = 0; i < 4; i++) {
        int id;
        ifs >> id;
        if (id >= 0 && id < PlayerFactory::GetPlayerCount()) {
            selectedParty.push_back(id);
        }
    }
}

void Party::LoadPlayerData(const std::string& filename) {
    std::ifstream ifs(filename);
    playerSaveData.clear();

    if (!ifs) return;

    int id, level, exp;
    while (ifs >> id >> level >> exp) {
        playerSaveData.push_back({ id, level, exp });
    }
}

void Party::SavePlayerData(const std::string& filename, const std::vector<PlayerSaveData>& data) {
    std::ofstream ofs(filename, std::ios::trunc);
    for (auto& d : data) {
        ofs << d.id << " " << d.level << " " << d.exp << "\n";
    }
}

void Party::AddExpToPlayer(int id, int amount) {
    for (auto& d : playerSaveData) {
        if (d.id == id) {
            d.exp += amount;

            // レベルアップ判定
            while (d.exp >= GetNextLevelExp(d.level)) {
                d.exp -= GetNextLevelExp(d.level);
                d.level++;
            }
        }
    }
    SavePlayerData(PLAYER_SAVE_FILE, playerSaveData);
}

int Party::GetNextLevelExp(int level) {
    return 100 + level * 50;  // 仮
}

LevelState Party::CalcLevelState(const BaseState& base, int level) {
    LevelState ls;
    ls.hp = base.hp + (level - 1) * 10;
    ls.atk = base.atk + (level - 1) * 5;
    ls.def = base.def + (level - 1) * 3;
    ls.hel = base.hel + (level - 1) * 3;
    ls.crit_rate = base.crit_rate + (level - 1) * 3;
    ls.crit_dmg = base.crit_dmg + (level - 1) * 3;
    ls.rg = base.rg + (level - 1) * 3;
    ls.atk_spd = base.atk_spd + (level - 1) * 3;
    return ls;
}
