#pragma once

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// アラインメントに関する関数
// 
// 製作者	: amateurK
// 作成日	: 2024/11/23
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


namespace Tools {

	/// @brief アラインメントがされているかをチェックする
	/// @tparam T 調べるオブジェクトの型
	/// @param ptr 調べるオブジェクトのポインタ
	/// @param alignment 何byteにアラインメントするか
	/// @details XMVECTORなどを使う際はコンストラクタでこの関数を呼びだすことを推奨
	template<typename T>
	inline void CheckAlignment(T* ptr, size_t alignment = alignof(T)) {
#ifdef _DEBUG
		if (reinterpret_cast<uintptr_t>(ptr) % alignment != 0) {
			throw std::runtime_error("このオブジェクトはアラインメントされていません。");
		}
#endif
	}
}