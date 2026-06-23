#pragma once
#include "define.h"

class MouseEffect
{
protected:

	// マウス座標
	SETTING(int, MouseX, 0);	// x軸
	SETTING(int, MouseY, 0);	// y軸

public:

	MouseEffect() {}

	void MouseSet() {
		GetMousePoint(&MouseX, &MouseY);
	}

	virtual void Update() {
		// マウス座標に合わせる
		MouseSet();
	}

};
