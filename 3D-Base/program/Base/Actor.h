#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �Q�[�����̑S�ẴI�u�W�F�N�g���p������N���X
// �I�u�W�F�N�g��؍\���ŏ������邽�߂̂���
// 
// �����	: amateurK
// �쐬��	: 2024/03/21
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "BaseWindow.h"
#include "Tools/EnumClassBitMask.h"

namespace AK_Base {

	class Component;
	class Transform;

	/// @brief Actor�̏�Ԃ�\��
	enum class ActorStatus : uint8_t {
		ACTION,		// �s����
		UPDATEONLY,	// Update()�̂�
		RENDERONLY,	// Render()�̂�
		REST,		// �x�e��(�Ȃɂ����Ȃ�)
		DEAD,		// ���S = �������I�������폜�����
	};

	/// @brief �A�N�^�[�N���X
	class Actor
	{
	protected:
		ActorStatus m_Status;	// ���݂̏�ԁi���ۂɎ��s����邩�͂킩��Ȃ��j
		ActorStatus m_EffectiveStatus;	// ���݂̏�ԁi�e�̏�Ԃ��܂߂�j
		bool m_StatusChanged;	// ���݂̏�Ԃ��ύX���ꂽ��


		std::wstring m_ActorName;	// Actor�̎��ʖ�

		/// @brief �qActor�̃��X�g
		/// @details �L�[�F�A�N�^�[�̎��ʖ�
		/// @details �l�@�F�q�A�N�^�[�ւ̃|�C���^
		std::unordered_map<std::wstring, Actor*> m_Children;	// �qActor�̃��X�g
		Actor* m_Parent;	// �eActor�ւ̃|�C���^

		/// @brief �R���|�[�l���g�̃��X�g
		/// @details �L�[�F�R���|�[�l���g�̃N���X�̌^�itypeid()�Ŏ�����́j
		/// @details �l�@�F�R���|�[�l���g�̎��� 
		std::unordered_map<std::type_index, Component*> m_ComponentList;

		/// @brief Transform�R���|�[�l���g�ւ̃|�C���^
		/// @details �悭�A�N�Z�X����̂ŕێ����Ă���
		/// @details Transform�����Z�b�g����̂ŁAActor�ŐG��K�v�͂Ȃ�
		Transform* m_Transform;

	public:
		/// @brief �R���X�g���N�^
		/// @param name : ���ʖ�
		/// @param status : �������
		Actor(
			std::wstring name = L"unnamed"
		);

		/// @brief �f�X�g���N�^
		virtual ~Actor();

		/// @brief �X�V
		/// @param totalTime : �A�v���P�[�V�����N������̌o�ߎ��ԁi�b�j
		/// @param elapsedTime : �O���Update()����̌o�ߎ��ԁi�b�j
		virtual void Update(const double& totalTime, const float& elapsedTime);
		/// @brief �`��
		/// @param totalTime : �A�v���P�[�V�����N������̌o�ߎ��ԁi�b�j
		/// @param elapsedTime : �O���Render()����̌o�ߎ��ԁi�b�j
		virtual void Render(const double& totalTime, const float& elapsedTime);

		/// @brief �q�A�N�^�[�̒ǉ�
		/// @param actor : �ǉ�����q�A�N�^�[
		virtual void AddChild(Actor* const actor);
		/// @brief �q�A�N�^�[���쐬���Ēǉ�
		/// @tparam T �A�N�^�[�^
		/// @tparam ...Args �A�N�^�[�̃R���X�g���N�^�ɓn���ψ���
		/// @param ...args �����̒l
		/// @return �쐬���ꂽ�A�N�^�[�̃|�C���^
		template<typename T, typename... Args>
		T* AddChild(Args&&... args)
		{
			auto actor = new T(std::forward<Args>(args)...);
			AddChild(actor);
			return actor;
		}
		/// @brief ���݂̏�Ԃ��m�F���āADEAD��ԂȂ�폜
		virtual void CheckStatus();

		/// @brief ACTIVE��Ԃ̎qActor�̐���Ԃ�
		/// @return �����ɍ����qActor�̐�
		int GetActionChildren() const;
		/// @brief DEAD��Ԃł͂Ȃ��qActor�̐���Ԃ�
		/// @return �����ɍ����qActor�̐�
		int GetAliveChildren() const;

		/// @brief �qActor�������̃N���X��T��
		/// @param type : �T�������N���X�itypeid()���g���j
		/// @param list : ���������N���X���i�[���邽�߂̃��X�g
		void SearchChildByClass(const type_info& type, std::list<Actor*>*& list);

		/// @brief �qActor�������̖��O��Actor��T��
		/// @param name : �T������Actor�̖��O
		/// @return ��������Actor�ւ̃|�C���^
		Actor* SearchChildByName(const std::wstring& name);

		/// @brief ���݂̏�Ԃ�ύX
		/// @param status �ύX��������ԁiActorStatus�^�j
		void SetStatus(const ActorStatus& status);

		/// @brief �e��Actor���Z�b�g
		/// @param actor �eActor�ւ̃|�C���^
		void SetParent(Actor* const actor);

		/// @brief ���݂̏�Ԃ��擾����
		/// @return ���݂̏�ԁi�e�̏�Ԃ��܂߂�j
		ActorStatus GetEffectiveStatus();

		inline Actor* const GetParent() const { return m_Parent; }
		inline std::wstring GetName() const { return m_ActorName; }
		inline Transform* GetTransform() const { return m_Transform; }
		inline void SetTransform(Transform* ptr) { m_Transform = ptr; }

		/// @brief �R���|�[�l���g��ǉ�
		/// @tparam T �R���|�[�l���g�̌^
		/// @tparam ...Args �R���|�[�l���g�ɂ킽���ψ���
		/// @param ...args �����̒l
		/// @return �쐬���ꂽ�R���|�[�l���g�̃|�C���^
		template<typename T, typename... Args>
		T* AddComponent(Args&&... args)
		{
			auto component = new T(this, std::forward<Args>(args)...);
			m_ComponentList[std::type_index(typeid(T))] = std::move(component);
			return component;
		}

		/// @brief �R���|�[�l���g���擾
		/// @tparam T �R���|�[�l���g�̌^
		/// @return �������R���|�[�l���g�i�Ȃ����nullptr�j
		template<typename T>
		T* GetComponent() const
		{
			auto itr = m_ComponentList.find(std::type_index(typeid(T)));
			return (itr != m_ComponentList.end()) ?
				static_cast<T*>(itr->second) : nullptr;
		}

		template<typename T>
		void RemoveComponent()
		{
			m_ComponentList.erase(std::type_index(typeid(T)));
		}

	private:
		/// @brief �e�̏󋵂��l�����Č��݂̏�Ԃ��v�Z���ĕԂ�
		/// @return ���݂̏��
		ActorStatus UpdateEffectiveStatus() const;

		// StatusChanged��true�ɂ���
		void MarkStatusChanged();
	};
}
