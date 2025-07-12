//======================================================
// 
// �X�R�A�̏���
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _SCORE_H_
#define _SCORE_H_

#include "number.h"
#include "object.h"

// �ő包��
#define MAX_COLUMES (8)

//*****************************************************************************
// �X�R�A�N���X
//*****************************************************************************
class CScore :public CObject
{
public:
	// �R���X�g���N�^
	CScore(int nPriority = 7);
	// �f�X�g���N�^
	~CScore();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CScore* Create(void);
	static void AddScore(int nScore);

private:

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;						// �ʒu

	// �ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`���̃|�C���^
	static CNumber* m_apNumer[MAX_COLUMES];
	static int m_nScore;					// �X�R�A
};

#endif
