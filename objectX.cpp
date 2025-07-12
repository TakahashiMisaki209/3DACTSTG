//======================================================
// 
// Xファイルの処理
// Author:Takahashi Misaki
// 
//======================================================

#include "objectX.h"
#include "manager.h"

//********************************************
// コンストラクタ
//********************************************
CObjectX::CObjectX(int nPriority) :CObject(nPriority)
{
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_dwNumMat = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//********************************************
// デストラクタ
//********************************************
CObjectX::~CObjectX()
{
}

//********************************************
// 初期化処理
//********************************************
HRESULT CObjectX::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスへのポインタ

	m_pos = D3DXVECTOR3(0.0f, 0.0f, -100.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\Player\\00_body.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	return S_OK;
}

//********************************************
// 終了処理
//********************************************
void CObjectX::Uninit(void)
{
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// マテリアルの破棄
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	// オブジェクト自身の破棄
	CObject::Release();
}

//********************************************
// 更新処理
//********************************************
void CObjectX::Update(void)
{

}

//********************************************
// 描画処理
//********************************************
void CObjectX::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL* pMat;							// マテリアルデータへのポインタ

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転してから位置移動を判定！！！！！

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を更新
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの固定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//  現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, NULL);// g_apTextureBlock[nCntMat]

		// ブロックパーツの描画
		m_pMesh->DrawSubset(nCntMat);

	}

	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//********************************************
// クリエイト処理
//********************************************
CObjectX* CObjectX::Create(void)
{
	CObjectX* pObjectX;

	// オブジェクトXを生成
	pObjectX = new CObjectX;

	// 初期化処理
	pObjectX->Init();

	return pObjectX;
}
