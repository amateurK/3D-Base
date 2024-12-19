
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 速度検証用シーン
// 
// 製作者	: amateurK
// 作成日	: 2024/12/13
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "FastCheck.h"
#include "Base/Actor.h"

namespace Scene {

	FastCheck::FastCheck(std::wstring name)
		: Scene(name)
	{
		m_StepTimer.SetFixedTimeStep(false);




	}
	//--------------------------------------------------------------------------------------
	FastCheck::~FastCheck()
	{

	}


	//--------------------------------------------------------------------------------------
	void FastCheck::Update(const double& totalTime, const float& elapsedTime)
	{
		uint64_t first = 0;
		uint64_t second = 0;
		uint64_t third = 0;

		int testCount = 1000;
		int loopCount = 1;
		float dummy;

		auto myGame(&AK_Base::BaseWindow::GetInstance());


		for (int cnt = 0; cnt < loopCount; ++cnt) {

			for (int i = 0; i < testCount; ++i) {
				m_StepTimer.Tick([]() {});
				// start First
				this->AddChild<AK_Base::Actor>(L"tester" + i);
				// end First
				m_StepTimer.Tick([]() {});
				first += m_StepTimer.GetElapsedTicks();
			}

			for (int i = 0; i < testCount; ++i) {
				m_StepTimer.Tick([]() {});
				// start Second
				this->SearchName(L"tester" + i);
				// end Second
				m_StepTimer.Tick([]() {});
				second += m_StepTimer.GetElapsedTicks();
			}

			for (int i = 0; i < testCount; ++i) {
				m_StepTimer.Tick([]() {});
				// start Third
				this->GetAliveChildren();
				// end Third
				m_StepTimer.Tick([]() {});
				third += m_StepTimer.GetElapsedTicks();
			}
		}

		Scene::Update(totalTime, elapsedTime);
	}

}