//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ゲーム内の全てのオブジェクトが継承するクラス
// オブジェクトを木構造で処理するためのもの
// 
// 製作者	: amateurK
// 作成日	: 2024/03/21
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Actor.h"
#include "Component.h"
#include "Component/Transform.h"

namespace AK_Base {
	//--------------------------------------------------------------------------------------
	Actor::Actor(
		std::wstring name
	)
		: m_Status(ActorStatus::ACTION)
		, m_ActorName(name)
		, m_Parent(nullptr)
		, m_Transform(nullptr)
	{
		m_Children.clear();
		m_ComponentList.clear();
	}

	//--------------------------------------------------------------------------------------
	Actor::~Actor()
	{
		for (auto& child : m_Children) {
			delete child.second;
		}
		m_Children.clear();
		for (auto& component : m_ComponentList) {
			delete component.second;
		}
		m_ComponentList.clear();
	}

	//--------------------------------------------------------------------------------------
	void Actor::Update(const double& totalTime, const float& elapsedTime)
	{
		for (auto& component : m_ComponentList) {
			component.second->Update(totalTime, elapsedTime);
		}
		for (auto& child : m_Children) {
			if (child.second->m_Status == ActorStatus::ACTION ||
				child.second->m_Status == ActorStatus::UPDATEONLY) {
				child.second->Update(totalTime, elapsedTime);
			}
		}
	}

	//--------------------------------------------------------------------------------------
	void Actor::Render(const double& totalTime, const float& elapsedTime)
	{
		for (auto& component : m_ComponentList) {
			component.second->Render(totalTime, elapsedTime);
		}
		for (auto& child : m_Children) {
			if (child.second->m_Status == ActorStatus::ACTION ||
				child.second->m_Status == ActorStatus::RENDERONLY) {
				child.second->Render(totalTime, elapsedTime);
			}
		}
	}

	//--------------------------------------------------------------------------------------
	void Actor::AddChild(Actor* const actor)
	{
		m_Children[actor->GetName()] = actor;
		actor->SetParent(this);
	}

	//--------------------------------------------------------------------------------------
	void Actor::CheckStatus()
	{
		// 自分が死んでいたら子をDEAD状態にする
		if (this->m_Status == ActorStatus::DEAD) {
			for (auto child : m_Children) {
				child.second->m_Status = ActorStatus::DEAD;
			}
		}

		// 子を巡回（再帰処理）
		for (auto& child : m_Children) {
			child.second->CheckStatus();
		}

		// DEAT状態の子を削除
		// erase()を使うので範囲forはダメ
		for (auto itr = m_Children.begin(); itr != m_Children.end();) {
			if ((*itr).second->m_Status == ActorStatus::DEAD) {
				delete itr->second;
				itr = m_Children.erase(itr);
			}
			else {
				itr++;
			}
		}
	}

	//--------------------------------------------------------------------------------------
	int Actor::GetActionChildren() const
	{
		int cnt = 0;
		for (auto& child : m_Children) {
			if (child.second->m_Status == ActorStatus::ACTION) {
				cnt++;
				cnt += child.second->GetActionChildren();
			}
		}
		return cnt;
	}

	//--------------------------------------------------------------------------------------
	int Actor::GetAliveChildren() const
	{
		int cnt = 0;
		for (auto& child : m_Children) {
			if (child.second->m_Status != ActorStatus::DEAD) {
				cnt++;
				cnt += child.second->GetAliveChildren();
			}
		}
		return cnt;
	}

	//--------------------------------------------------------------------------------------
	void Actor::SearchChildByClass(const type_info& type, std::list<Actor*>*& list)
	{
		if (typeid(*this) == type) {
			list->push_back(this);
		}

		for (auto& child : m_Children) {
			child.second->SearchChildByClass(type, list);
		}

		return;
	}

	//--------------------------------------------------------------------------------------
	Actor* Actor::SearchChildByName(const std::wstring& name)
	{
		if (this->m_ActorName == name) {
			return this;
		}

		Actor* target = nullptr;
		for (auto& child : m_Children) {
			target = child.second->SearchChildByName(name);
			if (target != nullptr)return target;
		}

		return nullptr;
	}

	//--------------------------------------------------------------------------------------
	void Actor::SetStatus(const ActorStatus& status)
	{
		m_Status = status;
	}

	//--------------------------------------------------------------------------------------
	void Actor::SetParent(Actor* const actor)
	{
		m_Parent = actor;
	}
}