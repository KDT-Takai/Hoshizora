#include "Input.h"
#include "DxLib.h"

InputManager::InputManager() {
	beforKeyInput.fill(0);
	nowKeyInput.fill(0);
	mouseX = 0;
	mouseY = 0;
	beforMouseInput.fill(0);
	nowMouseInput.fill(0);
}

InputManager::~InputManager() {}

void InputManager::Update()
{
	//	キー入力
	beforKeyInput = nowKeyInput;				//	前の入力を保存
	GetHitKeyStateAll(nowKeyInput.data());		//	入力を保存して行く
	//	マウス入力
	GetMousePoint(&mouseX, &mouseY);			//	マウス座標取得
	beforMouseInput = nowMouseInput;			//	前の入力を保存
	int mouse = GetMouseInput();				//	入力を保持
	for (int i = 0; i < MOUSE_BUTTON_MAX; i++) {
		if (mouse == i) {
			nowMouseInput[i] = true;
			continue;
		}
		nowMouseInput[i] = false;
	}
}
//	その瞬間だけの入力確認
bool InputManager::IsGetKey(const int& keyCode) const
{
	return nowKeyInput[keyCode] && !beforKeyInput[keyCode];
}
//	今入力されているかの確認
bool InputManager::GetKey(const int& keyCode) const
{
	return nowKeyInput[keyCode];
}
//	長押しで押されているかの確認
bool InputManager::GetKeyRepeat(const int& keyCode)const
{
	return nowKeyInput[keyCode] && beforKeyInput[keyCode];
}
//	その瞬間だけの入力確認
bool InputManager::IsGetMouse(const int& mouseID)const
{
	return nowMouseInput[mouseID] && !beforMouseInput[mouseID];
}
//	長押しで押されているかの確認
bool InputManager::GetMouseRepeat(const int& mouseID)const
{
	return nowMouseInput[mouseID] && beforMouseInput[mouseID];
}
//	マウスのX座標を取得
int InputManager::GetMouseX()
{
	return mouseX;
}
//	マウスのY座標を取得
int InputManager::GetMouseY()
{
	return mouseY;
}