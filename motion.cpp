//======================================================
// 
// モーションの処理
// Author:Takahashi Misaki
// 
//======================================================

#include "motion.h"
#include "debugproc.h"

//********************************************
// コンストラクタ
//********************************************
CMotion::CMotion()
{
	// 値をクリアする
	m_pfile = NULL;

	for (int nCount = 0; nCount < MAX_CHARACTER; nCount++)
	{
		m_aString[nCount] = NULL;
	}

	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		m_MotionInfo[nCount] = {};
	}

	m_NowType = TYPE_MAX;
	m_nNumKey = 0;
	m_nNumParts = 0;
	m_bLoop = false;
	m_nKey = 0;
	m_nNextKey = 0;
	m_nCounterMotion = 0;
	m_bMotionEnd = false;
	m_ppModel = {};

}

//********************************************
// デストラクタ
//********************************************
CMotion::~CMotion()
{
}

//********************************************
// 初期化処理
//********************************************
void CMotion::Init(void)
{
	m_pfile = NULL;

	for (int nCount = 0; nCount < MAX_CHARACTER; nCount++)
	{
		m_aString[nCount] = NULL;
	}

	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		m_MotionInfo[nCount] = {};
	}

	m_NowType = TYPE_MAX;
	m_nNumKey = 0;
	m_nNumParts = 0;
	m_bLoop = false;
	m_nKey = 0;
	m_nNextKey = 1;
	m_nCounterMotion = 0;
	m_bMotionEnd = false;
	m_ppModel = {};

	// ファイル読み込み処理
	Load("data\\MOTION\\motion001.txt");
}

//********************************************
// 終了処理
//********************************************
void CMotion::Uninit(void)
{
	m_pfile = NULL;

	for (int nCount = 0; nCount < MAX_CHARACTER; nCount++)
	{
		m_aString[nCount] = NULL;
	}

	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		m_MotionInfo[nCount] = {};
	}

	m_NowType = TYPE_MAX;
	m_nNumKey = 0;
	m_nNumParts = 0;
	m_bLoop = false;
	m_nKey = 0;
	m_nNextKey = 0;
	m_nCounterMotion = 0;
	m_bMotionEnd = false;
	m_ppModel = {};
}

