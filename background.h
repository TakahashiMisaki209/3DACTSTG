//======================================================
// 
// 背景処理
// Author:Takahashi Misaki
// 
//======================================================
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "object2D.h"

// マクロ定義
#define MAX_BG (3)

//*****************************************************************************
// 背景クラス
//*****************************************************************************
class CBG2D :public CObject2D
{
public:
	// コンストラクタ
	CBG2D(int nPriority = 1);
	// デストラクタ
	~CBG2D();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ変数
	static CBG2D* Create(void);

private:
	// メンバ変数
	Texture* m_pBGTex;
	int m_nID;
};

#endif _BACKGROUND_H_