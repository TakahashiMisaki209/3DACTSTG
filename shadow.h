//======================================================
// 
// �e�̏���
// Author:Takahashi Misaki
// 
//======================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"
#include "object3D.h"

//*****************************************************************************
// �e�N���X
//*****************************************************************************
class CShadow :public CObject3D
{
public:

	// �R���X�g���N�^
	CShadow(int nPriority = 4);
	// �f�X�g���N�^
	~CShadow();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(float fPosX, float fPosZ);

	// �ÓI�����o�֐�
	static CShadow* Create(float fPosX, float fPosZ, D3DXVECTOR3 rot, float fWidth, float fHeight);

private:
	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_rot;					// ����
	D3DXCOLOR m_col;					// �F
	float m_fWidth;						// �e�̉���
	float m_fHeight;					// �e�̏c��
	int m_nIdxTexture;					// �e�N�X�`���̔ԍ�
};

#endif