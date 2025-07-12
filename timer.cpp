//======================================================
// 
// タイマー処理
// Author:Takahashi Misaki
// 
//======================================================

#include "timer.h"
#include "manager.h"

// 静的メンバ変数宣言
CNumber* CTimer::m_apNumer[MAX_COLUMET] = {};

//********************************************
// コンストラクタ
//********************************************
CTimer::CTimer(int nPriority) :CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntTime = 0;
}

//********************************************
// デストラクタ
//********************************************
CTimer::~CTimer()
{
}

//********************************************
// 初期化処理
//********************************************
HRESULT CTimer::Init(void)
{
	m_pos = D3DXVECTOR3(SCREEN_WIDTH * 0.4f, 40.0f, 0.0f);

	int Time = m_nCntTime;
	int number1 = 100, number2 = 10;

	for (int nCount = 0; nCount < MAX_COLUMET; nCount++)
	{
		m_apNumer[nCount] = CNumber::Create(m_pos);

		m_pos.x += 60.0f;
	}

	for (int nCount = 0; nCount < MAX_COLUMET; nCount++)
	{

		if (nCount == 0)
		{
			Time = m_nCntTime / number1;
		}
		else
		{
			Time = m_nCntTime % number1 / number2;
			number1 = number1 / 10;
			number2 = number2 / 10;
		}

		m_apNumer[nCount]->SetNumber(Time);
	}

	return S_OK;
}

//********************************************
// 終了処理
//********************************************
void CTimer::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_COLUMET; nCount++)
	{
		if (m_apNumer[nCount] != NULL)
		{
			// ナンバーの終了処理
			m_apNumer[nCount]->Uninit();
			delete m_apNumer[nCount];
			m_apNumer[nCount] = NULL;
		}
	}

	// オブジェクト自身の破棄
	CObject::Release();
}

//********************************************
// 更新処理
//********************************************
void CTimer::Update(void)
{
	// フレームをカウントする変数
	static int nCount = 0;
	int Time = m_nCntTime;
	int number1 = 100, number2 = 10;

	// カウントを一つ進める
	nCount++;

	if (nCount >= MAX_FRAME)
	{// カウントが最大フレームになったら

		// タイムを減らす
		m_nCntTime--;

		for (int nCount = 0; nCount < MAX_COLUMET; nCount++)
		{

			if (nCount == 0)
			{
				Time = m_nCntTime / number1;
			}
			else
			{
				Time = m_nCntTime % number1 / number2;
				number1 = number1 / 10;
				number2 = number2 / 10;
			}

			m_apNumer[nCount]->SetNumber(Time);
		}

		// カウントを初期値に戻す
		nCount = 0;
	}

	if (m_nCntTime <= 0)
	{// タイムが0になった時
		m_nCntTime = MAX_TIME;
	}

	for (int nCount = 0; nCount < MAX_COLUMET; nCount++)
	{
		// ナンバーの更新処理
		m_apNumer[nCount]->Update();
	}
}

//********************************************
// 描画処理
//********************************************
void CTimer::Draw(void)
{
	for (int nCount = 0; nCount < MAX_COLUMET; nCount++)
	{
		// ナンバーの描画処理
		m_apNumer[nCount]->Draw();
	}
}

//********************************************
// クリエイト処理
//********************************************
CTimer* CTimer::Create(void)
{
	CTimer* pTimer;

	// タイマーを生成
	pTimer = new CTimer;

	// タイムを設定
	pTimer->m_nCntTime = MAX_TIME;

	// 初期化処理
	pTimer->Init();

	return pTimer;
}
