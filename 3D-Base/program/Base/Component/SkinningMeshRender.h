#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// スキニングアニメーションをする3Dモデルを描画するコンポーネント
// 
// 製作者	: amateurK
// 作成日	: 2025/02/13
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../Component.h"
#include "../Actor.h"
#include "Transform.h"

namespace Shader { class ShaderSet; }
namespace Mesh { 
	class SkinningMesh;
	struct BoneData;
}
namespace Anim { class AnimationClip; }

namespace AK_Base {

	__declspec(align(16))
		class SkinningMeshRender : public Component
	{
	private:

		/// @brief 使用するシェーダーのポインタ
		Shader::ShaderSet* m_ShaderSet;

		/// @brief 使用するメッシュのポインタ
		Mesh::SkinningMesh* m_Mesh;

		/// @brief ボーンの行列
		std::vector<DirectX::XMMATRIX> m_BoneMatrices;

		/// @brief 再生中のアニメーションに関するデータ
		struct AnimationData
		{
			/// @brief 再生中のアニメーションデータ
			Anim::AnimationClip* Clip;
			/// @brief 現在の再生時間
			float Time;
			/// @brief 再生速度
			float Speed;
			/// @brief ループ再生するか
			bool Loop;

		} m_AnimationData;

	public:
		/// @brief コンストラクタ
		/// @param parent このコンポーネントを所有しているActor
		/// @param fileName ファイル名
		SkinningMeshRender(Actor* const parent, std::wstring fileName = L"__box");
		/// @brief デストラクタ
		virtual ~SkinningMeshRender() = default;

		/// @brief コンポーネントの名前を取得
		/// @return 名前の文字列
		inline virtual std::string GetName() const override { return "SkinningMeshRender"; }

		/// @brief 描画
		/// @param totalTime : アプリケーション起動からの経過時間（秒）
		/// @param elapsedTime : 前回のRender()からの経過時間（秒）
		virtual void Render(const double& totalTime, const float& elapsedTime) override;

		/// @brief 使用するシェーダーをセット
		/// @param name シェーダーセットの名前
		void SetShader(const std::string& name);


		/// @brief アニメーションを開始
		/// @param fileName アニメーションのファイルパス
		/// @param time 時間
		void PlayAnimation(const std::wstring& fileName, float time = 0.0f, float speed = 1.0f, bool isLoop = false);

		/// @brief アニメーションの停止・終了
		/// @details もう一度再生する場合はPlayAnimation()を呼ぶ
		inline void StopAnimation() { m_AnimationData.Clip = nullptr; }



		/// @brief アニメーション速度の変更（1.0fで等速）
		/// @details 0.0fで停止、-1.0fで逆再生が可能
		inline void SetAnimationSpeed(float speed) { m_AnimationData.Speed = speed; }

		/// @brief アニメーション速度の取得
		inline float GetAnimationSpeed() const { return m_AnimationData.Speed; }

		/// @brief ループ再生するかの設定
		inline void SetAnimationLoop(bool isLoop) { m_AnimationData.Loop = isLoop; }


	private:

		/// @brief リソースの作成
		/// @param fileName ファイル名
		/// @return 作成に成功したか
		HRESULT CreateResource(std::wstring fileName = L"__box");

		/// @brief 各ボーンのワールド変換を計算する
		/// @param bone 計算するボーン
		/// @param parentMatrix 親のボーンのワールド変換行列
		/// @param WorldMatrices ボーンのWorld変換行列の配列を代入するvector
		/// @details 再帰的に呼び出される
		void CalcBoneMatrices(const Mesh::BoneData* bone,
			const DirectX::XMMATRIX& parentMatrix,
			std::vector<DirectX::XMMATRIX>& worldMatrices);
	};
}