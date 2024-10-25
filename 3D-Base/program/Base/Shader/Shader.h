#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// シェーダークラス
// 抽象クラス
// 
// 製作者	: amateurK
// 作成日	: 2024/08/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


namespace Shader {

	/// @brief シェーダー
	__declspec(align(16))
		class Shader
	{
	protected:
		ID3D11Device* m_D3DDevice;
		ID3D11DeviceContext* m_ImmediateContext;

		// unique_ptrだとClass**で渡すときに面倒なのでComPtrを使う

		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_VertexLayout;
		Microsoft::WRL::ComPtr<ID3D11BlendState> m_BlendState;
		Microsoft::WRL::ComPtr<ID3D11SamplerState> m_Sampler;

		DirectX::XMMATRIX m_World;
		DirectX::XMMATRIX m_View;
		DirectX::XMMATRIX m_Projection;

	public:
		/// @brief コンストラクタ
		Shader();
		/// @brief デストラクタ
		virtual ~Shader();


		/// @brief レンダリングの準備
		virtual void SetRendering() = 0;


		/// @brief ワールド行列をセット
		/// @param world ワールド行列
		inline void SetWorldMatrix(DirectX::XMMATRIX world)
		{
			m_World = world;
		}
		/// @brief ビュー行列をセット
		/// @param view ビュー行列
		inline void SetViewMatrix(DirectX::XMMATRIX view)
		{
			m_View = view;
		}
		/// @brief 射影行列をセット
		/// @param projection 射影行列
		inline void SetProjectionMatrix(DirectX::XMMATRIX projection)
		{
			m_Projection = projection;
		}


		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Shader));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}

	private:
		/// @brief シェーダーを作成
		/// @return 成功したか
		/// @details シェーダーのコンパイルや設定などを行う。長すぎるのでわけただけ
		virtual HRESULT Create() = 0;

	};
}