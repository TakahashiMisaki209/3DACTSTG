//======================================================
// 
// ��������
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"
#include "object2D.h"

//*****************************************************************************
// �����N���X
//*****************************************************************************
class CExplosion :public CObject2D
{
public:

	// �R���X�g���N�^
	CExplosion(int nPriority = 6);
	// �f�X�g���N�^
	~CExplosion();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CExplosion* Create(const D3DXVECTOR3 Pos);

private:
	// �����o�ϐ�
	Texture* m_pExplosionTex;
	int m_nCountAnim;
	int m_nPatternAnim;
	int m_nCounter;
	D3DXCOLOR m_Col;
};

#endif _EXPLOSION_H_