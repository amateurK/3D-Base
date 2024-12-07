#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �f�o�C�X��X���b�v�`�F�C���Ȃǂ��쐬����N���X
// �Q�[�����[�v��E�B���h�E�ւ̏���������
// �p�����邱�Ƃ�O��ɍ쐬
// 
// �����	: amateurK
// �쐬��	: 2024/03/04
// 2D-Base����ڐA�����̂Ō��̍쐬���͕s��
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include"Singleton.h"
#include "StepTimer.h"

namespace AK_Base {

	class Actor;

	/// @brief �A�v���{�̂̃x�[�X�ƂȂ�N���X
	__declspec(align(16))
		class BaseWindow : public Singleton<BaseWindow>
	{
	private:
		// TODO: �p����̃V���O���g������BaseWindow�N���X�������Ŋ���������
		// �Ȃ����̌`�ɂ����̂��͂悭�킩��Ȃ��̂ŁA�ς��Ă���������
		friend class Singleton<BaseWindow>;

	private:
		HINSTANCE m_HInst = nullptr;
		HWND      m_HWnd = nullptr;
		D3D_DRIVER_TYPE m_DriverType = D3D_DRIVER_TYPE_NULL;
		D3D_FEATURE_LEVEL m_FeatureLevel = D3D_FEATURE_LEVEL_11_1;
		ID3D11Device* m_D3DDevice = nullptr;
		ID3D11DeviceContext* m_ImmediateContext = nullptr;
		IDXGISwapChain* m_SwapChain = nullptr;
		ID3D11RenderTargetView* m_RenderTargetView = nullptr;
		ID3D11RasterizerState* m_RasterStates = nullptr;
		ID3D11Texture2D* m_DepthStencil = nullptr;
		ID3D11DepthStencilView* m_DepthStencilView = nullptr;
		ID3D11BlendState* m_BlendState = nullptr;
		ID3D11SamplerState* m_Sampler = nullptr;


		// ���������[�N�Ď��p
#ifdef _DEBUG
		ID3D11Debug* m_D3DDebug = nullptr;
#endif

	protected:

		/// @brief �E�B���h�E�T�C�Y
		Point<int> m_WindowSize;

		/// @brief ���[�g�A�N�^�[
		Actor* m_RootActor = nullptr;

		/// @brief ��������
		/// @details 0��OFF
		UINT m_Vsync;

		/// @brief ���Ԍo�߂��Ǘ�����X�e�b�v�^�C�}�[
		DX::StepTimer m_StepTimer;

	public:
		/// @brief �R���X�g���N�^
		BaseWindow();
		/// @brief �f�X�g���N�^
		virtual ~BaseWindow();

		/// @brief �E�B���h�E�̐���
		/// @param hInstance : �C���X�^���g�n���h��
		/// @param nCmdShow : �E�B���h�E�̕\�����@
		/// @return �E�B���h�E����\���Ȃ�0�A�\������Ă���Ȃ�0�ȊO
		HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);

		/// @brief �f�o�C�X�̍쐬
		/// @return �f�o�C�X�̍쐬�ɐ���������S_OK
		HRESULT InitDevice();

		/// @brief �}�l�[�W���[�N���X���쐬����
		void CreateManager();

		/// @brief �}�l�[�W���[�N���X��j������
		void CleanupManager();

		/// @brief �쐬�����f�o�C�X�̍폜
		void CleanupDevice();

		/// @brief �Q�[�����[�v
		void GameLoop();

		/// @brief �t���[�����[�g�̕ύX
		/// @param num �t���[�����[�g�i0�Ŗ������A-1�Ő��������j
		void SetFrameRate(int16_t num);


		/// @brief �E�B���h�E�T�C�Y���Z�b�g
		/// @param size �E�B���h�E�T�C�Y
		void SetWindowSize(const Point<int>& size);

		/// @brief �E�B���h�E�T�C�Y���擾
		/// @return �E�B���h�E�T�C�Y
		const Point<int> GetWindowSize();

		/// @brief �f�o�C�X�̃A�h���X���擾����
		/// @return �擾�����f�o�C�X�̃A�h���X
		inline ID3D11Device* GetD3DDevice()
		{
			return m_D3DDevice;
		}

		/// @brief D3DDeviceContext���擾����
		/// @return �擾����D3DDeviceContext
		inline ID3D11DeviceContext* GetImmediateContext()
		{
			return m_ImmediateContext;
		}

		/// @brief ���[�g�A�N�^�[���擾����
		/// @return RootActor�ւ̃|�C���^
		inline Actor* const GetRootActor()
		{
			return m_RootActor;
		}


		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(BaseWindow));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};

}