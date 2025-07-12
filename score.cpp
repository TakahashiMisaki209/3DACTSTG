//======================================================
// 
// スコアの処理
// Author:Takahashi Misaki
// 
//======================================================

#include "score.h"
#include "manager.h"

// 静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CScore::m_pTexture = NULL;
CNumber* CScore::m_apNumer[MAX_COLUMES] = {};
int CScore::m_nScore = 0;

//********************************************
// コンストラクタ
//********************************************
CScore::CScore(int nPriority) :CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//********************************************
// デストラクタ
//********************************************
CScore::~CScore()
{
}

//********************************************
// 初期化処理
//********************************************
HRESULT CScore::Init(void)
{
	// 位置の設定
	m_pos = D3DXVECTOR3(SCREEN_WIDTH * 0.65f, 40.0f, 0.0f);

	int nScore = m_nScore;
	int number1 = 10000000, number2 = 1000000;

	for (int nCount = 0; nCount < MAX_COLUMES; nCount++)
	{
		m_apNumer[nCount] = CNumber::Create(m_pos);

		m_pos.x += 60.0f;

		if (nCount == 0)
		{
			nScore = m_nScore / number1;
		}
		else
		{
			nScore = m_nScore % number1 / number2;
			number1 = number1 / 10;
			number2 = number2 / 10;
		}

		m_apNumer[nCount]->SetNumber(nScore);
	}

	return S_OK;
}

//********************************************
// 終了処理
//********************************************
void CScore::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_COLUMES; nCount++)
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
void CScore::Update(void)
{
	int nScore = m_nScore;
	int number1 = 10000000, number2 = 1000000;

	for (int nCount = 0; nCount < MAX_COLUMES; nCount++)
	{
		if (nCount == 0)
		{
			nScore = m_nScore / number1;
		}
		else
		{
			nScore = m_nScore % number1 / number2;
			number1 = number1 / 10;
			number2 = number2 / 10;
		}

		// ナンバーの設定処理
		m_apNumer[nCount]->SetNumber(nScore);

		// ナンバーの更新処理
		m_apNumer[nCount]->Update();
	}
}

//********************************************
// 描画処理
//********************************************
void CScore::Draw(void)
{
	for (int nCount = 0; nCount < MAX_COLUMES; nCount++)
	{
		// ナンバーの描画処理
		m_apNumer[nCount]->Draw();
	}
}

//********************************************
// 加算処理
//********************************************
void CScore::AddScore(int nScore)
{
	m_nScore += nScore;
}

//********************************************
// クリエイト処理
//********************************************
CScore* CScore::Create(void)
{
	CScore* pScore;

	// スコアを生成
	pScore = new CScore;

	// 初期化処理
	pScore->Init();

	return pScore;
}