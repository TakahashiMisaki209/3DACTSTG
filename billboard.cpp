// ==============================================
// 
// ビルボードの処理
// Aouther:Takahashi Misaki
//
// ==============================================

#include "billboard.h"
#include "manager.h"
#include "texture.h"

//********************************************
// コンストラクタ
//********************************************
CObjectBillboard::CObjectBillboard(int nPriority) :CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//********************************************
// デストラクタ
//********************************************
CObjectBillboard::~CObjectBillboard()
{

}

//********************************************
// 初期化処理
//********************************************
HRESULT CObjectBillboard::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスへのポインタ

	// テクスチャのポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// テクスチャの指定
	m_nIdxTexture = pTexture->Register("data\\TEXTURE\\coin000.png");

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
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - MAX_TEXTURE_W * 0.5f, m_pos.y + MAX_TEXTURE_H * 0.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + MAX_TEXTURE_W * 0.5f, m_pos.y + MAX_TEXTURE_H * 0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - MAX_TEXTURE_W * 0.5f, m_pos.y - MAX_TEXTURE_H * 0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + MAX_TEXTURE_W * 0.5f, m_pos.y - MAX_TEXTURE_H * 0.5f, 0.0f);

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
void CObjectBillboard::Uninit(void)
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
void CObjectBillboard::Update(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	
	CInputKeyboard* pInputKeyboard;

	// キーボードの取得
	pInputKeyboard = CManager::GetInputKeyboard();

	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - MAX_TEXTURE_W * 0.5f, m_pos.y + MAX_TEXTURE_H * 0.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + MAX_TEXTURE_W * 0.5f, m_pos.y + MAX_TEXTURE_H * 0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - MAX_TEXTURE_W * 0.5f, m_pos.y - MAX_TEXTURE_H * 0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + MAX_TEXTURE_W * 0.5f, m_pos.y - MAX_TEXTURE_H * 0.5f, 0.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	if (pInputKeyboard->GetTrigger(DIK_F10) == true)
	{
		Uninit();
	}
}

//********************************************
// ビルボードの描画処理
//********************************************
void CObjectBillboard::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスへのポインタ

	// テクスチャのポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 計算マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	pDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// αテストを有効
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF,0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// ビューマトリックスを取得
	D3DXMATRIX mtxView;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// カメラの逆行列を設定
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	// 位置を更新
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの固定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ビルボードの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// αテストを無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//********************************************
// 生成処理
//********************************************
CObjectBillboard* CObjectBillboard::Create(D3DXVECTOR3 pos)
{
	CObjectBillboard* pBillboard;

	// ビルボードを生成
	pBillboard = new CObjectBillboard;

	// 初期化処理
	pBillboard->Init();

	// 位置を代入
	pBillboard->m_pos = pos;

	return pBillboard;
}