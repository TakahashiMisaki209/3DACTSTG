//======================================================
// 
// プレイヤーの処理
// Author:Takahashi Misaki
// 
//======================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "object.h"
#include "model.h"
#include "motion.h"
#include "shadow.h"

//******************************************************
// プレイヤークラス
//******************************************************
class CPlayer:public CObject
{
public:

	// コンストラクタ
	CPlayer(int nPriority = 3);

	// デストラクタ
	~CPlayer();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPos(void) { return m_pos; };
	D3DXVECTOR3 GetRot(void) { return m_rot; };
	D3DXVECTOR3 GetMove(void) { return m_move; };

	// 静的メンバ関数
	static CPlayer* Create(void);

private:

	// メンバ変数
	D3DXVECTOR3 m_pos;				// 位置
	D3DXVECTOR3 m_rot;				// 向き
	D3DXVECTOR3 m_rotDest;			// 向きたい方向までの差
	D3DXVECTOR3 m_move;				// 移動量
	D3DXMATRIX m_mtxWorld;			// ワールドマトリックス
	int m_nNumModel;				// モデル(パーツ)の総数
	bool m_bJump;					// ジャンプしてるかどうか
	CShadow* m_pShadow;				// 影へのポインタ
	CMotion* m_pMotion;				// モーションへのポインタ
	CModel* m_apModel[MAX_MODEL];	// モデル(パーツ)へのポインタ

};

#endif _PLAYER_H_