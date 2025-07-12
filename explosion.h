//======================================================
// 
// 爆発処理
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"
#include "object2D.h"

//*****************************************************************************
// 爆発クラス
//*****************************************************************************
class CExplosion :public CObject2D
{
public:

	// コンストラクタ
	CExplosion(int nPriority = 6);
	// デストラクタ
	~CExplosion();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CExplosion* Create(const D3DXVECTOR3 Pos);

private:
	// メンバ変数
	Texture* m_pExplosionTex;
	int m_nCountAnim;
	int m_nPatternAnim;
	int m_nCounter;
	D3DXCOLOR m_Col;
};

#endif _EXPLOSION_H_