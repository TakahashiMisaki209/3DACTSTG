//======================================================
// 
// ライトの処理
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

// マクロ定義
#define MAX_LIGHT (3)

//******************************************************
// ライトクラス
//******************************************************
class CLight
{
public:
	// コンストラクタ
	CLight();
	// デストラクタ
	~CLight();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	D3DLIGHT9 m_aLight[MAX_LIGHT];

};

#endif