
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
		// ���b�V����T��
		auto itr = m_MeshList.begin();
		while (itr != m_MeshList.end()) {
			// �ʒu
			if (fileName == itr->Name) {
				mesh = itr->Mesh;
				return S_OK;
			}
			itr++;
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
		if(extension == L"vrm"){
			newMesh = new VRMMesh();
		}
		else {
			throw std::exception("�g���q���s���ł��B");
			return S_FALSE;
		}

		hr = newMesh->CreateMesh(d3dDevice, d3dDeviceContext, fileName);
		if (FAILED(hr)) {
			throw std::exception("���b�V���̍쐬�Ɏ��s�B");
			return hr;
		}

		// ���X�g�ɓo�^
		MeshData data;
		data.Name = fileName;
		data.Mesh = newMesh;
		m_MeshList.push_back(data);

		mesh = newMesh;
		return S_OK;
	}

	//--------------------------------------------------------------------------------------
	void MeshManager::DestroyMesh(std::wstring& fileName)
	{
		auto itr = m_MeshList.begin();
		while (itr != m_MeshList.end()) {
			if (fileName == itr->Name) {
				delete itr->Mesh;
				itr->Mesh = nullptr;
				itr = m_MeshList.erase(itr);
			}
			else {
				itr++;
			}
		}
	}

	//--------------------------------------------------------------------------------------
	void MeshManager::DestroyAllMesh()
	{
		auto itr = m_MeshList.begin();
		while (itr != m_MeshList.end()) {
			delete itr->Mesh;
			itr->Mesh = nullptr;
			itr = m_MeshList.erase(itr);
		}
	}
}