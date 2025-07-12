// ==============================================
// 
// 空の処理
// Aouther:Takahashi Misaki
//
// ==============================================

#include "sky.h"
#include "manager.h"

//********************************************
// コンストラクタ
//********************************************
CSky::CSky(int nPriority) :CObject(nPriority)
{
	m_pVtxBuff = NULL;						// 頂点バッファのポインタ
	m_pIdxBuff = NULL;						// インデックスバッファのポインタ
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	m_nIdxTexture = 0;						// テクスチャのインデックス
	m_fRadius = 0;							// 円柱の半径
	m_fHeight = 0;							// 円柱の縦幅
	m_nIntervalX = 0;						// 横の頂点数
	m_nIntervalY = 0;						// 縦の頂点数
	m_nVertex = 0;							// 頂点数
	m_nPolygon = 0;							// ポリゴン数
	m_nIdx = 0;								// インデック
}

//********************************************
// デストラクタ
//********************************************
CSky::~CSky()
{
}

//********************************************
// 初期化処理
//********************************************
HRESULT CSky::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスへのポインタ

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nVertex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nIdx,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;

	// 現在の頂点番号
	int nVtx = 0;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntY = 0; nCntY <= m_nIntervalY; nCntY++)
	{
		for (int nCntX = 0; nCntX <= m_nIntervalX; nCntX++)
		{
			// 頂点を置く角度を計算
			m_rot.y = D3DX_PI - (D3DX_PI / (float)(m_nIntervalX / 2)) * nCntX;

			// 角度の正規化
			if (m_rot.y < D3DX_PI)
			{
				m_rot.y += D3DX_PI * 2.0f;
			}


			// 頂点座標の計算
			float fPosX = cosf(m_rot.y) * m_fRadius;
			float fPosY = ((float)m_fHeight / (float)m_nIntervalY) * (float)nCntY;
			float fPosZ = sinf(m_rot.y) * m_fRadius;

			// テクスチャ座標の計算
			float fTexX = (float)m_fRadius / ((float)m_fRadius * (float)m_nIntervalX) * (float)nCntX;
			float fTexY = (float)m_fHeight / ((float)m_fHeight * (float)m_nIntervalY) * (float)nCntY;

			// 頂点座標の設定
			pVtx[nVtx].pos.x = m_pos.x + fPosX;
			pVtx[nVtx].pos.y = m_pos.y + (-fPosY);
			pVtx[nVtx].pos.z = m_pos.z + fPosZ;

			// 各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
			pVtx[nVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 頂点カラーの設定
			pVtx[nVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[nVtx].tex.x = fTexX;
			pVtx[nVtx].tex.y = fTexY;

			nVtx++;
		}
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	WORD* pIdx;

	// インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// インデックス
	int nIdxA = m_nIntervalX + 1;
	int nIdxB = 0;
	// 現在のインデックス番号
	int nIdx = 0;

	for (int nCntY = 0; nCntY < m_nIntervalY; nCntY++)
	{
		for (int nCntX = 0; nCntX <= m_nIntervalX; nCntX++)
		{
			// pIdxに下段と上段の頂点番号を設定
			pIdx[nIdx] = nIdxA;			// 下段
			pIdx[nIdx + 1] = nIdxB;		// 上段

			// 番号を設定した数分進める
			nIdx += 2;

			// インデックスを一つ進める
			nIdxA++;
			nIdxB++;
		}

		// 縮退ポリゴン用の頂点番号設定を追加
		if (nCntY < m_nIntervalY - 1)
		{
			// pIdxに下段と上段の頂点番号を設定
			pIdx[nIdx] = nIdxB - 1;		// 下段
			pIdx[nIdx + 1] = nIdxA;		// 上段

			// 番号を設定した数分進める
			nIdx += 2;
		}

	}

	// インデックスバッファのアンロック
	m_pIdxBuff->Unlock();

	return S_OK;
}

//********************************************
// 終了処理
//********************************************
void CSky::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// インデックスバッファの破棄
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	// オブジェクト自身の破棄
	CObject::Release();
}

//********************************************
// 更新処理
//********************************************
void CSky::Update(void)
{
	// キーボードのポインタ
	CInputKeyboard* pInputKeyboard;

	// キーボードの取得
	pInputKeyboard = CManager::GetInputKeyboard();
}

//********************************************
// 描画処理
//********************************************
void CSky::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// テクスチャのポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// ワールドマトリックスの固定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	// テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// 空の描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVertex, 0, m_nPolygon);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//********************************************
// 空の設定処理
//********************************************
void CSky::SetSky(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Radius, float fHeight, int nIntervalX, int nIntervalY, const char* textname)
{
	// テクスチャのポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// テクスチャの指定
	m_nIdxTexture = pTexture->Register(textname);

	m_fRadius = Radius;																// 円柱の半径
	m_fHeight = fHeight;															// 円柱の縦幅
	m_pos = D3DXVECTOR3(pos.x, m_fHeight, pos.z);									// 位置
	m_rot = rot;																	// 向き
	m_nIntervalX = nIntervalX;														// 横の頂点数
	m_nIntervalY = nIntervalY;														// 縦の頂点数
	m_nVertex = (nIntervalX + 1) * (nIntervalY + 1);								// 頂点数
	m_nPolygon = (m_nIntervalX * m_nIntervalY * 2) + ((m_nIntervalY - 1) * 4);		// ポリゴン数
	m_nIdx = m_nPolygon + 2;														// インデック

}

//********************************************
// クリエイト処理
//********************************************
CSky* CSky::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Radius, float fHeight, int nIntervalX, int nIntervalY, const char* textname)
{
	CSky* pSky;

	// 空を生成
	pSky = new CSky;

	// 空の設定処理
	pSky->SetSky(pos, rot, Radius, fHeight, nIntervalX, nIntervalY, textname);

	// 初期化処理
	pSky->Init();

	return pSky;
}
