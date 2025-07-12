//======================================================
// 
// タイマーの処理
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _TIMER_H_
#define _TIMER_H_

#include "number.h"
#include "object.h"

// 最大フレーム
#define MAX_FRAME (60)
// 制限時間
#define MAX_TIME (120)
// 最大桁数
#define MAX_COLUMET (3)

//*****************************************************************************
// タイマークラス
//*****************************************************************************
class CTimer :public CObject
{
public:
	// コンストラクタ
	CTimer(int nPriority = 7);
	// デストラクタ
	~CTimer();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CTimer* Create(void);

private:

	// メンバ変数
	D3DXVECTOR3 m_pos;						// 位置
	int m_nCntTime;							// 時間

	// 静的メンバ変数
	static CNumber* m_apNumer[MAX_COLUMET];
};

#endif _TIMER_H_
