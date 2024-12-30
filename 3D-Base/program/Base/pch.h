#pragma once
// �v���R���p�C���ς݃w�b�_�[
// �S�Ẵw�b�_�[�t�@�C����cpp�t�@�C����include����
// VisualStudio�̃v���W�F�N�g > �v���p�e�B > C/C++ > �ڍאݒ� > �K���g�p�����C���N���[�h�t�@�C��
// �ɓ���Ă������ƂŁA�����include���Ă����i�v���O�����ɂ����Ȃ��Ă����j

// �Z�b�g�ɂȂ��Ă���pch.cpp��pch.h��ǂݍ��ނ����̎d��
// �v���p�e�B > C/C++ > �v���R���p�C���ς݃w�b�_�[ ����ݒ肷��
// pch.cpp�ɃR�����g�������ƂȂ���warning���o��

// �ꕔC++20�̋@�\���g���Ă���B�iconstruct_at�Ȃǁj
// �v���p�e�B > C/C++ > ���� > C++ ����W�� ����ݒ肷��
// ISO C++ 20 �W�� (/std:c++20) �ɃZ�b�g


// �����J�[�ɓn���ǉ����C�u����
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "xinput.lib")
#pragma comment(lib, "xaudio2.lib")
#pragma comment(lib, "Mf.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "Mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")
#pragma comment(lib, "dinput8.lib" )
#pragma comment(lib, "dxguid.lib" )


// �C���N���[�h�����ς�
#include <Windows.h>
#include <d3d11_2.h>		// Direct3D�̌^�E�N���X�E�֐��Ȃ�
#include <d3dcompiler.h>	// ����
#include <DirectXColors.h>	// DirectX�F�֘A
#include <DirectXMath.h>	// DirectX���w���C�u����
//#include <DirectXTex.h>		// DirectX�e�N�X�`�����C�u�����i�폜�ς݁j
#include <wrl/client.h>		// ComPtr�p
#include <xinput.h>			// ���͗p
#include <dxgidebug.h>		// �f�o�b�O�p�i��Ƀ��������[�N�Ď��j
#include <xaudio2.h>		// ���̏o��
#include <mfapi.h>			// Media Foundation�֘A
#include <mfidl.h>
#include <mfreadwrite.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>			// DirectInput�֘A



// �����̍���DirectX�̃}�N�� ������
#undef max
#undef min

// ���include
#include <algorithm>
#include <any>
#include <atomic>
#include <climits>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <iomanip>
#include <list>
#include <math.h>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <thread>
#include <typeindex>
#include <typeinfo>
#include <type_traits>
#include <utility>
#include <unordered_map>
#include <vector>


using namespace DirectX;

// �؂蕨
#include "Reader/ReadData.h"	// �R���p�C���σV�F�[�_�[�̓ǂݍ���


// �c�[����
#include "Tools/WStringToString.h"
#include "Tools/FilePath.h"
#include "Tools/LowercaseAndUppercase.h"

#include "Framework.h"




// 12Byte�̃��������[�N�𔭐�������iDebug�̎��ȊO�͎g�p�֎~�j
/*
#ifdef _DEBUG
	int* leakCheck = new int[3];
	leakCheck[0] = 1;
	leakCheck[1] = 2;
	leakCheck[2] = 3;
#endif
*/