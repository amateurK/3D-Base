//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ファイルのパスを操作する関数をまとめている
// 
// 製作者	: amateurK
// 作成日	: 2024/11/02
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#pragma once

namespace Tools {

	/// @brief ファイルのディレクトリのパスを返す
	/// @details 例 : Base/Tools/FilePath.h -> Base/Tools
	/// @param path ファイルへのパス
	/// @return ディレクトリのパス
	inline std::wstring GetDirectoryPath(const std::wstring& path)
	{
		// パスの一番最後の'/'の場所を取得
		auto idx = path.find_last_of('/');

		return path.substr(0, idx);

	}

	/// @brief ファイルの拡張子を返す
	/// @param path ファイルへのパス
	/// @return 拡張子（'.'は付いていない）
	inline std::wstring GetFileExtension(const std::wstring& path)
	{
		// '.'までの長さ（'.'を含む）
		auto idx = path.find_last_of(L'.') + 1;
		return path.substr(idx, wcslen(path.c_str() + idx));
	}

	/// @brief ファイルの拡張子を書き換える（中身は変更しない）
	/// @param path ファイルへのパス
	/// @param extension 書き換える拡張子
	/// @return 書き換えられた後のファイルのパス
	inline std::wstring ReplaceExtension(const std::wstring& path, const std::wstring& extension)
	{
		auto idx = path.find_last_of(L'.');
		return path.substr(0, idx + 1) + extension;
	}
}