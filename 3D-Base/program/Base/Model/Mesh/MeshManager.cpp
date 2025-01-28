
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// メッシュデータを管理するマネージャークラス
// シングルトンクラス
// 
// 製作者	: amateurK
// 作成日	: 2024/07/29
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
		// メッシュが作成済みかをチェック
		auto itr = m_MeshList.find(fileName);
		if (itr != m_MeshList.end()) {
			// 作成済み
			mesh = itr->second;
			return S_OK;
		}
		
		// メッシュが作られていないので準備
		mesh = nullptr;
		AK_Base::BaseWindow& bw(AK_Base::BaseWindow::GetInstance());
		ID3D11Device* d3dDevice = bw.GetD3DDevice();
		ID3D11DeviceContext* d3dDeviceContext = bw.GetImmediateContext();
		HRESULT hr = S_OK;

		// 拡張子別にメッシュを新規作成
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
				throw std::exception("拡張子が不明です。");
				return S_FALSE;
			}
		}

		hr = newMesh->CreateMesh(d3dDevice, d3dDeviceContext, fileName);
		if (FAILED(hr)) {
			throw std::exception("メッシュの作成に失敗。");
			return hr;
		}

		// リストに登録
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