#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// アニメーションデータを保持するクラス
// 
// 製作者	: amateurK
// 作成日	: 2025/02/17
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


namespace Anim {

	/// @brief 一つのキーフレームを表す構造体
	__declspec(align(16))
		struct KeyFrame
	{
		/// @brief 行列
		DirectX::XMVECTOR Vec;
		/// @brief 時間
		float Time;
	};
	struct BoneKeyFrames
	{
		/// @brief 移動のキーフレーム
		std::vector<KeyFrame> Transform;
		/// @brief 回転のキーフレーム
		std::vector<KeyFrame> Rotation;
	};

	// アニメーションデータを保持するクラス
	class AnimationClip
	{
	private:

		/// @brief ボーンごとのキーフレーム
		/// @details キー : ボーン名
		/// @details 値 : キーフレームのリスト
		std::unordered_map<std::string, BoneKeyFrames> m_BoneKeyFrames;

		/// @brief アニメーションの長さ
		float m_Duration;

	public:
		/// @brief コンストラクタ
		AnimationClip();
		/// @brief デストラクタ
		~AnimationClip();

		/// @brief アニメーションのロード
		HRESULT LoadAnimation(std::wstring fileName = L"");
		/// @brief アニメーションの削除
		void ClearAnimation();

		/// @brief ボーンの変換行列を取得
		/// @param boneName ボーンの名前
		/// @param time アニメーション開始からの時間
		/// @param output 変換行列
		/// @return 値が取得できたか（falseの場合、ボーンは存在しなかったことになる）
		bool GetBoneMatrix(const std::string& boneName, float time, DirectX::XMMATRIX& output) const;

		/// @brief アニメーションの長さを取得
		inline float GetDuration() const { return m_Duration; }

	private:
		/// @brief キーフレームから現在の位置を取得
		/// @param keyFrames キーフレーム
		/// @param time 現在時刻
		/// @return 位置を表すVECTOR
		const DirectX::XMVECTOR& InterpolateTransform(const std::vector<KeyFrame>& keyFrames, float time) const;
		/// @brief キーフレームから現在の回転を取得
		/// @param keyFrames キーフレーム
		/// @param time 現在時刻
		/// @return クォータニオン
		const DirectX::XMVECTOR& InterpolateRotation(const std::vector<KeyFrame>& keyFrames, float time) const;
	};
}