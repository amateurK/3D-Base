#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// カメラを管理するコンポーネント
// 
// 製作者	: amateurK
// 作成日	: 2025/02/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../Component.h"

namespace AK_Base {

	/// @brief カメラを管理するコンポーネント
	__declspec(align(16))
		class Camera : public Component
	{
	private:
		/// @brief ビュー行列
		DirectX::XMMATRIX m_View;
		/// @brief 射影行列
		DirectX::XMMATRIX m_Projection;

		/// @brief Transformの更新回数
		/// @details Transformが更新されているかを調べるときに使用
		uint32_t m_TransformChangedCount;

	public:
		/// @brief コンストラクタ
		/// @param parent このコンポーネントを所有しているActor（AddComponent<T>()で追加される）
		Camera(Actor* const parent);
		/// @brief デストラクタ
		~Camera() = default;

		/// @brief コンポーネントの名前を取得
		/// @return 名前の文字列
		inline virtual std::string GetName() const override { return "Camera"; }

		/// @brief 射影行列をセット
		/// @param angleY Y方向の視野（角度）
		/// @param aspect レンダーターゲットのアスペクト比
		/// @param nearZ ビュー空間の前方Z値
		/// @param farZ ビュー空間の後方Z値
		void SetScreen(const float angleY,
			const float aspect,
			const float nearZ = 0.01f,
			const float farZ = 100.0f);

		/// @brief ビュー行列を取得
		/// @return ビュー行列のポインタ
		const DirectX::XMMATRIX* GetView();

		inline const DirectX::XMMATRIX* GetProjection() const { return &m_Projection; }

	};
}