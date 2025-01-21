#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 中心座標、回転、スケールを保持するコンポーネント
// 正面を+Z軸、上を+Y軸、右を+X軸としている。
// 
// 製作者	: amateurK
// 作成日	: 2024/11/18
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../Component.h"

namespace AK_Base {

	/// @brief 中心座標、回転、スケールを保持するコンポーネント
	__declspec(align(16))
	class Transform : public Component
	{
	private:
		/// @brief 現在座標
		DirectX::XMVECTOR m_Position;
		/// @brief 回転角度（クォータニオン）
		DirectX::XMVECTOR m_Rotation;
		/// @brief スケール
		DirectX::XMVECTOR m_Scale;

		/// @brief ワールド行列
		DirectX::XMMATRIX m_World;
		/// @brief 更新が入ったか（falseならWorld行列を使いまわす）
		bool m_IsChanged;

		/// @brief 更新がされた回数
		uint32_t m_ChangedCount;

		Transform* m_Parent;
		std::vector<Transform*> m_Children;

	public:
		/// @brief コンストラクタ
		/// @param parent このコンポーネントを所有しているActor
		/// @param addChild 親ActorがTransformを持っているときに親子関係にするか
		Transform(Actor* const parent, bool addChild = true);
		/// @brief デストラクタ
		virtual ~Transform() = default;

		/// @brief コンポーネントの名前を取得
		/// @return 名前の文字列
		inline virtual std::string GetName() const override{ return "Transform"; }


		/// @brief 現在地から指定した距離移動
		/// @param offset 移動量
		void Translate(const DirectX::XMVECTOR& offset);
		/// @brief 現在地から指定した距離移動
		/// @param x x軸方向の移動量
		/// @param y y軸方向の移動量
		/// @param z z軸方向の移動量
		void Translate(float x, float y, float z);

		/// @brief 正面方向を基準に移動する
		/// @param offset 移動量(right, up, forword, 0.0f)
		void Move(const DirectX::XMVECTOR& offset);
		/// @brief 正面方向を基準に移動する
		/// @param forward 正面方向の移動量
		/// @param right 右方向の移動量
		/// @param up 上方向の移動量
		void Move(float forward, float right, float up);


		/// @brief 現在の角度から回転
		/// @param axis 回転する軸
		/// @param angle 角度
		void Rotate(const DirectX::XMVECTOR& axis, float angle);
		/// @brief 現在の角度から回転
		/// @param axis 正規化済みの回転する軸（正規化していないならRotate()を使う）
		/// @param angle 角度
		void RotateNorm(const DirectX::XMVECTOR& axis, float angle);

		/// @brief 現在の角度からローカル軸座標系で回転
		/// @param axis 回転する軸
		/// @param angle 角度
		void RotateLocal(const DirectX::XMVECTOR& axis, float angle);

		/// @brief X軸を中心に回転
		/// @param angle 角度
		void RotateX(float angle);
		/// @brief Y軸を中心に回転
		/// @param angle 角度
		void RotateY(float angle);
		/// @brief Z軸を中心に回転
		/// @param angle 角度
		void RotateZ(float angle);

		/// @brief X軸を中心に回転
		/// @param angle 角度
		void RotateLocalX(float angle);
		/// @brief Y軸を中心に回転
		/// @param angle 角度
		void RotateLocalY(float angle);
		/// @brief Z軸を中心に回転
		/// @param angle 角度
		void RotateLocalZ(float angle);

		/// @brief 指定した座標に向きを合わせる
		/// @param position 座標
		void LookAtPosition(const DirectX::XMVECTOR& position);


		/// @brief 拡大縮小
		/// @param mul 倍率
		void Scale(float mul);
		/// @brief 拡大縮小
		/// @param mul 倍率
		void Scale(const DirectX::XMVECTOR& mul);


		/// @brief IsChangedをtrueにする
		void MarkChanged();




		// ゲッターセッター

		inline const DirectX::XMVECTOR& GetPosition() const { return m_Position; }
		void SetPosition(const DirectX::XMVECTOR& position);
		void SetPosition(float x, float y, float z);

		inline const DirectX::XMVECTOR& GetRotation() const { return m_Rotation; }
		void SetRotation(const DirectX::XMVECTOR& rotation);
		void SetRotation(float x, float y, float z, float w);

		inline const DirectX::XMVECTOR& GetScele() const { return m_Scale; }
		void SetScele(const DirectX::XMVECTOR& scale);
		void SetScele(float x, float y, float z);

		const DirectX::XMMATRIX* GetWorldMatrix();

		inline const uint32_t GetChengedCount() const { return m_ChangedCount; }

		inline Transform* GetParent() const { return m_Parent; }
		void SetParent(Transform* parent);

		void AddChild(Transform* child);


	};

}