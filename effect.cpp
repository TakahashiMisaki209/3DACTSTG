//======================================================
// 
// エフェクト処理
// Author:Takahashi Misaki
// 
//======================================================

#include "effect.h"
#include "manager.h"

//********************************************
// コンストラクタ
//********************************************
CEffect::CEffect(int nPriority):CObject2D(nPriority)
{
	m_nLife = 0;
}

//********************************************
// デストラクタ
//********************************************
CEffect::~CEffect()
{
}

//********************************************
// 初期化処理
//********************************************
HRESULT CEffect::Init(void)
{
	// テクスチャの情報を取得
	m_pEffectTex = CObject2D::GetTexture();

	m_pEffectTex->Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pEffectTex->fWidth = 30.0f;
	m_pEffectTex->fHeight = 30.0f;
	m_pEffectTex->Col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

	m_nLife = 20;

	// オブジェクト2Dの初期化処理
	CObject2D::Init();

	return S_OK;
}

//********************************************
// 終了処理
//********************************************
void CEffect::Uninit(void)
{
	// オブジェクト2Dの終了処理
	CObject2D::Uninit();
}

//********************************************
// 更新処理
//********************************************
void CEffect::Update(void)
{
 	m_pEffectTex->fWidth = m_pEffectTex->fWidth * 0.93f;
	m_pEffectTex->fHeight = m_pEffectTex->fHeight * 0.93f;

	m_pEffectTex->Col.a = m_pEffectTex->Col.a * 0.8f;

	// オブジェクト2Dの更新処理
	CObject2D::Update();

	// エフェクトの体力を減らす
	m_nLife--;

	if (m_nLife <= 0)
	{
		// エフェクトの終了処理
		CEffect::Uninit();
	}
}

//********************************************
// 描画処理
//********************************************
void CEffect::Draw(void)
{
	// オブジェクト2Dの描画処理
	CObject2D::AlphaDraw();
}

//********************************************
// クリエイト処理
//********************************************
CEffect* CEffect::Create(const D3DXVECTOR3 Pos)
{
	CEffect* pEffect = NULL;

	int nNumAll = CObject::GetNumAll();

	//if (nNumAll < MAX_OBJECT - 1)
	//{// メモリが最大ではないとき

	//	// エフェクトの生成
	//	pEffect = new CEffect;

	//	// 初期化処理
	//	pEffect->Init();

	//	pEffect->m_pEffectTex->Pos = Pos;

	//	// オブジェクトの種類の設定
	//	pEffect->SetTYPE(TYPE_EFFECT);
	//}

	return pEffect;
}