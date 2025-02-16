#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 各種シェーダーの基底クラス
// 
// 
// 製作者	: amateurK
// 作成日	: 2024/11/30
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace Shader {

	class ShaderSet;


	/// @brief コンスタントバッファを管理するための構造体
	struct ConstantBuffer {
		/// @brief コンスタントバッファ
		Microsoft::WRL::ComPtr<ID3D11Buffer> Buffer;
		/// @brief Bufferのサイズ
		size_t Size;
		/// @brief シェーダーにセットする時のスロット番号
		UINT Slot;
	};

	/// @brief シェーダーを初期化する際に使用するパラメーター群
	struct ShaderInitParam {
		/// @brief .csoへのパス
		std::wstring FilePath;
	};


	/// @brief 各種シェーダーの基底クラス
	__declspec(align(16))
		class ShaderBase
	{
	protected:
		// 毎回参照するよりポインタを保持しておいた方が楽
		ID3D11Device* m_D3DDevice;
		ID3D11DeviceContext* m_ImmediateContext;

		/// @brief コンスタントバッファ構造体のリスト
		std::vector<ConstantBuffer> m_CBList;
		// TODO : キーをシェーダーの登録IDにしたmapで管理
	public:
		/// @brief コンストラクタ
		ShaderBase();
		/// @brief デストラクタ
		virtual ~ShaderBase();

		/// @brief 初期化
		/// @param params 使用するパラメータの構造体
		/// @return 成功したか
		/// @details エントリーポイントはVisualStudioのプロパティで設定してください
		virtual HRESULT Init(const ShaderInitParam& params) = 0;

		/// @brief シェーダーをGPUにセットする
		/// @param set ShaderSetのポインタ
		virtual void SetShader(const ShaderSet* set) = 0;

		/// @brief オブジェクトごとに変更される値をGPUにセットする
		/// @param set ShaderSetのポインタ
		virtual void SetPerObject(const ShaderSet* set) {};

		/// @brief シェーダーで使用される値をShaderSetに追加
		/// @param set ShaderSetのポインタ
		virtual void AddDataForShaderSet(ShaderSet* set) const {};

		/// @brief コンスタントバッファのデータを更新
		/// @param index 更新するコンスタントバッファのインデックス
		/// @param data データを格納している変数へのポインタ
		/// @return 成功したか
		template<typename T, typename... Args>
		HRESULT SetConstantBuffer(const size_t index, Args&&... dataArgs)
		{
			HRESULT hr = S_OK;
			auto buffer = m_CBList[index].Buffer.Get();

			// コンスタントバッファの更新
			D3D11_MAPPED_SUBRESOURCE subResource = {};
			hr = m_ImmediateContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
			if (FAILED(hr)) {
				m_ImmediateContext->Unmap(buffer, 0);
				return hr;
			}

			// GPUのメモリの置き換え
			// Q: なんでこんなめんどうなことをしてるの？
			// クラスのコンストラクタは引数無しとメンバー順に右辺値を渡すものしかない
			// そのため、Argsを使って初期化するには各クラスにコンストラクタを作らなければいけない
			// コンスタントバッファを作成するたびにそれを書くのは面倒なので、こちらの関数内で処理している
			// Q: if いらなくない？
			// 左辺値と右辺値で別の処理をしたい
			// 両方の引数に対応しておく方が使うときに楽そうだから
			if constexpr ((std::is_lvalue_reference_v<Args>&&...)) {
				// 左辺値の場合: placement newで置き換え
				new(subResource.pData) T(dataArgs...);
			}
			else {
				// 右辺値の場合: construct_atで置き換え
				std::construct_at(static_cast<T*>(subResource.pData), std::forward<Args>(dataArgs)...);
			}

			m_ImmediateContext->Unmap(buffer, 0);

			UpdateGPUConstantBuffer(index);
			return hr;
		}

		/// @brief コンスタントバッファのデータを更新（vector用）
		/// @tparam T 
		/// @param index 更新するコンスタントバッファのインデックス
		/// @param data データを格納している配列のデータの先頭へのポインタ
		/// @param elementCount 
		/// @return 
		template<typename T>
		HRESULT SetConstantBufferWithArray(const size_t index, const T* data, size_t elementCount)
		{
			HRESULT hr = S_OK;
			auto buffer = m_CBList[index].Buffer.Get();

			// コンスタントバッファの更新
			D3D11_MAPPED_SUBRESOURCE subResource = {};
			hr = m_ImmediateContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
			if (FAILED(hr)) {
				return hr;
			}

			// GPU のメモリにコピー
			memcpy(subResource.pData, data, sizeof(T) * elementCount);

			m_ImmediateContext->Unmap(buffer, 0);
			UpdateGPUConstantBuffer(index);
			return hr;
		}

		/// @brief コンスタントバッファをバインド
		/// @param index バインドするコンスタントバッファのインデックス
		virtual void UpdateGPUConstantBuffer(size_t index) = 0;
	protected:

		/// @brief コンスタントバッファを作成
		/// @param size コンスタントバッファの大きさ
		/// @return 成功したか
		HRESULT CreateConstantBuffer(UINT size);
	};
}
