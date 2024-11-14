//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �t�@�C���̃p�X�𑀍삷��֐����܂Ƃ߂Ă���
// 
// �����	: amateurK
// �쐬��	: 2024/11/02
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#pragma once

namespace Tools {

	/// @brief �t�@�C���̃f�B���N�g���̃p�X��Ԃ�
	/// @details �� : Base/Tools/FilePath.h -> Base/Tools
	/// @param path �t�@�C���ւ̃p�X
	/// @return �f�B���N�g���̃p�X
	inline std::wstring GetDirectoryPath(const std::wstring& path)
	{
		// �p�X�̈�ԍŌ��'/'�̏ꏊ���擾
		auto idx = path.find_last_of('/');

		return path.substr(0, idx);

	}

	/// @brief �t�@�C���̊g���q��Ԃ�
	/// @param path �t�@�C���ւ̃p�X
	/// @return �g���q�i'.'�͕t���Ă��Ȃ��j
	inline std::wstring GetFileExtension(const std::wstring& path)
	{
		// '.'�܂ł̒����i'.'���܂ށj
		auto idx = path.find_last_of(L'.') + 1;
		return path.substr(idx, wcslen(path.c_str() + idx));
	}

	/// @brief �t�@�C���̊g���q������������i���g�͕ύX���Ȃ��j
	/// @param path �t�@�C���ւ̃p�X
	/// @param extension ����������g���q
	/// @return ����������ꂽ��̃t�@�C���̃p�X
	inline std::wstring ReplaceExtension(const std::wstring& path, const std::wstring& extension)
	{
		auto idx = path.find_last_of(L'.');
		return path.substr(0, idx + 1) + extension;
	}
}