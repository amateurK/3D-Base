#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �V���O���g�����N���X
// public�p�����邱�ƂŃV���O���g�����ł���
// BaseWindow�N���X��p
// 
// �����	: amateurK
// �쐬��	: 2024/02/29
// 2D-Base����ڐA�����̂Ō��̍쐬���͕s��
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace AK_Base
{
	template<class T> class Singleton
	{
	private:
		// �C���X�^���X��ێ����Ă����ϐ�
		// unique_ptr<T>���ƃ_���H
		static T* SingletonObj;

	protected:
		// �f�t�H���g�R���X�g���N�^
		// 2��ڈȍ~�͗�O���o��
		// �������e�N���X�Ƃ��Ĉ����Ă�C���[�W
		explicit Singleton() {
			if (SingletonObj != nullptr) {
				throw std::exception("This class is a singleton.");
			}
			SingletonObj = reinterpret_cast<T*>(this);
		};

		virtual ~Singleton() {
			SingletonObj = nullptr;
		}

		// ������j�~
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;
		Singleton(Singleton&&) = delete;
		Singleton& operator=(Singleton&&) = delete;

	public:
		/// @brief �C���X�^���X���擾
		/// @return �C���X�^���X�i�쐬����ĂȂ��ꍇ��nullptr�j
		static inline T& GetInstance() {
			//if (SingletonObj == nullptr) {
			//	MessageBox(nullptr, L"FAILED : Singleton::GetInstance()\nNo instance created", L"Error", MB_OK);
			//}
			return *SingletonObj;
		}

	};

	template<class T> T* Singleton<T>::SingletonObj = nullptr;
};
