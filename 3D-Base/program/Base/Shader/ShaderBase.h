#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �e��V�F�[�_�[�̊��N���X
// 
// 
// �����	: amateurK
// �쐬��	: 2024/11/30
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace Shader {

	/// @brief �R���X�^���g�o�b�t�@���Ǘ����邽�߂̍\����
	struct ConstantBuffer {
		/// @brief �R���X�^���g�o�b�t�@
		Microsoft::WRL::ComPtr<ID3D11Buffer> Buffer;
		/// @brief Buffer�̃T�C�Y
		size_t Size;
		/// @brief �V�F�[�_�[�ɃZ�b�g���鎞�̃X���b�g�ԍ�
		UINT Slot;
	};

	/// @brief �V�F�[�_�[������������ۂɎg�p����p�����[�^�[�Q
	struct ShaderInitParam {
		/// @brief .cso�ւ̃p�X
		std::wstring FilePath;
	};


	/// @brief �e��V�F�[�_�[�̊��N���X
	__declspec(align(16))
		class ShaderBase
	{
	protected:
		// ����Q�Ƃ�����|�C���^��ێ����Ă����������y
		ID3D11Device* m_D3DDevice;
		ID3D11DeviceContext* m_ImmediateContext;

		/// @brief �R���X�^���g�o�b�t�@�\���̂̃��X�g
		std::vector<ConstantBuffer> m_CBList;
		// TODO : �L�[���V�F�[�_�[�̓o�^ID�ɂ���map�ŊǗ�
	public:
		/// @brief �R���X�g���N�^
		ShaderBase();
		/// @brief �f�X�g���N�^
		virtual ~ShaderBase();

		/// @brief ������
		/// @param params �g�p����p�����[�^�̍\����
		/// @return ����������
		/// @details �G���g���[�|�C���g��VisualStudio�̃v���p�e�B�Őݒ肵�Ă�������
		virtual HRESULT Init(const ShaderInitParam& params) = 0;

		/// @brief �V�F�[�_�[��GPU�ɃZ�b�g����
		virtual void SetShader() = 0;

		/// @brief �R���X�^���g�o�b�t�@�̃f�[�^���X�V
		/// @param index �X�V����R���X�^���g�o�b�t�@�̃C���f�b�N�X
		/// @param data �f�[�^���i�[���Ă���ϐ��ւ̃|�C���^
		/// @return ����������
		template<typename T, typename... Args>
		HRESULT SetConstantBuffer(const size_t index, Args&&... dataArgs)
		{
			HRESULT hr = S_OK;
			auto buffer = m_CBList[index].Buffer.Get();

			// �R���X�^���g�o�b�t�@�̍X�V
			D3D11_MAPPED_SUBRESOURCE subResource = {};
			hr = m_ImmediateContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
			if (FAILED(hr)) {
				m_ImmediateContext->Unmap(buffer, 0);
				return hr;
			}

			// GPU�̃������̒u������
			// Q: �Ȃ�ł���Ȃ߂�ǂ��Ȃ��Ƃ����Ă�́H
			// �N���X�̃R���X�g���N�^�͈��������ƃ����o�[���ɉE�Ӓl��n�����̂����Ȃ�
			// ���̂��߁AArgs���g���ď���������ɂ͊e�N���X�ɃR���X�g���N�^�����Ȃ���΂����Ȃ�
			// �R���X�^���g�o�b�t�@���쐬���邽�тɂ���������͖̂ʓ|�Ȃ̂ŁA������̊֐����ŏ������Ă���
			// Q: if ����Ȃ��Ȃ��H
			// ���Ӓl�ƉE�Ӓl�ŕʂ̏�����������
			// �����̈����ɑΉ����Ă��������g���Ƃ��Ɋy����������
			if constexpr ((std::is_lvalue_reference_v<Args>&&...)) {
				// ���Ӓl�̏ꍇ: placement new�Œu������
				new(subResource.pData) T(dataArgs...);
			}
			else {
				// �E�Ӓl�̏ꍇ: construct_at�Œu������
				std::construct_at(static_cast<T*>(subResource.pData), std::forward<Args>(dataArgs)...);
			}

			m_ImmediateContext->Unmap(buffer, 0);

			UpdateGPUConstantBuffer(index);
			return hr;
		}

		/// @brief �R���X�^���g�o�b�t�@���o�C���h
		/// @param index �o�C���h����R���X�^���g�o�b�t�@�̃C���f�b�N�X
		virtual void UpdateGPUConstantBuffer(size_t index) = 0;
	protected:

		/// @brief �R���X�^���g�o�b�t�@���쐬
		/// @param size �R���X�^���g�o�b�t�@�̑傫��
		/// @return ����������
		HRESULT CreateConstantBuffer(UINT size);
	};
}
