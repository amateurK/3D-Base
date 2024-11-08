#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// wstring �^�� string �^�ɕϊ�����
// 
// �����	: amateurK
// �쐬��	: 2024/08/08
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace Tools {

	/// @brief wstring�^��string�^�ɕϊ�����
	/// @param wstr �ϊ�������wstring�^�̕�����
	/// @return �ϊ�����string�^�̕�����
	inline std::string WStringToString(const std::wstring& wstr)
	{
		int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
		std::string str(bufferSize, 0);
		WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], bufferSize, nullptr, nullptr);
		return str;
	}


	/// @brief string�^��wstring�^�ɕϊ�����
	/// @param str �ϊ�������string�^�̕�����
	/// @return �ϊ�����wstring�^�̕�����
	inline std::wstring StringToWString(const std::string& str)
	{
		int bufferSize = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
		std::wstring wstr(bufferSize, 0);
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, &wstr[0], bufferSize);
		return wstr;
	}
}