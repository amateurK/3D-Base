#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ゲーム内の全てのオブジェクトが継承するクラス
// オブジェクトを木構造で処理するためのもの
// 
// 製作者	: amateurK
// 作成日	: 2024/03/21
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "BaseWindow.h"

namespace AK_Base {

	/// @brief Actorの状態を表す
	enum class ActorStatus {
		ACTION,		// 行動中
		MOVEONLY,	// Move()のみ
		RENDERONLY,	// Render()のみ
		REST,		// 休憩中(なにもしない)
		DEAD,		// 死亡 = 処理が終わったら削除される
	};

	/// @brief アクタークラス
	class Actor
	{
	protected:
		ActorStatus m_Status;	// 現在の状態
		std::wstring m_ActorName;	// Actorの識別名

		std::list<Actor*> m_Children;	// 子Actorのリスト
		Actor* m_Parent;	// 親Actorへのポインタ

	public:
		/// @brief コンストラクタ
		/// @param name : 識別名
		/// @param status : 初期状態
		Actor(
			std::wstring name = L"unnamed"
		);

		/// @brief デストラクタ
		virtual ~Actor();

		/// @brief 更新
		/// @param totalTime : アプリケーション起動からの経過時間（秒）
		/// @param elapsedTime : 前回のMove()からの経過時間（秒）
		virtual void Move(const double& totalTime, const float& elapsedTime);
		/// @brief 描画
		/// @param totalTime : アプリケーション起動からの経過時間（秒）
		/// @param elapsedTime : 前回のRender()からの経過時間（秒）
		virtual void Render(const double& totalTime, const float& elapsedTime);

		/// @brief 子アクターの追加
		/// @param actor : 追加する子アクター
		virtual void AddChild(Actor* const actor);
		/// @brief 現在の状態を確認して、DEAD状態なら削除
		virtual void CheckStatus();

		/// @brief ACTIVE状態の子Actorの数を返す
		/// @return 条件に合う子Actorの数
		int GetActionChildren() const;
		/// @brief DEAD状態ではない子Actorの数を返す
		/// @return 条件に合う子Actorの数
		int GetAliveChildren() const;

		/// @brief 子Actorから特定のクラスを探す
		/// @param type : 探したいクラス（typeid()を使う）
		/// @param list : 見つかったクラスを格納するためのリスト
		void SearchClass(const type_info& type, std::list<const Actor*>*& list) const;

		/// @brief 子Actorから特定の名前のActorを探す
		/// @param name : 探したいActorの名前
		/// @return 見つかったActorへのポインタ
		const Actor* SearchName(const std::wstring name) const;

		/// @brief 現在の状態を変更
		/// @param status 変更したい状態（ActorStatus型）
		void SetStatus(const ActorStatus status);

		/// @brief 親のActorをセット
		/// @param actor 親Actorへのポインタ
		void SetParent(Actor* const actor);
	};
}
