#pragma once
#include "DxLib.h"
#include "define.h"
#include "ScreenBase.h"

class Home : public ScreenBase
{
private:
	int tittle;	// ƒ^ƒCƒgƒ‹‚Ì•¶Žš
public:

	Home() {
		tittle = LoadGraph("Data/Tittle/Image/TittleText.png");
	};
	virtual ~Home() = default;

	void Update() override;
	void Draw() override;
};