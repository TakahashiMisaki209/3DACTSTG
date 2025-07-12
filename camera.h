//======================================================
// 
// カメラの処理
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//******************************************************
// カメラクラス
//******************************************************
class CCamera
{
public:
	// コンストラクタ
	CCamera();
	// デストラクタ
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	void SetPosCamera(D3DXVECTOR3 pos);
	void SetMoveCamera(D3DXVECTOR3 move);
	D3DXVECTOR3 GetRot(void) { return m_rot; };
	bool GetFollow(void) { return m_bFollow; };

private:
	D3DXMATRIX m_mtxView;		// ビューマトリックス
	D3DXMATRIX m_mtxProjection;	// プロジェクションマトリックス
	D3DXVECTOR3 m_posV;			// 視点
	D3DXVECTOR3 m_posR;			// 注視点
	D3DXVECTOR3 m_vecU;			// 上方向ベクトル
	D3DXVECTOR3 m_rot;			// 向き
	D3DXVECTOR3 m_move;			// 移動量
	D3DXVECTOR3 m_posVDest;		// 目的の視点
	D3DXVECTOR3 m_posRDest;		// 目的の注視点
	D3DXVECTOR3 m_rotDest;		// 目的の向き
	float m_fDistance;			// 視点から注視点の距離
	bool m_bFollow;				// 自動追従と手動旋回切り替え
	bool m_bCameraV;			// 視点と注視点の操作の切り替え
};

#endif