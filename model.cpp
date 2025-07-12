//======================================================
// 
// モデルの処理
// Author:Takahashi Misaki
// 
//======================================================

#include "model.h"
#include "manager.h"

//********************************************
// コンストラクタ
//********************************************
CModel::CModel()
{
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_dwNumMat = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Offsetpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Offsetrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pParent = NULL;
}

//********************************************
// デストラクタ
//********************************************
CModel::~CModel()
{
}

//********************************************
// 初期化処理
//********************************************
HRESULT CModel::Init(const char* pXfileName)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスへのポインタ

	// Xファイルの読み込み
	D3DXLoadMeshFromX(pXfileName,
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
void CModel::Uninit(void)
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
}

//********************************************
// 描画処理
//********************************************
void CModel::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DMATERIAL9 matDef;					// 現在のマテリアル保存用
	D3DXMATERIAL* pMat;						// マテリアルデータへのポインタ
	D3DXMATRIX mtxRotModel, mtxTransModel;	// 計算用マトリックス
	D3DXMATRIX mtxParent;					// 親のマトリックス

	// パーツのワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転してから位置移動を判定！！！！！

	// パーツの向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRotModel, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRotModel);

	// パーツの位置(オフセット)を反映
	D3DXMatrixTranslation(&mtxTransModel, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTransModel);

	// パーツの[親のマトリックス]を設定
	if (m_pParent != NULL)
	{// 親のモデルがある場合
		// 親モデルのマトリックスを取得する
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{// 親のモデルがない場合
		// 現在(最新)のマトリックスを取得する[ = プレイヤーのマトリックス]
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//  現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// 算出した「パーツのワールドマトリックス」と「親のマトリックス」を掛け合わせる
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// パーツのワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, NULL);// g_apTextureBlock[nCntMat]

		// パーツの描画
		m_pMesh->DrawSubset(nCntMat);

	}

	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//********************************************
// 設定処理
//********************************************
void CModel::SetParent(CModel* pModel, D3DXVECTOR3 Offsetpos, D3DXVECTOR3 Offsetrot)
{
	m_pParent = pModel;
	m_Offsetpos = Offsetpos;
	m_Offsetrot = Offsetrot;
	m_pos = Offsetpos;
	m_rot = Offsetrot;
}
//********************************************
// クリエイト処理
//********************************************
CModel* CModel::Create(const char* pXfileName)
{
	CModel* pModel;

	// オブジェクトXを生成
	pModel = new CModel;

	// 初期化処理
	pModel->Init(pXfileName);

	return pModel;
}
