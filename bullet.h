//======================================================
// 
// �ˌ�����
// Author:Takahashi Misaki
// 
//======================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "object2D.h"

//*****************************************************************************
// �e�N���X
//*****************************************************************************
class CBullet :public CObject2D
{
public:

	// �R���X�g���N�^
	CBullet(int nPriority = 2);
	// �f�X�g���N�^
	~CBullet();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool CollisionEnemy(D3DXVECTOR3 Pos);

	// �ÓI�����o�֐�
	static CBullet* Create(const D3DXVECTOR3 Pos, const TYPE type);

private:
	// �����o�ϐ�
	Texture* m_pBulletTex;
	TYPE m_type;
	int m_nCountAnim;
	int m_nPatternAnim;
	int m_nLife;
	float m_fMove;
};

#endif _BULLET_H_