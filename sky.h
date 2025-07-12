//======================================================
// 
// 空の処理
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _SKY_H_
#define _SKY_H_

#include "main.h"
#include "object.h"

//*****************************************************************************
// スカイクラス
//*****************************************************************************
class CSky :public CObject
{
public:

	// コンストラクタ
	CSky(int nPriority = 1);
	// デストラクタ
	~CSky();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPos(void) { return m_pos; };		// 位置情報の取得
	void SetSky(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Radius, float fHeight, int nIntervalX, int nIntervalY, const char* textname);

	// 静的メンバ関数
	static CSky* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Radius, float fHeight, int nIntervalX, int nIntervalY, const char* textname);

private:
	// メンバ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// インデックスバッファへのポインタ
	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス
	D3DXVECTOR3 m_pos;					// 頂点座標
	D3DXVECTOR3 m_rot;					// 向き
	float m_fRadius;					// 円柱の半径
	float m_fHeight;					// 円柱の縦幅
	int m_nIntervalX;					// 横の頂点数
	int m_nIntervalY;					// 縦の頂点数
	int m_nVertex;						// 頂点数
	int m_nPolygon;						// ポリゴン数
	int m_nIdx;							// インデックス数
	int m_nIdxTexture;					// テクスチャの番号

};

#endif