//********************************************
// 更新処理
//********************************************
void CMotion::Update(void)
{
	// 位置と向き
	D3DXVECTOR3 Diffpos, Diffrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 pos, rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	float fRataFrame = 0.0f;

	if (m_nNextKey < m_nNumKey && m_bMotionEnd == false)
	{// モーションの全体キーより値が低い場合

		m_nCounterMotion++;	// モーションカウント

		// 全モデル(パーツ)の更新
		for (int nCntModel = 0; nCntModel < m_nNumParts; nCntModel++)
		{
			// キー情報から位置・向きを算出
			Diffpos.x = m_MotionInfo[m_NowType].aKeyInfo[m_nNextKey].aKey[nCntModel].fPosX - m_MotionInfo[m_NowType].aKeyInfo[m_nKey].aKey[nCntModel].fPosX;
			Diffpos.y = m_MotionInfo[m_NowType].aKeyInfo[m_nNextKey].aKey[nCntModel].fPosY - m_MotionInfo[m_NowType].aKeyInfo[m_nKey].aKey[nCntModel].fPosY;
			Diffpos.z = m_MotionInfo[m_NowType].aKeyInfo[m_nNextKey].aKey[nCntModel].fPosZ - m_MotionInfo[m_NowType].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ;
			Diffrot.x = m_MotionInfo[m_NowType].aKeyInfo[m_nNextKey].aKey[nCntModel].fRotX - m_MotionInfo[m_NowType].aKeyInfo[m_nKey].aKey[nCntModel].fRotX;
			Diffrot.y = m_MotionInfo[m_NowType].aKeyInfo[m_nNextKey].aKey[nCntModel].fRotY - m_MotionInfo[m_NowType].aKeyInfo[m_nKey].aKey[nCntModel].fRotY;
			Diffrot.z = m_MotionInfo[m_NowType].aKeyInfo[m_nNextKey].aKey[nCntModel].fRotZ - m_MotionInfo[m_NowType].aKeyInfo[m_nKey].aKey[nCntModel].fRotZ;

			fRataFrame = (float)(m_nCounterMotion) / (float)(m_MotionInfo[m_NowType].aKeyInfo[m_nKey].nFrame);

			// パーツの位置・向きを設定
			pos.x = m_ppModel[nCntModel]->GetOffsetPos().x + m_MotionInfo[m_NowType].aKeyInfo[m_nKey].aKey[nCntModel].fPosX + Diffpos.x * fRataFrame;
			pos.y = m_ppModel[nCntModel]->GetOffsetPos().y + m_MotionInfo[m_NowType].aKeyInfo[m_nKey].aKey[nCntModel].fPosY + Diffpos.y * fRataFrame;
			pos.z = m_ppModel[nCntModel]->GetOffsetPos().z + m_MotionInfo[m_NowType].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ + Diffpos.z * fRataFrame;
			rot.x = m_ppModel[nCntModel]->GetOffsetRot().x + m_MotionInfo[m_NowType].aKeyInfo[m_nKey].aKey[nCntModel].fRotX + Diffrot.x * fRataFrame;
			rot.y = m_ppModel[nCntModel]->GetOffsetRot().y + m_MotionInfo[m_NowType].aKeyInfo[m_nKey].aKey[nCntModel].fRotY + Diffrot.y * fRataFrame;
			rot.z = m_ppModel[nCntModel]->GetOffsetRot().z + m_MotionInfo[m_NowType].aKeyInfo[m_nKey].aKey[nCntModel].fRotZ + Diffrot.z * fRataFrame;

			m_ppModel[nCntModel]->SetPos(pos);
			m_ppModel[nCntModel]->SetRot(rot);
		}

		if (m_nCounterMotion >= m_MotionInfo[m_NowType].aKeyInfo[m_nKey].nFrame)
		{// カウンターが再生フレームを超える時

			// モーションカウンターを初期化する
			m_nCounterMotion = 0;

			// キーを一つ進める
			m_nKey++;
			m_nNextKey++;

			if (m_nNextKey >= m_nNumKey)
			{// キーの総数を超えていた時

				if (m_bLoop == true)
				{// ループするモーションの場合
					// 次のキーを0に戻す
					m_nNextKey = 0;
				}
				else if (m_bLoop == false)
				{// ループしないモーションの場合
					// キーを初期化
					m_nKey = 0;
					m_nNextKey = 1;

					// モーションが終わった状態にする
					m_bMotionEnd = true;
				}

			}

			if (m_nKey >= m_nNumKey)
			{// キーの総数を超えていた時
				// 現在のキーを0に戻す
				m_nKey = 0;
			}
		}
	}
}

