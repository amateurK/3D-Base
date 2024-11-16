#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// フレームワーク
// ここにアクセスすればフレームワークが動かせるようになる
// 
// 製作者	: amateurK
// 作成日	: 2024/11/16
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Actor.h"

/// @brief フレームワーク
/// @param hInstance
/// @param hPrevInstance 
/// @param lpCmdLine 
/// @param nCmdShow 
/// @param sceneFunc Manager生成後の任意の初期化処理（Sceneの生成に使用を想定）
/// @return 終了コード（即座にreturnしてください）
int FrameworkMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow, _In_ std::function<void(AK_Base::Actor* root)> sceneFunc);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HRESULT CompileShaderFromFile(LPCWSTR, LPCSTR, LPCSTR, ID3DBlob**);