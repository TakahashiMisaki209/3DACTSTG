//======================================================
// 
// 背景処理
// Author:Takahashi Misaki
// 
//======================================================
 
#include "background.h" 
#include "manager.h"


//********************************************
// コンストラクタ
//********************************************
CBG2D::CBG2D(int nPriority) :CObject2D(nPriority)
{
	// テクスチャの情報を取得
	m_pBGTex = CObject2D::GetTexture();

	m_pBGTex->Pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
	m_pBGTex->Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pBGTex->fWidth = SCREEN_WIDTH;
	m_pBGTex->fHeight = SCREEN_HEIGHT;
	m_pBGTex->Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	m_nID = 0;
}

//********************************************
// デストラクタ
//********************************************
CBG2D::~CBG2D()
{
}

//********************************************
// 初期化処理
//********************************************
HRESULT CBG2D::Init(void)
{
	// オブジェクト2Dの初期化処理
	CObject2D::Init();

	return S_OK;
}

//********************************************
// 終了処理
//********************************************
void CBG2D::Uninit(void)
{
	// オブジェクト2Dの終了処理
	CObject2D::Uninit();
}

//********************************************
// 更新処理
//********************************************
void CBG2D::Update(void)
{
	// オブジェクト2Dの更新処理
	CObject2D::Update();

	// 背景のスクロール処理	
	CObject2D::SetBGScroll(m_nID);
}

//********************************************
// 描画処理
//********************************************
void CBG2D::Draw(void)
{
	// オブジェクト2Dの描画処理
	CObject2D::Draw();
}

//********************************************
// クリエイト処理
//********************************************
CBG2D* CBG2D::Create(void)
{
	static int nCount = 0;

	CBG2D* pBG;

	// 背景の生成
	pBG = new CBG2D;

	// 初期化処理
	pBG->Init();

	pBG->m_nID = nCount;

	nCount++;

	return pBG;
}
