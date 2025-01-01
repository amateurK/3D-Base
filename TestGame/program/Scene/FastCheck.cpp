
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 速度検証用シーン
// 
// 製作者	: amateurK
// 作成日	: 2024/12/13
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "FastCheck.h"
#include "Base/Actor.h"

using namespace DirectX;

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

	void stfunc()
	{
		int a;
		a = 1;
	}

	//--------------------------------------------------------------------------------------
	void FastCheck::Update(const double& totalTime, const float& elapsedTime)
	{
		uint64_t first = 0;
		uint64_t second = 0;
		uint64_t third = 0;

		int testCount = 1000000;
		int loopCount = 1;
		float dummy;
		dummy;

		auto myGame(&AK_Base::BaseWindow::GetInstance());

		std::function<void()> func;

		func = []() {
			int a;
			a = 1;
			};

		for (int cnt = 0; cnt < loopCount; ++cnt) {

			m_StepTimer.Tick([]() {});
			for (int i = 0; i < testCount; ++i) {
				// start First

				int a;
				a = 1;

				// end First
			}
			m_StepTimer.Tick([]() {});
			first += m_StepTimer.GetElapsedTicks();

			m_StepTimer.Tick([]() {});
			for (int i = 0; i < testCount; ++i) {
				// start Second
				func();
				// end Second
			}
			m_StepTimer.Tick([]() {});
			second += m_StepTimer.GetElapsedTicks();

			m_StepTimer.Tick([]() {});
			for (int i = 0; i < testCount; ++i) {
				// start Third
				stfunc();
				// end Third
			}
			m_StepTimer.Tick([]() {});
			third += m_StepTimer.GetElapsedTicks();
		}

		Scene::Update(totalTime, elapsedTime);
	}

}