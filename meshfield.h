//======================================================
// 
// ���b�V���t�B�[���h�̏���
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"
#include "object.h"

//*****************************************************************************
// ���b�V���t�B�[���h�N���X
//*****************************************************************************
class CMeshfield:public CObject
{
public:

	// �R���X�g���N�^
	CMeshfield(int nPriority = 1);
	// �f�X�g���N�^
	~CMeshfield();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPos(void) { return m_pos; };		// �ʒu���̎擾
	float GetSizeX(void) { return m_fWidth; };		// �����̎擾
	float GetSizeZ(void) { return m_fHeight; };		// ���s�̎擾
	void SetMeshfield(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Width, float fHeight, int nIntervalX, int nIntervalZ, const char* textname);

	// �ÓI�����o�֐�
	static CMeshfield* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Width, float fHeight, int nIntervalX, int nIntervalZ, const char* textname);

private:

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;					// ���_���W
	D3DXVECTOR3 m_rot;					// ����
	int m_nIdxTexture;					// �e�N�X�`���̔ԍ�
	bool m_bWireFrame;					// ���C���[�t���[�����I���ɂ��邩�ǂ���
	float m_fWidth;						// �|���S���̉���
	float m_fHeight;					// �|���S���̏c��
	int m_nIntervalX;					// ���̒��_��
	int m_nIntervalZ;					// �c�̒��_��
	int m_nVertex;						// �S�Ă̒��_��
	int m_nPolygon;						// �|���S����
	int m_nIdx;							// �C���f�b�N�X��

};
#endif