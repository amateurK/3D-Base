#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// wstring Œ^‚ğ string Œ^‚É•ÏŠ·‚·‚é
// 
// »ìÒ	: amateurK
// ì¬“ú	: 2024/08/08
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace Tools {

	/// @brief wstringŒ^‚ğstringŒ^‚É•ÏŠ·‚·‚é
	/// @param wstr •ÏŠ·‚µ‚½‚¢wstringŒ^‚Ì•¶š—ñ
	/// @return •ÏŠ·‚µ‚½stringŒ^‚Ì•¶š—ñ
	inline std::string WStringToString(const std::wstring& wstr)
	{
		int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
		std::string str(bufferSize, 0);
		WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], bufferSize, nullptr, nullptr);
		return str;
	}

	// ChatGPT‚ª—DG
}