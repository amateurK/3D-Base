
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ���x���ؗp�V�[��
// 
// �����	: amateurK
// �쐬��	: 2024/12/13
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
		// �j���[�g���@��1��K�p (1��̔����ł��Ȃ�̐��x�𓾂���)
		float half = 0.5f * x;
		int i = *(int*)&x;              // ���������_�𐮐��^�ɍĉ���
		i = 0x5f3759df - (i >> 1);      // �����ߎ�
		x = *(float*)&i;                // �ĉ��߂��ĕ��������_�ɖ߂�
		x = x * (1.5f - half * x * x);  // �j���[�g���@
		return 1.0f / x;                // �������̋t����Ԃ�
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