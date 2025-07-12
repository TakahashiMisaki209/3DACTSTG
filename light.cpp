// ==============================================
// 
// ���C�g�̏���
// Aouther:Takahashi Misaki
//
// ==============================================

#include "light.h"
#include "manager.h"

//********************************************
// �R���X�g���N�^
//********************************************
CLight::CLight()
{
	// ���C�g���N���A����
	ZeroMemory(&m_aLight, sizeof(m_aLight));
}

//********************************************
// �f�X�g���N�^
//********************************************
CLight::~CLight()
{
}

//********************************************
// ����������
//********************************************
HRESULT CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�ւ̃|�C���^

	D3DXVECTOR3 vecDir[MAX_LIGHT];	// ���C�g�̕����x�N�g��

	// ���C�g���N���A����
	ZeroMemory(&m_aLight, sizeof(m_aLight));

	// ���C�g�̕�����ݒ�
	vecDir[0] = D3DXVECTOR3(0.2f, -0.48f, -0.4f);
	vecDir[1] = D3DXVECTOR3(-0.6f, -0.39f, 0.4f);
	vecDir[2] = D3DXVECTOR3(1.0f, -0.55f, 0.4f);

	for (int nCount = 0; nCount < MAX_LIGHT; nCount++)
	{
		// ���C�g�̎�ނ�ݒ�
		m_aLight[nCount].Type = D3DLIGHT_DIRECTIONAL;

		// ���C�g�̊g�U����ݒ�
		m_aLight[nCount].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ���K������(�傫���P�̃x�N�g���ɂ���)
		for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
		{
			D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);
		}

		m_aLight[nCount].Direction = vecDir[nCount];

		// ���C�g��ݒ肷��
		pDevice->SetLight(nCount, &m_aLight[nCount]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCount, TRUE);
	}

	return S_OK;
}
//********************************************
// �I������
//********************************************
void CLight::Uninit(void)
{

}
//********************************************
// �X�V����
//********************************************
void CLight::Update(void)
{

}
