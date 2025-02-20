#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �A�j���[�V�����f�[�^��ێ�����N���X
// 
// �����	: amateurK
// �쐬��	: 2025/02/17
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


namespace Anim {

	/// @brief ��̃L�[�t���[����\���\����
	__declspec(align(16))
		struct KeyFrame
	{
		/// @brief �s��
		DirectX::XMVECTOR Vec;
		/// @brief ����
		float Time;
	};
	struct BoneKeyFrames
	{
		/// @brief �ړ��̃L�[�t���[��
		std::vector<KeyFrame> Transform;
		/// @brief ��]�̃L�[�t���[��
		std::vector<KeyFrame> Rotation;
	};

	// �A�j���[�V�����f�[�^��ێ�����N���X
	class AnimationClip
	{
	private:

		/// @brief �{�[�����Ƃ̃L�[�t���[��
		/// @details �L�[ : �{�[����
		/// @details �l : �L�[�t���[���̃��X�g
		std::unordered_map<std::string, BoneKeyFrames> m_BoneKeyFrames;

		/// @brief �A�j���[�V�����̒���
		float m_Duration;

	public:
		/// @brief �R���X�g���N�^
		AnimationClip();
		/// @brief �f�X�g���N�^
		~AnimationClip();

		/// @brief �A�j���[�V�����̃��[�h
		HRESULT LoadAnimation(std::wstring fileName = L"");
		/// @brief �A�j���[�V�����̍폜
		void ClearAnimation();

		/// @brief �{�[���̕ϊ��s����擾
		/// @param boneName �{�[���̖��O
		/// @param time �A�j���[�V�����J�n����̎���
		/// @param output �ϊ��s��
		/// @return �l���擾�ł������ifalse�̏ꍇ�A�{�[���͑��݂��Ȃ��������ƂɂȂ�j
		bool GetBoneMatrix(const std::string& boneName, float time, DirectX::XMMATRIX& output) const;

		/// @brief �A�j���[�V�����̒������擾
		inline float GetDuration() const { return m_Duration; }

	private:
		/// @brief �L�[�t���[�����猻�݂̈ʒu���擾
		/// @param keyFrames �L�[�t���[��
		/// @param time ���ݎ���
		/// @return �ʒu��\��VECTOR
		const DirectX::XMVECTOR& InterpolateTransform(const std::vector<KeyFrame>& keyFrames, float time) const;
		/// @brief �L�[�t���[�����猻�݂̉�]���擾
		/// @param keyFrames �L�[�t���[��
		/// @param time ���ݎ���
		/// @return �N�H�[�^�j�I��
		const DirectX::XMVECTOR& InterpolateRotation(const std::vector<KeyFrame>& keyFrames, float time) const;
	};
}