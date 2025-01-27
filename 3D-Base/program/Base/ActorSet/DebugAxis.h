#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// デバッグ用のXYZ軸を表示するActor
// 
// 製作者	: amateurK
// 作成日	: 2024/12/10
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../Actor.h"
#include "../Component.h"
#include "../Component/Transform.h"
#include "../Component/MeshRender.h"

namespace ActorSet {
	/// @brief デバッグ用のX軸を表示するActor
	/// @param parent 軸を取り付けるActor
	inline void CreateDebugAxisX(AK_Base::Actor* parent) {

		auto actor = parent->AddChild<AK_Base::Actor>(parent->GetName() + L"_DebugAxisX");
		auto transform = actor->AddComponent<AK_Base::Transform>();
		auto meshRender = actor->AddComponent<AK_Base::MeshRender>(L"Line");
		meshRender->SetShader("BasicRed");
	}

	/// @brief デバッグ用のY軸を表示するActor
	/// @param parent 軸を取り付けるActor
	inline void CreateDebugAxisY(AK_Base::Actor* parent) {

		auto actor = parent->AddChild<AK_Base::Actor>(parent->GetName() + L"_DebugAxisY");
		auto transform = actor->AddComponent<AK_Base::Transform>();
		transform->RotateLocalZ(DirectX::XM_PIDIV2);
		auto meshRender = actor->AddComponent<AK_Base::MeshRender>(L"Line");
		meshRender->SetShader("BasicGreen");
	}

	/// @brief デバッグ用のZ軸を表示するActor
	/// @param parent 軸を取り付けるActor
	inline void CreateDebugAxisZ(AK_Base::Actor* parent) {

		auto actor = parent->AddChild<AK_Base::Actor>(parent->GetName() + L"_DebugAxisZ");
		auto transform = actor->AddComponent<AK_Base::Transform>();
		transform->RotateLocalY(-DirectX::XM_PIDIV2);
		auto meshRender = actor->AddComponent<AK_Base::MeshRender>(L"Line");
		meshRender->SetShader("BasicBlue");
	}

	/// @brief デバッグ用のXYZ軸を表示するActor
	/// @param parent 軸を取り付けるActor
	inline void CreateDebugAxis(AK_Base::Actor* parent) {

		CreateDebugAxisX(parent);
		CreateDebugAxisY(parent);
		CreateDebugAxisZ(parent);
	}



	/// @brief デバッグ用のX軸を表示するActor
	/// @param parent 軸を取り付けるActor
	inline void CreateDebugAxisCubeX(AK_Base::Actor* parent) {

		auto actor = parent->AddChild<AK_Base::Actor>(parent->GetName() + L"_DebugAxisX");
		auto transform = actor->AddComponent<AK_Base::Transform>();
		transform->SetPosition(0.5f, 0.0f, 0.0f);
		transform->SetScele(0.5f, 0.005f, 0.005f);
		auto meshRender = actor->AddComponent<AK_Base::MeshRender>(L"resource/testData/testBox.glb");
		meshRender->SetShader("BasicRed");
	}

	/// @brief デバッグ用のY軸を表示するActor
	/// @param parent 軸を取り付けるActor
	inline void CreateDebugAxisCubeY(AK_Base::Actor* parent) {

		auto actor = parent->AddChild<AK_Base::Actor>(parent->GetName() + L"_DebugAxisY");
		auto transform = actor->AddComponent<AK_Base::Transform>();
		transform->SetPosition(0.0f, 0.5f, 0.0f);
		transform->SetScele(0.005f, 0.5f, 0.005f);
		auto meshRender = actor->AddComponent<AK_Base::MeshRender>(L"resource/testData/testBox.glb");
		meshRender->SetShader("BasicGreen");
	}

	/// @brief デバッグ用のZ軸を表示するActor
	/// @param parent 軸を取り付けるActor
	inline void CreateDebugAxisCubeZ(AK_Base::Actor* parent) {

		auto actor = parent->AddChild<AK_Base::Actor>(parent->GetName() + L"_DebugAxisZ");
		auto transform = actor->AddComponent<AK_Base::Transform>();
		transform->SetPosition(0.0f, 0.0f, 0.5f);
		transform->SetScele(0.005f, 0.005f, 0.5f);
		auto meshRender = actor->AddComponent<AK_Base::MeshRender>(L"resource/testData/testBox.glb");
		meshRender->SetShader("BasicBlue");
	}

	/// @brief デバッグ用のXYZ軸を表示するActor
	/// @param parent 軸を取り付けるActor
	inline void CreateDebugAxisCube(AK_Base::Actor* parent) {

		CreateDebugAxisCubeX(parent);
		CreateDebugAxisCubeY(parent);
		CreateDebugAxisCubeZ(parent);
	}
}