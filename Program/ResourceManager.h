#pragma once
#include <string>

class ResourceManager
{
private:
	ResourceManager() {}
	~ResourceManager() = default;
public:
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	static ResourceManager& Instance() {
		static ResourceManager instance;
		return instance;
	}
public:
	/// <summary>
	/// 画像読み込みエラー処理
	/// </summary>
	/// <param name="filename">ファイル名（.png）</param>
	/// <param name="className">クラス名</param>
	inline void ShowImageLoadError(const char* filename, const char* className) {
		std::string msg = std::string("【") + className + ("】画像の読み込みに失敗: ") + filename;
		MessageBoxA(nullptr, msg.c_str(), "エラー", MB_OK | MB_ICONERROR);
		// 末尾のフラグ（オプション）説明:メッセージボックスのボタンとアイコンの種類
		// MB_OK			「OK」ボタン１つ ユーザーが「OK」を押して閉じる
		// MB_ICONERROR		 エラー（×マーク）のアイコン メッセージボックスにエラーアイコンを表示
		// MB_OKCANCEL		「OK」と「キャンセル」ボタン
		// MB_YESNO			「はい」「いいえ」ボタン
		// MB_ICONWARNING	 警告（！マーク）アイコン
		// MB_ICONQUESTION	 疑問（？マーク）アイコン
	}
};