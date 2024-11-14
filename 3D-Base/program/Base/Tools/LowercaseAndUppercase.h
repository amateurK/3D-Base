#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ‘å•¶š‚â¬•¶š‚ğ‘€ì‚·‚é
// 
// »ìÒ	: amateurK
// ì¬“ú	: 2024/11/09
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace Tools {

	/// @brief ¬•¶š‚É•ÏŠ·‚·‚é
	/// @param str •ÏŠ·‚·‚é•¶š—ñ
	/// @return ¬•¶š‚Ì•¶š—ñ
	inline std::string ToLowercase(std::string& str)
	{
		std::string ret = str;
		std::transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
		return ret;
	}

	/// @brief ¬•¶š‚É•ÏŠ·‚·‚é
	/// @param str •ÏŠ·‚·‚é•¶š—ñ
	/// @return ¬•¶š‚Ì•¶š—ñ
	inline std::wstring ToLowercase(std::wstring& str)
	{
		std::wstring ret = str;
		std::transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
		return ret;
	}

}