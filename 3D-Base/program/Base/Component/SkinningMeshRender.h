#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// スキニングアニメーションをする3Dモデルを描画するコンポーネント
// 
// 製作者	: amateurK
// 作成日	: 2025/02/13
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../Component.h"
#include "../Actor.h"
#include "Transform.h"

namespace Shader { class ShaderSet; }
namespace Mesh { 
	class SkinningMesh;
	struct BoneData;
}

namespace AK_Base {

	__declspec(align(16))
		class SkinningMeshRender : public Component
	{
	private:

		/// @brief 使用するシェーダーのポインタ
		Shader::ShaderSet* m_ShaderSet;

		/// @brief 使用するメッシュのポインタ
		Mesh::SkinningMesh* m_Mesh;

		/// @brief ボーンの行列
		std::vector<DirectX::XMMATRIX> m_BoneMatrices;

	public:
		/// @brief コンストラクタ
		/// @param parent このコンポーネントを所有しているActor
		/// @param fileName ファイル名
		SkinningMeshRender(Actor* const parent, std::wstring fileName = L"__box");
		/// @brief デストラクタ
		virtual ~SkinningMeshRender() = default;

		/// @brief コンポーネントの名前を取得
		/// @return 名前の文字列
		inline virtual std::string GetName() const override { return "SkinningMeshRender"; }

		/// @brief 描画
		/// @param totalTime : アプリケーション起動からの経過時間（秒）
		/// @param elapsedTime : 前回のRender()からの経過時間（秒）
		virtual void Render(const double& totalTime, const float& elapsedTime) override;

		/// @brief 使用するシェーダーをセット
		/// @param name シェーダーセットの名前
		void SetShader(const std::string& name);


	private:

		/// @brief リソースの作成
		/// @param fileName ファイル名
		/// @return 作成に成功したか
		HRESULT CreateResource(std::wstring fileName = L"__box");

	};
}