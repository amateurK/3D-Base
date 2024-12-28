#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// シェーダーを管理するマネージャークラス
// シングルトンクラス
// 
// 製作者	: amateurK
// 作成日	: 2024/11/29
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "ShaderBase.h"
#include "VertexShader/LambertVS.h"
#include "ShaderSet/ShaderSet.h"

namespace Shader {

	__declspec(align(16))
	class ShaderManager {

	private:
		/// @brief コンストラクタ
		ShaderManager();
		/// @brief デストラクタ
		~ShaderManager();

		static ShaderManager* Instance;
	public:
		ShaderManager(ShaderManager&&) = delete;
		ShaderManager& operator=(ShaderManager&&) = delete;

		ShaderManager(ShaderManager const&) = delete;
		ShaderManager& operator=(ShaderManager const&) = delete;

		/// @brief このクラスのインスタンスを取得
		/// @return インスタンス
		static ShaderManager* GetInstance() {
			return Instance;
		}
		/// @brief インスタンスを生成
		static void Create() {
			if (Instance == nullptr) {
				Instance = new ShaderManager;
			}
			else {
				throw std::exception("ShaderManager is a singleton");
			}
		}
		/// @brief インスタンスの解放
		static void Destroy() {
			delete Instance;
			Instance = nullptr;
		}

	private:
		/// @brief シェーダーのリスト
		std::unordered_map<std::string, ShaderBase*> m_ShaderList;

		/// @brief シェーダーをまとめたセットのリスト
		std::unordered_map<std::string, ShaderSet*> m_ShaderSetList;

		/// @brief VP行列（View * Projection）
		XMMATRIX m_VPMatrix;

	public:

		/// @brief シェーダーの追加
		/// @tparam T シェーダーのクラスの型（ShaderBaseを継承していない場合エラー）
		/// @param name シェーダーの識別用の名前
		/// @param param シェーダーごとのパラメーター
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

		/// @brief シェーダーセットを作成
		/// @param setName シェーダーセットの名前
		/// @param nameList 使用するシェーダーの名前リスト
		/// @return 作成したShaderSetへのポインタ
		ShaderSet* AddShaderSet(
			const std::string& setName,
			const std::unordered_map<ShaderType, std::string>& nameList
		);

		/// @brief シェーダーを取得
		/// @param name シェーダーの識別名
		/// @return ShaderBase型のポインタ
		inline ShaderBase* GetShader(const std::string& name) { return m_ShaderList[name]; }

		/// @brief シェーダーセットを取得
		/// @param name シェーダーセットの識別名
		/// @return ShaderSet型のポインタ
		inline ShaderSet* GetShaderSet(const std::string& name) { return m_ShaderSetList[name]; }

		/// @brief VP行列を更新（View * Projection）
		void SetVPMatrix(const XMMATRIX& view, const XMMATRIX& proj);

		/// @brief WVP行列を計算し取得する（転置済み）
		/// @param world World行列
		/// @return WVP行列
		inline XMMATRIX CalcWVPMatrix(const XMMATRIX& world) const{ return XMMatrixTranspose(world * m_VPMatrix); }


		// ゲッター

		inline const XMMATRIX* GetVPMatrix() const { return &m_VPMatrix; }

	};
}