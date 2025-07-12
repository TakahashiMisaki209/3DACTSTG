//======================================================
// 
// �i���o�[�̏���
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"

//*****************************************************************************
// �i���o�[�N���X
//*****************************************************************************
class CNumber
{
public:

	// �R���X�g���N�^
	CNumber();
	// �f�X�g���N�^
	~CNumber();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNumber(int nNumber);

	// �ÓI�����o�֐�
	static CNumber* Create(D3DXVECTOR3 pos);

private:

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�̃|�C���^
	D3DXVECTOR3 pos;						// �ʒu
	float fWidth;							// ����
	float fHeight;							// �c��
	int m_nNumber;							// �i���o�[�����ϐ�
	int m_nColume;							// ����
	int m_nIdxTexture;						// �e�N�X�`���̔ԍ�
};

#endif
