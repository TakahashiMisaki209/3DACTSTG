//======================================================
// 
// �e�N�X�`���̏���
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "main.h"

// �}�N����`
#define MAX_NUMTEXTUER (20)

//******************************************************
// �e�N�X�`���N���X
//******************************************************
class CTexture
{
public:
	// �R���X�g���N�^
	CTexture();
	// �f�X�g���N�^
	~CTexture();

	// �����o�֐�
	HRESULT Load(void);
	void Unload(void);
	int Register(const char* pFilename);
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx) { return m_apTexture[nIdx]; };

private:
	// �����o�ϐ�
	LPDIRECT3DTEXTURE9 m_apTexture[MAX_NUMTEXTUER];

	// �ÓI�����o�ϐ�
	static int m_nNumAll;

};

#endif