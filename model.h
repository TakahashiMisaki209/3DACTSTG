//======================================================
// 
// モデルの処理
// Author:Takahashi Misaki
// 
//======================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

// マクロ定義
#define MAX_MODEL (10)			// モデルの最大数

//******************************************************
// モデルクラス
//******************************************************
class CModel
{
public:

	// コンストラクタ
	CModel();

	// デストラクタ
	~CModel();

	// メンバ関数
	HRESULT Init(const char* pXfileName);
	void Uninit(void);
	void Draw(void);
	void SetParent(CModel* pModel, D3DXVECTOR3 Offsetpos, D3DXVECTOR3 Offsetrot);
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }
	void SetPos(D3DXVECTOR3 pos){ m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot){ m_rot = rot; }
	D3DXVECTOR3 GetOffsetPos(void) { return m_Offsetpos; }
	D3DXVECTOR3 GetOffsetRot(void) { return m_Offsetrot; }

	// 静的メンバ関数
	static CModel* Create(const char* pXfileName);

private:
	// メンバ変数
	LPD3DXMESH m_pMesh;
	LPD3DXBUFFER m_pBuffMat;
	DWORD m_dwNumMat;

	D3DXVECTOR3 m_pos;			// 位置
	D3DXVECTOR3 m_rot;			// 向き
	D3DXVECTOR3 m_Offsetpos;	// 位置(オフセット)
	D3DXVECTOR3 m_Offsetrot;	// 向き(オフセット)
	D3DXMATRIX m_mtxWorld;		// ワールドマトリックス
	CModel* m_pParent;			// 親モデルのポインタ
};

#endif