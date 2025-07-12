//======================================================
// 
// プレイヤー処理
// Author:Takahashi Misaki
// 
//======================================================

#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "bullet.h"
#include "camera.h"
#include "object3D.h"

//********************************************
// コンストラクタ
//********************************************
CPlayer::CPlayer(int nPriority) :CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumModel = 0;
	m_bJump = false;
	m_pMotion = NULL;
	m_pShadow = NULL;

	for (int nCount = 0; nCount < MAX_MODEL; nCount++)
	{
		m_apModel[nCount] = NULL;

		m_nNumModel++;
	}
}

//********************************************
// デストラクタ
//********************************************
CPlayer::~CPlayer()
{

}

//********************************************
// 初期化処理
//********************************************
HRESULT CPlayer::Init(void)
{
	// カメラのポインタ
	CCamera* pCamera;

	// カメラの取得
	pCamera = CManager::GetCamera();

	// モーションの生成
	m_pMotion = new CMotion;

	// モーションの初期化処理
	m_pMotion->Init();

	m_pos = D3DXVECTOR3(0.0f, 0.0f, -100.0f);
	m_rot = D3DXVECTOR3(0.0f, pCamera->GetRot().y - D3DX_PI * 0.5f, 0.0f);
	m_rotDest.y = pCamera->GetRot().y - D3DX_PI * 0.5f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// モデルの生成(全パーツ分)
	m_apModel[0] = CModel::Create("data\\MODEL\\Player\\00_body.x");	// 体
	m_apModel[1] = CModel::Create("data\\MODEL\\Player\\01_head.x");	// 頭
	m_apModel[2] = CModel::Create("data\\MODEL\\Player\\04_armL.x");	// 左腕
	m_apModel[3] = CModel::Create("data\\MODEL\\Player\\05_handL.x");	// 左手
	m_apModel[4] = CModel::Create("data\\MODEL\\Player\\02_armR.x");	// 右腕
	m_apModel[5] = CModel::Create("data\\MODEL\\Player\\03_handR.x");	// 右手
	m_apModel[6] = CModel::Create("data\\MODEL\\Player\\08_legL.x");	// 左脚
	m_apModel[7] = CModel::Create("data\\MODEL\\Player\\09_footL.x");	// 左足
	m_apModel[8] = CModel::Create("data\\MODEL\\Player\\06_legR.x");	// 右脚
	m_apModel[9] = CModel::Create("data\\MODEL\\Player\\07_footR.x");	// 右足

	// 親モデルの設定(全パーツ分)
	m_apModel[0]->SetParent(NULL, D3DXVECTOR3(0.0f, 15.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));			// 体
	m_apModel[1]->SetParent(m_apModel[0], D3DXVECTOR3(0.0f, 15.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// 頭
	m_apModel[2]->SetParent(m_apModel[0], D3DXVECTOR3(-7.0f, 12.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// 左腕
	m_apModel[3]->SetParent(m_apModel[2], D3DXVECTOR3(-10.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// 左手
	m_apModel[4]->SetParent(m_apModel[0], D3DXVECTOR3(7.0f, 12.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// 右腕
	m_apModel[5]->SetParent(m_apModel[4], D3DXVECTOR3(10.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// 右手
	m_apModel[6]->SetParent(m_apModel[0], D3DXVECTOR3(-4.0f, -0.2f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// 左脚
	m_apModel[7]->SetParent(m_apModel[6], D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// 左足
	m_apModel[8]->SetParent(m_apModel[0], D3DXVECTOR3(4.0f, -0.2f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// 右脚
	m_apModel[9]->SetParent(m_apModel[8], D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// 右足

	// モーションの設定処理
	m_pMotion->SetModel(m_apModel, m_nNumModel);

	// プレイヤーのモーションタイプを設定
	m_pMotion->SetType(CMotion::TYPE_NEUTRAL);

	// カメラの位置をプレイヤーの位置に設定
	pCamera->SetPosCamera(m_pos);

	// 影の生成
	m_pShadow = CShadow::Create(m_pos.x, m_pos.z, m_rot, 50.0f, 50.0f);

	return S_OK;
}

//********************************************
// 終了処理
//********************************************
void CPlayer::Uninit(void)
{
	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{// NULLチェック
			// モデルの終了処理
			m_apModel[nCount]->Uninit();
			delete m_apModel[nCount];
			m_apModel[nCount] = NULL;
		}
	}

	if (m_pMotion != NULL)
	{// NULLチェック
		// モデルの終了処理
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = NULL;
	}

	// オブジェクト自身の破棄
	CObject::Release();
}

//********************************************
// 更新処理
//********************************************
void CPlayer::Update(void)
{
	// デバイスのポインタ
	CInputKeyboard* pInputKeyboard;
	//// サウンドのポイント
	//CSound* pSound;
	// カメラのポインタ
	CCamera* pCamera;
	// メッシュフィールドのポインタ
	CMeshfield* pMeshfield;

	// キーボードの取得
	pInputKeyboard = CManager::GetInputKeyboard();
	//// サウンドの取得
	//pSound = CManager::GetSound();
	// カメラの取得
	pCamera = CManager::GetCamera();
	// メッシュフィールドの取得
	pMeshfield = CManager::GetMeshfield();

	// 重力
	float fGravity = 1.0f;

	// 向きたい方向への差
	float fDiff = 0.0f;

	//=============================================
	// プレイヤーの移動処理
	//=============================================

	if (pInputKeyboard->GetPress(DIK_W) == true)
	{// 奥移動
		
		if (pInputKeyboard->GetPress(DIK_A) == true)
		{// 左奥移動
			m_rotDest.y = -pCamera->GetRot().y + D3DX_PI * 0.25f;

			m_move.x -= cosf(pCamera->GetRot().y + D3DX_PI * 0.25f) * 1.5f;
			m_move.z -= sinf(pCamera->GetRot().y + D3DX_PI * 0.25f) * 1.5f;
		}
		else if (pInputKeyboard->GetPress(DIK_D) == true)
		{// 右奥移動
			m_rotDest.y = -pCamera->GetRot().y + D3DX_PI * 0.75f;

			m_move.x -= cosf(pCamera->GetRot().y - D3DX_PI * 0.25f) * 1.5f;
			m_move.z -= sinf(pCamera->GetRot().y - D3DX_PI * 0.25f) * 1.5f;
		}
		else
		{// 奥移動
			m_rotDest.y = -pCamera->GetRot().y + D3DX_PI * 0.5f;

			m_move.x -= cosf(pCamera->GetRot().y) * 1.5f;
			m_move.z -= sinf(pCamera->GetRot().y) * 1.5f;
		}

		if (m_bJump == false)
		{// ジャンプしていない場合のみ
			// 走るモーションに設定
			m_pMotion->SetType(CMotion::TYPE_WALK);
		}
	}
	else if (pInputKeyboard->GetPress(DIK_S) == true)
	{// 手前移動

		if (pInputKeyboard->GetPress(DIK_A) == true)
		{// 左手前移動
			m_rotDest.y = -pCamera->GetRot().y - D3DX_PI * 0.25f;

			m_move.x += cosf(pCamera->GetRot().y - D3DX_PI * 0.25f) * 1.5f;
			m_move.z += sinf(pCamera->GetRot().y - D3DX_PI * 0.25f) * 1.5f;
		}
		else if (pInputKeyboard->GetPress(DIK_D) == true)
		{// 右手前移動
			m_rotDest.y = -pCamera->GetRot().y - D3DX_PI * 0.75f;

			m_move.x += cosf(pCamera->GetRot().y + D3DX_PI * 0.25f) * 1.5f;
			m_move.z += sinf(pCamera->GetRot().y + D3DX_PI * 0.25f) * 1.5f;
		}
		else
		{// 手前移動
			m_rotDest.y = -pCamera->GetRot().y - D3DX_PI * 0.5f;

			m_move.x += cosf(pCamera->GetRot().y) * 1.5f;
			m_move.z += sinf(pCamera->GetRot().y) * 1.5f;
		}

		if (m_bJump == false)
		{// ジャンプしていない場合のみ
			// 走るモーションに設定
			m_pMotion->SetType(CMotion::TYPE_WALK);
		}
	}
	else if (pInputKeyboard->GetPress(DIK_A) == true)
	{// 左移動
		m_rotDest.y = -pCamera->GetRot().y;

		m_move.x += sinf(pCamera->GetRot().y) * 1.5f;
		m_move.z -= cosf(pCamera->GetRot().y) * 1.5f;

		if (m_bJump == false)
		{// ジャンプしていない場合のみ
			// 走るモーションに設定
			m_pMotion->SetType(CMotion::TYPE_WALK);
		}
	}
	else if (pInputKeyboard->GetPress(DIK_D) == true)
	{// 右移動
		m_rotDest.y = -pCamera->GetRot().y - D3DX_PI;

		m_move.x -= sinf(pCamera->GetRot().y) * 1.5f;
		m_move.z += cosf(pCamera->GetRot().y) * 1.5f;

		if (m_bJump == false)
		{// ジャンプしていない場合のみ
			// 走るモーションに設定
			m_pMotion->SetType(CMotion::TYPE_WALK);
		}
	}
	else
	{
		if (m_bJump == false && m_pMotion->GetType() == CMotion::TYPE_WALK)
		{// 走るモーションの場合
			// 待機モーションに設定
			m_pMotion->SetType(CMotion::TYPE_NEUTRAL);
		}
	}

	//=============================================
	// プレイヤーのジャンプ処理
	//=============================================
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true && m_bJump == false)
	{
		// ジャンプしている状態にする
		m_bJump = true;

		m_move.y = 20.0f;

		// ジャンプモーションに設定
		m_pMotion->SetType(CMotion::TYPE_JUMP);
	}

	// 向きたい方向への差を求める
	fDiff = m_rotDest.y - m_rot.y;

	if (fDiff < -D3DX_PI)
	{// 差が-3.14を超えたとき
		fDiff += D3DX_PI * 2.0f;
	}
	else if (fDiff > D3DX_PI)
	{// 差が3.14を超えたとき
		fDiff -= D3DX_PI * 2.0f;
	}

	// 角度を更新
	m_rot.y += fDiff * 0.25f;

	// 角度の正規化
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}

	if (m_bJump == true)
	{// ジャンプしている場合
		// 重力を加算
		m_move.y -= fGravity;
	}

	// 移動の慣性
	m_move.x = m_move.x * 0.85f;
	m_move.z = m_move.z * 0.85f;

	// 移動量を加算
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	// 地面の範囲外に出たら移動量を０にする
	if (m_pos.x < pMeshfield->GetPos().x)
	{// 左端についたとき
		m_pos.x = pMeshfield->GetPos().x;

		m_move.x = 0.0f;
	}
	else if (m_pos.x > pMeshfield->GetPos().x + pMeshfield->GetSizeX())
	{// 右端についたとき
		m_pos.x = pMeshfield->GetPos().x + pMeshfield->GetSizeX() ;

		m_move.x = 0.0f;
	}

	if (m_pos.z > pMeshfield->GetPos().z)
	{// 奥についたとき
		m_pos.z = pMeshfield->GetPos().z;

		m_move.z = 0.0f;
	}
	else if (m_pos.z < pMeshfield->GetPos().z - pMeshfield->GetSizeZ())
	{// 手前についたとき
		m_pos.z = pMeshfield->GetPos().z - pMeshfield->GetSizeZ();

		m_move.z = 0.0f;
	}

	if (m_pos.y <= pMeshfield->GetPos().y)
	{// プレイヤーの位置が地面を超える時
		if (m_bJump == true)
		{// モーション切り替え
			// 着地モーションに設定
 			m_pMotion->SetType(CMotion::TYPE_LANDING);
		}

		// ジャンプしていない状態にする
		m_bJump = false;

		m_pos.y = pMeshfield->GetPos().y;
	}

	if (m_pMotion->IsFinish() == true && m_pMotion->GetType() == CMotion::TYPE_LANDING)
	{// 着地モーションが終わったら
		// 待機モーションに設定
		m_pMotion->SetType(CMotion::TYPE_NEUTRAL);
	}

	if (pCamera->GetFollow() == true)
	{// カメラ追従がONになっている時

		// カメラの位置をプレイヤーの位置に設定
		pCamera->SetPosCamera(m_pos);
	}

	// モーションの更新処理
	m_pMotion->Update();

	// 影の位置設定
	m_pShadow->SetPos(m_pos.x, m_pos.z);
}

//********************************************
// 描画処理
//********************************************
void CPlayer::Draw(void)
{
	// デバック表示のポインタ
	CDebugproc* pDebugproc;

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転してから位置移動を判定！！！！！

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を更新
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// モデルの描画処理

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		m_apModel[nCount]->Draw();
	}

	// デバック表示
	pDebugproc->Print("プレイヤーの位置 X:%.1f, Y:%.1f, Z:%.1f\n", m_pos.x, m_pos.y, m_pos.z);
	pDebugproc->Print("プレイヤーの向き X:%.1f, Y:%.1f, Z:%.1f\n", m_rot.x, m_rot.y, m_rot.z);
}

//********************************************
// 生成処理
//********************************************
CPlayer* CPlayer::Create(void)
{
	CPlayer* pPlayer;

	// プレイヤーの生成
	pPlayer = new CPlayer;

	// 初期化処理
	pPlayer->Init();

	// オブジェクトの種類の設定
	pPlayer->SetTYPE(TYPE_PLAYER);

	return pPlayer;
}

