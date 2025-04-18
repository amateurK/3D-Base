
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// アニメーションデータを保持するクラス
// 
// 製作者	: amateurK
// 作成日	: 2025/02/17
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "AnimationClip.h"
#include "../../Reader/tiny_gltf.h"

namespace Anim {

	AnimationClip::AnimationClip()
		: m_Duration(0.0f)
	{
		m_BoneKeyFrames.clear();
	}
	//--------------------------------------------------------------------------------------
	AnimationClip::~AnimationClip()
	{
		ClearAnimation();
	}

	//--------------------------------------------------------------------------------------
	HRESULT AnimationClip::LoadAnimation(std::wstring fileName)
	{
		HRESULT hr = S_OK;

		tinygltf::Model model;
		tinygltf::TinyGLTF loader;

		std::string err, warn;

		// ファイルのロード
		bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, Tools::WStringToString(fileName));
		if (!ret)
		{
			throw std::exception("ファイルのロードに失敗。");
			return S_FALSE;
		}

		// ボーン情報を読み込み
		// VRMは拡張機能部分にボーン情報が格納されている
		// JSONを解析してボーン情報を取得しなければいけない
		std::unordered_map<int, std::string> boneIndexMap;
		const auto& vrmaItr = model.extensions.find("VRMC_vrm_animation");
		if (vrmaItr != model.extensions.end())
		{
			const auto& vrmAnim = vrmaItr->second.Get<tinygltf::Value::Object>();
			const auto& humanoidItr = vrmAnim.find("humanoid");
			if (humanoidItr != vrmAnim.end())
			{
				const auto& humanoid = humanoidItr->second.Get<tinygltf::Value::Object>();
				const auto& humanBonesItr = humanoid.find("humanBones");
				if (humanBonesItr != humanoid.end())
				{
					auto& humanBones = humanBonesItr->second.Get<tinygltf::Value::Object>();

					// 各ボーンを取得しboneIndexMapに格納
					for (const auto& bone : humanBones)
					{
						const auto& nodeID = bone.second.Get<tinygltf::Value::Object>().find("node");
						if (nodeID != bone.second.Get<tinygltf::Value::Object>().end())
						{
							boneIndexMap[nodeID->second.Get<int>()] = bone.first;
						}
					}
				}
			}
		}
		if (boneIndexMap.empty())
		{
			return E_FAIL;
		}

		m_Duration = 0.0f;

