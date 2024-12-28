#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �V�F�[�_�[���Ǘ�����}�l�[�W���[�N���X
// �V���O���g���N���X
// 
// �����	: amateurK
// �쐬��	: 2024/11/29
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "ShaderBase.h"
#include "VertexShader/LambertVS.h"
#include "ShaderSet/ShaderSet.h"

namespace Shader {

	__declspec(align(16))
	class ShaderManager {

	private:
		/// @brief �R���X�g���N�^
		ShaderManager();
		/// @brief �f�X�g���N�^
		~ShaderManager();

		static ShaderManager* Instance;
	public:
		ShaderManager(ShaderManager&&) = delete;
		ShaderManager& operator=(ShaderManager&&) = delete;

		ShaderManager(ShaderManager const&) = delete;
		ShaderManager& operator=(ShaderManager const&) = delete;

		/// @brief ���̃N���X�̃C���X�^���X���擾
		/// @return �C���X�^���X
		static ShaderManager* GetInstance() {
			return Instance;
		}
		/// @brief �C���X�^���X�𐶐�
		static void Create() {
			if (Instance == nullptr) {
				Instance = new ShaderManager;
			}
			else {
				throw std::exception("ShaderManager is a singleton");
			}
		}
		/// @brief �C���X�^���X�̉��
		static void Destroy() {
			delete Instance;
			Instance = nullptr;
		}

	private:
		/// @brief �V�F�[�_�[�̃��X�g
		std::unordered_map<std::string, ShaderBase*> m_ShaderList;

		/// @brief �V�F�[�_�[���܂Ƃ߂��Z�b�g�̃��X�g
		std::unordered_map<std::string, ShaderSet*> m_ShaderSetList;

		/// @brief VP�s��iView * Projection�j
		XMMATRIX m_VPMatrix;

	public:

		/// @brief �V�F�[�_�[�̒ǉ�
		/// @tparam T �V�F�[�_�[�̃N���X�̌^�iShaderBase���p�����Ă��Ȃ��ꍇ�G���[�j
		/// @param name �V�F�[�_�[�̎��ʗp�̖��O
		/// @param param �V�F�[�_�[���Ƃ̃p�����[�^�[
		template<typename T>
		void AddShader(
			const std::string& name,
			const ShaderInitParam& params
		)
		{
			T* shader = new T();
			shader->Init(params);

			m_ShaderList[name] = shader;
		}

		/// @brief �V�F�[�_�[�Z�b�g���쐬
		/// @param setName �V�F�[�_�[�Z�b�g�̖��O
		/// @param nameList �g�p����V�F�[�_�[�̖��O���X�g
		/// @return �쐬����ShaderSet�ւ̃|�C���^
		ShaderSet* AddShaderSet(
			const std::string& setName,
			const std::unordered_map<ShaderType, std::string>& nameList
		);

		/// @brief �V�F�[�_�[���擾
		/// @param name �V�F�[�_�[�̎��ʖ�
		/// @return ShaderBase�^�̃|�C���^
		inline ShaderBase* GetShader(const std::string& name) { return m_ShaderList[name]; }

		/// @brief �V�F�[�_�[�Z�b�g���擾
		/// @param name �V�F�[�_�[�Z�b�g�̎��ʖ�
		/// @return ShaderSet�^�̃|�C���^
		inline ShaderSet* GetShaderSet(const std::string& name) { return m_ShaderSetList[name]; }

		/// @brief VP�s����X�V�iView * Projection�j
		void SetVPMatrix(const XMMATRIX& view, const XMMATRIX& proj);

		/// @brief WVP�s����v�Z���擾����i�]�u�ς݁j
		/// @param world World�s��
		/// @return WVP�s��
		inline XMMATRIX CalcWVPMatrix(const XMMATRIX& world) const{ return XMMatrixTranspose(world * m_VPMatrix); }


		// �Q�b�^�[

		inline const XMMATRIX* GetVPMatrix() const { return &m_VPMatrix; }

	};
}