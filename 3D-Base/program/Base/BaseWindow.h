#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// デバイスやスワップチェインなどを作成するクラス
// ゲームループやウィンドウへの処理もここ
// 継承することを前提に作成
// 
// 製作者	: amateurK
// 作成日	: 2024/03/04
// 2D-Baseから移植したので元の作成日は不明
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include"Singleton.h"
#include "StepTimer.h"

namespace AK_Base {

	class Actor;

	/// @brief アプリ本体のベースとなるクラス
	__declspec(align(16))
		class BaseWindow : public Singleton<BaseWindow>
	{
	private:
		// TODO: 継承先のシングルトン化をBaseWindowクラス内だけで完結させる
		// なぜこの形にしたのかはよくわからないので、変えてもいいかも
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


		// メモリリーク監視用
#ifdef _DEBUG
		ID3D11Debug* m_D3DDebug = nullptr;
#endif

	protected:

		/// @brief ウィンドウサイズ
		Point<int> m_WindowSize;

		/// @brief ルートアクター
		Actor* m_RootActor = nullptr;

		/// @brief 垂直同期
		/// @details 0でOFF
		UINT m_Vsync;

		/// @brief 時間経過を管理するステップタイマー
		DX::StepTimer m_StepTimer;

	public:
		/// @brief コンストラクタ
		BaseWindow();
		/// @brief デストラクタ
		virtual ~BaseWindow();

		/// @brief ウィンドウの生成
		/// @param hInstance : インスタントハンドル
		/// @param nCmdShow : ウィンドウの表示方法
		/// @return ウィンドウが非表示なら0、表示されているなら0以外
		HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);

		/// @brief デバイスの作成
		/// @return デバイスの作成に成功したらS_OK
		HRESULT InitDevice();

		/// @brief マネージャークラスを作成する
		void CreateManager();

		/// @brief マネージャークラスを破棄する
		void CleanupManager();

		/// @brief 作成したデバイスの削除
		void CleanupDevice();

		/// @brief ゲームループ
		void GameLoop();

		/// @brief フレームレートの変更
		/// @param num フレームレート（0で無制限、-1で垂直同期）
		void SetFrameRate(int16_t num);


		/// @brief ウィンドウサイズをセット
		/// @param size ウィンドウサイズ
		void SetWindowSize(const Point<int>& size);

		/// @brief ウィンドウサイズを取得
		/// @return ウィンドウサイズ
		const Point<int> GetWindowSize();

		/// @brief デバイスのアドレスを取得する
		/// @return 取得したデバイスのアドレス
		inline ID3D11Device* GetD3DDevice()
		{
			return m_D3DDevice;
		}

		/// @brief D3DDeviceContextを取得する
		/// @return 取得したD3DDeviceContext
		inline ID3D11DeviceContext* GetImmediateContext()
		{
			return m_ImmediateContext;
		}

		/// @brief ルートアクターを取得する
		/// @return RootActorへのポインタ
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