		for (const auto& animation : model.animations)
		{
			for (const auto& channel : animation.channels)
			{
				int samplerIndex = channel.sampler;
				int targetNode = channel.target_node;
				std::string path = channel.target_path;

				// エラーチェック
				if (samplerIndex < 0 || samplerIndex >= animation.samplers.size())
				{
					continue;
				}

				// humanBonesに存在しないボーンは無視
				const auto& boneItr = boneIndexMap.find(targetNode);
				if (boneItr == boneIndexMap.end())
				{
					continue;
				}

				std::string boneName = boneItr->second;
				BoneKeyFrames& boneKeyFrames = m_BoneKeyFrames[boneName];


				// サンプラーの取得
				const auto& sampler = animation.samplers[samplerIndex];

				// 入力データ（時間）の取得
				const tinygltf::Accessor& inputAccessor = model.accessors[sampler.input];
				const tinygltf::BufferView& inputBufferView = model.bufferViews[inputAccessor.bufferView];
				const tinygltf::Buffer& inputBuffer = model.buffers[inputBufferView.buffer];
				const float* times = reinterpret_cast<const float*>(&inputBuffer.data[inputBufferView.byteOffset + inputAccessor.byteOffset]);
				// 出力データ（値）の取得
				const tinygltf::Accessor& outputAccessor = model.accessors[sampler.output];
				const tinygltf::BufferView& outputBufferView = model.bufferViews[outputAccessor.bufferView];
				const tinygltf::Buffer& outputBuffer = model.buffers[outputBufferView.buffer];
				const float* values = reinterpret_cast<const float*>(&outputBuffer.data[outputBufferView.byteOffset + outputAccessor.byteOffset]);

				if (outputAccessor.componentType != TINYGLTF_COMPONENT_TYPE_FLOAT)
				{
					throw std::exception("未対応");
				}

				// キーフレームの取得
				if (path == "translation")
				{
					// データ型チェック
					if (outputAccessor.type != TINYGLTF_TYPE_VEC3)
					{
						throw std::exception("未対応");
					}

					// 基本の位置を取得
					DirectX::XMVECTOR initPos;
					const auto& Inittrans = model.nodes[targetNode].translation;
					if (Inittrans.empty())
					{
						initPos = DirectX::XMVectorZero();
					}
					else
					{
						initPos = DirectX::XMVectorSet((float)-Inittrans[0], (float)Inittrans[1], (float)-Inittrans[2], 0.0f);
					}

					// 位置
					for (size_t i = 0; i < inputAccessor.count; ++i)
					{
						KeyFrame keyFrame;
						keyFrame.Time = times[i];
						keyFrame.Vec = DirectX::XMVectorSet(-values[i * 3], values[i * 3 + 1], -values[i * 3 + 2], 0.0f);
						keyFrame.Vec = DirectX::XMVectorSubtract(keyFrame.Vec, initPos);

						boneKeyFrames.Transform.push_back(keyFrame);
					}
				}
				else if (path == "rotation")
				{
					// データ型チェック
					if (outputAccessor.type != TINYGLTF_TYPE_VEC4)
					{
						throw std::exception("未対応");
					}
					// 基本の回転を取得
					DirectX::XMVECTOR initRot;
					const auto& InitRotation = model.nodes[targetNode].rotation;
					if (InitRotation.empty())
					{
						initRot = DirectX::XMQuaternionIdentity();
					}
					else
					{
						initRot = DirectX::XMVectorSet((float)-InitRotation[0], (float)InitRotation[1], (float)-InitRotation[2], (float)InitRotation[3]);
					}
					//initRot = DirectX::XMQuaternionInverse(initRot);


					// ↑まだ正しくない


					// 回転
					for (size_t i = 0; i < inputAccessor.count; ++i)
					{
						KeyFrame keyFrame;
						keyFrame.Time = times[i];
						keyFrame.Vec = DirectX::XMVectorSet(-values[i * 4 + 0], values[i * 4 + 1], -values[i * 4 + 2], values[i * 4 + 3]);
						//keyFrame.Vec = DirectX::XMQuaternionMultiply(initRot,keyFrame.Vec);

						//keyFrame.Vec = { 0.993926167, -2.66535896e-08, -2.95112046e-09, 0.110049300 };
						//
						//DirectX::XMVECTOR axis = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
						//float rot = DirectX::XM_PIDIV2 * 0.5f;
						//if (channel.target_node != 100) {
						//	axis = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f);
						//	//rot = -DirectX::XM_PIDIV2;
						//	rot = 0.0f;
						//}
						////keyFrame.Vec = DirectX::XMQuaternionRotationAxis(axis, rot);

						//DirectX::XMQuaternionToAxisAngle(&axis, &rot, keyFrame.Vec);

						//DirectX::XMVECTOR qu;
						//if (!DirectX::XMVector3Equal(axis, DirectX::XMVectorZero()))
						//{
						//	keyFrame.Vec = DirectX::XMQuaternionRotationAxis(axis, rot);
						//}
						//if (!DirectX::XMVector4Equal(qu, keyFrame.Vec))
						//{
						//	int a = 0;
						//}

						// {-0.993926167, -2.66535896e-08, -2.95112046e-09, 0.110049300}
						// initRot
						// 30 {-0.843790531, -0.00230843923, -4.64234962e-09, -0.536668181}
						// 60 {-0.154939786, -0.705950022, -0.00230840221, -0.691103041}
						// 90 {-0.157192290, -4.21533297e-09, -0.705949962, -0.690598011}

						// none
						// 30 {-0.626267076, -0.000254058541, 0.00229439349, 0.779605448}
						// 60 {-0.703956366, -0.0799836963, 0.701408088, 0.0779433027}
						// 90 {-0.703702331, -0.701662123, -0.0776892975, 0.0802377015}





						// クォータニオンが正規化されていない場合は正規化（普通はない）
						if (std::abs(DirectX::XMVectorGetX(DirectX::XMQuaternionLength(keyFrame.Vec)) - 1.0f) >= 0.01f)
						{
							keyFrame.Vec = DirectX::XMQuaternionNormalize(keyFrame.Vec);
						}

						boneKeyFrames.Rotation.push_back(keyFrame);
					}
				}
				else {
					// 未対応のため無視
				}

				// アニメーション時間を計測
				m_Duration = std::max(m_Duration, times[inputAccessor.count - 1]);
			}
		}

