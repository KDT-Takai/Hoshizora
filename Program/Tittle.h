#pragma once
#include "DxLib.h"
#include "define.h"
#include "ScreenBase.h"

class Tittle : public ScreenBase
{
private:
	int image;	// タイトル画像用
	int tittle;	// タイトルの文字

	// メニューボタン
	int menuX = 40;
	int menuY = 630;
	int menuW = 50;
	int menuH = 30;

	// メニューの描画
	enum MenuMode {
		NoDraw,
		DoDraw,
	};
	MenuMode mode = NoDraw;

public:

	Tittle() {
		image = LoadGraph("Data/Tittle/Image/TittleImage.jpg");
		tittle = LoadGraph("Data/Tittle/Image/TittleText.png");
	}
	virtual ~Tittle() = default;

	void Update() override;
	void Draw() override;

};