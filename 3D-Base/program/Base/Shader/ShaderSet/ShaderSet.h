#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 使用するシェーダーを保持するクラス
// 
// 
// 製作者	: amateurK
// 作成日	: 2024/11/30
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../ShaderBase.h"

namespace Shader {

	/// @brief シェーダーの種類
	/// @details シェーダーを新規で増やす場合ここに種類を追加
	enum class ShaderType {
		None = 0,
		VertexShader,
		PixelShader,
	};

	/// @brief 使用するシェーダーを保持するクラス
	__declspec(align(16))
		class ShaderSet
	{
	private:
		/// @brief 使用するシェーダーのリスト
		std::unordered_map<ShaderType, ShaderBase*> m_ShaderList;

	public:
		/// @brief コンストラクタ
		ShaderSet();
		/// @brief デストラクタ
		virtual ~ShaderSet();

		/// @brief リストにあるシェーダーのSetShader()を実行
		void SetShaders();

		/// @brief リストにシェーダーを追加
		/// @param type シェーダーの種類
		/// @param shader シェーダークラスへのポインタ
		void AddShader(ShaderType type, ShaderBase* shader);

		/// @brief シェーダーを取得
		/// @param type シェーダーの種類
		/// @return ShaderBaseのポインタ
		inline ShaderBase* GetShader(ShaderType type) { return m_ShaderList[type]; }
	};
}
