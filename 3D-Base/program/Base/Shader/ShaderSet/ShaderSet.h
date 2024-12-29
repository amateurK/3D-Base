#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 使用するシェーダーを保持するクラス
// Unityのマテリアルとかにちょっと似てる
// 
// 製作者	: amateurK
// 作成日	: 2024/11/30
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../ShaderBase.h"

namespace Shader {

	/// @brief シェーダーの種類
	/// @details シェーダーを新規で増やす場合ここに種類を追加
	enum class ShaderType {
		None = 0,
		VertexShader,
		PixelShader,
	};

	/// @brief 使用するシェーダーを保持するクラス
	__declspec(align(16))
		class ShaderSet
	{
	private:
		/// @brief 使用するシェーダーのリスト
		std::unordered_map<ShaderType, ShaderBase*> m_ShaderList;

		/// @brief BindFuncで使用するデータへのポインタ
		std::unordered_map<std::string, std::any> m_Data;

		// @brief 名前
		std::string m_Name;

	public:
		/// @brief コンストラクタ
		ShaderSet();
		/// @brief デストラクタ
		virtual ~ShaderSet();

		/// @brief 自身とメンバ変数が同じShaderSetを作成する
		/// @param copyName 作成したShaderSetの名前
		/// @return 作成したShaderSetのポインタ
		ShaderSet* Clone(const std::string& copyName);

		/// @brief リストにあるシェーダーのSetShader()を実行
		/// @details シェーダーを切り替える時に使用
		void SetShaders();
		/// @brief リストにあるシェーダーのSetPerObject()を実行
		/// @details オブジェクトごとに違う情報をセットする
		void SetPerObject();

		/// @brief リストにシェーダーを追加
		/// @param type シェーダーの種類
		/// @param shader シェーダークラスへのポインタ
		void AddShader(ShaderType type, ShaderBase* shader);

		/// @brief シェーダーを取得
		/// @param type シェーダーの種類
		/// @return ShaderBaseのポインタ
		inline ShaderBase* GetShader(ShaderType type) { return m_ShaderList[type]; }

		/// @brief シェーダーに渡すデータの追加
		/// @tparam T 変数の型
		/// @param key 値の識別名
		/// @param val 値
		template<typename T>
		void SetData(const std::string& key, const T& val) {
			m_Data[key] = val;
		}
		template <typename T>
		void SetData(const std::string& key, T&& val) {
			m_Data[key] = std::forward<T>(val);
		}

		/// @brief シェーダーに渡すデータの取得
		/// @tparam T データの型
		/// @param key 値の識別名
		/// @return 値
		template<typename T>
		const T& GetData(const std::string& key) const {
			auto itr = m_Data.find(key);
			// TODO : Releaseではエラーチェックなくしてもいいかも？
			if (itr != m_Data.end()) {
				return std::any_cast<const T&>(itr->second); // 参照型でキャスト
			}
			else {
				throw std::exception("key is not found.");
			}
		}

		inline void SetName(const std::string& name) { m_Name = name; }
		inline std::string GetName() const { return m_Name; }
	};
}
