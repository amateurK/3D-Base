#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 中心座標、回転、スケールを保持するコンポーネント
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

		Transform* m_Parent;
		std::vector<Transform*> m_Children;

	public:
		/// @brief コンストラクタ
		/// @param addChild 親ActorがTransformを持っているときに親子関係にするか
		Transform(bool addChild = true);
		/// @brief デストラクタ
		virtual ~Transform() = default;

		/// @brief コンポーネントの名前を取得
		/// @return 名前の文字列
		inline virtual std::string GetName() const override{ return "Transform"; }

		/// @brief 移動
		/// @param offset 移動量
		void Translate(const DirectX::XMVECTOR& offset);
		/// @brief 移動
		/// @param x x軸方向の移動量
		/// @param y y軸方向の移動量
		/// @param z z軸方向の移動量
		void Translate(float x, float y, float z);

		/// @brief 回転
		/// @param axis 回転する軸
		/// @param angle 角度
		void Rotate(const DirectX::XMVECTOR& axis, float angle);
		/// @brief 回転
		/// @param axis 正規化済みの回転する軸（正規化していないならRotate()を使う）
		/// @param angle 角度
		void RotateNorm(const DirectX::XMVECTOR& axis, float angle);

		/// @brief 拡大縮小
		/// @param mul 倍率
		void Scale(float mul);
		/// @brief 拡大縮小
		/// @param mul 倍率
		void Scale(const DirectX::XMVECTOR& mul);

		/// @brief 指定した座標に向きを合わせる
		/// @param position 座標
		void LookAt(DirectX::XMVECTOR& position);

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

		const DirectX::XMMATRIX& GetWorldMatrix();

		inline Transform* GetParent() const { return m_Parent; }
		void SetParent(Transform* parent);

		void AddChild(Transform* child);


	};

}