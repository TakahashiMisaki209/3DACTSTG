//======================================================
// 
// プレイヤー処理
// Author:Takahashi Misaki
// 
//======================================================

#include "enemy.h"
#include "manager.h"
#include "input.h"
#include "Bullet.h"


//********************************************
// コンストラクタ
//********************************************
CEnemy::CEnemy(int nPriority) :CObject2D(nPriority)
{
	m_Move = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);

	// テクスチャの情報を取得
	m_pEnemyTex = CObject2D::GetTexture();

	m_pEnemyTex->Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pEnemyTex->fWidth = 60.0f;
	m_pEnemyTex->fHeight = 60.0f;
	m_pEnemyTex->Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}
//********************************************
// デストラクタ
//********************************************
CEnemy::~CEnemy()
{
}

//********************************************
// 初期化処理
//********************************************
HRESULT CEnemy::Init(void)
{
	// オブジェクト2Dの初期化処理
	CObject2D::Init();

	return S_OK;
}

//********************************************
// 終了処理
//********************************************
void CEnemy::Uninit(void)
{
	// オブジェクト2Dの終了処理
	CObject2D::Uninit();
}

//********************************************
// 更新処理
//********************************************
void CEnemy::Update(void)
{
	// 弾を打つ間隔をカウントする変数
	static int nCntTime = 0;

	// オブジェクト2Dの更新処理
	CObject2D::Update();

	switch (m_Type)
	{
	case ENEMY_1:
		// 敵１
		
		//==================================
		// 移動の処理
		//==================================
		if (m_pEnemyTex->Pos.x <= 0.0f)
		{
			m_Move.x = 2.0f;
		}
		else if (m_pEnemyTex->Pos.x >= SCREEN_WIDTH)
		{
			m_Move.x = -2.0f;
		}

		if (m_pEnemyTex->Pos.y <= 0.0f)
		{
			m_Move.y = 1.0f;
		}
		else if (m_pEnemyTex->Pos.y >= SCREEN_HEIGHT)
		{
			m_Move.y = -1.0f;
		}

		break;

	case ENEMY_2:
		// 敵２

		if (m_pEnemyTex->Pos.x <= 0.0f)
		{
			m_Move.x = 1.0f;
		}
		else if (m_pEnemyTex->Pos.x >= SCREEN_WIDTH)
		{
			m_Move.x = -1.0f;
		}

		if (m_pEnemyTex->Pos.y <= 0.0f)
		{
			m_Move.y = 2.0f;
		}
		else if (m_pEnemyTex->Pos.y >= SCREEN_HEIGHT)
		{
			m_Move.y= -2.0f;
		}

		break;

	case ENEMY_3:
		// 敵３

		if (m_pEnemyTex->Pos.x <= 0.0f)
		{
			m_Move.x = 2.0f;
		}
		else if (m_pEnemyTex->Pos.x >= SCREEN_WIDTH)
		{
			m_Move.x = -2.0f;
		}

		if (m_pEnemyTex->Pos.y <= 0.0f)
		{
			m_Move.y = 2.0f;
		}
		else if (m_pEnemyTex->Pos.y >= SCREEN_HEIGHT)
		{
			m_Move.y = -2.0f;
		}

		break;

	}

	// 移動量を加算
	m_pEnemyTex->Pos.x += m_Move.x;
	m_pEnemyTex->Pos.y += m_Move.y;

	nCntTime++;

	if (nCntTime >= 100)
	{
		nCntTime = 0;

		CBullet::Create(m_pEnemyTex->Pos, TYPE_ENEMY);
	}
}

//********************************************
// 描画処理
//********************************************
void CEnemy::Draw(void)
{
	// オブジェクト2Dの描画処理
	CObject2D::Draw();
}

//********************************************
// クリエイト処理
//********************************************
CEnemy* CEnemy::Create(const D3DXVECTOR3 Pos, const ENEMY Type)
{
	CEnemy* pEnemy;

	// 敵の生成
	pEnemy = new CEnemy;
	
	// 敵の位置を代入
	pEnemy->m_pEnemyTex->Pos = Pos;

	// 敵の種類を代入
	pEnemy->m_Type = Type;

	// 種類ごとの設定
	switch (pEnemy->m_Type)
	{
	case ENEMY_1:
		
		// 色の設定
		pEnemy->m_pEnemyTex->Col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		break;

	case ENEMY_2:

		// 色の設定
		pEnemy->m_pEnemyTex->Col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

		break;

	case ENEMY_3:

		// 色の設定
		pEnemy->m_pEnemyTex->Col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

		break;

	}

	// 初期化処理
	pEnemy->Init();

	// オブジェクトの種類の設定
	pEnemy->SetTYPE(TYPE_ENEMY);

	return pEnemy;
}
