
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 音の再生・停止・音量調整などを行うクラス
// シングルトンクラス
// 
// 製作者	: amateurK
// 作成日	: 2025/04/19
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "AudioManager.h"


namespace AK_Base {
	AudioManager* AudioManager::Instance = nullptr;

	AudioManager::AudioManager()
		: m_AudioEngine(nullptr)
		, m_MasteringVoice(nullptr)
		, m_BGMVolume(1.0f)
		, m_SEVolume(1.0f)
		, m_TerminateThread(false)
	{
		HRESULT hr = S_OK;

		m_SoundData.clear();
		m_BGMSourceVoices.clear();
		m_SESourceVoices.clear();

		// MediaFoundationの初期化
		hr = MFStartup(MF_VERSION, MFSTARTUP_NOSOCKET);
		if (FAILED(hr)) {
			throw std::exception("MediaFoundationの初期化に失敗");
		}

		// XAudio2エンジンの初期化
		UINT32 flags = 0;
#if defined(_DEBUG)
		flags |= XAUDIO2_DEBUG_ENGINE;
#endif
		hr = XAudio2Create(&m_AudioEngine, 0, flags);
		if (FAILED(hr)) {
			throw std::exception("XAudio2エンジンの作成に失敗");
		}

		// マスターボイスの作成
		hr = m_AudioEngine->CreateMasteringVoice(&m_MasteringVoice);
		if (FAILED(hr)) {
			throw std::exception("マスターボイスの作成に失敗");
		}

		// スレッドの初期化
		m_Thread = std::thread([this]() {

			// ステップタイマーの初期設定
			m_Timer.SetFixedTimeStep(true);
			m_Timer.SetTargetElapsedSeconds(1.0f / 60.0f);

			while (!m_TerminateThread) {
				m_Timer.Tick([this]() {
					// スレッドの処理
					ThreadFunc();
					});

				// 処理が終わったので他のスレッドに処理を渡す
				SwitchToThread();
			}
			});
	}

	//--------------------------------------------------------------------------------------
	AudioManager::~AudioManager()
	{
		// スレッドの終了を待つ
		m_TerminateThread = true;
		if (m_Thread.joinable()) {
			m_Thread.join();
		}

		// 全ての音を停止
		StopBGM();
		StopSE();

		// 読み込んだ音源を全て解放
		for (auto& sound : m_SoundData) {
			CoTaskMemFree(sound.second->WaveFormat);
			delete sound.second;
		}
		m_SoundData.clear();

		// マスターボイスの解放
		if (m_MasteringVoice) {
			m_MasteringVoice->DestroyVoice();
			m_MasteringVoice = nullptr;
		}
		// XAudio2エンジンの解放
		if (m_AudioEngine) {
			m_AudioEngine->Release();
			m_AudioEngine = nullptr;
		}

	}

