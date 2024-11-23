#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 3Dモデルを描画するコンポーネント
// 
// 製作者	: amateurK
// 作成日	: 2024/11/23
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../Component.h"

namespace AK_Base {

	__declspec(align(16))
		class MeshRender : public Component
	{
	public:
		/// @brief コンストラクタ
		/// @param parent このコンポーネントを所有しているActor
		MeshRender(Actor* const parent);
		/// @brief デストラクタ
		virtual ~MeshRender() = default;

		/// @brief コンポーネントの名前を取得
		/// @return 名前の文字列
		inline virtual std::string GetName() const override { return "MeshRender"; }

		/// @brief 描画
		/// @param totalTime : アプリケーション起動からの経過時間（秒）
		/// @param elapsedTime : 前回のRender()からの経過時間（秒）
		virtual void Render(const double& totalTime, const float& elapsedTime) override;

	};
}