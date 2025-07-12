//======================================================
// 
// オブジェクト2D処理
// Author:Takahashi Misaki
// 
//======================================================

#include "object2D.h"
#include "manager.h"
#include "input.h"

//********************************************
// コンストラクタ
//********************************************
CObject2D::CObject2D(int nPriority) :CObject(nPriority)
{
	m_Texture.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Texture.Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Texture.fWidth = 0.0f;
	m_Texture.fHeight = 0.0f;
	m_Texture.Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_nCountAnim = 0;
	m_nPatternAnim = 0;
	m_fLength = 0;
	m_fAngle = 0;
	m_aPosTexU = 0;
}

//********************************************
// デストラクタ
//********************************************
CObject2D::~CObject2D()
{
}

//********************************************
// 初期化処理
//********************************************
HRESULT CObject2D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;  // デバイスへのポインタ

	// デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	// 対角線の長さを算出する
	m_fLength = sqrtf(m_Texture.fWidth * m_Texture.fWidth + m_Texture.fHeight * m_Texture.fHeight) / 2.0f;

	// 対角線の角度を算出する
	m_fAngle = atan2f(m_Texture.fWidth, m_Texture.fHeight);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D* pVtx;  // 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos.x = m_Texture.Pos.x + sinf(m_Texture.Rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.y = m_Texture.Pos.y + cosf(m_Texture.Rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_Texture.Pos.x + sinf(m_Texture.Rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.y = m_Texture.Pos.y + cosf(m_Texture.Rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_Texture.Pos.x + sinf(m_Texture.Rot.z + (0.0f - m_fAngle)) * m_fLength;
	pVtx[2].pos.y = m_Texture.Pos.y + cosf(m_Texture.Rot.z + (0.0f - m_fAngle)) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_Texture.Pos.x + sinf(m_Texture.Rot.z + (0.0f + m_fAngle)) * m_fLength;
	pVtx[3].pos.y = m_Texture.Pos.y + cosf(m_Texture.Rot.z + (0.0f + m_fAngle)) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = m_Texture.Col;
	pVtx[1].col = m_Texture.Col;
	pVtx[2].col = m_Texture.Col;
	pVtx[3].col = m_Texture.Col;

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//********************************************
// 終了処理
//********************************************
void CObject2D::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// オブジェクト自身の破棄
	CObject::Release();
}

//********************************************
// 更新処理
//********************************************
void CObject2D::Update(void)
{
	VERTEX_2D* pVtx;  // 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos.x = m_Texture.Pos.x + sinf(m_Texture.Rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.y = m_Texture.Pos.y + cosf(m_Texture.Rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_Texture.Pos.x + sinf(m_Texture.Rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.y = m_Texture.Pos.y + cosf(m_Texture.Rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_Texture.Pos.x + sinf(m_Texture.Rot.z + (0.0f - m_fAngle)) * m_fLength;
	pVtx[2].pos.y = m_Texture.Pos.y + cosf(m_Texture.Rot.z + (0.0f - m_fAngle)) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_Texture.Pos.x + sinf(m_Texture.Rot.z + (0.0f + m_fAngle)) * m_fLength;
	pVtx[3].pos.y = m_Texture.Pos.y + cosf(m_Texture.Rot.z + (0.0f + m_fAngle)) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	// 頂点カラーの設定
	pVtx[0].col = m_Texture.Col;
	pVtx[1].col = m_Texture.Col;
	pVtx[2].col = m_Texture.Col;
	pVtx[3].col = m_Texture.Col;

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//********************************************
// 描画処理
//********************************************
void CObject2D::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();  // デバイスへのポインタ

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ドットの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//********************************************
// アルファブレンドありの描画処理
//********************************************
void CObject2D::AlphaDraw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();  // デバイスへのポインタ

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ドットの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//********************************************
// テクスチャのアニメーション処理
//********************************************
void CObject2D::SetTextureAnim(const int nCountAnim, const int nPatternAnim)
{
	VERTEX_2D* pVtx;  // 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * (10.0f / nPatternAnim * 0.1f), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * (10.0f / nPatternAnim * 0.1f) + (10.0f / nPatternAnim * 0.1f), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * (10.0f / nPatternAnim * 0.1f), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * (10.0f / nPatternAnim * 0.1f) + (10.0f / nPatternAnim * 0.1f), 1.0f);

	m_nCountAnim++;

	if ((m_nCountAnim % nCountAnim == 0))
	{
		m_nCountAnim = 0;
		
		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * (10.0f / nPatternAnim * 0.1f),0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * (10.0f / nPatternAnim * 0.1f) + (10.0f / nPatternAnim * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * (10.0f / nPatternAnim * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * (10.0f / nPatternAnim * 0.1f) + (10.0f / nPatternAnim * 0.1f), 1.0f);
	
		m_nPatternAnim = (m_nPatternAnim + 1) % nPatternAnim;

	}	

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//********************************************
// 背景のスクロール処理
//********************************************
void CObject2D::SetBGScroll(int nCount)
{
	VERTEX_2D* pVtx;  // 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_aPosTexU += 0.002f * (1 + nCount);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(m_aPosTexU, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_aPosTexU + 1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_aPosTexU, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_aPosTexU + 1.0f, 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}
