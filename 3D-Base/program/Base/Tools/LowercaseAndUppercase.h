#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 大文字や小文字を操作する
// 
// 製作者	: amateurK
// 作成日	: 2024/11/09
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace Tools {

	/// @brief 小文字に変換する
	/// @param str 変換する文字列
	/// @return 小文字の文字列
	inline std::string ToLowercase(std::string& str)
	{
		std::string ret = str;
		std::transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
		return ret;
	}

	/// @brief 小文字に変換する
	/// @param str 変換する文字列
	/// @return 小文字の文字列
	inline std::wstring ToLowercase(std::wstring& str)
	{
		std::wstring ret = str;
		std::transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
		return ret;
	}

}