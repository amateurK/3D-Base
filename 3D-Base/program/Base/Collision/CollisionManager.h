#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 衝突判定を奥なうColliderコンポーネントを管理するクラス
// シングルトンクラス
// 
// 製作者	: amateurK
// 作成日	: 2025/01/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//#include "../Component/Collider.h"

//
// そのうち処理速度が厳しくなると思うので、そのうちやることをメモ
// 1. Collisionを複数のリストに分ける
// 　"Enemy"、"Player"などのようなリストに分ける
// 　"Enemy"同士の衝突判定は行わない、"Enemy"と"EnemyBullet"の衝突判定は行わない、など
// 　必要なリストのみを衝突判定を行うことで処理速度を向上させる
// 2. 衝突判定の結果をキャッシュする
// 3. Octreeを実装する
//　衝突判定を行うオブジェクトを空間分割することで、衝突判定の対象を絞り込む
// 4. 球や四角でオブジェクトを囲い、それで大まかに衝突判定を行う
// 　3.があるので要らないかも
//


namespace AK_Base {

	class Collider;
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

			/// @brief 衝突判定の結果をキャッシュ（Colliderのリストも兼ねている）
			/// @details 1フレーム中に同じCollider同士の衝突判定を複数回行うことを防ぐ
			/// @details first : Collider, second : <firstと衝突しているColliderの集合, firstと衝突していないColliderの集合>
			std::unordered_map<Collider*, std::pair<std::unordered_set<Collider*>, std::unordered_set<Collider*>>> m_IsCollideCache;

		public:
			/// @brief Colliderを追加
			void AddCollider(Collider* collider);

			/// @brief Colliderを削除
			void RemoveCollider(Collider* collider);

			/// @brief 衝突判定を行う
			void CollisionDetection();

			/// @brief 衝突しているColliderの集合を取得
			/// @param collider 調べるCollider
			/// @return 集合のポインタ
			std::unordered_set<Collider*>* GetCollideSet(Collider* collider);
	};
}
