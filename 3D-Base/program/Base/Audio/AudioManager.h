#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ���̍Đ��E��~�E���ʒ����Ȃǂ��s���N���X
// �V���O���g���N���X
// 
// �����	: amateurK
// �쐬��	: 2025/04/19
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../Tools/StepTimer.h"

namespace AK_Base {

	/// @brief ���̍Đ��E��~�E���ʒ����Ȃǂ��s���N���X
	class AudioManager
	{
	private:
		/// @brief �R���X�g���N�^
		AudioManager();
		/// @brief �f�X�g���N�^
		~AudioManager();

		static AudioManager* Instance;
	public:
		AudioManager(AudioManager&&) = delete;
		AudioManager& operator=(AudioManager&&) = delete;

		AudioManager(AudioManager const&) = delete;
		AudioManager& operator=(AudioManager const&) = delete;

		/// @brief ���̃N���X�̃C���X�^���X���擾
		/// @return �C���X�^���X
		static AudioManager* GetInstance() {
			return Instance;
		}
		/// @brief �C���X�^���X�𐶐�
		static void Create() {
			if (Instance == nullptr) {
				Instance = new AudioManager;
			}
			else {
				throw std::exception("AudioManager is a singleton");
			}
		}
		/// @brief �C���X�^���X�̉��
		static void Destroy() {
			delete Instance;
			Instance = nullptr;
		}

	private:

		// �\�[�X�{�C�X�����̂ɕK�v�Ȃ���
		struct SoundData {
			WAVEFORMATEX* WaveFormat;
			std::vector<BYTE> MediaData;
		};

		/// @brief XAudio2�G���W��
		IXAudio2* m_AudioEngine;
		/// @brief �}�X�^�[�{�C�X
		IXAudio2MasteringVoice* m_MasteringVoice;

		/// @brief �����f�[�^�̃��X�g
		std::unordered_map<uint8_t, SoundData*> m_SoundData;

		/// @brief �Đ�����BGM�̃��X�g
		std::unordered_set<IXAudio2SourceVoice*> m_BGMSourceVoices;
		/// @brief �Đ�����SE�̃��X�g
		std::unordered_set<IXAudio2SourceVoice*> m_SESourceVoices;
		//std::list<IXAudio2SubmixVoice*> m_SubmixVoices;

		/// @brief �Đ����̃\�[�X�{�C�X�̉��ʂ̃��X�g
		std::unordered_map<IXAudio2SourceVoice*, float> m_SourceVoiceVolume;

		/// @brief ���p�X���b�h
		std::thread m_Thread;
		/// @brief ���p�X���b�h���I������ۂ�true�ɂ���t���O
		std::atomic<bool> m_TerminateThread;
		/// @brief ���p�X���b�h�̏����p�^�C�}�[
		DX::StepTimer m_Timer;

		/// @brief BGM�̉���
		float m_BGMVolume;
		/// @brief SE�̉���
		float m_SEVolume;

	public:
		/// @brief ���y�t�@�C����ǂݍ���
		/// @param id �o�^����ID
		/// @param fileName �t�@�C���ւ̃p�X
		/// @return ID���d�����Ă��邩�A�ǂݍ��ݎ��s�����FAILED
		HRESULT RoadSoundFile(uint8_t id, const std::wstring& fileName);

		/// @brief SE���Đ�
		/// @param id ������ID
		/// @param volume ����
		/// @return �Đ����ꂽ�\�[�X�{�C�X�ւ̃|�C���^
		IXAudio2SourceVoice* PlaySE(uint8_t id, float volume = 1.0f);
		/// @brief SE�̍Đ����~
		/// @param sourceVoice ��~����\�[�X�{�C�X�ւ̃|�C���^�Anullptr�̏ꍇ�͑S�Ē�~
		void StopSE(IXAudio2SourceVoice* sourceVoice = nullptr);

		/// @brief BGM���Đ��i���ݗ���Ă���BGM���~�j
		/// @param id ������ID
		/// @return �Đ����ꂽ�\�[�X�{�C�X�ւ̃|�C���^
		IXAudio2SourceVoice* ChangeBGM(uint8_t id, float volume = 1.0f);
		/// @brief BGM���Đ��i���ݗ���Ă���BGM�͂��̂܂܁j
		/// @param id ������ID
		/// @return �Đ����ꂽ�\�[�X�{�C�X�ւ̃|�C���^
		IXAudio2SourceVoice* AddBGM(uint8_t id, float volume = 1.0f);
		/// @brief BGM�̍Đ����~
		/// @param sourceVoice ��~����\�[�X�{�C�X�ւ̃|�C���^�Anullptr�̏ꍇ�͑S�Ē�~
		void StopBGM(IXAudio2SourceVoice* sourceVoice = nullptr);
		
		/// @brief �S�̂̉��ʂ��Z�b�g
		/// @param volume ����
		void SetMasterVolume(float volume);
		/// @brief BGM�̉��ʂ��Z�b�g
		/// @param volume ����
		void SetBGMVolume(float volume);
		/// @brief SE�̉��ʂ��Z�b�g
		/// @param volume ����
		void SetSEVolume(float volume);

	private:
		/// @brief ���p�X���b�h�̏���
		void ThreadFunc();

		/// @brief �\�[�X�{�C�X���쐬���A�Đ�����
		/// @param id ������ID
		/// @param volume ����
		/// @param Loop ���[�v�����邩
		/// @return �Đ����ꂽ�\�[�X�{�C�X�ւ̃|�C���^
		IXAudio2SourceVoice* CreateSourceVoiceAndPlay(uint8_t id, float volume, bool isLoop = false);

		/// @brief ���ʂ����E�l���z���Ă����ꍇ�ɐ���
		/// @param volume ����
		void LimitVolume(float& volume) const;
	};
}
