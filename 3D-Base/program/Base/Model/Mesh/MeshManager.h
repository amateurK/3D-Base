#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// メッシュデータを管理するマネージャークラス
// シングルトンクラス
// 
// 製作者	: amateurK
// 作成日	: 2024/07/29
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Mesh.h"

namespace Mesh {

	enum class MeshType {
		BasicMesh,
		FbxMesh,
	};

	/// @brief メッシュデータを管理するマネージャークラス
	class MeshManager
	{
	private:
		/// @brief メッシュクラスと名前のセット
		struct MeshData {
			std::wstring Name;
			Mesh* Mesh;
		};

		/// @brief コンストラクタ
		MeshManager();
		/// @brief デストラクタ
		~MeshManager();

		static MeshManager* Instance;
	public:
		MeshManager(MeshManager&& moveFrom) = delete;
		MeshManager& operator=(MeshManager&& moveFrom) = delete;

		MeshManager(MeshManager const&) = delete;
		MeshManager& operator=(MeshManager const&) = delete;

		/// @brief このクラスのインスタンスを取得
		/// @return インスタンス
		static MeshManager* GetInstance() {
			return Instance;
		}
		/// @brief インスタンスを生成
		static void Create() {
			if (Instance == nullptr) {
				Instance = new MeshManager;
			}
			else {
				throw std::exception("MeshManager is a singleton");
			}
		}
		/// @brief インスタンスの解放
		static void Destroy() {
			delete Instance;
			Instance = nullptr;
		}

	private:
		/// @brief メッシュのリスト
		std::list<MeshData> m_MeshList;

	public:
		/// @brief メッシュを作成して取得する
		/// @param fileName メッシュファイルへのパス
		/// @param mesh 作成したメッシュを返す
		/// @return 正常に取得できたか
		HRESULT CreateMesh(std::wstring& fileName, MeshType meshType, Mesh*& mesh);

		/// @brief 指定したメッシュを破棄する
		/// @param fileName 破棄したいメッシュファイルへのパス
		void DestroyMesh(std::wstring& fileName);

		/// @brief メッシュを全て破棄する
		void DestroyAllMesh();
	};
}