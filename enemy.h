//======================================================
// 
// �G�̏���
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "object2D.h"

//*****************************************************************************
// �G�N���X
//*****************************************************************************
class CEnemy :public CObject2D
{
public:

	// �G�̎��
	typedef enum
	{
		ENEMY_NONE = 0,
		ENEMY_1,
		ENEMY_2,
		ENEMY_3,
		ENEMY_MAX
	}ENEMY;

	// �R���X�g���N�^
	CEnemy(int nPriority = 2);
	// �f�X�g���N�^
	~CEnemy();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CEnemy* Create(const D3DXVECTOR3 Pos, const ENEMY Type);

private:
	// �����o�ϐ�
	Texture* m_pEnemyTex;
	D3DXVECTOR3 m_Move;
	ENEMY m_Type;

};

#endif _ENEMY_H_