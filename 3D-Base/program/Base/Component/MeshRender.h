#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 3Dモデルを描画するコンポーネント
// 
// 製作者	: amateurK
// 作成日	: 2024/11/23
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../Component.h"
#include "../Actor.h"
#include "Transform.h"

namespace Shader { class Shader; }
namespace Mesh { class Mesh; }

namespace AK_Base {
	class Transform;

	__declspec(align(16))
		class MeshRender : public Component
	{
	private:

		/// @brief 同じActorのTransformコンポーネント
		Transform* m_Transform;

		/// @brief 使用するシェーダーのポインタ
		Shader::Shader* m_Shader;

		/// @brief 使用するメッシュのポインタ
		Mesh::Mesh* m_Mesh;

	public:
		/// @brief コンストラクタ
		/// @param parent このコンポーネントを所有しているActor
		/// @param fileName ファイル名
		MeshRender(Actor* const parent, std::wstring fileName = L"__box");
		/// @brief デストラクタ
		virtual ~MeshRender() = default;

		/// @brief コンポーネントの名前を取得
		/// @return 名前の文字列
		inline virtual std::string GetName() const override { return "MeshRender"; }

		/// @brief 描画
		/// @param totalTime : アプリケーション起動からの経過時間（秒）
		/// @param elapsedTime : 前回のRender()からの経過時間（秒）
		virtual void Render(const double& totalTime, const float& elapsedTime) override;

		/// @brief シェーダーをセット
		/// todo シェーダー管理クラスが出来たら消す
		void SetShader(Shader::Shader* shader) { m_Shader = shader; }

	private:

		/// @brief リソースの作成
		/// @param fileName ファイル名
		/// @return 作成に成功したか
		HRESULT CreateResource(std::wstring fileName = L"__box");
	};
}