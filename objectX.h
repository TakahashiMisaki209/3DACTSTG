//======================================================
// 
// X�t�@�C���̏���
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "main.h"
#include "object.h"

#define MAX_TEXUTE_ALL (10)

//*****************************************************************************
// �I�u�W�F�N�gX�N���X
//*****************************************************************************
class CObjectX :public CObject
{
public:

	// �R���X�g���N�^
	CObjectX(int nPriority = 3);
	// �f�X�g���N�^
	~CObjectX();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CObjectX* Create(void);

private:

	// �����o�ϐ�
	LPD3DXMESH m_pMesh;
	LPD3DXBUFFER m_pBuffMat;
	DWORD m_dwNumMat;
	D3DXMATRIX m_mtxWorld;
	D3DXVECTOR3 m_pos;			// �ʒu
	D3DXVECTOR3 m_rot;			// ����

	// �ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXUTE_ALL];	// �e�N�X�`���ւ̃|�C���^

};
#endif