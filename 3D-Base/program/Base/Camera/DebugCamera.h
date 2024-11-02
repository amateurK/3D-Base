#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// デバッグ用のカメラを管理するクラス
// 自由に動ける
// 
// 製作者	: amateurK
// 作成日	: 2024/11/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Camera.h"

namespace Camera {

	__declspec(align(16))
		class DebugCamera : public Camera
	{
	private:

	public:
		/// @brief コンストラクタ
		DebugCamera();
		/// @brief デストラクタ
		~DebugCamera();

		/// @brief 視点を基準にカメラを移動させる
		/// @param front 前方方向への移動ベクトル
		/// @param right 右方向への移動ベクトル
		/// @param up 上方向への移動ベクトル
		void MoveWithViewpoint(float front, float right, float up);

		/// @brief 視点を基準にカメラを移動させる
		/// @param x x座標への移動ベクトル
		/// @param y y座標への移動ベクトル
		/// @param z z座標への移動ベクトル
		void MoveWithAxis(float x, float y, float z);

		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(DebugCamera));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}