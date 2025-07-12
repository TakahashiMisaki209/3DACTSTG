//=============================================================================
//
// �T�E���h����
// Author:Takahashi Misaki
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�N���X
//*****************************************************************************
class CSound
{
public:
	// �R���X�g���N�^
	CSound();
	// �f�X�g���N�^
	~CSound();

	//====================================
	// �T�E���h�ꗗ
	//====================================
	typedef enum
	{
		LABEL_SE000 = 0,
		LABEL_SE001,
		LABEL_MAX,
	}LABEL;

	//====================================
	// �T�E���h���̍\���̒�`
	//====================================
	typedef struct
	{
		const char* pFilename;	// �t�@�C����
		int nCntLoop;			// ���[�v�J�E���g
	}INFO;

	// �����o�֐�
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(LABEL label);
	void Stop(LABEL label);
	void StopAll(void);

private:

	// �����o�֐�
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	// �����o�ϐ�
	IXAudio2* m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice* m_apSourceVoice[LABEL_MAX];	// �\�[�X�{�C�X
	BYTE* m_apDataAudio[LABEL_MAX];						// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[LABEL_MAX];						// �I�[�f�B�I�f�[�^�T�C�Y

	// �ÓI�����o�ϐ�
	static INFO m_aSoundInfo[LABEL_MAX];

};

#endif
