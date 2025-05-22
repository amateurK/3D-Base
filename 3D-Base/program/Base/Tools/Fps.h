#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// FPSを計測するクラス
// 一定時間ごとに実測値は更新される
// 
// 製作者	: amateurK
// 作成日	: 2025/05/22
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace Tools {
	class Fps
	{
	private:
		/// @brief Fps実測値
		uint16_t m_Fps;
		/// @brief 測定時のカウンター
		uint16_t m_Count;
		/// @brief 測定時の開始からの時間
		float m_TotalTime;

	public:
		/// @brief コンストラクタ
		Fps()
			: m_Fps(0)
			, m_Count(0)
			, m_TotalTime(0.0f)
		{}

		/// @brief デストラクタ
		~Fps() = default;

		/// @brief 毎フレーム実行
		inline void Update(const float elapsedTime)
		{
			m_TotalTime += elapsedTime;
			m_Count++;
			// 一定時間経過していたら実測値を更新
			if (m_TotalTime >= 1.0f) {
				m_Fps = m_Count;
				m_Count = 0;
				m_TotalTime -= 1.0f;
			}
		}

		/// @brief Fpsを取得
		/// @return Fpsの実測値
		int GetFps() const
		{
			return m_Fps;
		}
	};
}

