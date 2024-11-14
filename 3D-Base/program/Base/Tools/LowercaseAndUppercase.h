#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �啶���⏬�����𑀍삷��
// 
// �����	: amateurK
// �쐬��	: 2024/11/09
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace Tools {

	/// @brief �������ɕϊ�����
	/// @param str �ϊ����镶����
	/// @return �������̕�����
	inline std::string ToLowercase(std::string& str)
	{
		std::string ret = str;
		std::transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
		return ret;
	}

	/// @brief �������ɕϊ�����
	/// @param str �ϊ����镶����
	/// @return �������̕�����
	inline std::wstring ToLowercase(std::wstring& str)
	{
		std::wstring ret = str;
		std::transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
		return ret;
	}

}