//======================================================
// 
// 影の処理
// Author:Takahashi Misaki
// 
//======================================================

#include "shadow.h"
#include "texture.h"
#include "manager.h"

//********************************************
// コンストラクタ
//********************************************
CShadow::CShadow(int nPriority) :CObject3D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_nIdxTexture = 0;
}

//********************************************
// デストラクタ
//********************************************
CShadow::~CShadow()
{

}

//********************************************
// 初期化処理
//********************************************
HRESULT CShadow::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスへのポインタ

	// テクスチャのポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// テクスチャの指定
	m_nIdxTexture = pTexture->Register("data\\TEXTURE\\shadow000.jpg");

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth * 0.5f, m_pos.y, m_pos.z + m_fHeight * 0.5f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth * 0.5f, m_pos.y, m_pos.z + m_fHeight * 0.5f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth * 0.5f, m_pos.y, m_pos.z - m_fHeight * 0.5f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth * 0.5f, m_pos.y, m_pos.z - m_fHeight * 0.5f);

	// 各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

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
void CShadow::Uninit(void)
{
	// オブジェクト3Dの終了処理
	CObject3D::Uninit();
}

//********************************************
// 更新処理
//********************************************
void CShadow::Update(void)
{
	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth * 0.5f, m_pos.y, m_pos.z + m_fHeight * 0.5f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth * 0.5f, m_pos.y, m_pos.z + m_fHeight * 0.5f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth * 0.5f, m_pos.y, m_pos.z - m_fHeight * 0.5f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth * 0.5f, m_pos.y, m_pos.z - m_fHeight * 0.5f);

	// 各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//********************************************
// 描画処理
//********************************************
void CShadow::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスへのポインタ
	// テクスチャのポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// 減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// ワールドマトリックスの固定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// 影の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// 設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//********************************************
// 位置の設定処理
//********************************************
void CShadow::SetPos(float fPosX, float fPosZ)
{
	m_pos.x = fPosX;
	m_pos.z = fPosZ;
}

//********************************************
// クリエイト処理
//********************************************
CShadow* CShadow::Create(float fPosX, float fPosZ ,D3DXVECTOR3 rot, float fWidth, float fHeight)
{
	CShadow* pShadow;

	// 影を生成
	pShadow = new CShadow;

	// 引数を各変数に代入する
	pShadow->m_pos.x = fPosX;
	pShadow->m_pos.z = fPosZ;
	pShadow->m_rot = rot;
	pShadow->m_fWidth = fWidth;
	pShadow->m_fHeight = fHeight;

	// 初期化処理
	pShadow->Init();

	return pShadow;

}