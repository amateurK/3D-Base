#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �e�X�g�p
// �Q�[���{��
// BaseWindow���p��
// 
// �����	: amateurK
// �쐬��	: 2024/03/06
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Base/BaseWindow.h"
#include "Base/Shader/Shader.h"

class MyGame :public AK_Base::BaseWindow
{
private:
	// TODO : �V�F�[�_�[�Ǘ��N���X��������ق����ǂ�����
	std::unique_ptr<Shader::Shader> m_TestShader;

public:
	MyGame();
	virtual ~MyGame();

	/// @brief �q�A�N�^�[���쐬����
	/// @details �f�o�C�X�쐬��Ɏq�A�N�^�[�̏������s������
	virtual void CreateActor() override;

	/// @brief Shader�ւ̃|�C���^��Ԃ�
	/// @return �|�C���^
	inline Shader::Shader* const GetTestShader()
	{
		return m_TestShader.get();
	}
};