	//--------------------------------------------------------------------------------------
	HRESULT AudioManager::RoadSoundFile(uint8_t id, const std::wstring& fileName)
	{
		using namespace Microsoft::WRL;	// ComPtr用
		HRESULT hr = S_OK;

		// IDの重複をチェック
		if (m_SoundData.find(id) != m_SoundData.end()) {
			return E_FAIL; // IDが重複している
		}

		// WAVEファイルを開く
		ComPtr<IMFSourceReader> sourceReader;	// 例外時のためにスマートポインタを使用
		hr = MFCreateSourceReaderFromURL(fileName.c_str(), nullptr, sourceReader.ReleaseAndGetAddressOf());
		if (FAILED(hr)) {
			return hr; // ファイルの読み込みに失敗
		}

		// WAVEFORMATEX構造体を取得
		ComPtr<IMFMediaType> mediaType;
		hr = MFCreateMediaType(mediaType.ReleaseAndGetAddressOf());
		if (FAILED(hr)) {
			return hr; // メディアタイプの作成に失敗
		}
		mediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
		mediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);
		sourceReader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, mediaType.Get());

		sourceReader->GetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, mediaType.GetAddressOf());

		WAVEFORMATEX* waveFormat = nullptr;
		MFCreateWaveFormatExFromMFMediaType(mediaType.Get(), &waveFormat, nullptr);


		// データの読み込み
		std::vector<BYTE> mediaData;
		// 読み込み終わるまでループ
		for (;;) {
			ComPtr<IMFSample> sample;
			DWORD dwStreamFlags;
			hr = sourceReader->ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM,
				0, nullptr, &dwStreamFlags, nullptr, sample.ReleaseAndGetAddressOf());
			if (FAILED(hr)) {
				return E_FAIL; // サンプルの読み込みに失敗
			}

			if (dwStreamFlags & MF_SOURCE_READERF_ENDOFSTREAM)
			{
				break;
			}

			if (sample == nullptr) {
				continue; // サンプルが取得できなかった
			}

			IMFMediaBuffer* mediaBuffer = nullptr;
			sample->ConvertToContiguousBuffer(&mediaBuffer);

			BYTE* buffer = nullptr;
			DWORD currentLength = 0;
			// バッファをロック
			mediaBuffer->Lock(&buffer, nullptr, &currentLength);
			// データを追加
			mediaData.insert(mediaData.end(), buffer, buffer + currentLength);
			// バッファのロックを解除
			mediaBuffer->Unlock();
		}

		// データを登録
		SoundData* soundData = new SoundData;
		soundData->WaveFormat = waveFormat;
		soundData->MediaData = std::move(mediaData);
		m_SoundData[id] = soundData;

		return S_OK;
	}

	//--------------------------------------------------------------------------------------
	IXAudio2SourceVoice* AudioManager::PlaySE(uint8_t id)
	{
		IXAudio2SourceVoice* sourceVoice;

		// SEを再生
		sourceVoice = CreateSourceVoiceAndPlay(id, m_SEVolume, false);
		if (sourceVoice == nullptr) {
			return nullptr; // 再生に失敗
		}

		// 再生中のSEのリストに追加
		m_SESourceVoices.insert(sourceVoice);

		return sourceVoice;

	}

	//--------------------------------------------------------------------------------------
	void AudioManager::StopSE(IXAudio2SourceVoice* sourceVoice)
	{
		if (sourceVoice == nullptr) {
			// 全てのSEを停止
			for (auto& voice : m_SESourceVoices) {
				voice->Stop(0);
				voice->DestroyVoice();
			}
			m_SESourceVoices.clear();
		}
		else {
			// 指定したSEを停止
			sourceVoice->Stop(0);
			sourceVoice->DestroyVoice();
			m_SESourceVoices.erase(sourceVoice);
		}

	}

	//--------------------------------------------------------------------------------------
	IXAudio2SourceVoice* AudioManager::ChangeBGM(uint8_t id)
	{
		IXAudio2SourceVoice* sourceVoice;

		// SEを再生
		sourceVoice = CreateSourceVoiceAndPlay(id, m_BGMVolume, true);
		if (sourceVoice == nullptr) {
			return nullptr; // 再生に失敗
		}

		// 現在流れているBGMを停止
		StopBGM();

		// 再生中のBGMのリストに追加
		m_BGMSourceVoices.insert(sourceVoice);

		return sourceVoice;
	}

	//--------------------------------------------------------------------------------------
	IXAudio2SourceVoice* AudioManager::AddBGM(uint8_t id)
	{
		IXAudio2SourceVoice* sourceVoice;

		// SEを再生
		sourceVoice = CreateSourceVoiceAndPlay(id, m_BGMVolume, true);
		if (sourceVoice == nullptr) {
			return nullptr; // 再生に失敗
		}

		// 再生中のBGMのリストに追加
		m_BGMSourceVoices.insert(sourceVoice);

		return sourceVoice;
	}

	//--------------------------------------------------------------------------------------
	void AudioManager::StopBGM(IXAudio2SourceVoice* sourceVoice)
	{
		if (sourceVoice == nullptr) {
			// 全てのSEを停止
			for (auto& voice : m_BGMSourceVoices) {
				voice->Stop(0);
				voice->DestroyVoice();
			}
			m_BGMSourceVoices.clear();
		}
		else {
			// 指定したSEを停止
			sourceVoice->Stop(0);
			sourceVoice->DestroyVoice();
			m_BGMSourceVoices.erase(sourceVoice);
		}
	}

	//--------------------------------------------------------------------------------------
	void AudioManager::SetMasterVolume(float volume)
	{
		LimitVolume(volume);

		m_MasteringVoice->SetVolume(volume);
	}

	//--------------------------------------------------------------------------------------
	void AudioManager::SetBGMVolume(float volume)
	{
		LimitVolume(volume);

		// 再生中のBGMの音量を変更
		for (auto& voice : m_BGMSourceVoices) {
			voice->SetVolume(volume);
		}
		m_BGMVolume = volume;
	}

	//--------------------------------------------------------------------------------------
	void AudioManager::SetSEVolume(float volume)
	{
		LimitVolume(volume);

		// 再生中のSEの音量を変更
		for (auto& voice : m_SESourceVoices) {
			voice->SetVolume(volume);
		}
		m_SEVolume = volume;
	}

	//--------------------------------------------------------------------------------------
	void AudioManager::ThreadFunc()
	{
		// 再生が終わったソースボイスを削除
		for (auto itr = m_SESourceVoices.begin(); itr != m_SESourceVoices.end();) {
			XAUDIO2_VOICE_STATE state;
			(*itr)->GetState(&state);
			if (state.BuffersQueued <= 0) {
				(*itr)->DestroyVoice();
				itr = m_SESourceVoices.erase(itr);
			}
			else {
				++itr;
			}
		}
	}

	//--------------------------------------------------------------------------------------
	IXAudio2SourceVoice* AudioManager::CreateSourceVoiceAndPlay(uint8_t id, float volume, bool isLoop)
	{

		HRESULT hr;

		// IDが登録されているかチェック
		auto itr = m_SoundData.find(id);
		if (itr == m_SoundData.end()) {
			return nullptr; // IDが登録されていない
		}
		// 音源データを取得
		SoundData* soundData = itr->second;

		// ソースボイスの作成
		IXAudio2SourceVoice* sourceVoice = nullptr;
		hr = m_AudioEngine->CreateSourceVoice(&sourceVoice, soundData->WaveFormat);
		if (FAILED(hr)) {
			return nullptr; // ソースボイスの作成に失敗
		}

		// 音量を設定
		sourceVoice->SetVolume(volume);
		// 音源データを設定
		XAUDIO2_BUFFER buffer = { 0 };
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.AudioBytes = static_cast<UINT32>(soundData->MediaData.size());
		buffer.pAudioData = soundData->MediaData.data();
		if (isLoop) {
			buffer.LoopCount = XAUDIO2_LOOP_INFINITE; // 無限ループ
		}
		// 再生
		hr = sourceVoice->SubmitSourceBuffer(&buffer);
		if (FAILED(hr)) {
			sourceVoice->DestroyVoice();
			return nullptr; // 音源データの設定に失敗
		}
		hr = sourceVoice->Start(0);
		if (FAILED(hr)) {
			sourceVoice->DestroyVoice();
			return nullptr; // 再生に失敗
		}

		return sourceVoice;
	}

	//--------------------------------------------------------------------------------------
	void AudioManager::LimitVolume(float& volume) const
	{
		if (volume > XAUDIO2_MAX_VOLUME_LEVEL)
			volume = XAUDIO2_MAX_VOLUME_LEVEL;
		else if (volume < -XAUDIO2_MAX_VOLUME_LEVEL)
			volume = -XAUDIO2_MAX_VOLUME_LEVEL;
	}
}