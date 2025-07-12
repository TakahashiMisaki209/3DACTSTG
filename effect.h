//======================================================
// 
// エフェクト処理
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
#include "object2D.h"

//*****************************************************************************
// エフェクトクラス
//*****************************************************************************
class CEffect :public CObject2D
{
public:

	// コンストラクタ
	CEffect(int nPriority = 6);
	// デストラクタ
	~CEffect();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CEffect* Create(const D3DXVECTOR3 Pos);

private:
	// メンバ変数
	Texture* m_pEffectTex;
	int m_nLife;

};

#endif _EFFECT_H_