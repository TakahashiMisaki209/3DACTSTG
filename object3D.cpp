// ==============================================
// 
// オブジェクト3Dの処理
// Aouther:Takahashi Misaki
//
// ==============================================

#include "object3D.h"
#include "manager.h"
#include "input.h"

//********************************************
// コンストラクタ
//********************************************
CObject3D::CObject3D(int nPriority) :CObject(nPriority)
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fWidth = 0.0f;	
	m_fHeight = 0.0f;
	m_bWireFrame = false;
	m_nIdxTexture = 0;
}

//********************************************
// デストラクタ
//********************************************
CObject3D::~CObject3D()
{

}

//********************************************
// 初期化処理
//********************************************
HRESULT CObject3D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスへのポインタ

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
void CObject3D::Uninit(void)
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
void CObject3D::Update(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CInputKeyboard* pInputKeyboard;

	// キーボードの取得
	pInputKeyboard = CManager::GetInputKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_F1) == true)
	{// ワイヤーフレーム機能の切り替え
		m_bWireFrame ? true : false;
	}

	if (m_bWireFrame == false)
	{// ワイヤーフレームをオンにする
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

		m_bWireFrame = true;
	}
	else if (m_bWireFrame == true)
	{// ワイヤーフレームをオフにする
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

		m_bWireFrame = false;
	}

}

//********************************************
// 描画処理
//********************************************
void CObject3D::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// デバック表示のポインタ
	CDebugproc* pDebugproc;

	// テクスチャのポインタ取得
	CTexture* pTexture = CManager::GetTexture();

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

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	if (m_bWireFrame == true)
	{// ワイヤーフレーム機能がオンになっている時
		pDebugproc->Print("[F1] ワイヤーフレーム:ON\n");
	}
	else if (m_bWireFrame == false)
	{// ワイヤーフレーム機能がオフになっている時
		pDebugproc->Print("[F1] ワイヤーフレーム:OFF\n");
	}
}
