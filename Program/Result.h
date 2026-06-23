#pragma once
#include "DxLib.h"
#include "define.h"
#include "ScreenBase.h"

#include "ResultData.h"

class Result : public ScreenBase
{
private:
	// ホームに戻るボタン
	int backX = 1000;
	int backY = 600;
	int backW = 200;
	int backH = 60;

	std::unique_ptr<ResultData> result;

    // フォント
    int titleFont = -1;
    int normalFont = -1;
    int smallFont = -1;   // 小さい文字用 (22px)
    int bigFont = -1;   // 大きい文字用 (28px)
public:

	// デフォルト用（仮のリザルト）
	Result()
		: result(std::make_unique<ResultData>()) { }

	// データ受け取り用
	Result(std::unique_ptr<ResultData> data)
		: result(std::move(data))
	{}

	virtual ~Result() = default;

	void Update() override;
	void Draw() override;

    // 角丸四角を描く関数
    void DrawRoundBox(int x1, int y1, int x2, int y2, int radius, unsigned int color, bool fill) {
        // 四隅の円
        if (fill) {
            DrawCircle(x1 + radius, y1 + radius, radius, color, TRUE);
            DrawCircle(x2 - radius, y1 + radius, radius, color, TRUE);
            DrawCircle(x1 + radius, y2 - radius, radius, color, TRUE);
            DrawCircle(x2 - radius, y2 - radius, radius, color, TRUE);
        }
        else {
            DrawCircle(x1 + radius, y1 + radius, radius, color, FALSE);
            DrawCircle(x2 - radius, y1 + radius, radius, color, FALSE);
            DrawCircle(x1 + radius, y2 - radius, radius, color, FALSE);
            DrawCircle(x2 - radius, y2 - radius, radius, color, FALSE);
        }

        // 上下左右の四角でつなぐ
        if (fill) {
            DrawBox(x1 + radius, y1, x2 - radius, y2, color, TRUE);
            DrawBox(x1, y1 + radius, x2, y2 - radius, color, TRUE);
        }
        else {
            DrawLine(x1 + radius, y1, x2 - radius, y1, color);
            DrawLine(x1 + radius, y2, x2 - radius, y2, color);
            DrawLine(x1, y1 + radius, x1, y2 - radius, color);
            DrawLine(x2, y1 + radius, x2, y2 - radius, color);
        }
    }
};