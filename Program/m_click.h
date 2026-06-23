#pragma once
#include <iostream>

#include "m_effect.h"
#include "input.h"
#include "dxlib.h"

class ClickEffect : public MouseEffect
{
private:

	// 円の描画のカウント
	SETTING(int, count, 0);
	SETTING(bool, mode, 0);
	//
	SETTING(int, mouseX, 0);
	SETTING(int, mouseY, 0);
	// マウスハンドル
	std::unique_ptr<MouseHandler> inputPtr;

	// 円の最大サイズ（今後消す可能性あり）
	SETTING(float, circlesize, 0.0);

public:

	ClickEffect() : inputPtr(std::make_unique<MouseHandler>()) {}

	/// <summary>
	/// 円の処理
	/// </summary>
	void Circle() {
		if (mode){
			// カウントを増やしていく
			count++;
			// ６０フレーム内
			if (count <= 60) {
				circlesize++;
				if (circlesize > 20) circlesize = 20;
				// 描画ブレンドモードをアルファブレンドにする
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 125);
				// 円の描画
				DrawCircle(mouseX, mouseY, circlesize, GetColor(WHITE), true);
				// 描画ブレンドモードをノーブレンドに戻す。
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			} else {
				// 終了
				mode = false;
				count = 0;
			}
		}
	}

	/// <summary>
	/// 入力処理
	/// </summary>
	void Input() {
		if (inputPtr->CheckMouseHit()) {
			circlesize = 0;
			count = 0;
			mode = true;
			mouseX = GetMouseX();
			mouseY = GetMouseY();
		}
	}

	void Update() override{
		MouseEffect::Update();
		// 入力処理入力
		Input();
		// 円の処理
		Circle();
	}
};