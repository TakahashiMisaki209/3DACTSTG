//=============================================================================
//
// サウンド処理
// Author:Takahashi Misaki
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドクラス
//*****************************************************************************
class CSound
{
public:
	// コンストラクタ
	CSound();
	// デストラクタ
	~CSound();

	//====================================
	// サウンド一覧
	//====================================
	typedef enum
	{
		LABEL_SE000 = 0,
		LABEL_SE001,
		LABEL_MAX,
	}LABEL;

	//====================================
	// サウンド情報の構造体定義
	//====================================
	typedef struct
	{
		const char* pFilename;	// ファイル名
		int nCntLoop;			// ループカウント
	}INFO;

	// メンバ関数
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(LABEL label);
	void Stop(LABEL label);
	void StopAll(void);

private:

	// メンバ関数
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	// メンバ変数
	IXAudio2* m_pXAudio2;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice;			// マスターボイス
	IXAudio2SourceVoice* m_apSourceVoice[LABEL_MAX];	// ソースボイス
	BYTE* m_apDataAudio[LABEL_MAX];						// オーディオデータ
	DWORD m_aSizeAudio[LABEL_MAX];						// オーディオデータサイズ

	// 静的メンバ変数
	static INFO m_aSoundInfo[LABEL_MAX];

};

#endif
