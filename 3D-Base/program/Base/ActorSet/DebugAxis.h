#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �f�o�b�O�p��XYZ����\������Actor
// 
// �����	: amateurK
// �쐬��	: 2024/12/10
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../Actor.h"
#include "../Component.h"
#include "../Component/Transform.h"
#include "../Component/MeshRender.h"

namespace ActorSet {
	/// @brief �f�o�b�O�p��X����\������Actor
	/// @param parent �������t����Actor
	void CreateDebugAxisX(AK_Base::Actor* parent) {

		auto actor = parent->AddChild<AK_Base::Actor>(parent->GetName() + L"_DebugAxisX");
		auto transform = actor->AddComponent<AK_Base::Transform>();
		transform->SetPosition(0.5f, 0.0f, 0.0f);
		transform->SetScele(0.5f, 0.005f, 0.005f);
		auto meshRender = actor->AddComponent<AK_Base::MeshRender>(L"resource/testData/testBox.glb");
		meshRender->SetShader("BasicShader");
	}

	/// @brief �f�o�b�O�p��Y����\������Actor
	/// @param parent �������t����Actor
	void CreateDebugAxisY(AK_Base::Actor* parent) {

		auto actor = parent->AddChild<AK_Base::Actor>(parent->GetName() + L"_DebugAxisY");
		auto transform = actor->AddComponent<AK_Base::Transform>();
		transform->SetPosition(0.0f, 0.5f, 0.0f);
		transform->SetScele(0.005f, 0.5f, 0.005f);
		auto meshRender = actor->AddComponent<AK_Base::MeshRender>(L"resource/testData/testBox.glb");
		meshRender->SetShader("BasicShader");
	}

	/// @brief �f�o�b�O�p��Z����\������Actor
	/// @param parent �������t����Actor
	void CreateDebugAxisZ(AK_Base::Actor* parent) {

		auto actor = parent->AddChild<AK_Base::Actor>(parent->GetName() + L"_DebugAxisZ");
		auto transform = actor->AddComponent<AK_Base::Transform>();
		transform->SetPosition(0.0f, 0.0f, 0.5f);
		transform->SetScele(0.005f, 0.005f, 0.5f);
		auto meshRender = actor->AddComponent<AK_Base::MeshRender>(L"resource/testData/testBox.glb");
		meshRender->SetShader("BasicShader");
	}

	/// @brief �f�o�b�O�p��XYZ����\������Actor
	/// @param parent �������t����Actor
	void CreateDebugAxis(AK_Base::Actor* parent) {

		CreateDebugAxisX(parent);
		CreateDebugAxisY(parent);
		CreateDebugAxisZ(parent);
	}
}