#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �X�L�j���O�A�j���[�V����������3D���f����`�悷��R���|�[�l���g
// 
// �����	: amateurK
// �쐬��	: 2025/02/13
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

		/// @brief �g�p����V�F�[�_�[�̃|�C���^
		Shader::ShaderSet* m_ShaderSet;

		/// @brief �g�p���郁�b�V���̃|�C���^
		Mesh::SkinningMesh* m_Mesh;

		/// @brief �{�[���̍s��
		std::vector<DirectX::XMMATRIX> m_BoneMatrices;

		/// @brief �Đ����̃A�j���[�V�����Ɋւ���f�[�^
		struct AnimationData
		{
			/// @brief �Đ����̃A�j���[�V�����f�[�^
			Anim::AnimationClip* Clip;
			/// @brief ���݂̍Đ�����
			float Time;
			/// @brief �Đ����x
			float Speed;
			/// @brief ���[�v�Đ����邩
			bool Loop;

		} m_AnimationData;

	public:
		/// @brief �R���X�g���N�^
		/// @param parent ���̃R���|�[�l���g�����L���Ă���Actor
		/// @param fileName �t�@�C����
		SkinningMeshRender(Actor* const parent, std::wstring fileName = L"__box");
		/// @brief �f�X�g���N�^
		virtual ~SkinningMeshRender() = default;

		/// @brief �R���|�[�l���g�̖��O���擾
		/// @return ���O�̕�����
		inline virtual std::string GetName() const override { return "SkinningMeshRender"; }

		/// @brief �`��
		/// @param totalTime : �A�v���P�[�V�����N������̌o�ߎ��ԁi�b�j
		/// @param elapsedTime : �O���Render()����̌o�ߎ��ԁi�b�j
		virtual void Render(const double& totalTime, const float& elapsedTime) override;

		/// @brief �g�p����V�F�[�_�[���Z�b�g
		/// @param name �V�F�[�_�[�Z�b�g�̖��O
		void SetShader(const std::string& name);


		/// @brief �A�j���[�V�������J�n
		/// @param fileName �A�j���[�V�����̃t�@�C���p�X
		/// @param time ����
		void PlayAnimation(const std::wstring& fileName, float time = 0.0f, float speed = 1.0f, bool isLoop = false);

		/// @brief �A�j���[�V�����̒�~�E�I��
		/// @details ������x�Đ�����ꍇ��PlayAnimation()���Ă�
		inline void StopAnimation() { m_AnimationData.Clip = nullptr; }



		/// @brief �A�j���[�V�������x�̕ύX�i1.0f�œ����j
		/// @details 0.0f�Œ�~�A-1.0f�ŋt�Đ����\
		inline void SetAnimationSpeed(float speed) { m_AnimationData.Speed = speed; }

		/// @brief �A�j���[�V�������x�̎擾
		inline float GetAnimationSpeed() const { return m_AnimationData.Speed; }

		/// @brief ���[�v�Đ����邩�̐ݒ�
		inline void SetAnimationLoop(bool isLoop) { m_AnimationData.Loop = isLoop; }


	private:

		/// @brief ���\�[�X�̍쐬
		/// @param fileName �t�@�C����
		/// @return �쐬�ɐ���������
		HRESULT CreateResource(std::wstring fileName = L"__box");

		/// @brief �e�{�[���̃��[���h�ϊ����v�Z����
		/// @param bone �v�Z����{�[��
		/// @param parentMatrix �e�̃{�[���̃��[���h�ϊ��s��
		/// @param WorldMatrices �{�[����World�ϊ��s��̔z���������vector
		/// @details �ċA�I�ɌĂяo�����
		void CalcBoneMatrices(const Mesh::BoneData* bone,
			const DirectX::XMMATRIX& parentMatrix,
			std::vector<DirectX::XMMATRIX>& worldMatrices);
	};
}