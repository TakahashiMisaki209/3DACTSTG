//======================================================
// 
// 影の処理
// Author:Takahashi Misaki
// 
//======================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"
#include "object3D.h"

//*****************************************************************************
// 影クラス
//*****************************************************************************
class CShadow :public CObject3D
{
public:

	// コンストラクタ
	CShadow(int nPriority = 4);
	// デストラクタ
	~CShadow();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(float fPosX, float fPosZ);

	// 静的メンバ関数
	static CShadow* Create(float fPosX, float fPosZ, D3DXVECTOR3 rot, float fWidth, float fHeight);

private:
	// メンバ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス
	D3DXVECTOR3 m_pos;					// 位置
	D3DXVECTOR3 m_rot;					// 向き
	D3DXCOLOR m_col;					// 色
	float m_fWidth;						// 影の横幅
	float m_fHeight;					// 影の縦幅
	int m_nIdxTexture;					// テクスチャの番号
};

#endif