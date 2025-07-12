//======================================================
// 
// �r���{�[�h�̏���
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"
#include "object.h"

#define MAX_TEXTURE_W (100.0f)	// ����
#define MAX_TEXTURE_H (100.0f)	// �c��

//******************************************************
// �r���{�[�h�N���X
//******************************************************
class CObjectBillboard :public CObject
{
public:
	// �R���X�g���N�^
	CObjectBillboard(int nPriority = 2);
	// �f�X�g���N�^
	~CObjectBillboard();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CObjectBillboard* Create(D3DXVECTOR3 pos);

private:
	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;					// ���_���W
	D3DXVECTOR3 m_rot;					// ����
	int m_nIdxTexture;					// �e�N�X�`���̔ԍ�
};

#endif