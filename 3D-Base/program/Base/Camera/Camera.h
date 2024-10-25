#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// カメラの役割を担う
// Shaderに渡すビュー行列、射影行列もここで管理する
// 
// 製作者	: amateurK
// 作成日	: 2024/07/30
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace Camera {

	__declspec(align(16))
		class Camera
	{
	private:
		/// @brief ビュー行列
		DirectX::XMMATRIX m_View;
		/// @brief 射影行列
		DirectX::XMMATRIX m_Projection;

	public:
		/// @brief コンストラクタ
		Camera();
		/// @brief デストラクタ
		~Camera() = default;

		/// @brief ビュー行列(カメラ)をセット
		/// @param eye カメラの位置
		/// @param at カメラの注視点
		/// @param up カメラの上方向ベクトル
		void SetCamera(const DirectX::XMVECTOR& eye,
			const DirectX::XMVECTOR& at = { 0.0f, 0.0f, 0.0f, 0.0f },
			const DirectX::XMVECTOR& up = { 0.0f, 1.0f, 0.0f, 0.0f });

		/// @brief 射影行列をセット
		/// @param angleY Y方向の視野（角度）
		/// @param aspect レンダーターゲットのアスペクト比
		/// @param nearZ ビュー空間の前方Z値
		/// @param farZ ビュー空間の後方Z値
		void SetScreen(const float angleY,
			const float aspect,
			const float nearZ = 0.01f,
			const float farZ = 100.0f);

		/// @brief カメラを移動させる
		/// @param matrix ビュー行列をかける行列
		void MoveCamera(const DirectX::XMMATRIX& matrix);


		DirectX::XMMATRIX GetView() const { return m_View; }
		DirectX::XMMATRIX GetProjection() const { return m_Projection; }


		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Camera));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}