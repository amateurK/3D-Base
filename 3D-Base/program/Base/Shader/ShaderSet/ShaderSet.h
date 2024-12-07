#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �g�p����V�F�[�_�[��ێ�����N���X
// 
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

	public:
		/// @brief �R���X�g���N�^
		ShaderSet();
		/// @brief �f�X�g���N�^
		virtual ~ShaderSet();

		/// @brief ���X�g�ɂ���V�F�[�_�[��SetShader()�����s
		void SetShaders();

		/// @brief ���X�g�ɃV�F�[�_�[��ǉ�
		/// @param type �V�F�[�_�[�̎��
		/// @param shader �V�F�[�_�[�N���X�ւ̃|�C���^
		void AddShader(ShaderType type, ShaderBase* shader);

		/// @brief �V�F�[�_�[���擾
		/// @param type �V�F�[�_�[�̎��
		/// @return ShaderBase�̃|�C���^
		inline ShaderBase* GetShader(ShaderType type) { return m_ShaderList[type]; }
	};
}
