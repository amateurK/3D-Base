#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// —”‚ğ¶¬‚·‚é
// 
// »ìÒ	: amateurK
// ì¬“ú	: 2025/03/25
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


namespace Tools {

	/// @brief —”‚ğ¶¬ ”ÍˆÍ: [min, max]
	/// @param min Å¬’l
	/// @param max Å‘å’l
	/// @return ¶¬‚³‚ê‚½—”
	inline static int GetRandom(int min = INT_MIN, int max = INT_MAX) {
		static std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<int> dist(min, max);
		return dist(mt);
	}

};
