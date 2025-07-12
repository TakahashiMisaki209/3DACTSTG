//======================================================
// 
// �G�t�F�N�g����
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
#include "object2D.h"

//*****************************************************************************
// �G�t�F�N�g�N���X
//*****************************************************************************
class CEffect :public CObject2D
{
public:

	// �R���X�g���N�^
	CEffect(int nPriority = 6);
	// �f�X�g���N�^
	~CEffect();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CEffect* Create(const D3DXVECTOR3 Pos);

private:
	// �����o�ϐ�
	Texture* m_pEffectTex;
	int m_nLife;

};

#endif _EFFECT_H_