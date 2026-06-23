#pragma once
#include "Pos.h"

//--------------------------------------------------
// 直線距離を求める関数
//--------------------------------------------------

// 2点間の長さを取得する関数
// 引数	座標１、座標２
// 戻り値	直線距離
float GetDistance(Pos pos1, Pos pos2);
template <typename T>
float GetDistance(T aX, T aY, T bX, T bY) {
	// Xの距離を求める
	float x = aX - bX;
	// Yの距離を求める
	float y = aY - bY;
	// Xの距離、Yの距離、直線距離の3つの辺でできる三角形として考え、
	// 三平方の定理を使って斜辺（直線距離）を出す
	float dis = sqrtf(x * x + y * y);
	// 直線距離の値を返す
	return dis;
};

//---------------------------------------------------------------------------------
// 当たり判定
//---------------------------------------------------------------------------------

// 円同士の当たり判定
// 引数	円１の座標、円１の半径、円２の座標、円２の半径
// 戻り値	true,false
bool CircleHit(Pos circle1, float radius1, Pos circle2, float radius2);
template <typename T>
bool CircleHit(T c_x1, T c_y1, float radius1, T c_x2, T c_y2, float radius2) {
	//	2点間の直線距離を求める
	float distance = GetDistance(c_x1, c_y1, c_x2, c_y2);
	//	2つの円の半径の合計を求める
	float radius = radius1 + radius2;
	//	2点間の直線距離が2つの半径の合計以下なら
	if (distance <= radius) {
		//	実行へ
		return true;
	}
	return false;
}

// 点と円の当たり判定
// 引数	点の座標、円の座標、円の半径
// 戻り値	true,false
bool DotCircleHit(Pos point, Pos circle, float radius);
template <typename T>
bool DotCircleHit(T pointX, T pointY, T circleX, T circleY, T radius) {
	//	2点間の直線距離を求める
	float distance = GetDistance(pointX, pointY, circleX, circleY);
	//	2点間の直線距離が円の半径以下なら
	if (distance <= radius) {
		//	実行へ
		return true;
	}
	return false;
};

////	点と円の当たり判定
////	引数	点の座標、円
////	戻り値	true,false
////bool CheckPointCircleHit(CPos point, CBase circle);
//
////	四角同士の当たり判定
////	引数	円座標、円半径、四角座標（左上）、四角幅
////	戻り値	true,false
//bool CheckBoxHit(CPos box1, CPos box1Size, CPos box2, CPos box2Size);

//	点と四角の当たり判定
//	引数	点の座標、四角の左上座標、四角の大きさ
//	戻り値	true,false
//bool CheckPointBoxHit(Pos point, Pos boxPos, float boxSize);
//
//bool CheckPointBoxHit(CPos point, CPos boxPos, float boxSize);

template <typename T>
bool CheckPointBoxHit(T px, T py, T x, T y, T w, T h) {
	return (px >= x && px <= x + w && py >= y && py <= y + h);
}

////	円と四角の当たり判定
////	円と四角の四隅のみ判定あり
////	四角が非常に大きく、円が四隅の点にあたらないときは使用不可
////	引数	円の座標、半径、四角の左上座標、四角の大きさ
////	戻り値	true,false
//bool CheckCircleBoxHit(CPos circle, float radius, CPos boxPos, CPos boxSize);
//
////	円と四角の当たり判定
////　円のｘ、円のｙ、円の半径、ボックスのｘ（左上）、ボックスのｙ（左上）、ボックスのサイズｘ、ボックスのサイズｙ
//bool CheckHitBoxCircle(float circle_x, float circle_y, float circle_r, float box_x, float box_y, float box_x_size, float box_y_size);
//
////	円と四角の当たり判定
////　円のｘ、円のｙ、円の半径、ボックスのｘ（左上）、ボックスのｙ（左上）、ボックスのサイズｘ、ボックスのサイズｙ
//bool CheckHitBoxCircle(CPos circle, float circle_r, float box_x, float box_y, float box_x_size, float box_y_size);
//
////	円と四角形の当たり判定
//bool CheckHitCircleBlock(CPos circle, float circleR, CPos boxPos, float boxSize);
//
//
////	線と円の当たり判定
//bool CheckCircleLineHit(CPos circle, float radius, CPos LinePos1, CPos LinePos2);

//	点と四角の当たり判定
bool CheckHitPointBox(const int& pointX, const int& pointY,
	const int& boxX, const int& boxY, const int& boxWidth, const int& boxHeight);
