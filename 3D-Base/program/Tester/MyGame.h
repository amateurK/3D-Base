#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// テスト用
// ゲーム本体
// BaseWindowを継承
// 
// 製作者	: amateurK
// 作成日	: 2024/03/06
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Base/BaseWindow.h"
#include "Base/Shader/Shader.h"

class MyGame :public AK_Base::BaseWindow
{
private:
	// TODO : シェーダー管理クラスを作ったほうが良いかも
	std::unique_ptr<Shader::Shader> m_TestShader;

public:
	MyGame();
	virtual ~MyGame();

	/// @brief 子アクターを作成する
	/// @details デバイス作成後に子アクターの処理を行うため
	virtual void CreateActor() override;

	/// @brief Shaderへのポインタを返す
	/// @return ポインタ
	inline Shader::Shader* const GetTestShader()
	{
		return m_TestShader.get();
	}
};