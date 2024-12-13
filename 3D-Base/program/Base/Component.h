#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �R���|�[�l���g
// Actor�Ɏ��t���Ďg��
// 
// �����	: amateurK
// �쐬��	: 2024/11/16
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


namespace AK_Base {

	class Actor;

	/// @brief �R���|�[�l���g
	class Component
	{
	private:

		/// @brief ���̃R���|�[�l���g�����L���Ă���Actor
		Actor* m_Parent;


	public:

		/// @brief �R���X�g���N�^
		/// @param parent ���̃R���|�[�l���g�����L���Ă���Actor�iAddComponent<T>()�Œǉ������j
		Component(Actor* const parent)
			: m_Parent(parent)
		{}
		/// @brief �f�X�g���N�^
		virtual ~Component() {}

		/// @brief �R���|�[�l���g�̖��O���擾
		/// @return ���O�̕�����
		virtual std::string GetName() const = 0;


		/// @brief �X�V
		/// @param totalTime : �A�v���P�[�V�����N������̌o�ߎ��ԁi�b�j
		/// @param elapsedTime : �O���Update()����̌o�ߎ��ԁi�b�j
		virtual void Update(const double& totalTime, const float& elapsedTime) {};

		/// @brief �`��
		/// @param totalTime : �A�v���P�[�V�����N������̌o�ߎ��ԁi�b�j
		/// @param elapsedTime : �O���Render()����̌o�ߎ��ԁi�b�j
		virtual void Render(const double& totalTime, const float& elapsedTime) {};

		/// @brief ���̃R���|�[�l���g�����L���Ă���Actor��Ԃ�
		/// @return Actor�̃|�C���^
		Actor* GetActor() const
		{
			return m_Parent;
		}
	};

}