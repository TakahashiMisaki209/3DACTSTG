// ==============================================
// 
// テクスチャの処理
// Aouther:Takahashi Misaki
//
// ==============================================

#include "texture.h"
#include "manager.h"

// 静的メンバ変数宣言
int CTexture::m_nNumAll = 0;

//********************************************
// コンストラクタ
//********************************************
CTexture::CTexture()
{
	for (int nCount = 0; nCount < MAX_NUMTEXTUER; nCount++)
	{
		m_apTexture[nCount] = NULL;
	}
}

//********************************************
// デストラクタ
//********************************************
CTexture::~CTexture()
{
}

//********************************************
// 読み込み処理
//********************************************
HRESULT CTexture::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスへのポインタ

	// すべてのテクスチャ読み込み
	for (int nCount = 0; nCount < MAX_NUMTEXTUER; nCount++)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			NULL,
			&m_apTexture[nCount]);
	}

	return S_OK;
}

//********************************************
// テクスチャの破棄の処理
//********************************************
void CTexture::Unload(void)
{
	// 全てのテクスチャ破棄
	for (int nCount = 0; nCount < MAX_NUMTEXTUER; nCount++)
	{
		// 頂点バッファの破棄
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//********************************************
// 指定テクスチャの読み込み処理
//********************************************
int CTexture::Register(const char* pFilename)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスへのポインタ

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		pFilename,
		&m_apTexture[m_nNumAll]);

	return m_nNumAll++;

}