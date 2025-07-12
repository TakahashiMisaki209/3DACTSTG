//======================================================
// 
// メッシュフィールドの処理
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"
#include "object.h"

//*****************************************************************************
// メッシュフィールドクラス
//*****************************************************************************
class CMeshfield:public CObject
{
public:

	// コンストラクタ
	CMeshfield(int nPriority = 1);
	// デストラクタ
	~CMeshfield();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPos(void) { return m_pos; };		// 位置情報の取得
	float GetSizeX(void) { return m_fWidth; };		// 横幅の取得
	float GetSizeZ(void) { return m_fHeight; };		// 奥行の取得
	void SetMeshfield(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Width, float fHeight, int nIntervalX, int nIntervalZ, const char* textname);

	// 静的メンバ関数
	static CMeshfield* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Width, float fHeight, int nIntervalX, int nIntervalZ, const char* textname);

private:

	// メンバ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// インデックスバッファへのポインタ
	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス
	D3DXVECTOR3 m_pos;					// 頂点座標
	D3DXVECTOR3 m_rot;					// 向き
	int m_nIdxTexture;					// テクスチャの番号
	bool m_bWireFrame;					// ワイヤーフレームをオンにするかどうか
	float m_fWidth;						// ポリゴンの横幅
	float m_fHeight;					// ポリゴンの縦幅
	int m_nIntervalX;					// 横の頂点数
	int m_nIntervalZ;					// 縦の頂点数
	int m_nVertex;						// 全ての頂点数
	int m_nPolygon;						// ポリゴン数
	int m_nIdx;							// インデックス数

};
#endif