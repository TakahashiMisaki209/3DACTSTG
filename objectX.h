//======================================================
// 
// Xファイルの処理
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "main.h"
#include "object.h"

#define MAX_TEXUTE_ALL (10)

//*****************************************************************************
// オブジェクトXクラス
//*****************************************************************************
class CObjectX :public CObject
{
public:

	// コンストラクタ
	CObjectX(int nPriority = 3);
	// デストラクタ
	~CObjectX();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CObjectX* Create(void);

private:

	// メンバ変数
	LPD3DXMESH m_pMesh;
	LPD3DXBUFFER m_pBuffMat;
	DWORD m_dwNumMat;
	D3DXMATRIX m_mtxWorld;
	D3DXVECTOR3 m_pos;			// 位置
	D3DXVECTOR3 m_rot;			// 向き

	// 静的メンバ変数
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXUTE_ALL];	// テクスチャへのポインタ

};
#endif