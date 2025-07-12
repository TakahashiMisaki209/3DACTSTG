//======================================================
// 
// 爆発処理
// Author:Takahashi Misaki
// 
//======================================================

#include "explosion.h"
#include "manager.h"

//********************************************
// コンストラクタ
//********************************************
CExplosion::CExplosion(int nPriority):CObject2D(nPriority)
{
	// テクスチャの情報を取得
	m_pExplosionTex = CObject2D::GetTexture();

	m_pExplosionTex->fWidth = 50.0f;
	m_pExplosionTex->fHeight = 50.0f;

	m_nCountAnim  = 5;
	m_nPatternAnim = 8;
	m_nCounter = m_nCountAnim * m_nPatternAnim;
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

}
//********************************************
// デストラクタ
//********************************************
CExplosion::~CExplosion()
{
}
//********************************************
// 初期化処理
//********************************************
HRESULT CExplosion::Init(void)
{
	// オブジェクト2Dの初期化処理
	CObject2D::Init();

	// テクスチャのアニメーション処理
	CObject2D::SetTextureAnim(m_nCountAnim, m_nPatternAnim);

	return S_OK;
}

//********************************************
// 終了処理
//********************************************
void CExplosion::Uninit(void)
{
	// オブジェクト2Dの終了処理
	CObject2D::Uninit();
}

//********************************************
// 更新処理
//********************************************
void CExplosion::Update(void)
{
	// オブジェクト2Dの更新処理
	CObject2D::Update();

	// テクスチャのアニメーション処理
	CObject2D::SetTextureAnim(m_nCountAnim, m_nPatternAnim);

	m_nCounter--;

	if (m_nCounter ==  0)
	{// アニメーションが終わったら
		// 終了処理
		CExplosion::Uninit();
	}

}

//********************************************
// 描画処理
//********************************************
void CExplosion::Draw(void)
{
	// オブジェクト2Dの描画処理
	CObject2D::Draw();
}
//********************************************
// クリエイト処理
//********************************************
CExplosion* CExplosion::Create(const D3DXVECTOR3 Pos)
{
	CExplosion* pExplosion = NULL;

	int nNumAll = CObject::GetNumAll();

	//if (nNumAll < MAX_OBJECT - 1)
	//{// メモリが最大ではないとき

	//	// 爆発の生成
	//	pExplosion = new CExplosion(4);

	//	// 初期化処理
	//	pExplosion->Init();

	//	pExplosion->m_pExplosionTex->Pos = Pos;
	//}

	return pExplosion;
}
