#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// コンポーネント
// Actorに取り付けて使う
// 
// 製作者	: amateurK
// 作成日	: 2024/11/16
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


namespace AK_Base {

	class Actor;

	/// @brief コンポーネント
	class Component
	{
	private:

		/// @brief このコンポーネントを所有しているActor
		Actor* m_Parent;


	public:

		/// @brief コンストラクタ
		/// @param parent このコンポーネントを所有しているActor（AddComponent<T>()で追加される）
		Component(Actor* const parent)
			: m_Parent(parent)
		{}
		/// @brief デストラクタ
		virtual ~Component() {}

		/// @brief コンポーネントの名前を取得
		/// @return 名前の文字列
		virtual std::string GetName() const = 0;


		/// @brief 更新
		/// @param totalTime : アプリケーション起動からの経過時間（秒）
		/// @param elapsedTime : 前回のUpdate()からの経過時間（秒）
		virtual void Update(const double& totalTime, const float& elapsedTime) {};

		/// @brief 描画
		/// @param totalTime : アプリケーション起動からの経過時間（秒）
		/// @param elapsedTime : 前回のRender()からの経過時間（秒）
		virtual void Render(const double& totalTime, const float& elapsedTime) {};

		/// @brief このコンポーネントを所有しているActorを返す
		/// @return Actorのポインタ
		Actor* GetActor() const
		{
			return m_Parent;
		}
	};

}