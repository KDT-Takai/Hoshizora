#pragma once
// キー入力
#include "Input.h"

//　デバック
#define DEBUG

// 宣言 (型,変数名,初期値)
#define SETTING(type, name, value)\
protected:\
	type name = value;\
public:\
	void Set ## name(type num) {\
		name = num;\
	}\
	type Get ## name()const {\
		return name;\
	}

#define RadToDeg 57.29577951f
/// <summary>
/// ラジアン角から度に直す
/// </summary>
#define DEGREE(rad) rad * RadToDeg

#define DegToRad 0.017453293f
/// <summary>
/// 度からラジアン角に直す
/// </summary>
#define RADIAN(deg) deg * DegToRad

/// <summary>
/// 画面比率
/// </summary>
#define WINDOW_W	1280
#define WINDOW_H	720

/// <summary>
/// 色深度
/// </summary>
#define COLOR_DEPTH	32

/// <summary>
/// 円の角形
/// </summary>
#define C_POSNUM	64

// RGB形式: R, G, B の各成分を 0~255 で定義
struct Color { int r, g, b; };

const Color RED		= { 255, 0, 0 };		// 赤
const Color GREEN	= { 0, 255, 0 };		// 緑
const Color BLUE	= { 0, 0, 255 };		// 青
const Color WHITE	= { 255, 255, 255 };	// 白
const Color BLACK	= { 0, 0, 0 };			// 黒
const Color YELLOW	= { 255, 255, 0 };		// 黄色
const Color CYAN	= { 0, 255, 255 };		// シアン
const Color MAGENTA = { 255, 0, 255 };		// マゼンタ
const Color ORANGE	= { 255, 165, 0 };		// オレンジ
const Color PINK	= { 255, 192, 203 };	// ピンク
const Color GRAY	= { 169, 169, 169 };	// グレー
const Color LIGHT_GRAY	= { 128, 128, 128 };	// 明るめグレー
const Color BROWN	= { 139, 69, 19 };		// ブラウン
const Color LIGHT_BLUE	= { 173, 216, 230 };// ライトブルー
const Color LIGHT_GREEN	= { 144, 238, 144 };// ライトグリーン
const Color PURPLE	= { 128, 0, 128 };		// 紫
const Color VIOLET	= { 238, 130, 238 };	// バイオレット

// inline は実行速度は早い
inline int GetColor(const Color& color) {
	return GetColor(color.r,color.g,color.b);
}
// 背景色の設定
inline int SetBackgroundColor(const Color& color) {
	return SetBackgroundColor(color.r, color.g, color.b);
}