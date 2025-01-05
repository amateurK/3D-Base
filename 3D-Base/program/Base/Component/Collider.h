#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 衝突判定を行うコンポーネント
// 
// 製作者	: amateurK
// 作成日	: 2025/01/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../Component.h"

namespace AK_Base {

	__declspec(align(16))
		class Collider : public Component
	{
	private:

		/// @brief 同じActorのTransformコンポーネント
		Transform* m_Transform;


	public:
		/// @brief コンストラクタ
		/// @param parent このコンポーネントを所有しているActor
		/// @param fileName ファイル名
		Collider(Actor* const parent);
		/// @brief デストラクタ
		virtual ~Collider() = default;

		/// @brief コンポーネントの名前を取得
		/// @return 名前の文字列
		inline virtual std::string GetName() const override { return "Collider"; }

	};
}