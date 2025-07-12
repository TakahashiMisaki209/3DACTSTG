//======================================================
// 
// �I�u�W�F�N�g3D�̏���
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "main.h"
#include "object.h"

//*****************************************************************************
// �I�u�W�F�N�g3D�N���X
//*****************************************************************************
class CObject3D :public CObject
{
public:

	// �R���X�g���N�^
	CObject3D(int nPriority = 3);
	// �f�X�g���N�^
	~CObject3D();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPos(void) { return m_pos; };		// �ʒu���̎擾

private:

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;					// ���_���W
	D3DXVECTOR3 m_rot;					// ����
	float m_fWidth;						// �|���S���̉���
	float m_fHeight;					// �|���S���̏c��
	bool m_bWireFrame;					// ���C���[�t���[�����I���ɂ��邩�ǂ���
	int m_nIdxTexture;					// �e�N�X�`���̔ԍ�
};
#endif