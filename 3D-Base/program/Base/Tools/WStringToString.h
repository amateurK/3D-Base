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


	/// @brief stringŒ^‚ğwstringŒ^‚É•ÏŠ·‚·‚é
	/// @param str •ÏŠ·‚µ‚½‚¢stringŒ^‚Ì•¶š—ñ
	/// @return •ÏŠ·‚µ‚½wstringŒ^‚Ì•¶š—ñ
	inline std::wstring StringToWString(const std::string& str)
	{
		int bufferSize = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
		std::wstring wstr(bufferSize, 0);
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, &wstr[0], bufferSize);
		return wstr;
	}
}