//********************************************
// ファイル読み込み処理
//********************************************
void CMotion::Load(const char* Motionfile)
{
	// デバック表示のポインタ
	CDebugproc* pDebugproc;

	// 現在のキー数
	int nCntKey = 0;

	// 現在のパーツ
	int nCntParts = 0;

	// 現在読み込んでいるモーションのタイプ
	int nType = -1;

	// ループするかどうか
	int bLoop = 0;

	// 現在の文字数をカウントする変数
	int nCnt = 0;

	// 読み込んだ文字を保存する変数
	char String = NULL;
	char aString[3] = {};

	int nResult = 0;

	// ファイルを読み込む
	m_pfile = fopen(Motionfile, "r");

	if (m_pfile != NULL)
	{
		while (1)
		{
			// メモリのクリア
			memset(&String, 0, sizeof(String));

			// 先頭の文字の読み込み
			nResult = fscanf(m_pfile, "%c", &String);
			
			// 読み飛ばし処理
			if (String == '#')
			{// コメントを読み込んだ場合
				while (1)
				{
					nResult = fscanf(m_pfile, "%c", &String);

					if (String == '\n' || String == EOF)
					{
						break;
					}
				}

				continue;
			}
			else if (String == '\t')
			{// タブの空白を読み込んだ場合
				continue;
			}
			else if (String == '\n')
			{// 改行を読んだ場合
				continue;
			}
			else if (String == ' ')
			{// 空白を読み込んだ場合
				continue;
			}

			// 読み込んだ文字を代入する
			m_aString[nCnt] = String;

			// カウントを一つ進める
			nCnt++;

			if (strcmp(&m_aString[0], "SCRIPT") == 0)
			{
				// メモリのクリア
				memset(&m_aString[0], 0, sizeof(m_aString));

				// カウントを初期化する
				nCnt = 0;
			}
			else if (strcmp(&m_aString[0], "MOTIONSET") == 0)
			{
				// モーションの種類を増やす
				nType++;

				// メモリのクリア
				memset(&m_aString[0], 0, sizeof(m_aString));

				// カウントを初期化する
				nCnt = 0;
			}
			else if (strcmp(&m_aString[0], "LOOP") == 0)
			{
				// =と空白分を読み込む
				fgets(aString, 3, m_pfile);

				// モーションがループするかどうかを読み込み
				nResult = fscanf(m_pfile, "%d", &bLoop);

				if (bLoop == 0)
				{// ループしない場合
					m_MotionInfo[nType].bLoop = false;
				}
				else
				{// ループする場合
					m_MotionInfo[nType].bLoop = true;
				}

				// メモリのクリア
				memset(&m_aString[0], 0, sizeof(m_aString));

				// カウントを初期化する
				nCnt = 0;
			}
			else if (strcmp(&m_aString[0], "NUM_KEY") == 0)
			{
				// =と空白分を読み込む
				fgets(aString, 3, m_pfile);

				// モーションのキー総数を読み込み
				nResult = fscanf(m_pfile, "%d", &m_MotionInfo[nType].nNumKey);

				// メモリのクリア
				memset(&m_aString[0], 0, sizeof(m_aString));

				// カウントを初期化する
				nCnt = 0;
			}
			else if (strcmp(&m_aString[0], "KEYSET") == 0)
			{
				// メモリのクリア
				memset(&m_aString[0], 0, sizeof(m_aString));

				// カウントを初期化する
				nCnt = 0;

				// キー情報の読み込み処理
				KeysetLoad(nType, nCntKey, nCntParts);

				// キーを増やす
				nCntKey++;
			}
			else if (strcmp(&m_aString[0], "END_MOTIONSET") == 0)
			{
				// キーを最初に戻す
				nCntKey = 0;

				// メモリのクリア
				memset(&m_aString[0], 0, sizeof(m_aString));

				// カウントを初期化する
				nCnt = 0;
			}
			else if (strcmp(&m_aString[0], "END_SCRIPT") == 0)
			{
				// メモリのクリア
				memset(&m_aString[0], 0, sizeof(m_aString));

				// カウントを初期化する
				nCnt = 0;

				break;
			}

			if (nResult == NULL)
			{// 正しく読み込めなかった場合
				break;
			}
			else if (nResult == EOF)
			{// テキストファイルを全て読み切った場合
				break;
			}

		}

		// ファイルを閉じる
		fclose(m_pfile);
	}
	else
	{
		// デバック表示
		pDebugproc->Print("モーションファイルを開けませんでした\n");
	}
}

