#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// wstring 型を string 型に変換する
// 
// 製作者	: amateurK
// 作成日	: 2024/08/08
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace Tools {

	/// @brief wstring型をstring型に変換する
	/// @param wstr 変換したいwstring型の文字列
	/// @return 変換したstring型の文字列
	inline std::string WStringToString(const std::wstring& wstr)
	{
		int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
		std::string str(bufferSize, 0);
		WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], bufferSize, nullptr, nullptr);
		return str;
	}


	/// @brief string型をwstring型に変換する
	/// @param str 変換したいstring型の文字列
	/// @return 変換したwstring型の文字列
	inline std::wstring StringToWString(const std::string& str)
	{
		int bufferSize = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
		std::wstring wstr(bufferSize, 0);
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, &wstr[0], bufferSize);
		return wstr;
	}
}