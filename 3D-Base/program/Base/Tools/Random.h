#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �����𐶐�����
// 
// �����	: amateurK
// �쐬��	: 2025/03/25
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


namespace Tools {

	/// @brief �����𐶐� �͈�: [min, max]
	/// @param min �ŏ��l
	/// @param max �ő�l
	/// @return �������ꂽ����
	inline static int GetRandom(int min = INT_MIN, int max = INT_MAX) {
		static std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<int> dist(min, max);
		return dist(mt);
	}

};
