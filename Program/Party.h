#pragma once
#include "DxLib.h"
#include "define.h"
#include "ScreenBase.h"
#include <vector>
#include <fstream>
#include <string>
#include "CharaState.h"
#include "body.h"

class Party : public ScreenBase
{
private:
    // スクロール関連
    int scrollY = 0;         // 現在のスクロール位置
    bool isDragging = false; // ドラッグ中かどうか
    int lastMouseY = 0;      // 直前のマウス座標（ドラッグ判定用）

    // レイアウト用
    const int startX = 50;
    const int startY = 400;       // 所持キャラリストの描画開始位置
    const int boxW = 120;         // 所持キャラの枠の幅
    const int boxH = 60;          // 所持キャラの枠の高さ
    const int margin = 20;        // キャラ間の余白
    const int colsPerRow = 6;     // 1行あたりのキャラ数
    const int visibleHeight = 250;// スクロール可能な高さ

    // 編成枠
    const int partyBoxW = 150;
    const int partyBoxH = 80;
    const int partyY = 150;       // 編成枠のY座標

    std::vector<int> selectedParty;   // 選択したパーティ（最大4人）

    int hoveredPlayerId = -1; // ホバー中キャラID

    void SaveParty();
    void LoadParty();

    int gTitleFont = CreateFontToHandle("ＭＳ ゴシック", 36, 6, DX_FONTTYPE_ANTIALIASING_EDGE);
    int gSubFont = CreateFontToHandle("ＭＳ ゴシック", 22, 4, DX_FONTTYPE_ANTIALIASING_EDGE);

    std::vector<std::unique_ptr<CharaBody>> partyMembers;

public:
    // プレイヤーのセーブデータ
    struct PlayerSaveData {
        int id;
        int level;
        int exp;
    };

    std::vector<PlayerSaveData> playerSaveData; // ← メンバに追加


    Party();
    virtual ~Party() = default;

    void Update() override;
    void Draw() override;

    // 保存ファイル名（統一）
    static constexpr const char* PLAYER_SAVE_FILE = "Data/Save/playerdata.txt";
    static constexpr const char* PARTY_SAVE_FILE = "Data/Save/party.txt";

    int GetPlayerLevel(int id);
    int GetPlayerExp(int id);
    void LoadPlayerData(const std::string& filename);
    void SavePlayerData(const std::string& filename, const std::vector<PlayerSaveData>& data);
    void AddExpToPlayer(int id, int amount);
    int GetNextLevelExp(int level);
    LevelState CalcLevelState(const BaseState& base, int level);
};