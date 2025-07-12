//======================================================
// 
// カメラの処理
// Author:Takahashi Misaki
// 
//======================================================

#include "camera.h"
#include "input.h"
#include "manager.h"
#include "player.h"

//********************************************
// コンストラクタ
//********************************************
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 視点
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 注視点
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			// 上方向ベクトル
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向き
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 移動量
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の視点
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の注視点
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向き
	m_fDistance = 0.0f;								// 視点から注視点の距離
	m_bFollow = true;								// カメラを使用しているかどうか
	m_bCameraV = false;								// 視点と注視点の操作の切り替え
}

//********************************************
// デストラクタ
//********************************************
CCamera::~CCamera()
{

}

//********************************************
// 初期化処理
//********************************************
HRESULT CCamera::Init(void)
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// 視点
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// 注視点
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);							// 上方向(固定)
	m_rot = D3DXVECTOR3(D3DX_PI * 0.5f, -D3DX_PI * 0.5f, 0.0f);		// 向き
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// 移動量
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 目的の視点
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 目的の注視点
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 目的の向き
	m_fDistance = 200.0f;											// 視点と注視点までの距離
	m_bCameraV = true;												// 操作できるカメラ(視点)

	return S_OK;
}
//********************************************
// 終了処理
//********************************************
void CCamera::Uninit(void)
{

}
//********************************************
// 更新処理
//********************************************
void CCamera::Update(void)
{
	// キーボードのポインタ
	CInputKeyboard* pInputKeyboard;
	// マウスのポインタ
	CInputMouse* pInputMouse;
	// プレイヤーのポインタ
	CPlayer* pPlayer;
	// メッシュフィールドのポインタ
	CMeshfield* pMeshfield;

	// キーボードの取得
	pInputKeyboard = CManager::GetInputKeyboard();
	// マウスの取得
	pInputMouse = CManager::GetInputMouse();
	// プレイヤーの取得
	pPlayer = CManager::GetPlayer();
	// メッシュフィールドの取得
	pMeshfield = CManager::GetMeshfield();

	// 視点移動の速さ
	float fSpeed = 5.0f;

	//=================================================
	// カメラ使用状態切り替え
	//=================================================
	if (pInputKeyboard->GetTrigger(DIK_F2) == true)
	{// SPACEキーを押した時
		Init();

		m_bFollow = m_bFollow ? false : true;
	}

	if (m_bFollow == false)
	{// カメラが手動処理の時

		//=================================================
		// 注視点の旋回(横回転)
		//=================================================
		if (pInputKeyboard->GetPress(DIK_Q) == true)
		{// 左回転
			m_rot.y += 0.03f;

			// 視点操作を注視点に切り替える
			m_bCameraV = false;
		}

		if (pInputKeyboard->GetPress(DIK_E) == true)
		{// 右回転
			m_rot.y -= 0.03f;

			// 視点操作を注視点に切り替える
			m_bCameraV = false;
		}

		//=================================================
		// 注視点の旋回(縦回転)
		//=================================================
		if (pInputKeyboard->GetPress(DIK_R) == true)
		{// 上回転
			m_rot.x += 0.03f;

			// 視点操作を注視点に切り替える
			m_bCameraV = false;
		}

		if (pInputKeyboard->GetPress(DIK_F) == true)
		{// 下回転
			m_rot.x -= 0.03f;

			// 視点操作を注視点に切り替える
			m_bCameraV = false;
		}

		//=================================================
		// 視点の旋回(横回転)
		//=================================================
		if (pInputKeyboard->GetPress(DIK_Z) == true)
		{// 左回転
			m_rot.y += 0.03f;

			// 視点操作を視点に切り替える
			m_bCameraV = true;
		}

		if (pInputKeyboard->GetPress(DIK_C) == true)
		{// 右回転
			m_rot.y -= 0.03f;

			// 視点操作を視点に切り替える
			m_bCameraV = true;
		}

		//=================================================
		// 視点の旋回(縦回転)
		//=================================================
		if (pInputKeyboard->GetPress(DIK_T) == true)
		{// 上回転
			m_rot.x -= 0.03f;

			// 視点操作を視点に切り替える
			m_bCameraV = true;
		}

		if (pInputKeyboard->GetPress(DIK_G) == true)
		{// 下回転
			m_rot.x += 0.03f;

			// 視点操作を視点に切り替える
			m_bCameraV = true;
		}

		//=================================================
		// 視点の移動
		//=================================================
		if (pInputKeyboard->GetPress(DIK_LEFT) == true)
		{// 左移動
			m_move.x = sinf(m_rot.y) * fSpeed;
			m_move.z = -cosf(m_rot.y) * fSpeed;
		}

		if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
		{// 右移動
			m_move.x = -sinf(m_rot.y) * fSpeed;
			m_move.z = cosf(m_rot.y) * fSpeed;
		}

		if (pInputKeyboard->GetPress(DIK_UP) == true)
		{// 前移動
			m_move.x = -cosf(m_rot.y) * fSpeed;
			m_move.z = -sinf(m_rot.y) * fSpeed;
		}

		if (pInputKeyboard->GetPress(DIK_DOWN) == true)
		{// 後移動
			m_move.x = cosf(m_rot.y) * fSpeed;
			m_move.z = sinf(m_rot.y) * fSpeed;
		}

		// 角度の正規化
		if (m_rot.x > D3DX_PI - 0.01f)
		{
			m_rot.x = D3DX_PI - 0.01f;
		}
		else if (m_rot.x < 0.01f)
		{
			m_rot.x = 0.0f + 0.01f;
		}

		if (m_rot.y > D3DX_PI)
		{
			m_rot.y -= D3DX_PI * 2.0f;
		}
		else if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2.0f;
		}

		// 移動の慣性
		m_move = m_move * 0.85f;

		if (m_bCameraV == true)
		{// 視点操作の時
			// 移動量を加算
			m_posR += m_move;

			// 視点の位置を球座標に変換
			m_posV.x = m_posR.x + sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
			m_posV.y = m_posR.y + cosf(m_rot.x) * m_fDistance;
			m_posV.z = m_posR.z + sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
		}
		else if (m_bCameraV == false)
		{// 注視点操作の時
			// 移動量を加算
			m_posV += m_move;

			// 注視点の位置を球座標に変換
			m_posR.x = m_posV.x + sinf(m_rot.x) * cosf(m_rot.y) * -m_fDistance;
			m_posR.y = m_posV.y + cosf(m_rot.x) * -m_fDistance;
			m_posR.z = m_posV.z + sinf(m_rot.x) * sinf(m_rot.y) * -m_fDistance;
		}
	}
	else if (m_bFollow == true)
	{// カメラが追従処理の時

		//=================================================
		// 視点の横旋回(キーボード)
		//=================================================
		if (pInputKeyboard->GetPress(DIK_Q) == true)
		{// 左回転
			m_rot.y += 0.03f;
		}

		if (pInputKeyboard->GetPress(DIK_E) == true)
		{// 右回転
			m_rot.y -= 0.03f;
		}

		if (pInputKeyboard->GetPress(DIK_R) == true)
		{// 上回転
			m_rot.x -= 0.03f;
		}

		if (pInputKeyboard->GetPress(DIK_F) == true)
		{// 下回転
			m_rot.x += 0.03f;

		}

		////=================================================
		//// 注視点の旋回(マウス)
		////=================================================
		//// 左右回転
		//m_rot.y -= pInputMouse->GetMove().x * 0.003f;

		//// 上下回転
		//m_rot.x -= pInputMouse->GetMove().y * 0.003f;

		// 角度の正規化
		if (m_rot.x > D3DX_PI - 0.01f)
		{
			m_rot.x = D3DX_PI - 0.01f;
		}
		else if (m_rot.x < 0.01f)
		{
			m_rot.x = 0.0f + 0.01f;
		}

		if (m_rot.y > D3DX_PI)
		{
			m_rot.y -= D3DX_PI * 2.0f;
		}
		else if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2.0f;
		}

		// 移動量を加算
		m_posR += m_move;

		// 視点の位置を球座標に変換
		m_posV.x = m_posR.x + sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
		m_posV.y = m_posR.y + cosf(m_rot.x) * m_fDistance;
		m_posV.z = m_posR.z + sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
	}

	// 視点の位置がポリゴンの高さを下回るとき
	if (m_posV.y <= pMeshfield->GetPos().y)
	{
		m_posV.y = pMeshfield->GetPos().y;
	}

}
//********************************************
// 設定処理
//********************************************
void CCamera::SetCamera(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// デバック表示のポインタ
	CDebugproc* pDebugproc;

	// ビューマトリックスの初期化
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIsIdentity(&m_mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		3000.0f);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// デバック表示
	if (m_bFollow == true)
	{
		pDebugproc->Print("[F2] カメラの追従:ON\n");
	}
	else if (m_bFollow == false)
	{
		pDebugproc->Print("[F2] カメラの追従:OFF\n");

		pDebugproc->Print("--------カメラの移動方法--------\n");
		pDebugproc->Print("視点移動：矢印キー\n");
		pDebugproc->Print("視点縦回転：T [上回転], G [下回転]\n");
		pDebugproc->Print("視点横回転：Z [左回転], C [右回転]\n");
		pDebugproc->Print("注視点縦回転：R [上回転], F [下回転]\n");
		pDebugproc->Print("注視点横回転：Q [左回転], E [右回転]\n\n");


	}

	// 視点の位置と向き
	pDebugproc->Print("視点の位置:X %.1f, Y %.1f, Z %.1f\n", m_posV.x, m_posV.y, m_posV.z);
	pDebugproc->Print("視点の向き:X %.1f, Y %.1f, Z %.1f\n", m_rot.x, m_rot.y, m_rot.z);
	// 注視点の位置
	pDebugproc->Print("注視点の位置:X %.1f, Y %.1f, Z %.1f\n", m_posR.x, m_posR.y, m_posR.z);

}
//********************************************
// カメラの位置の設定処理
//********************************************
void CCamera::SetPosCamera(D3DXVECTOR3 pos)
{
	m_posV = pos + D3DXVECTOR3(0.0f, 70.f, -200.0f);
	m_posR = pos + D3DXVECTOR3(0.0f, 70.f, 0.0f);
}

//********************************************
// カメラの移動量の設定処理
//********************************************
void CCamera::SetMoveCamera(D3DXVECTOR3 move)
{
	m_move = move;
}