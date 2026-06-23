#pragma once
// deletaTijmeの実装
#include <chrono>

class Time
{
private:
	Time() {
		// 初期化
		previousTime = std::chrono::high_resolution_clock::now();
		timeScale = 1.0f;	// デフォルトは通常スピード
	}
	~Time() = default;
public:
	Time(const Time&) = delete;
	Time& operator=(const Time&) = delete;
	static Time& Instance() {
		static Time instance;
		return instance;
	}
private:
	// タイムカウンター
	float timer_count = 0.0f;
	// 前回の時間
	std::chrono::steady_clock::time_point previousTime;
	// 実際の時間：デルタタイム
	std::chrono::nanoseconds deltaTime;
	// タイムスケール ゲーム内の時間調整
	float timeScale;
	// タイムスケールによって倍率がかかった後のデルタタイム
	float scaledDeltaTime;

public:

	void Update() {
		// 現在の時間を取得
		auto currentTime = std::chrono::high_resolution_clock::now();
		// デルタタイムを計算 (ミリ秒単位に変換)前回の時間と現在の時間の差分
		deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - previousTime);
		// 現在の時間を次のループの基準時間に更新
		previousTime = currentTime;

		// 倍率をかけたデルタタイム計算
		double deltaSec = std::chrono::duration<double>(deltaTime).count();
		scaledDeltaTime = deltaSec * timeScale;

		// デルタタイムをタイマーに加算
		timer_count += static_cast<float>(scaledDeltaTime);
	}

	// スケール後のデルタタイム
	inline double GetDeltaScale() const { return scaledDeltaTime; }

	// 実時間デルタタイム
	inline double GetDelta() const { return std::chrono::duration<double>(deltaTime).count(); }

	// ゲームスピード調整
	inline void SetTimeScale(float scale) { timeScale = scale; }	// ゲームスピードのセット
	inline float GetTimeScale() const { return timeScale; }		// ゲームスピードのゲット

	// 経過時間（ゲーム開始からの累積秒数）
	inline float GetTotalTime() const { return timer_count; }
};