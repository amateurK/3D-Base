#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 3Dモデル描画管理クラス
// 
// 製作者	: amateurK
// 作成日	: 2024/04/12
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../Shader/Shader.h"
#include "Mesh/Mesh.h"

namespace AK_Base {
	/// @brief 3Dモデル描画管理クラス
	/// @details 3Dモデルの管理はModelActorと別で処理したいため
	class ModelRender
	{
	private:
		Shader::Shader* m_Shader;
		Mesh::Mesh* m_Mesh;

	public:
		/// @brief コンストラクタ
		/// @param shader 使用するシェーダー
		ModelRender(Shader::Shader* const shader);
		/// @brief デストラクタ
		virtual ~ModelRender();

		/// @brief リソースの作成
		/// @return 作成に成功したか
		HRESULT CreateResource(std::wstring fileName = L"__box");

		/// @brief 描画
		/// @param worldMatrix 描画するオブジェクトのワールド行列
		void Render(const DirectX::XMMATRIX& worldMatrix);

	};
}