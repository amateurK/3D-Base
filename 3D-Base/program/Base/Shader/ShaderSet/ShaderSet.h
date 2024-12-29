#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �g�p����V�F�[�_�[��ێ�����N���X
// Unity�̃}�e���A���Ƃ��ɂ�����Ǝ��Ă�
// 
// �����	: amateurK
// �쐬��	: 2024/11/30
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../ShaderBase.h"

namespace Shader {

	/// @brief �V�F�[�_�[�̎��
	/// @details �V�F�[�_�[��V�K�ő��₷�ꍇ�����Ɏ�ނ�ǉ�
	enum class ShaderType {
		None = 0,
		VertexShader,
		PixelShader,
	};

	/// @brief �g�p����V�F�[�_�[��ێ�����N���X
	__declspec(align(16))
		class ShaderSet
	{
	private:
		/// @brief �g�p����V�F�[�_�[�̃��X�g
		std::unordered_map<ShaderType, ShaderBase*> m_ShaderList;

		/// @brief BindFunc�Ŏg�p����f�[�^�ւ̃|�C���^
		std::unordered_map<std::string, std::any> m_Data;

		// @brief ���O
		std::string m_Name;

	public:
		/// @brief �R���X�g���N�^
		ShaderSet();
		/// @brief �f�X�g���N�^
		virtual ~ShaderSet();

		/// @brief ���g�ƃ����o�ϐ�������ShaderSet���쐬����
		/// @param copyName �쐬����ShaderSet�̖��O
		/// @return �쐬����ShaderSet�̃|�C���^
		ShaderSet* Clone(const std::string& copyName);

		/// @brief ���X�g�ɂ���V�F�[�_�[��SetShader()�����s
		/// @details �V�F�[�_�[��؂�ւ��鎞�Ɏg�p
		void SetShaders();
		/// @brief ���X�g�ɂ���V�F�[�_�[��SetPerObject()�����s
		/// @details �I�u�W�F�N�g���ƂɈႤ�����Z�b�g����
		void SetPerObject();

		/// @brief ���X�g�ɃV�F�[�_�[��ǉ�
		/// @param type �V�F�[�_�[�̎��
		/// @param shader �V�F�[�_�[�N���X�ւ̃|�C���^
		void AddShader(ShaderType type, ShaderBase* shader);

		/// @brief �V�F�[�_�[���擾
		/// @param type �V�F�[�_�[�̎��
		/// @return ShaderBase�̃|�C���^
		inline ShaderBase* GetShader(ShaderType type) { return m_ShaderList[type]; }

		/// @brief �V�F�[�_�[�ɓn���f�[�^�̒ǉ�
		/// @tparam T �ϐ��̌^
		/// @param key �l�̎��ʖ�
		/// @param val �l
		template<typename T>
		void SetData(const std::string& key, const T& val) {
			m_Data[key] = val;
		}
		template <typename T>
		void SetData(const std::string& key, T&& val) {
			m_Data[key] = std::forward<T>(val);
		}

		/// @brief �V�F�[�_�[�ɓn���f�[�^�̎擾
		/// @tparam T �f�[�^�̌^
		/// @param key �l�̎��ʖ�
		/// @return �l
		template<typename T>
		const T& GetData(const std::string& key) const {
			auto itr = m_Data.find(key);
			// TODO : Release�ł̓G���[�`�F�b�N�Ȃ����Ă����������H
			if (itr != m_Data.end()) {
				return std::any_cast<const T&>(itr->second); // �Q�ƌ^�ŃL���X�g
			}
			else {
				throw std::exception("key is not found.");
			}
		}

		inline void SetName(const std::string& name) { m_Name = name; }
		inline std::string GetName() const { return m_Name; }
	};
}
