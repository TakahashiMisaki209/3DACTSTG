// ==============================================
// 
// ライトの処理
// Aouther:Takahashi Misaki
//
// ==============================================

#include "light.h"
#include "manager.h"

//********************************************
// コンストラクタ
//********************************************
CLight::CLight()
{
	// ライトをクリアする
	ZeroMemory(&m_aLight, sizeof(m_aLight));
}

//********************************************
// デストラクタ
//********************************************
CLight::~CLight()
{
}

//********************************************
// 初期化処理
//********************************************
HRESULT CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスへのポインタ

	D3DXVECTOR3 vecDir[MAX_LIGHT];	// ライトの方向ベクトル

	// ライトをクリアする
	ZeroMemory(&m_aLight, sizeof(m_aLight));

	// ライトの方向を設定
	vecDir[0] = D3DXVECTOR3(0.2f, -0.48f, -0.4f);
	vecDir[1] = D3DXVECTOR3(-0.6f, -0.39f, 0.4f);
	vecDir[2] = D3DXVECTOR3(1.0f, -0.55f, 0.4f);

	for (int nCount = 0; nCount < MAX_LIGHT; nCount++)
	{
		// ライトの種類を設定
		m_aLight[nCount].Type = D3DLIGHT_DIRECTIONAL;

		// ライトの拡散光を設定
		m_aLight[nCount].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// 正規化する(大きさ１のベクトルにする)
		for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
		{
			D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);
		}

		m_aLight[nCount].Direction = vecDir[nCount];

		// ライトを設定する
		pDevice->SetLight(nCount, &m_aLight[nCount]);

		// ライトを有効にする
		pDevice->LightEnable(nCount, TRUE);
	}

	return S_OK;
}
//********************************************
// 終了処理
//********************************************
void CLight::Uninit(void)
{

}
//********************************************
// 更新処理
//********************************************
void CLight::Update(void)
{

}
