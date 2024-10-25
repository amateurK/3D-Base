#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// シングルトン基底クラス
// public継承することでシングルトン化できる
// BaseWindowクラス専用
// 
// 製作者	: amateurK
// 作成日	: 2024/02/29
// 2D-Baseから移植したので元の作成日は不明
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace AK_Base
{
	template<class T> class Singleton
	{
	private:
		// インスタンスを保持しておく変数
		// unique_ptr<T>だとダメ？
		static T* SingletonObj;

	protected:
		// デフォルトコンストラクタ
		// 2回目以降は例外が出る
		// 無理やり親クラスとして扱ってるイメージ
		explicit Singleton() {
			if (SingletonObj != nullptr) {
				throw std::exception("This class is a singleton.");
			}
			SingletonObj = reinterpret_cast<T*>(this);
		};

		virtual ~Singleton() {
			SingletonObj = nullptr;
		}

		// 複製を阻止
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;
		Singleton(Singleton&&) = delete;
		Singleton& operator=(Singleton&&) = delete;

	public:
		/// @brief インスタンスを取得
		/// @return インスタンス（作成されてない場合はnullptr）
		static inline T& GetInstance() {
			//if (SingletonObj == nullptr) {
			//	MessageBox(nullptr, L"FAILED : Singleton::GetInstance()\nNo instance created", L"Error", MB_OK);
			//}
			return *SingletonObj;
		}

	};

	template<class T> T* Singleton<T>::SingletonObj = nullptr;
};
