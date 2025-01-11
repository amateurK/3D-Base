#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 衝突判定を奥なうColliderコンポーネントを管理するクラス
// シングルトンクラス
// 
// 製作者	: amateurK
// 作成日	: 2025/01/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../Component/Collider.h"


namespace AK_Base {

	__declspec(align(16))
		class CollisionManager {

		private:
			/// @brief コンストラクタ
			CollisionManager();
			/// @brief デストラクタ
			~CollisionManager();

			static CollisionManager* Instance;
		public:
			CollisionManager(CollisionManager&&) = delete;
			CollisionManager& operator=(CollisionManager&&) = delete;

			CollisionManager(CollisionManager const&) = delete;
			CollisionManager& operator=(CollisionManager const&) = delete;

			/// @brief このクラスのインスタンスを取得
			/// @return インスタンス
			static CollisionManager* GetInstance() {
				return Instance;
			}
			/// @brief インスタンスを生成
			static void Create() {
				if (Instance == nullptr) {
					Instance = new CollisionManager;
				}
				else {
					throw std::exception("CollisionManager is a singleton");
				}
			}
			/// @brief インスタンスの解放
			static void Destroy() {
				delete Instance;
				Instance = nullptr;
			}

		private:
			/// @brief Colliderコンポーネントのリスト
			/// @details キー : 登録するリストの名前
			/// @details 値　 : リスト
			std::unordered_map<std::string, std::vector<Collider*>> m_ColliderList;

			/// @brief 衝突判定を行うリスト
			/// @details ColliderListのインデックスをpairにして追加する
			std::vector<std::pair<std::string, std::string>> m_CheckList;

		public:

			/// @brief Colliderのリストに追加する
			/// @param listName 登録するリストの名前
			/// @param ptr 登録するColliderの名前
			void AddColliderList(const std::string& listName, Collider* ptr);

			/// @brief あたり判定を行うペアを追加
			/// @param listName1 リストの名前
			/// @param listName2 リストの名前（listName1と同じでもよい）
			void AddCkeckList(const std::string& listName1, const std::string& listName2);

			/// @brief あたり判定を行うペアを削除
			/// @param listName1 リストの名前
			/// @param listName2 リストの名前
			void RemoveCheckList(const std::string& listName1, const std::string& listName2);

			/// @brief リスト内のColliderが衝突しているかを調べる
			void CheckCollide(std::vector<Collider*>& list1, std::vector<Collider*> list2) const;
	};
}
