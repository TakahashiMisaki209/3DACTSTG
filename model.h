//======================================================
// 
// ���f���̏���
// Author:Takahashi Misaki
// 
//======================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

// �}�N����`
#define MAX_MODEL (10)			// ���f���̍ő吔

//******************************************************
// ���f���N���X
//******************************************************
class CModel
{
public:

	// �R���X�g���N�^
	CModel();

	// �f�X�g���N�^
	~CModel();

	// �����o�֐�
	HRESULT Init(const char* pXfileName);
	void Uninit(void);
	void Draw(void);
	void SetParent(CModel* pModel, D3DXVECTOR3 Offsetpos, D3DXVECTOR3 Offsetrot);
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }
	void SetPos(D3DXVECTOR3 pos){ m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot){ m_rot = rot; }
	D3DXVECTOR3 GetOffsetPos(void) { return m_Offsetpos; }
	D3DXVECTOR3 GetOffsetRot(void) { return m_Offsetrot; }

	// �ÓI�����o�֐�
	static CModel* Create(const char* pXfileName);

private:
	// �����o�ϐ�
	LPD3DXMESH m_pMesh;
	LPD3DXBUFFER m_pBuffMat;
	DWORD m_dwNumMat;

	D3DXVECTOR3 m_pos;			// �ʒu
	D3DXVECTOR3 m_rot;			// ����
	D3DXVECTOR3 m_Offsetpos;	// �ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 m_Offsetrot;	// ����(�I�t�Z�b�g)
	D3DXMATRIX m_mtxWorld;		// ���[���h�}�g���b�N�X
	CModel* m_pParent;			// �e���f���̃|�C���^
};

#endif