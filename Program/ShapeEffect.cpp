#include "shapeEffect.h"

//--------------------------------------------------
// 図形エフェクト
//--------------------------------------------------

// 更新処理
void CShapeEf::Updata()
{
	// 更新
	for (int i = 0; i < mObj.size();) {
		// それぞれの図形の座標移動
		mObj[i]->mPos.Add(mObj[i]->mMove.Get());
		// 透明度を減らす
		mObj[i]->mAlpha -= EF_ALPHA_SPEED;
		// 透明度が0以下なら
		if (mObj[i]->mAlpha <= 0) {
			// i番目の要素を削除
			mObj.erase(mObj.begin() + i);
		} else {
			// インデックスカウンター
			i++;
		}
	}
}

// 残りがあるかの確認
bool CShapeEf::CheckEnable()
{
	// 中身があるかどうか
	if (mObj.size() > 0) {
		return true;
	}
	return false;
}

// 描画
void CShapeEf::Draw()
{
	// 描画
	for (int i = 0; i < mObj.size(); i++) {
		// 透明度を変更
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, mObj[i]->mAlpha);

		// 図形を描画
		DrawCircleAA(mObj[i]->mPos.GetX(), mObj[i]->mPos.GetY(),
			mObj[i]->mRadius, mObj[i]->mDivision,
			mObj[i]->mColor, true, mObj[i]->mAngle);
	}
	// 透明度を戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}