		return hr;
	}

	//--------------------------------------------------------------------------------------
	void AnimationClip::ClearAnimation()
	{
		for (auto& bone : m_BoneKeyFrames)
		{
			bone.second.Transform.clear();
			bone.second.Rotation.clear();
		}
		m_BoneKeyFrames.clear();
	}

	//--------------------------------------------------------------------------------------
	bool AnimationClip::GetBoneMatrix(const std::string& boneName, float time, DirectX::XMMATRIX& output) const
	{
		const auto& keyFrameItr = m_BoneKeyFrames.find(boneName);
		if (keyFrameItr == m_BoneKeyFrames.end())
		{
			// ボーン名が存在しない場合
			return false;
		}

		//output = DirectX::XMMatrixRotationQuaternion(InterpolateRotation(keyFrameItr->second.Rotation, time))
		//	* DirectX::XMMatrixTranslationFromVector(InterpolateTransform(keyFrameItr->second.Transform, time));
		output = DirectX::XMMatrixTranspose(
			DirectX::XMMatrixRotationQuaternion(InterpolateRotation(keyFrameItr->second.Rotation, time))
			* DirectX::XMMatrixTranslationFromVector(InterpolateTransform(keyFrameItr->second.Transform, time))
		);

		//output = DirectX::XMMatrixTranspose(
		//	DirectX::XMMatrixTranslationFromVector(InterpolateTransform(keyFrameItr->second.Transform, time))
		//	* DirectX::XMMatrixRotationQuaternion(InterpolateRotation(keyFrameItr->second.Rotation, time))
		//);
		//output = 
		//	DirectX::XMMatrixTranslationFromVector(InterpolateTransform(keyFrameItr->second.Transform, time))
		//	* DirectX::XMMatrixRotationQuaternion(InterpolateRotation(keyFrameItr->second.Rotation, time));
		return true;
	}

	//--------------------------------------------------------------------------------------
	const DirectX::XMVECTOR& AnimationClip::InterpolateTransform(const std::vector<KeyFrame>& keyFrames, float time) const
	{
		// キーフレームがない場合
		if (keyFrames.empty())
		{
			return DirectX::XMVectorZero();
		}

		// 二分探索で現在の時間に対応するキーフレームを探す
		auto itr = std::lower_bound(keyFrames.begin(), keyFrames.end(), time,
			[](const KeyFrame& kf, const float& t)
			{ return kf.Time < t; });

		// 最初のキーフレームより前の場合
		if (itr == keyFrames.begin())
		{
			return keyFrames.front().Vec;
		}
		// 最後のキーフレームより後の場合
		else if (itr == keyFrames.end())
		{
			return keyFrames.back().Vec;
		}
		// キーフレームの間にある場合
		else
		{
			const KeyFrame& prevKeyFrame = *(itr - 1);
			const KeyFrame& nextKeyFrame = *itr;

			// 現在の時間が前後のキーフレームのどの位置にあるか
			float t = (time - prevKeyFrame.Time) / (nextKeyFrame.Time - prevKeyFrame.Time);
			// 線形補間
			return DirectX::XMVectorLerp(prevKeyFrame.Vec, nextKeyFrame.Vec, t);
		}
	}

	//--------------------------------------------------------------------------------------
	const DirectX::XMVECTOR& AnimationClip::InterpolateRotation(const std::vector<KeyFrame>& keyFrames, float time) const
	{
		// キーフレームがない場合
		if (keyFrames.empty())
		{
			return DirectX::XMQuaternionIdentity();
		}

		// 二分探索で現在の時間に対応するキーフレームを探す
		auto itr = std::lower_bound(keyFrames.begin(), keyFrames.end(), time,
			[](const KeyFrame& kf, const float& t)
			{ return kf.Time < t; });

		// 最初のキーフレームより前の場合
		if (itr == keyFrames.begin())
		{
			return keyFrames.front().Vec;
		}
		// 最後のキーフレームより後の場合
		else if (itr == keyFrames.end())
		{
			return keyFrames.back().Vec;
		}
		// キーフレームの間にある場合
		else
		{
			const KeyFrame& prevKeyFrame = *(itr - 1);
			const KeyFrame& nextKeyFrame = *itr;

			// 現在の時間が前後のキーフレームのどの位置にあるか
			float t = (time - prevKeyFrame.Time) / (nextKeyFrame.Time - prevKeyFrame.Time);

			// 球面線形補間
			return DirectX::XMQuaternionSlerp(prevKeyFrame.Vec, nextKeyFrame.Vec, t);
		}
	}
};