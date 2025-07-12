//======================================================
// 
// モーションの処理
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _MOTION_H_
#define _MOTION_H_

#include "main.h"
#include "model.h"

// マクロ定義
#define KEY_MAX (16)			// キーの最大数
#define KEYINFO_MAX (32)		// キーインフォの最大数
#define MAX_CHARACTER (256)		// 文字の最大数

//*****************************************************************************
// モーションクラス
//*****************************************************************************
class CMotion
{
public:
	// モーションの種類
	typedef enum
	{
		TYPE_NEUTRAL = 0,	// 待機
		TYPE_WALK,			// 歩く
		TYPE_ATTACK,		// 攻撃
		TYPE_JUMP,			// ジャンプ
		TYPE_LANDING,		// 着地
		TYPE_MAX
	}TYPE;

	// キーの構造体
	typedef struct
	{
		float fPosX;	// 位置X
		float fPosY;	// 位置Y
		float fPosZ;	// 位置Z
		float fRotX;	// 向きX
		float fRotY;	// 向きY
		float fRotZ;	// 向きZ
	}KEY;

	// キー情報の構造体
	typedef struct
	{
		int nFrame;			// 再生フレーム
		KEY aKey[KEY_MAX];	// 各パーツのキー要素
	}KEY_INFO;

	// キーモーション情報構造体
	typedef struct
	{
		bool bLoop;				        // ループするかどうか
		int nNumKey;			        // キーの総数
		KEY_INFO aKeyInfo[KEYINFO_MAX];	// モデルのキー情報
	}INFO;

	// コンストラクタ
	CMotion();
	// デストラクタ
	~CMotion();

	// メンバ関数
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Load(const char* Motionfile);
	void KeysetLoad(int nType, int nCntKey, int nCntParts);
	TYPE GetType(void) { return m_NowType; };
	bool IsFinish(void);
	//void SetMotionInfo(INFO m_MotionInfo);
	void SetType(TYPE Type);
	void SetModel(CModel** apModel,int nNumParts);

private:
	// メンバ変数
	INFO m_MotionInfo[TYPE_MAX];	// モーション情報
	TYPE m_NowType;					// 現在のモーションタイプ
	int m_nNumKey;					// キーの総数
	int m_nNumParts;				// パーツの総数
	bool m_bLoop;					// ループするかどうか
	int m_nKey;						// 現在のキーNo.
	int m_nNextKey;					// 次のキーNo.
	int m_nCounterMotion;			// モーションカウンター
	bool m_bMotionEnd;				// モーションが終わっているか
	CModel** m_ppModel;				// モデルへのダブルポインタ

	FILE* m_pfile;					// 読み込むファイル
	char m_aString[MAX_CHARACTER];

};

#endif