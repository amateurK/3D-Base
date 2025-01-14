#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 球体のColliderを持つコンポーネント
// 
// 製作者	: amateurK
// 作成日	: 2025/01/11
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../Collider.h"
#include "../../Math/primitive.h"
#include "../../Math/AK_Math.h"

namespace AK_Base {

	__declspec(align(16))
		class SphereCollider : public Collider
	{
	private:

		/// @brief 相対座標
		/// @details 親Actorのローカル座標系
		AK_Math::Sphere3 m_Relative;
		/// @brief 絶対座標
		/// @details ワールド座標系
		AK_Math::Sphere3 m_Absolute;

	public:
		/// @brief コンストラクタ
		/// @param parent このコンポーネントを所有しているActor
		/// @param fileName ファイル名
		SphereCollider(Actor* const parent, AK_Math::Sphere3 sphere = {})
			: Collider(parent)
			, m_Relative(sphere)
			, m_Absolute(sphere)
		{
			UpdateAbsolutePos();
		}
		/// @brief デストラクタ
		virtual ~SphereCollider() = default;

		/// @brief コンポーネントの名前を取得
		/// @return 名前の文字列
		inline virtual std::string GetName() const override { return "SphereCollider"; }

		/// @brief 衝突しているかを調べる
		/// @param other 判定を行うCollider
		/// @return 衝突しているならtrue
		inline virtual bool CheckCollision(Collider* const other) override
		{
			return other->CheckCollisionWithSphere(this);
		}
		inline virtual bool CheckCollisionWithSphere(SphereCollider* const other) override
		{
			// Sphere x Sphere
			return AK_Math::IsCollide(m_Absolute, other->m_Absolute);
		}

		// セッター

		void SetCollider(const AK_Math::Sphere3& sphere)
		{
			m_Relative = sphere;
			UpdateAbsolutePos();
		}

	private:
		/// @brief 相対座標に基づいて絶対座標を更新
		virtual void UpdateAbsolutePos() override
		{
			// ローカル座標系をワールド座標系に変換
			m_Absolute.point = XMVector3Transform(m_Relative.point, *m_ParentActor->GetTransform()->GetWorldMatrix());

			// サイズによって半径が変わるが、楕円は別の処理になるのでx座標で判断
			m_Absolute.radius = m_Relative.radius * m_ParentActor->GetTransform()->GetScele().m128_f32[0];
		}
	};
}