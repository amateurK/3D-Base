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

namespace AK_Base {
	//--------------------------------------------------------------------------------------
	Actor::Actor(
		std::wstring name
	)
		: m_Status(ActorStatus::ACTION)
		, m_ActorName(name)
		, m_Parent(nullptr)
	{
		m_Children.clear();
		m_ComponentList.clear();
	}

	//--------------------------------------------------------------------------------------
	Actor::~Actor()
	{
		for (auto& child : m_Children) {
			delete child;
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
			if (child->m_Status == ActorStatus::ACTION ||
				child->m_Status == ActorStatus::UPDATEONLY) {
				child->Update(totalTime, elapsedTime);
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
			if (child->m_Status == ActorStatus::ACTION ||
				child->m_Status == ActorStatus::RENDERONLY) {
				child->Render(totalTime, elapsedTime);
			}
		}
	}

	//--------------------------------------------------------------------------------------
	void Actor::AddChild(Actor* const actor)
	{
		m_Children.push_back(actor);
		actor->SetParent(this);
	}

	//--------------------------------------------------------------------------------------
	void Actor::CheckStatus()
	{
		// 自分が死んでいたら子をDEAD状態にする
		if (this->m_Status == ActorStatus::DEAD) {
			for (auto child : m_Children) {
				child->m_Status = ActorStatus::DEAD;
			}
		}

		// 子を巡回（再帰処理）
		for (auto& child : m_Children) {
			child->CheckStatus();
		}

		// DEAT状態の子を削除
		// erase()を使うので範囲forはダメ
		for (auto itr = m_Children.begin(); itr != m_Children.end();) {
			if ((*itr)->m_Status == ActorStatus::DEAD) {
				delete* itr;
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
			if (child->m_Status == ActorStatus::ACTION) {
				cnt++;
				cnt += child->GetActionChildren();
			}
		}
		return cnt;
	}

	//--------------------------------------------------------------------------------------
	int Actor::GetAliveChildren() const
	{
		int cnt = 0;
		for (auto& child : m_Children) {
			if (child->m_Status != ActorStatus::DEAD) {
				cnt++;
				cnt += child->GetAliveChildren();
			}
		}
		return cnt;
	}

	//--------------------------------------------------------------------------------------
	void Actor::SearchClass(const type_info& type, std::list<const Actor*>*& list) const
	{
		if (typeid(*this) == type) {
			list->push_back(this);
		}

		for (auto& child : m_Children) {
			child->SearchClass(type, list);
		}

		return;
	}

	//--------------------------------------------------------------------------------------
	const Actor* Actor::SearchName(const std::wstring name) const
	{
		if (this->m_ActorName == name) {
			return this;
		}

		const Actor* target = nullptr;
		for (auto& child : m_Children) {
			target = child->SearchName(name);
			if (target != nullptr)return target;
		}

		return nullptr;
	}

	//--------------------------------------------------------------------------------------
	void Actor::SetStatus(const ActorStatus status)
	{
		m_Status = status;
	}

	//--------------------------------------------------------------------------------------
	void Actor::SetParent(Actor* const actor)
	{
		m_Parent = actor;
	}
}