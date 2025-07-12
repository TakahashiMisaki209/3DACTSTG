//======================================================
// 
// ナンバー処理
// Author:Takahashi Misaki
// 
//======================================================

#include "number.h"
#include "manager.h"
#include "texture.h"

//********************************************
// コンストラクタ
//********************************************
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	fWidth = 0.0f;
	fHeight = 0.0f;
	m_nNumber = 0;
	m_nColume = 0;
	m_nIdxTexture = 0;
}

//********************************************
// デストラクタ
//********************************************
CNumber::~CNumber()
{
}

//********************************************
// 初期化処理
//********************************************
HRESULT CNumber::Init(void)
{
	// 値の設定
	fWidth = 60.0f;
	fHeight = 80.0f;

	LPDIRECT3DDEVICE9 pDevice;  // デバイスへのポインタ

	// デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャのポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// テクスチャの指定
	m_nIdxTexture = pTexture->Register("data\\TEXTURE\\number000.png");

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
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth * 0.5f, pos.y - fHeight * 0.5f, pos.z);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth * 0.5f, pos.y - fHeight * 0.5f, pos.z);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth * 0.5f, pos.y + fHeight * 0.5f, pos.z);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth * 0.5f, pos.y + fHeight * 0.5f, pos.z);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f * 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f * 0.1f, 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//********************************************
// 終了処理
//********************************************
void CNumber::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//********************************************
// 更新処理
//********************************************
void CNumber::Update(void)
{
	VERTEX_2D* pVtx;  // 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth * 0.5f, pos.y - fHeight * 0.5f, pos.z);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth * 0.5f, pos.y - fHeight * 0.5f, pos.z);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth * 0.5f, pos.y + fHeight * 0.5f, pos.z);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth * 0.5f, pos.y + fHeight * 0.5f, pos.z);

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2((1.0f * 0.1f * m_nNumber), 0.0f);
	pVtx[1].tex = D3DXVECTOR2((1.0f * 0.1f * m_nNumber) + 1.0f * 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((1.0f * 0.1f * m_nNumber), 1.0f);
	pVtx[3].tex = D3DXVECTOR2((1.0f * 0.1f * m_nNumber) + 1.0f * 0.1f, 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//********************************************
// 描画処理
//********************************************
void CNumber::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();  // デバイスへのポインタ

	// テクスチャのポインタ
	CTexture* pTexture = CManager::GetTexture();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// ドットの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//********************************************
// 設定処理
//********************************************
void CNumber::SetNumber(int nNumber)
{
	m_nNumber = nNumber;
}

//********************************************
// クリエイト処理
//********************************************
CNumber* CNumber::Create(D3DXVECTOR3 pos)
{
	CNumber* pNumber;

	// 数字を生成
	pNumber = new CNumber;

	// 初期化処理
	pNumber->Init();

	// 引数を代入
	pNumber->pos = pos;

	return pNumber;
}