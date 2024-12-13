
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 速度検証用シーン
// 
// 製作者	: amateurK
// 作成日	: 2024/12/13
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "FastCheck.h"

namespace Scene {

	FastCheck::FastCheck()
		: Scene()
	{
		m_StepTimer.SetFixedTimeStep(false);




	}
	//--------------------------------------------------------------------------------------
	FastCheck::~FastCheck()
	{

	}

	//--------------------------------------------------------------------------------------
	float FastSqrt(float x) {
		// ニュートン法を1回適用 (1回の反復でかなりの精度を得られる)
		float half = 0.5f * x;
		int i = *(int*)&x;              // 浮動小数点を整数型に再解釈
		i = 0x5f3759df - (i >> 1);      // 初期近似
		x = *(float*)&i;                // 再解釈して浮動小数点に戻す
		x = x * (1.5f - half * x * x);  // ニュートン法
		return 1.0f / x;                // 平方根の逆数を返す
	}
	float dummyFunc(float x) { return x; }

	//--------------------------------------------------------------------------------------
	void FastCheck::Update(const double& totalTime, const float& elapsedTime)
	{
		uint64_t first = 0;
		uint64_t second = 0;
		uint64_t third = 0;

		int testCount = 10000;
		int loopCount = 1;
		float dummy;

		for (int cnt = 0; cnt < loopCount; ++cnt) {

			m_StepTimer.Tick([]() {});
			for (int i = 0; i < testCount; ++i) {
				dummy = sqrtf((float)i);
			}
			m_StepTimer.Tick([]() {});
			first += m_StepTimer.GetElapsedTicks();

			m_StepTimer.Tick([]() {});
			for (int i = 0; i < testCount; ++i) {
				dummy = cos((float)i);
			}
			m_StepTimer.Tick([]() {});
			second += m_StepTimer.GetElapsedTicks();

			m_StepTimer.Tick([]() {});
			for (int i = 0; i < testCount; ++i) {
				dummy = dummyFunc((float)i);
			}
			m_StepTimer.Tick([]() {});
			third += m_StepTimer.GetElapsedTicks();
		}

		Scene::Update(totalTime, elapsedTime);
	}

}