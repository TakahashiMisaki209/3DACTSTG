//======================================================
// 
// ��̏���
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _SKY_H_
#define _SKY_H_

#include "main.h"
#include "object.h"

//*****************************************************************************
// �X�J�C�N���X
//*****************************************************************************
class CSky :public CObject
{
public:

	// �R���X�g���N�^
	CSky(int nPriority = 1);
	// �f�X�g���N�^
	~CSky();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPos(void) { return m_pos; };		// �ʒu���̎擾
	void SetSky(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Radius, float fHeight, int nIntervalX, int nIntervalY, const char* textname);

	// �ÓI�����o�֐�
	static CSky* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Radius, float fHeight, int nIntervalX, int nIntervalY, const char* textname);

private:
	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;					// ���_���W
	D3DXVECTOR3 m_rot;					// ����
	float m_fRadius;					// �~���̔��a
	float m_fHeight;					// �~���̏c��
	int m_nIntervalX;					// ���̒��_��
	int m_nIntervalY;					// �c�̒��_��
	int m_nVertex;						// ���_��
	int m_nPolygon;						// �|���S����
	int m_nIdx;							// �C���f�b�N�X��
	int m_nIdxTexture;					// �e�N�X�`���̔ԍ�

};

#endif