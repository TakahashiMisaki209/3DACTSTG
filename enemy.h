//======================================================
// 
// 敵の処理
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "object2D.h"

//*****************************************************************************
// 敵クラス
//*****************************************************************************
class CEnemy :public CObject2D
{
public:

	// 敵の種類
	typedef enum
	{
		ENEMY_NONE = 0,
		ENEMY_1,
		ENEMY_2,
		ENEMY_3,
		ENEMY_MAX
	}ENEMY;

	// コンストラクタ
	CEnemy(int nPriority = 2);
	// デストラクタ
	~CEnemy();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CEnemy* Create(const D3DXVECTOR3 Pos, const ENEMY Type);

private:
	// メンバ変数
	Texture* m_pEnemyTex;
	D3DXVECTOR3 m_Move;
	ENEMY m_Type;

};

#endif _ENEMY_H_