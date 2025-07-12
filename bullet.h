//======================================================
// 
// 射撃処理
// Author:Takahashi Misaki
// 
//======================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "object2D.h"

//*****************************************************************************
// 弾クラス
//*****************************************************************************
class CBullet :public CObject2D
{
public:

	// コンストラクタ
	CBullet(int nPriority = 2);
	// デストラクタ
	~CBullet();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool CollisionEnemy(D3DXVECTOR3 Pos);

	// 静的メンバ関数
	static CBullet* Create(const D3DXVECTOR3 Pos, const TYPE type);

private:
	// メンバ変数
	Texture* m_pBulletTex;
	TYPE m_type;
	int m_nCountAnim;
	int m_nPatternAnim;
	int m_nLife;
	float m_fMove;
};

#endif _BULLET_H_