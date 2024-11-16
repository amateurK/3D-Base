#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �t���[�����[�N
// �����ɃA�N�Z�X����΃t���[�����[�N����������悤�ɂȂ�
// 
// �����	: amateurK
// �쐬��	: 2024/11/16
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Actor.h"

/// @brief �t���[�����[�N
/// @param hInstance
/// @param hPrevInstance 
/// @param lpCmdLine 
/// @param nCmdShow 
/// @param sceneFunc Manager������̔C�ӂ̏����������iScene�̐����Ɏg�p��z��j
/// @return �I���R�[�h�i������return���Ă��������j
int FrameworkMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow, _In_ std::function<void(AK_Base::Actor* root)> sceneFunc);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HRESULT CompileShaderFromFile(LPCWSTR, LPCSTR, LPCSTR, ID3DBlob**);