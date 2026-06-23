#include "HitCheck.h"
#include "math.h"

//--------------------------------------------------
// 直線距離を求める関数
//--------------------------------------------------

// 2点間の長さを取得する関数
// 引数	座標１、座標２
// 戻り値	直線距離
float GetDistance(Pos pos1, Pos pos2)
{
	// Xの距離を求める
	float x = pos1.GetX() - pos2.GetX();
	// Yの距離を求める
	float y = pos1.GetY() - pos2.GetY();
	// Xの距離、Yの距離、直線距離の3つの辺でできる三角形として考え、
	// 三平方の定理を使って斜辺（直線距離）を出す
	float dis = sqrtf(x * x + y * y);

	// 直線距離の値を返す
	return dis;
}

//---------------------------------------------------------------------------------
// 当たり判定
//---------------------------------------------------------------------------------

// 円同士の当たり判定
// 引数	円１の座標、円１の半径、円２の座標、円２の半径
// 戻り値	true,false
bool CircleHit(Pos circle1, float radius1, Pos circle2, float radius2)
{
	//	2点間の直線距離を求める
	float distance = GetDistance(circle1, circle2);
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
bool DotCircleHit(Pos point, Pos circle, float radius)
{
	//	2点間の直線距離を求める
	float distance = GetDistance(point, circle);
	//	2点間の直線距離が円の半径以下なら
	if (distance <= radius) {
		//	実行へ
		return true;
	}
	return false;
}

////	点と円の当たり判定
////	引数	点の座標、円
////	戻り値	true,false
////bool CheckPointCircleHit(CPos point, CBase circle)
////{
////	//	2点間の直線距離を求める
////	float distance = GetDistance(point, circle.GetPos());
////
////	//	2点間の直線距離が円の半径以下なら
////	if (distance <= circle.GetRadius()) {
////
////		//	実行へ
////		return true;
////	}
////
////	return false;
////}

//	四角同士の当たり判定
//	引数	円座標、円半径、四角座標（左上）、四角幅
//	戻り値	true,false
//bool CheckBoxHit(Pos box1, Pos box1Size, Pos box2, Pos box2Size)
//{
//	//	Xの当たり判定
//	if (box1.GetX() + box1Size.GetX() >= box2.GetX() &&
//		box1.GetX() <= box2.GetX() + box2Size.GetX()) {
//		//	Yの当たり判定
//		if (box1.GetY() + box1Size.GetY() >= box2.GetY() &&
//			box1.GetY() <= box2.GetY() + box2Size.GetY()) {
//
//			//	実行へ
//			return true;
//		}
//	}
//
//	return false;
//}

////	点と四角の当たり判定
////	引数	点の座標、四角の左上座標、四角の大きさ
////	戻り値	true,false
//bool CheckPointBoxHit(CPos point, CPos boxPos, CPos boxSize)
//{
//	//	Xの当たり判定
//	if (point.GetX() >= boxPos.GetX() &&
//		point.GetX() <= boxPos.GetX() + boxSize.GetX()) {
//		//	Yの当たり判定
//		if (point.GetY() >= boxPos.GetY() &&
//			point.GetY() <= boxPos.GetY() + boxSize.GetY()) {
//
//			//	実行へ
//			return true;
//		}
//	}
//
//	return false;
//}
//
////	点と四角の当たり判定
////	引数	点の座標、四角の左上座標、四角の大きさ
////	戻り値	true,false
//bool CheckPointBoxHit(CPos point, CPos boxPos, float boxSize)
//{
//	//	Xの当たり判定
//	if (point.GetX() >= boxPos.GetX() &&
//		point.GetX() <= boxPos.GetX() + boxSize) {
//		//	Yの当たり判定
//		if (point.GetY() >= boxPos.GetY() &&
//			point.GetY() <= boxPos.GetY() + boxSize) {
//
//			//	実行へ
//			return true;
//		}
//	}
//
//	return false;
//}
////	円と四角の当たり判定
////	円と四角の四隅のみ判定あり
////	四角が非常に大きく、円が四隅の点にあたらないときは使用不可
////	引数	円の座標、半径、四角の左上座標、四角の大きさ
////	戻り値	true,false
//bool CheckCircleBoxHit(CPos circle, float radius, CPos boxPos, CPos boxSize)
//{
//	//	一番近い点を記録する変数
//	CPos nearPos = {};
//
//	//	左側
//	if (nearPos.GetX() < boxPos.GetX()) {
//		nearPos.SetX(boxPos.GetX());
//	}
//	//	右側
//	if (nearPos.GetX() > boxPos.GetX() + boxSize.GetX()) {
//		nearPos.SetX(boxPos.GetX() + boxSize.GetX());
//	}
//	//	上側
//	if (nearPos.GetY() < boxPos.GetY()) {
//		nearPos.SetY(boxPos.GetY());
//	}
//	//	下側
//	if (nearPos.GetY() > boxPos.GetY() + boxSize.GetY()) {
//		nearPos.SetY(boxPos.GetY() + boxSize.GetY());
//	}
//
//	//	円と点の当たり判定
//	if (CheckPointCircleHit(nearPos, circle, radius)) {
//
//		//	実行
//		return true;
//	}
//
//	return false;
//}
//
////	円と四角の当たり判定
////　円のｘ、円のｙ、円の半径、ボックスのｘ（左上）、ボックスのｙ（左上）、ボックスのサイズｘ、ボックスのサイズｙ
//bool CheckHitBoxCircle(float circle_x, float circle_y, float circle_r, float box_x, float box_y, float box_x_size, float box_y_size) {
//	//　左上
//	float left_above_x = box_x - circle_x;
//	float left_above_y = box_y - circle_y;
//	float left_above = sqrtf(left_above_x * left_above_x + left_above_y * left_above_y);
//	//　右上
//	float right_above_x = box_x + box_x_size - circle_x;
//	float right_above_y = box_y - circle_y;
//	float right_above = sqrtf(right_above_x * right_above_x + right_above_y * right_above_y);
//	//　左下
//	float left_under_x = box_x - circle_x;
//	float left_under_y = box_y + box_y_size - circle_y;
//	float left_under = sqrtf(left_under_x * left_under_x + left_under_y * left_under_y);
//	//　右下
//	float right_under_x = box_x + box_x_size - circle_x;
//	float right_under_y = box_y + box_y_size - circle_y;
//	float right_under = sqrtf(right_under_x * right_under_x + right_under_y * right_under_y);
//	if (left_above <= circle_r || right_above <= circle_r || left_under <= circle_r || right_under <= circle_r ||
//		circle_x + circle_r >= box_x + circle_r && circle_x - circle_r <= box_x + box_x_size - circle_r &&
//		circle_y + circle_r >= box_y && circle_y - circle_r <= box_y + box_y_size || circle_x + circle_r >= box_x &&
//		circle_x - circle_r <= box_x + box_x_size && circle_y + circle_r >= box_y + circle_r &&
//		circle_y - circle_r <= box_y + box_y_size - circle_r) {
//
//		return true;
//	}
//	else {
//		return false;
//	}
//}
//
////	円と四角の当たり判定
////　円の座標、円の半径、ボックスのｘ（左上）、ボックスのｙ（左上）、ボックスのサイズｘ、ボックスのサイズｙ
//bool CheckHitBoxCircle(CPos circle, float circle_r, float box_x, float box_y, float box_x_size, float box_y_size) {
//
//	float circle_x = circle.GetX();
//	float circle_y = circle.GetY();
//
//	//　左上
//	float left_above_x = box_x - circle_x;
//	float left_above_y = box_y - circle_y;
//	float left_above = sqrtf(left_above_x * left_above_x + left_above_y * left_above_y);
//	//　右上
//	float right_above_x = box_x + box_x_size - circle_x;
//	float right_above_y = box_y - circle_y;
//	float right_above = sqrtf(right_above_x * right_above_x + right_above_y * right_above_y);
//	//　左下
//	float left_under_x = box_x - circle_x;
//	float left_under_y = box_y + box_y_size - circle_y;
//	float left_under = sqrtf(left_under_x * left_under_x + left_under_y * left_under_y);
//	//　右下
//	float right_under_x = box_x + box_x_size - circle_x;
//	float right_under_y = box_y + box_y_size - circle_y;
//	float right_under = sqrtf(right_under_x * right_under_x + right_under_y * right_under_y);
//	if (left_above <= circle_r || right_above <= circle_r || left_under <= circle_r || right_under <= circle_r ||
//		circle_x + circle_r >= box_x + circle_r && circle_x - circle_r <= box_x + box_x_size - circle_r &&
//		circle_y + circle_r >= box_y && circle_y - circle_r <= box_y + box_y_size || circle_x + circle_r >= box_x &&
//		circle_x - circle_r <= box_x + box_x_size && circle_y + circle_r >= box_y + circle_r &&
//		circle_y - circle_r <= box_y + box_y_size - circle_r) {
//
//		return true;
//	}
//	return false;
//}
//
////	円と四角の当たり判定
//bool CheckHitCircleBlock(CPos circle, float circleR, CPos boxPos, float boxSize)
//{
//	//	縦長の四角で判定
//	CPos box1LeftUp;
//	CPos box1size;
//	box1LeftUp.Set(boxPos.GetX(), boxPos.GetY() + circleR);
//	box1size.Set(boxSize, boxSize + (circleR * 2));
//	if (CheckPointBoxHit(circle, box1LeftUp, box1size))
//	{
//		return true;
//	}
//
//	//	横長の四角で判定
//	CPos box2LeftUp;
//	CPos box2size;
//	box2LeftUp.Set(boxPos.GetX() + circleR, boxPos.GetY() );
//	box2size.Set(boxSize + (circleR * 2), boxSize );
//	if (CheckPointBoxHit(circle, box2LeftUp, box2size))
//	{
//		return true;
//	}
//
//	//	一番近い点を記録する変数
//	CPos nearPos = {};
//
//	//	左側
//	if (nearPos.GetX() < boxPos.GetX()) {
//		nearPos.SetX(boxPos.GetX());
//	}
//	//	右側
//	if (nearPos.GetX() > boxPos.GetX() + boxSize) {
//		nearPos.SetX(boxPos.GetX() + boxSize);
//	}
//	//	上側
//	if (nearPos.GetY() < boxPos.GetY()) {
//		nearPos.SetY(boxPos.GetY());
//	}
//	//	下側
//	if (nearPos.GetY() > boxPos.GetY() + boxSize) {
//		nearPos.SetY(boxPos.GetY() + boxSize);
//	}
//	//	円と点の当たり判定
//	if (CheckPointCircleHit(circle, nearPos, circleR)) 
//	{
//		return true;
//	}
//
//	return false;
//}
//
////	線と円の当たり判定
//bool CheckCircleLineHit(CPos circle, float radius, CPos LinePos1, CPos LinePos2)
//{
//	//	線の長さ
//	//	始点と終点
//	float lineLength = GetDistance(LinePos1, LinePos2);
//	//	線の始点と終点
//	//	水平な線との角度
//	float lineXv = LinePos1.GetX() - LinePos2.GetX();
//	float lineYv = LinePos1.GetY() - LinePos2.GetY();
//	float lineRot = atan2f(lineYv, lineXv);
//
//	//	x = 線の開始座標から円までのベクトルx
//	float disXv = LinePos1.GetX() - circle.GetX();
//	float disYv = LinePos1.GetY() - circle.GetY();
//	float lineRot2 = atan2f(disYv, disXv);
//
//	//	三角形として見たときの内角の大きさ
//	float rot = lineRot - lineRot2;
//
//	//	円と線の距離
//	//	始点と円の中心
//	float disLength = GetDistance(LinePos1, circle);
//
//	//	当たり判定に使う直線
//	//	円から線への最短距離
//	//	内角に斜辺をsinを使ってかけて求める
//	float hitDis = disLength * (float)sin(rot);
//
//	//	絶対値に変換
//	if (hitDis < 0) {
//		hitDis *= -1;
//	}
//
//	//	線分の範囲内かどうか
//	float posUp;
//	float posDown;
//	float posLeft;
//	float posRight;
//
//	//	上下左右の点の位置を確認
//
//	//	始点が終点より上側にあるなら
//	if (LinePos1.GetY() < LinePos2.GetY()) {
//		//	上側の点指定
//		posUp = LinePos1.GetY();
//		//	下側の点指定
//		posDown = LinePos2.GetY();
//	}
//	else {
//		//	上側の点指定
//		posUp = LinePos2.GetY();
//		//	下側の点指定
//		posDown = LinePos1.GetY();
//	}
//
//	//	始点が終点より左側にあるなら
//	if (LinePos1.GetX() < LinePos2.GetX()) {
//		//	左側の点指定
//		posLeft = LinePos1.GetX();
//		//	右側の点指定
//		posRight = LinePos2.GetX();
//	}
//	else {
//		//	左側の点指定
//		posLeft = LinePos2.GetX();
//		//	右側の点指定
//		posRight = LinePos1.GetX();
//	}
//
//	//	半径の値だけ範囲をずらしておく
//	posUp -= radius / 2;
//	posDown += radius / 2;
//	posLeft -= radius / 2;
//	posRight += radius / 2;
//
//	//	円の中心のX座標が
//	//	小さい方の値に半径を引いた値より大きく
//	//	大きい方の値に半径を足した値より小さければ
//	if (circle.GetX() >= posLeft && circle.GetX() <= posRight) {
//
//		//	Y座標も同じ判定をとる
//		if (circle.GetY() >= posUp && circle.GetX() <= posRight) {
//
//			//	指定範囲内に入っているときに線との距離が一定以下か
//			//	直線距離と半径での比較
//			if (hitDis <= radius) {
//
//				//	実行へ
//				return true;
//			}
//
//		}
//	}
//
//	return false;
//}
//

//  点と四角の当たり判定
bool CheckHitPointBox(const int& pointX, const int& pointY, 
    const int& boxX, const int& boxY, const int& boxWidth, const int& boxHeight)
{
    return boxX < pointX && pointX < boxX + boxWidth &&
        boxY < pointY && pointY < boxY + boxHeight;
}