//********************************************
// KEYの読み込み処理
//********************************************
void CMotion::KeysetLoad(int nType, int nCntKey, int nCntParts)
{
	// 読み込んだ文字を保存する変数
	char String = NULL;
	char aString[3] = {};

	int nResult = 0;

	int nCnt = 0;

	while (1)
	{
		// メモリのクリア
		memset(&String, 0, sizeof(String));

		// 先頭の文字の読み込み
		nResult = fscanf(m_pfile, "%c", &String);

		// 読み飛ばし処理
		if (String == '#')
		{// コメントを読み込んだ場合
			while (1)
			{
				nResult = fscanf(m_pfile, "%c", &String);

				if (String == '\n' || String == EOF)
				{
					break;
				}
			}

			continue;
		}
		else if (String == '\t')
		{// タブの空白を読み込んだ場合
			continue;
		}
		else if (String == '\n')
		{// 改行を読んだ場合
			continue;
		}
		else if (String == ' ')
		{// 空白を読み込んだ場合
			continue;
		}

		// 読み込んだ文字を代入する
		m_aString[nCnt] = String;

		// カウントを一つ進める
		nCnt++;

		if (strcmp(&m_aString[0], "FRAME") == 0)
		{
			// =と空白分を読み込む
			fgets(aString, 3, m_pfile);

			// モーションのフレーム数を読み込み
			nResult = fscanf(m_pfile, "%d", &m_MotionInfo[nType].aKeyInfo[nCntKey].nFrame);

			// メモリのクリア
			memset(&m_aString[0], 0, sizeof(m_aString));

			// カウントを初期化する
			nCnt = 0;
		}
		else if (strcmp(&m_aString[0], "KEY") == 0)
		{
			// メモリのクリア
			memset(&m_aString[0], 0, sizeof(m_aString));

			// カウントを初期化する
			nCnt = 0;
		}
		else if (strcmp(&m_aString[0], "POS") == 0)
		{
			// =と空白分を読み込む
			fgets(aString, 3, m_pfile);

			// モーションの位置を読み込み
			nResult = fscanf(m_pfile, "%f", &m_MotionInfo[nType].aKeyInfo[nCntKey].aKey[nCntParts].fPosX);
			nResult = fscanf(m_pfile, "%f", &m_MotionInfo[nType].aKeyInfo[nCntKey].aKey[nCntParts].fPosY);
			nResult = fscanf(m_pfile, "%f", &m_MotionInfo[nType].aKeyInfo[nCntKey].aKey[nCntParts].fPosZ);

			// メモリのクリア
			memset(&m_aString[0], 0, sizeof(m_aString));

			// カウントを初期化する
			nCnt = 0;
		}
		else if (strcmp(&m_aString[0], "ROT") == 0)
		{
			// =と空白分を読み込む
			fgets(aString, 3, m_pfile);

			// モーションの向きを読み込み
			nResult = fscanf(m_pfile, "%f", &m_MotionInfo[nType].aKeyInfo[nCntKey].aKey[nCntParts].fRotX);
			nResult = fscanf(m_pfile, "%f", &m_MotionInfo[nType].aKeyInfo[nCntKey].aKey[nCntParts].fRotY);
			nResult = fscanf(m_pfile, "%f", &m_MotionInfo[nType].aKeyInfo[nCntKey].aKey[nCntParts].fRotZ);

			// メモリのクリア
			memset(&m_aString[0], 0, sizeof(m_aString));

			// カウントを初期化する
			nCnt = 0;
		}
		else if (strcmp(&m_aString[0], "END_KEY") == 0)
		{
			// 次のパーツに移る
			nCntParts++;

			// メモリのクリア
			memset(&m_aString[0], 0, sizeof(m_aString));

			// カウントを初期化する
			nCnt = 0;

			// 次の文字を読み込み
			nResult = fscanf(m_pfile, "%s", &m_aString[0]);

			if (strcmp(&m_aString[0], "END_KEYSET") == 0)
			{// END_KEYSETだった場合

				// パーツを最初に戻す
				nCntParts = 0;

				// メモリのクリア
				memset(&m_aString[0], 0, sizeof(m_aString));

				break;
			}
			else
			{
				// メモリのクリア
				memset(&m_aString[0], 0, sizeof(m_aString));
			}
		}
	}
}

//********************************************
// 種類設定処理
//********************************************
void CMotion::SetType(TYPE nType)
{
	// そのモーションの情報を現在のモーションに設定
	m_nNumKey = m_MotionInfo[nType].nNumKey;	// キーの総数
	m_bLoop = m_MotionInfo[nType].bLoop;		// ループするかどうか
	m_bMotionEnd = false;							// モーションが終わっていない状態にする

	if (m_bLoop == false)
	{// ループしないモーションの場合
		m_nKey = 0;										// 現在のキーNo.
		m_nNextKey = m_nKey + 1;						// 次のキーNo.
		m_nCounterMotion = 0;							// カウントを初期化する
	}
	else if (m_bLoop == true)
	{// ループするモーションの場合
		if (m_NowType != nType)
		{// 現在のモーションと種類が違う場合
			m_nCounterMotion = 0;							// カウントを初期化する
			m_nKey = 0;									// 現在のキーNo.
			m_nNextKey = m_nKey + 1;					// 次のキーNo.
		}
	}

	// モーションの種類の設定
	m_NowType = nType;

}

//********************************************
// 設定処理
//********************************************
void CMotion::SetModel(CModel** apModel, int nNumParts)
{
	m_ppModel = apModel;
	m_nNumParts = nNumParts;
}

//********************************************
// モーションが終わるかどうかの処理
//********************************************
bool CMotion::IsFinish(void)
{
	return m_bMotionEnd;
}
