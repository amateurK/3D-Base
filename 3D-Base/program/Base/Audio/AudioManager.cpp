
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ���̍Đ��E��~�E���ʒ����Ȃǂ��s���N���X
// �V���O���g���N���X
// 
// �����	: amateurK
// �쐬��	: 2025/04/19
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

		// MediaFoundation�̏�����
		hr = MFStartup(MF_VERSION, MFSTARTUP_NOSOCKET);
		if (FAILED(hr)) {
			throw std::exception("MediaFoundation�̏������Ɏ��s");
		}

		// XAudio2�G���W���̏�����
		UINT32 flags = 0;
#if defined(_DEBUG)
		flags |= XAUDIO2_DEBUG_ENGINE;
#endif
		hr = XAudio2Create(&m_AudioEngine, 0, flags);
		if (FAILED(hr)) {
			throw std::exception("XAudio2�G���W���̍쐬�Ɏ��s");
		}

		// �}�X�^�[�{�C�X�̍쐬
		hr = m_AudioEngine->CreateMasteringVoice(&m_MasteringVoice);
		if (FAILED(hr)) {
			throw std::exception("�}�X�^�[�{�C�X�̍쐬�Ɏ��s");
		}

		// �X���b�h�̏�����
		m_Thread = std::thread([this]() {

			// �X�e�b�v�^�C�}�[�̏����ݒ�
			m_Timer.SetFixedTimeStep(true);
			m_Timer.SetTargetElapsedSeconds(1.0f / 60.0f);

			while (!m_TerminateThread) {
				m_Timer.Tick([this]() {
					// �X���b�h�̏���
					ThreadFunc();
					});

				// �������I������̂ő��̃X���b�h�ɏ�����n��
				SwitchToThread();
			}
			});
	}

	//--------------------------------------------------------------------------------------
	AudioManager::~AudioManager()
	{
		// �X���b�h�̏I����҂�
		m_TerminateThread = true;
		if (m_Thread.joinable()) {
			m_Thread.join();
		}

		// �S�Ẳ����~
		StopBGM();
		StopSE();

		// �ǂݍ��񂾉�����S�ĉ��
		for (auto& sound : m_SoundData) {
			CoTaskMemFree(sound.second->WaveFormat);
			delete sound.second;
		}
		m_SoundData.clear();

		// �}�X�^�[�{�C�X�̉��
		if (m_MasteringVoice) {
			m_MasteringVoice->DestroyVoice();
			m_MasteringVoice = nullptr;
		}
		// XAudio2�G���W���̉��
		if (m_AudioEngine) {
			m_AudioEngine->Release();
			m_AudioEngine = nullptr;
		}

	}

	//--------------------------------------------------------------------------------------
	HRESULT AudioManager::RoadSoundFile(uint8_t id, const std::wstring& fileName)
	{
		using namespace Microsoft::WRL;	// ComPtr�p
		HRESULT hr = S_OK;

		// ID�̏d�����`�F�b�N
		if (m_SoundData.find(id) != m_SoundData.end()) {
			return E_FAIL; // ID���d�����Ă���
		}

		// WAVE�t�@�C�����J��
		ComPtr<IMFSourceReader> sourceReader;	// ��O���̂��߂ɃX�}�[�g�|�C���^���g�p
		hr = MFCreateSourceReaderFromURL(fileName.c_str(), nullptr, sourceReader.ReleaseAndGetAddressOf());
		if (FAILED(hr)) {
			return hr; // �t�@�C���̓ǂݍ��݂Ɏ��s
		}

		// WAVEFORMATEX�\���̂��擾
		ComPtr<IMFMediaType> mediaType;
		hr = MFCreateMediaType(mediaType.ReleaseAndGetAddressOf());
		if (FAILED(hr)) {
			return hr; // ���f�B�A�^�C�v�̍쐬�Ɏ��s
		}
		mediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
		mediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);
		sourceReader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, mediaType.Get());

		sourceReader->GetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, mediaType.GetAddressOf());

		WAVEFORMATEX* waveFormat = nullptr;
		MFCreateWaveFormatExFromMFMediaType(mediaType.Get(), &waveFormat, nullptr);


		// �f�[�^�̓ǂݍ���
		std::vector<BYTE> mediaData;
		// �ǂݍ��ݏI���܂Ń��[�v
		for (;;) {
			ComPtr<IMFSample> sample;
			DWORD dwStreamFlags;
			hr = sourceReader->ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM,
				0, nullptr, &dwStreamFlags, nullptr, sample.ReleaseAndGetAddressOf());
			if (FAILED(hr)) {
				return E_FAIL; // �T���v���̓ǂݍ��݂Ɏ��s
			}

			if (dwStreamFlags & MF_SOURCE_READERF_ENDOFSTREAM)
			{
				break;
			}

			if (sample == nullptr) {
				continue; // �T���v�����擾�ł��Ȃ�����
			}

			IMFMediaBuffer* mediaBuffer = nullptr;
			sample->ConvertToContiguousBuffer(&mediaBuffer);

			BYTE* buffer = nullptr;
			DWORD currentLength = 0;
			// �o�b�t�@�����b�N
			mediaBuffer->Lock(&buffer, nullptr, &currentLength);
			// �f�[�^��ǉ�
			mediaData.insert(mediaData.end(), buffer, buffer + currentLength);
			// �o�b�t�@�̃��b�N������
			mediaBuffer->Unlock();
		}

		// �f�[�^��o�^
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

		// SE���Đ�
		sourceVoice = CreateSourceVoiceAndPlay(id, m_SEVolume, false);
		if (sourceVoice == nullptr) {
			return nullptr; // �Đ��Ɏ��s
		}

		// �Đ�����SE�̃��X�g�ɒǉ�
		m_SESourceVoices.insert(sourceVoice);

		return sourceVoice;

	}

	//--------------------------------------------------------------------------------------
	void AudioManager::StopSE(IXAudio2SourceVoice* sourceVoice)
	{
		if (sourceVoice == nullptr) {
			// �S�Ă�SE���~
			for (auto& voice : m_SESourceVoices) {
				voice->Stop(0);
				voice->DestroyVoice();
			}
			m_SESourceVoices.clear();
		}
		else {
			// �w�肵��SE���~
			sourceVoice->Stop(0);
			sourceVoice->DestroyVoice();
			m_SESourceVoices.erase(sourceVoice);
		}

	}

	//--------------------------------------------------------------------------------------
	IXAudio2SourceVoice* AudioManager::ChangeBGM(uint8_t id)
	{
		IXAudio2SourceVoice* sourceVoice;

		// SE���Đ�
		sourceVoice = CreateSourceVoiceAndPlay(id, m_BGMVolume, true);
		if (sourceVoice == nullptr) {
			return nullptr; // �Đ��Ɏ��s
		}

		// ���ݗ���Ă���BGM���~
		StopBGM();

		// �Đ�����BGM�̃��X�g�ɒǉ�
		m_BGMSourceVoices.insert(sourceVoice);

		return sourceVoice;
	}

	//--------------------------------------------------------------------------------------
	IXAudio2SourceVoice* AudioManager::AddBGM(uint8_t id)
	{
		IXAudio2SourceVoice* sourceVoice;

		// SE���Đ�
		sourceVoice = CreateSourceVoiceAndPlay(id, m_BGMVolume, true);
		if (sourceVoice == nullptr) {
			return nullptr; // �Đ��Ɏ��s
		}

		// �Đ�����BGM�̃��X�g�ɒǉ�
		m_BGMSourceVoices.insert(sourceVoice);

		return sourceVoice;
	}

	//--------------------------------------------------------------------------------------
	void AudioManager::StopBGM(IXAudio2SourceVoice* sourceVoice)
	{
		if (sourceVoice == nullptr) {
			// �S�Ă�SE���~
			for (auto& voice : m_BGMSourceVoices) {
				voice->Stop(0);
				voice->DestroyVoice();
			}
			m_BGMSourceVoices.clear();
		}
		else {
			// �w�肵��SE���~
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

		// �Đ�����BGM�̉��ʂ�ύX
		for (auto& voice : m_BGMSourceVoices) {
			voice->SetVolume(volume);
		}
		m_BGMVolume = volume;
	}

	//--------------------------------------------------------------------------------------
	void AudioManager::SetSEVolume(float volume)
	{
		LimitVolume(volume);

		// �Đ�����SE�̉��ʂ�ύX
		for (auto& voice : m_SESourceVoices) {
			voice->SetVolume(volume);
		}
		m_SEVolume = volume;
	}

	//--------------------------------------------------------------------------------------
	void AudioManager::ThreadFunc()
	{
		// �Đ����I������\�[�X�{�C�X���폜
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

		// ID���o�^����Ă��邩�`�F�b�N
		auto itr = m_SoundData.find(id);
		if (itr == m_SoundData.end()) {
			return nullptr; // ID���o�^����Ă��Ȃ�
		}
		// �����f�[�^���擾
		SoundData* soundData = itr->second;

		// �\�[�X�{�C�X�̍쐬
		IXAudio2SourceVoice* sourceVoice = nullptr;
		hr = m_AudioEngine->CreateSourceVoice(&sourceVoice, soundData->WaveFormat);
		if (FAILED(hr)) {
			return nullptr; // �\�[�X�{�C�X�̍쐬�Ɏ��s
		}

		// ���ʂ�ݒ�
		sourceVoice->SetVolume(volume);
		// �����f�[�^��ݒ�
		XAUDIO2_BUFFER buffer = { 0 };
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.AudioBytes = static_cast<UINT32>(soundData->MediaData.size());
		buffer.pAudioData = soundData->MediaData.data();
		if (isLoop) {
			buffer.LoopCount = XAUDIO2_LOOP_INFINITE; // �������[�v
		}
		// �Đ�
		hr = sourceVoice->SubmitSourceBuffer(&buffer);
		if (FAILED(hr)) {
			sourceVoice->DestroyVoice();
			return nullptr; // �����f�[�^�̐ݒ�Ɏ��s
		}
		hr = sourceVoice->Start(0);
		if (FAILED(hr)) {
			sourceVoice->DestroyVoice();
			return nullptr; // �Đ��Ɏ��s
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