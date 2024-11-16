#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 駒(piece)のクラス
// 
// 製作者	: amateurK
// 作成日	: 2024/04/23
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Base/Model/ModelActor.h"

namespace Piece {

	/// @brief 駒(piece)
	__declspec(align(16))
		class Piece : public AK_Base::ModelActor
	{
	protected:
		/// @brief 駒の価値
		int m_Value;

	public:
		/// @brief コンストラクタ
		/// @param name : 識別名
		/// @param status : 初期状態
		Piece(
			Shader::Shader* const shader
			, std::wstring name = L"unnamed"
			, std::wstring fileName = L""
		);

		/// @brief デストラクタ
		virtual ~Piece();


		/// @brief 更新
		/// @param totalTime : アプリケーション起動からの経過時間（秒）
		/// @param elapsedTime : 前回のMove()からの経過時間（秒）
		virtual void Move(const double& totalTime, const float& elapsedTime) override;
		/// @brief 描画
		/// @param totalTime : アプリケーション起動からの経過時間（秒）
		/// @param elapsedTime : 前回のRender()からの経過時間（秒）
		virtual void Render(const double& totalTime, const float& elapsedTime) override;

		/// @brief 座標をセットする
		/// @param pos3 座標
		inline void SetPosition(DirectX::XMFLOAT3A pos3)
		{
			m_Position = pos3;
		}
		/// @brief 座標をセットする
		/// @param x 座標x
		/// @param y 座標y
		/// @param z 座標z
		inline void SetPosition(float x, float y, float z)
		{
			m_Position = DirectX::XMFLOAT3A(x, y, z);
		}

		/// @brief サイズの変更
		/// @param x x軸方向
		/// @param y y軸方向
		/// @param z z軸方向
		inline void Scaling(float x, float y, float z)
		{
			m_Scale = DirectX::XMFLOAT3A(x, y, z);
		}
		/// @brief サイズの変更
		/// @param 倍率
		inline void Scaling(float scale)
		{
			m_Scale = DirectX::XMFLOAT3A(scale, scale, scale);
		}

		// 移動可能な場所を返す

		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Piece));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}

