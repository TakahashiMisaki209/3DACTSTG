//======================================================
// 
// 射撃処理
// Author:Takahashi Misaki
// 
//======================================================

#include "bullet.h"
#include "manager.h"
#include "explosion.h"
#include "player.h"
#include "score.h"
#include "effect.h"

//********************************************
// コンストラクタ
//********************************************
CBullet::CBullet(int nPriority) :CObject2D(nPriority)
{
	m_nCountAnim = 0;
	m_nPatternAnim = 0;
	m_nLife = 0;
	m_fMove = 0.0f;
}

//********************************************
// デストラクタ
//********************************************
CBullet::~CBullet()
{
}

//********************************************
// 初期化処理
//********************************************
HRESULT CBullet::Init(void)
{
	// テクスチャの情報を取得
	m_pBulletTex = CObject2D::GetTexture();

	m_pBulletTex->Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pBulletTex->Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pBulletTex->fWidth = 30.0f;
	m_pBulletTex->fHeight = 30.0f;

	m_nCountAnim = 5;
	m_nPatternAnim = 4;
	m_nLife = 120;
	m_fMove = 5.0f;

	// オブジェクト2Dの初期化処理
	CObject2D::Init();

	// テクスチャのアニメーション処理
	CObject2D::SetTextureAnim(m_nCountAnim, m_nPatternAnim);

	return S_OK;
}

//********************************************
// 終了処理
//********************************************
void CBullet::Uninit(void)
{
	// オブジェクト2Dの終了処理
	CObject2D::Uninit();
}

//********************************************
// 更新処理
//********************************************
void CBullet::Update(void)
{
	bool bCollision = false;

	if (m_type == TYPE_PLAYER)
	{
		m_pBulletTex->Pos.x += m_fMove;

		// エフェクトの生成
		CEffect::Create(m_pBulletTex->Pos);

	}
	else if (m_type == TYPE_ENEMY)
	{
		m_pBulletTex->Pos.x -= m_fMove;
	}

	// オブジェクト2Dの更新処理
	CObject2D::Update();

	// テクスチャのアニメーション処理
	CObject2D::SetTextureAnim(m_nCountAnim, m_nPatternAnim);

	// 敵との当たり判定
	bCollision = CollisionEnemy(m_pBulletTex->Pos);

	if (false == bCollision)
	{// 敵と当たっていなかったら
		
		// 体力を減らす
		m_nLife--;

		if (m_pBulletTex->Pos.x <= 0 || m_pBulletTex->Pos.x >= SCREEN_WIDTH || m_pBulletTex->Pos.y <= 0 || m_pBulletTex->Pos.y >= SCREEN_HEIGHT)
		{// 画面外に出たら

			//// 爆発を生成
			//CExplosion::Create(m_pBulletTex->Pos);

			// 終了処理
			Uninit();

		}
		else if (m_nLife == 0)
		{// 体力がなくなったら

			//// 爆発を生成
			//CExplosion::Create(m_pBulletTex->Pos);

			// 終了処理
			Uninit();
		}
	}
}

//********************************************
// 描画処理
//********************************************
void CBullet::Draw(void)
{
	// オブジェクト2Dの描画処理
	CObject2D::Draw();
}

//********************************************
// 敵との当たり判定
//********************************************
bool CBullet::CollisionEnemy(D3DXVECTOR3 Pos)
{
	D3DXVECTOR3 pos = {};

	//for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	//{
	//	CObject* pObj;

	//	// オブジェクトの取得
	//	pObj = GetCObject(nCount);

	//	if (pObj != NULL)
	//	{
	//		TYPE type;

	//		// 種類の取得
	//		type = pObj->GetTYPE();

	//		if (type == TYPE_ENEMY && m_type == TYPE_PLAYER )
	//		{// 種類が敵の時

	//			// 敵の位置を代入
	//			pos = pObj->GetPos();

	//			if (pos.x - m_pBulletTex->fWidth <= Pos.x && pos.x + m_pBulletTex->fWidth >= Pos.x)
	//			{// 敵と当たっている場合(X軸)

	//				if (pos.y - m_pBulletTex->fHeight <= Pos.y && pos.y + m_pBulletTex->fHeight >= Pos.y)
	//				{// 敵と当たっている場合(Y軸)

	//					//// 爆発を生成
	//					//CExplosion::Create(Pos);

	//					// スコアの加算処理
	//					CScore::AddScore(100);

	//					// 敵の終了処理
	//					pObj->Uninit();

	//					// 終了処理
	//					Uninit();

	//					return true;
	//				}
	//			}
	//		}
	//		else if (type == TYPE_PLAYER && m_type == TYPE_ENEMY)
	//		{// 種類がプレイヤーの時

	//			// プレイヤーの位置を代入
	//			pos = pObj->GetPos();

	//			if (pos.x - m_pBulletTex->fWidth <= Pos.x && pos.x + m_pBulletTex->fWidth >= Pos.x)
	//			{// プレイヤーと当たっている場合(X軸)

	//				if (pos.y - m_pBulletTex->fHeight <= Pos.y && pos.y + m_pBulletTex->fHeight >= Pos.y)
	//				{// プレイヤーと当たっている場合(Y軸)

	//					//// 爆発を生成
 // 						// CExplosion::Create(Pos);

	//					//// プレイヤーのヒット処理
	//					//CPlayer::HitBullet(true);

	//					// 終了処理
	//					Uninit();

	//					return true;
	//				}
	//			}
	//		}
	//	}
	//}

	return false;
}

//********************************************
// クリエイト処理
//********************************************
CBullet* CBullet::Create(const D3DXVECTOR3 Pos, const TYPE type)
{
	CBullet* pBullet = NULL;

	int nNumAll = CObject::GetNumAll();

	//if (nNumAll < MAX_OBJECT - 1)
	//{// メモリが最大ではないとき

	//	// 弾の生成
	//	pBullet = new CBullet;

	//	// 初期化処理
	//	pBullet->Init();

	//	pBullet->m_pBulletTex->Pos = Pos;

	//	pBullet->m_type = type;

	//	// オブジェクトの種類の設定
	//	pBullet->SetTYPE(TYPE_BULLET);
	//}

	return pBullet;
}