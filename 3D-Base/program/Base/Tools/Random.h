#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 乱数を生成する
// 
// 製作者	: amateurK
// 作成日	: 2025/03/25
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


namespace Tools {

	/// @brief 乱数を生成 範囲: [min, max]
	/// @param min 最小値
	/// @param max 最大値
	/// @return 生成された乱数
	inline static int GetRandom(int min = INT_MIN, int max = INT_MAX) {
		static std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<int> dist(min, max);
		return dist(mt);
	}

};
