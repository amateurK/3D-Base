#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 衝突判定を行うコンポーネント
// 
// 製作者	: amateurK
// 作成日	: 2025/01/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../Component.h"
#include "Transform.h"
#include "../Collision/CollisionManager.h"

namespace AK_Base {

	class SphereCollider;

	__declspec(align(16))
		class Collider : public Component
	{
	private:
		/// @brief Transformの更新回数
		/// @details Transformが更新されているかを調べるときに使用
		uint32_t m_TransformChangedCount;

		/// @brief 衝突時の処理
		std::function<void(Collider* const)> m_OnCollision;

	public:
		/// @brief コンストラクタ
		/// @param parent このコンポーネントを所有しているActor
		/// @param fileName ファイル名
		Collider(Actor* const parent)
			: Component(parent)
			, m_TransformChangedCount(0)
			, m_OnCollision(nullptr)
		{
			CollisionManager::GetInstance()->AddCollider(this);
		}
		/// @brief デストラクタ
		virtual ~Collider()
		{
			CollisionManager::GetInstance()->RemoveCollider(this);
		}

		/// @brief コンポーネントの名前を取得
		/// @return 名前の文字列
		inline virtual std::string GetName() const override { return "Collider"; }


		/// @brief 他のColliderと衝突したときの処理
		/// @param other 衝突したCollider
		virtual void OnCollision(Collider* const other)
		{
			if (m_OnCollision != nullptr)
			{
				m_OnCollision(other);
			}
		};

		/// @brief 衝突時の処理を設定
		/// @param func 衝突時に実行する関数
		void SetOnCollision(const std::function<void(Collider* const)>& func)
		{
			m_OnCollision = func;
		}

		/// @brief 衝突しているかを調べる
		/// @param other 判定を行うCollider
		/// @return 衝突しているならtrue
		virtual bool CheckCollision(Collider* const other) = 0;

		/// @brief 球体と衝突しているかを調べる
		/// @param other 判定を行う球体
		/// @return 衝突しているならtrue
		virtual bool CheckCollisionWithSphere(SphereCollider* const other) = 0;

		/// @brief 絶対座標を更新する必要があれば更新
		inline void CheckAbsolutePosUpdate() {
			if (CheckTransformUpdate()) {
				UpdateAbsolutePos();
			}
		}

	private:

		/// @brief 相対座標に基づいて絶対座標を更新
		virtual void UpdateAbsolutePos() = 0;

		/// @brief Transformが更新されたかをチェック
		/// @return 更新されていた場合true
		inline bool CheckTransformUpdate() {
			auto cnt = m_ParentActor->GetTransform()->GetChengedCount();
			// Transformが変更されている場合
			if (m_TransformChangedCount != cnt)
			{
				m_TransformChangedCount = cnt;
				return true;
			}
			return false;
		}
	};
}