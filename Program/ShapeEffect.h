#pragma once
#include "DxLib.h"
#include "Pos.h"
#include "vector"
#include "memory"

//	--------------------------------------------------
//	複数の図形で作るエフェクト
//	--------------------------------------------------

//	図形情報
struct ShapeEfData
{
	Pos			mPos = {};			// 座標
	int			mDivision = 0;		// 分割数
	float		mRadius = 0.0f;		// 半径
	float		mAngle = 0.0f;		// 角度
	Pos			mMove = {};			// 移動速度
	int			mAlpha = 0;			// 透明度
	float		mSpeed = 0.0f;		// 速度
	int			mColor = 0;			// 色

	//	コンストラクタ
	ShapeEfData(Pos argPos)
	{
		// 座標
		mPos = argPos;

		// 分割数
		mDivision = GetRand(6) + 1;
		// 半径
		mRadius = (float)GetRand(3)+10;
		// 角度
		mAngle = (float)GetRand(360);
		// 透明度
		mAlpha = GetRand(30) + 80;
		// 速度
		mSpeed = (float)GetRand(1.4) + 1;

		// 移動量のベクトルを求める
		float y = mSpeed * (float)sin(mAngle);
		float x = mSpeed * (float)cos(mAngle);

		// 移動量を求める
		mMove.Set(x, y);

		int col1 = GetRand(150) + 105;
		int col3 = GetRand(150) + 105;

		// 色を決める
		mColor = GetColor(0,col1,col1);
	}

};

// 図形の透明度を変える速度
#define EF_ALPHA_SPEED 3

// 複数の図形でエフェクトを作るクラス
class CShapeEf {

	// 図形最大数
	const int mMAX = 5; // 30

	// 図形データ
	// 中身へのアクセスはポインタを使う
	std::vector<std::shared_ptr<ShapeEfData>> mObj;


public:

	// コンストラクタ
	CShapeEf(Pos argBasePos)
	{
		// 一定数実体化
		for (int i = 0; i < mMAX; i++) {
			mObj.push_back(std::make_shared<ShapeEfData>(argBasePos));
		}

	};

	// 更新
	void Updata();

	// 残りがあるか
	bool CheckEnable();

	// 描画
	void Draw();



};