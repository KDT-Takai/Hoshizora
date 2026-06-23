#pragma once
#include "array"

namespace
{
	constexpr int KEY_MAX = 256;			//	キーの入力用
	constexpr int MOUSE_BUTTON_MAX = 8;		//	マウスの入力用
}
//	入力クラス
class InputManager
{
private:
	InputManager();
	~InputManager();
public:
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	static InputManager& Instance() {
		static InputManager instance;
		return instance;
	}
private:
	//	キーの入力保持用
	std::array<char, KEY_MAX> beforKeyInput;
	std::array<char, KEY_MAX> nowKeyInput;
	//	マウスの入力保持用
	int mouseX;
	int mouseY;
	std::array<char, MOUSE_BUTTON_MAX> beforMouseInput;
	std::array<char, MOUSE_BUTTON_MAX> nowMouseInput;
public:
	void Update();
	//	その瞬間だけの入力確認
	bool IsGetKey(const int& keyCode) const;
	//	今入力されているかの確認
	bool GetKey(const int& keyCode) const;
	//	長押しで押されているかの確認
	bool GetKeyRepeat(const int& keyCode)const;
	//	その瞬間だけの入力確認
	bool IsGetMouse(const int& mouseID)const;
	//	長押しで押されているかの確認
	bool GetMouseRepeat(const int& mouseID)const;
	//	マウスのX座標を取得
	int GetMouseX();
	//	マウスのY座標を取得
	int GetMouseY();
};