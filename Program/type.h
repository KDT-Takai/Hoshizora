#pragma once


/// <summary>
/// キャラクタータイプ
/// </summary>
class TYPE
{
private:
	int type;
public:
	enum FORM {
		RANGE,		// 遠距離タイプ
		FIGHTER,	// 近距離タイプ
		HEALER,		// ヒーラータイプ
	};

	// コンストラクタ
//	TYPE(FORM form = RANGE) : type(form == RANGE) {}
	TYPE(FORM form = RANGE) : type(form) {}

	// bool型への型変換
	operator int() { return type; }
//	BOOL& operator =(int argType) { type = argType; }

    // キャラクターのタイプを設定
    TYPE& operator =(int argType) {
        type = argType;
        return *this;  // コピー代入を返す
    }

    // キャラクタータイプを取得（FORM 型で）
    FORM GetType() const {
//        return type ? RANGE : FIGHTER;
        return static_cast<FORM>(type);  // 0, 1, 2 の値を FORM に変換
    }

#ifdef DEBUG

    // デバッグ用：タイプを文字列で返す
    const char* toString() const {
        switch (GetType()) {
        case RANGE:   return "Range";
        case FIGHTER: return "Fighter";
        case HEALER:  return "Healer";
        default:      return "Unknown";
        }
    }

#endif // DEBUG
};