//======================================================
// 
// マネージャー処理
// Author:Takahashi Misaki
// 
//======================================================

#include "manager.h"

// 静的メンバ変数
CRenderer* CManager::m_pRenderer = NULL;
CInputKeyboard* CManager::m_pkeyboard = NULL;
CInputMouse* CManager::m_pMouse = NULL;
CSound* CManager::m_pSound = NULL;
CCamera* CManager::m_pCamera = NULL;
CLight* CManager::m_pLight = NULL;
CTexture* CManager::m_pTexture = NULL;
CPlayer* CManager::m_pPlayer = NULL;
CObject3D* CManager::m_pObject3D = NULL;
CSky* CManager::m_Sky = NULL;
CMeshfield* CManager::m_pMeshfield = NULL;

//********************************************
// コンストラクタ
//********************************************
CManager::CManager()
{
	m_pRenderer = NULL;
	m_pkeyboard = NULL;
	m_pMouse = NULL;
	m_pSound = NULL;
	m_pCamera = NULL;
	m_pLight = NULL;
	m_pTexture = NULL;
	m_pPlayer = NULL;
	m_pObject3D = NULL;
	m_Sky = NULL;
}
//********************************************
// デストラクタ
//********************************************
CManager::~CManager()
{
}

//********************************************
// 初期化処理
//********************************************
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// レンダラーを生成
	m_pRenderer = new CRenderer;
	// キーボードを生成
	m_pkeyboard = new CInputKeyboard;
	// マウスを生成
	m_pMouse = new CInputMouse;
	// サウンドを生成
	m_pSound = new CSound;
	// カメラを生成
	m_pCamera = new CCamera;
	// ライトを生成
	m_pLight = new CLight;
	// テクスチャを生成
	m_pTexture = new CTexture;

	// レンダラーの初期化処理
	if (FAILED(m_pRenderer->Init(hInstance, hWnd, TRUE)))
	{// 初期化処理が失敗したとき
		return-1;
	}

	// キーボードの初期化処理
	if (FAILED(m_pkeyboard->Init(hInstance, hWnd)))
	{// 初期化処理が失敗したとき
		return-1;
	}

	// マウスの初期化処理
	if (FAILED(m_pMouse->Init(hInstance, hWnd)))
	{// 初期化処理が失敗したとき
		return-1;
	}

	// サウンドの初期化処理
	if (FAILED(m_pSound->Init(hWnd)))
	{// 初期化処理が失敗したとき
		return-1;
	}

	// カメラの初期化処理
	if (FAILED(m_pCamera->Init()))
	{// 初期化処理が失敗したとき
		return-1;
	}

	// ライトの初期化処理
	if (FAILED(m_pLight->Init()))
	{// 初期化処理が失敗したとき
		return-1;
	}

	// テクスチャの読み込み処理
	m_pTexture->Load();

	// プレイヤーの生成
	m_pPlayer = CPlayer::Create();

	// タイマーの生成
	CTimer::Create();

	// スコアの生成
	CScore::Create();

	// メッシュフィールドの生成
	m_pMeshfield = CMeshfield::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2000.0f, 2000.0f, 100, 100, "data\\TEXTURE\\ground000.jpg");

	// 空の生成
	CSky::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2000.0f, 2000.0f, 50, 50, "data\\TEXTURE\\sky000.jpeg");

	// ビルボードの生成
	CObjectBillboard::Create(D3DXVECTOR3(-100.0f, 0.0f, 0.0f));
	CObjectBillboard::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f));

	return S_OK;
}

//********************************************
// 終了処理
//********************************************
void CManager::Uninit(void)
{
	// 全てのオブジェクトの破棄
	CObject::ReleaseAll();

	// テクスチャの終了処理
	m_pTexture->Unload();

	// テクスチャの破棄
	if (m_pLight != NULL)
	{
		m_pTexture->Unload();
		delete m_pTexture;
		m_pTexture = NULL;
	}

	// ライトの破棄
	if (m_pLight != NULL)
	{
		// 終了処理
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	// カメラの破棄
	if (m_pCamera != NULL)
	{
		// 終了処理
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

	// サウンドの破棄
	if (m_pSound != NULL)
	{
		// 終了処理
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}

	// マウスの破棄
	if (m_pMouse != NULL)
	{
		// 終了処理
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = NULL;
	}

	// キーボードの破棄
	if (m_pkeyboard != NULL)
	{
		// 終了処理
		m_pkeyboard->Uninit();
		delete m_pkeyboard;
		m_pkeyboard = NULL;
	}

	// レンダラーの破棄
	if (m_pRenderer != NULL)
	{
		// 終了処理
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//********************************************
// 更新処理
//********************************************
void CManager::Update(void)
{
	// キーボードの更新処理
	m_pkeyboard->Update();
	// マウスの更新処理
	m_pMouse->Update();
	// レンダラーの更新処理
	m_pRenderer->Update();
	// カメラの更新処理
	m_pCamera->Update();
	// ライトの更新処理
	m_pLight->Update();
}

//********************************************
// 描画処理
//********************************************
void CManager::Draw(void)
{
	// レンダラーの描画処理
	m_pRenderer->Draw();
}
