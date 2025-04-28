#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 音の再生・停止・音量調整などを行うクラス
// シングルトンクラス
// 
// 製作者	: amateurK
// 作成日	: 2025/04/19
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../Tools/StepTimer.h"

namespace AK_Base {

	/// @brief 音の再生・停止・音量調整などを行うクラス
	class AudioManager
	{
	private:
		/// @brief コンストラクタ
		AudioManager();
		/// @brief デストラクタ
		~AudioManager();

		static AudioManager* Instance;
	public:
		AudioManager(AudioManager&&) = delete;
		AudioManager& operator=(AudioManager&&) = delete;

		AudioManager(AudioManager const&) = delete;
		AudioManager& operator=(AudioManager const&) = delete;

		/// @brief このクラスのインスタンスを取得
		/// @return インスタンス
		static AudioManager* GetInstance() {
			return Instance;
		}
		/// @brief インスタンスを生成
		static void Create() {
			if (Instance == nullptr) {
				Instance = new AudioManager;
			}
			else {
				throw std::exception("AudioManager is a singleton");
			}
		}
		/// @brief インスタンスの解放
		static void Destroy() {
			delete Instance;
			Instance = nullptr;
		}

	private:

		// ソースボイスを作るのに必要なもの
		struct SoundData {
			WAVEFORMATEX* WaveFormat;
			std::vector<BYTE> MediaData;
		};

		/// @brief XAudio2エンジン
		IXAudio2* m_AudioEngine;
		/// @brief マスターボイス
		IXAudio2MasteringVoice* m_MasteringVoice;

		/// @brief 音源データのリスト
		std::unordered_map<uint8_t, SoundData*> m_SoundData;

		/// @brief 再生中のBGMのリスト
		std::unordered_set<IXAudio2SourceVoice*> m_BGMSourceVoices;
		/// @brief 再生中のSEのリスト
		std::unordered_set<IXAudio2SourceVoice*> m_SESourceVoices;
		//std::list<IXAudio2SubmixVoice*> m_SubmixVoices;

		/// @brief 再生中のソースボイスの音量のリスト
		std::unordered_map<IXAudio2SourceVoice*, float> m_SourceVoiceVolume;

		/// @brief 音用スレッド
		std::thread m_Thread;
		/// @brief 音用スレッドを終了する際にtrueにするフラグ
		std::atomic<bool> m_TerminateThread;
		/// @brief 音用スレッドの処理用タイマー
		DX::StepTimer m_Timer;

		/// @brief BGMの音量
		float m_BGMVolume;
		/// @brief SEの音量
		float m_SEVolume;

	public:
		/// @brief 音楽ファイルを読み込み
		/// @param id 登録するID
		/// @param fileName ファイルへのパス
		/// @return IDが重複しているか、読み込み失敗するとFAILED
		HRESULT RoadSoundFile(uint8_t id, const std::wstring& fileName);

		/// @brief SEを再生
		/// @param id 音源のID
		/// @param volume 音量
		/// @return 再生されたソースボイスへのポインタ
		IXAudio2SourceVoice* PlaySE(uint8_t id, float volume = 1.0f);
		/// @brief SEの再生を停止
		/// @param sourceVoice 停止するソースボイスへのポインタ、nullptrの場合は全て停止
		void StopSE(IXAudio2SourceVoice* sourceVoice = nullptr);

		/// @brief BGMを再生（現在流れているBGMを停止）
		/// @param id 音源のID
		/// @return 再生されたソースボイスへのポインタ
		IXAudio2SourceVoice* ChangeBGM(uint8_t id, float volume = 1.0f);
		/// @brief BGMを再生（現在流れているBGMはそのまま）
		/// @param id 音源のID
		/// @return 再生されたソースボイスへのポインタ
		IXAudio2SourceVoice* AddBGM(uint8_t id, float volume = 1.0f);
		/// @brief BGMの再生を停止
		/// @param sourceVoice 停止するソースボイスへのポインタ、nullptrの場合は全て停止
		void StopBGM(IXAudio2SourceVoice* sourceVoice = nullptr);
		
		/// @brief 全体の音量をセット
		/// @param volume 音量
		void SetMasterVolume(float volume);
		/// @brief BGMの音量をセット
		/// @param volume 音量
		void SetBGMVolume(float volume);
		/// @brief SEの音量をセット
		/// @param volume 音量
		void SetSEVolume(float volume);

	private:
		/// @brief 音用スレッドの処理
		void ThreadFunc();

		/// @brief ソースボイスを作成し、再生する
		/// @param id 音源のID
		/// @param volume 音量
		/// @param Loop ループさせるか
		/// @return 再生されたソースボイスへのポインタ
		IXAudio2SourceVoice* CreateSourceVoiceAndPlay(uint8_t id, float volume, bool isLoop = false);

		/// @brief 音量が限界値を越えていた場合に制限
		/// @param volume 音量
		void LimitVolume(float& volume) const;
	};
}
