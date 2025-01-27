
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ���b�V���f�[�^���Ǘ�����}�l�[�W���[�N���X
// �V���O���g���N���X
// 
// �����	: amateurK
// �쐬��	: 2024/07/29
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "MeshManager.h"
#include "../../BaseWindow.h"
#include "VRMMesh.h"
#include "LineMesh.h"

namespace Mesh {

	MeshManager* MeshManager::Instance = nullptr;

	MeshManager::MeshManager()
	{
		m_MeshList.clear();
	}

	//--------------------------------------------------------------------------------------
	MeshManager::~MeshManager()
	{
		DestroyAllMesh();
	}

	//--------------------------------------------------------------------------------------
	HRESULT MeshManager::CreateMesh(std::wstring& fileName, Mesh*& mesh)
	{
		// ���b�V�����쐬�ς݂����`�F�b�N
		auto itr = m_MeshList.find(fileName);
		if (itr != m_MeshList.end()) {
			// �쐬�ς�
			mesh = itr->second;
			return S_OK;
		}
		
		// ���b�V��������Ă��Ȃ��̂ŏ���
		mesh = nullptr;
		AK_Base::BaseWindow& bw(AK_Base::BaseWindow::GetInstance());
		ID3D11Device* d3dDevice = bw.GetD3DDevice();
		ID3D11DeviceContext* d3dDeviceContext = bw.GetImmediateContext();
		HRESULT hr = S_OK;

		// �g���q�ʂɃ��b�V����V�K�쐬
		Mesh* newMesh = nullptr;
		auto extension = Tools::GetFileExtension(fileName);
		extension = Tools::ToLowercase(extension);
		if(extension == L"vrm" || extension == L"glb") {
			newMesh = new VRMMesh();
		}
		else {
			if (fileName == L"Line") {
				newMesh = new LineMesh();
			}
			else {
				throw std::exception("�g���q���s���ł��B");
				return S_FALSE;
			}
		}

		hr = newMesh->CreateMesh(d3dDevice, d3dDeviceContext, fileName);
		if (FAILED(hr)) {
			throw std::exception("���b�V���̍쐬�Ɏ��s�B");
			return hr;
		}

		// ���X�g�ɓo�^
		m_MeshList[fileName] = newMesh;

		mesh = newMesh;
		return S_OK;
	}

	//--------------------------------------------------------------------------------------
	void MeshManager::DestroyMesh(std::wstring& fileName)
	{
		auto itr = m_MeshList.find(fileName);
		if (itr != m_MeshList.end()) {
			delete itr->second;
			itr->second = nullptr;
		}
	}

	//--------------------------------------------------------------------------------------
	void MeshManager::DestroyAllMesh()
	{
		auto itr = m_MeshList.begin();
		while (itr != m_MeshList.end()) {
			delete itr->second;
			itr->second = nullptr;
			itr = m_MeshList.erase(itr);
		}
	}
}