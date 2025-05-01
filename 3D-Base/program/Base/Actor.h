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
#include "Tools/EnumClassBitMask.h"

namespace AK_Base {

	class Component;
	class Transform;

	/// @brief Actorの状態を表す
	enum class ActorStatus : uint8_t {
		ACTION,		// 行動中
		UPDATEONLY,	// Update()のみ
		RENDERONLY,	// Render()のみ
		REST,		// 休憩中(なにもしない)
		DEAD,		// 死亡 = 処理が終わったら削除される
	};

	/// @brief アクタークラス
	class Actor
	{
	protected:
		ActorStatus m_Status;	// 現在の状態（実際に実行されるかはわからない）
		ActorStatus m_EffectiveStatus;	// 現在の状態（親の状態も含める）
		bool m_StatusChanged;	// 現在の状態が変更されたか


		std::wstring m_ActorName;	// Actorの識別名

		/// @brief 子Actorのリスト
		/// @details キー：アクターの識別名
		/// @details 値　：子アクターへのポインタ
		std::unordered_map<std::wstring, Actor*> m_Children;	// 子Actorのリスト
		Actor* m_Parent;	// 親Actorへのポインタ

		/// @brief コンポーネントのリスト
		/// @details キー：コンポーネントのクラスの型（typeid()で取れるもの）
		/// @details 値　：コンポーネントの実体 
		std::unordered_map<std::type_index, Component*> m_ComponentList;

		/// @brief Transformコンポーネントへのポインタ
		/// @details よくアクセスするので保持しておく
		/// @details Transform側がセットするので、Actorで触る必要はない
		Transform* m_Transform;

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
		/// @param elapsedTime : 前回のUpdate()からの経過時間（秒）
		virtual void Update(const double& totalTime, const float& elapsedTime);
		/// @brief 描画
		/// @param totalTime : アプリケーション起動からの経過時間（秒）
		/// @param elapsedTime : 前回のRender()からの経過時間（秒）
		virtual void Render(const double& totalTime, const float& elapsedTime);

		/// @brief 子アクターの追加
		/// @param actor : 追加する子アクター
		virtual void AddChild(Actor* const actor);
		/// @brief 子アクターを作成して追加
		/// @tparam T アクター型
		/// @tparam ...Args アクターのコンストラクタに渡す可変引数
		/// @param ...args 引数の値
		/// @return 作成されたアクターのポインタ
		template<typename T, typename... Args>
		T* AddChild(Args&&... args)
		{
			auto actor = new T(std::forward<Args>(args)...);
			AddChild(actor);
			return actor;
		}
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
		void SearchChildByClass(const type_info& type, std::list<Actor*>*& list);

		/// @brief 子Actorから特定の名前のActorを探す
		/// @param name : 探したいActorの名前
		/// @return 見つかったActorへのポインタ
		Actor* SearchChildByName(const std::wstring& name);

		/// @brief 現在の状態を変更
		/// @param status 変更したい状態（ActorStatus型）
		void SetStatus(const ActorStatus& status);

		/// @brief 親のActorをセット
		/// @param actor 親Actorへのポインタ
		void SetParent(Actor* const actor);

		/// @brief 現在の状態を取得する
		/// @return 現在の状態（親の状態も含める）
		ActorStatus GetEffectiveStatus();

		inline Actor* const GetParent() const { return m_Parent; }
		inline std::wstring GetName() const { return m_ActorName; }
		inline Transform* GetTransform() const { return m_Transform; }
		inline void SetTransform(Transform* ptr) { m_Transform = ptr; }

		/// @brief コンポーネントを追加
		/// @tparam T コンポーネントの型
		/// @tparam ...Args コンポーネントにわたす可変引数
		/// @param ...args 引数の値
		/// @return 作成されたコンポーネントのポインタ
		template<typename T, typename... Args>
		T* AddComponent(Args&&... args)
		{
			auto component = new T(this, std::forward<Args>(args)...);
			m_ComponentList[std::type_index(typeid(T))] = std::move(component);
			return component;
		}

		/// @brief コンポーネントを取得
		/// @tparam T コンポーネントの型
		/// @return 見つけたコンポーネント（なければnullptr）
		template<typename T>
		T* GetComponent() const
		{
			auto itr = m_ComponentList.find(std::type_index(typeid(T)));
			return (itr != m_ComponentList.end()) ?
				static_cast<T*>(itr->second) : nullptr;
		}

		template<typename T>
		void RemoveComponent()
		{
			m_ComponentList.erase(std::type_index(typeid(T)));
		}

	private:
		/// @brief 親の状況を考慮して現在の状態を計算して返す
		/// @return 現在の状態
		ActorStatus UpdateEffectiveStatus() const;

		// StatusChangedをtrueにする
		void MarkStatusChanged();
	};
}
