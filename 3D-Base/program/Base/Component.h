
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// コンポーネント
// Actorに取り付けて使う
// 
// 製作者	: amateurK
// 作成日	: 2024/11/16
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#pragma once


namespace AK_Base { class Actor; }

namespace Component {

	/// @brief コンポーネント
	class Component
	{
	public:

		/// @brief コンストラクタ
		Component();
		/// @brief デストラクタ
		virtual ~Component();

		/// @brief このコンポーネントを所有しているActor
		AK_Base::Actor* m_Parent;

		/// @brief コンポーネント作成時に呼び出される関数
		virtual void Setup();

		/// @brief 更新
		/// @param totalTime : アプリケーション起動からの経過時間（秒）
		/// @param elapsedTime : 前回のMove()からの経過時間（秒）
		virtual void Move(const double& totalTime, const float& elapsedTime);

		/// @brief 描画
		/// @param totalTime : アプリケーション起動からの経過時間（秒）
		/// @param elapsedTime : 前回のRender()からの経過時間（秒）
		virtual void Render(const double& totalTime, const float& elapsedTime);
	};

}