//=================================================
//
// [Score.cpp]	// スコアの処理全般
// Author: chikada shouya
//
//=================================================
#include "score.h"
#include "number.h"
#include "manager.h"

// 静的メンバ変数宣言
CNumber* CScore::m_pNumber[MAX_SCORE] = {};

//=================================================
// コンストラクタ
//=================================================
CScore::CScore(int nPriority) : CObject(nPriority)
{
	m_pos = VEC3_NULL;
	m_nScore = NULL;
	m_nAddScore = NULL;

}

//=================================================
// デストラクタ
//=================================================
CScore::~CScore()
{

}

//=================================================
// タイマーの生成処理
//=================================================
CScore* CScore::Create(D3DXVECTOR3 pos)
{
	CScore* pScore = nullptr;
	pScore = new CScore;

	if (pScore != nullptr)
	{
		pScore->SetPosition(pos);
		pScore->Init();
		return pScore;
	}
	else
	{
		return nullptr;
	}
}

//=================================================
// 初期化処理
//=================================================
HRESULT CScore::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		m_pNumber[nCnt] = new CNumber;

		if (m_pNumber[nCnt] != nullptr)
		{
			m_pNumber[nCnt]->Init(m_pos.x, nCnt, 50.0f, "data\\TEXTURE\\number005.png", CNumber::NUM_SCORE);
		}
	}
	
	SetScore(0);

	return S_OK;
}

//=================================================
// 終了処理
//=================================================
void CScore::Uninit(void)
{
	//ナンバーの破棄
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (m_pNumber[nCnt] != NULL)
		{
			m_pNumber[nCnt]->Uninit();
			delete m_pNumber[nCnt];
			m_pNumber[nCnt] = NULL;
		}
	}

	CObject::Release();
}

//=================================================
// 更新処理
//=================================================
void CScore::Update(void)
{

}

//=================================================
// 描画処理
//=================================================
void CScore::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		m_pNumber[nCnt]->Draw();
	}
}

//=================================================
// 設定処理
//=================================================
void CScore::SetScore(int nScore)
{
	//各桁の数字を格納
	int aPosTexU[MAX_SCORE] = {};
	int nData = 100000;
	int aData =  10000;	

	m_nScore = nScore;

	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{

		//桁ごとに分割する
		if (nCount == 0)
		{
			aPosTexU[0] = m_nScore / nData;//8桁目
		}
		else
		{
			aPosTexU[nCount] = m_nScore % nData / aData;//7桁目
			nData = nData / 10;
			aData = aData / 10;
		}
		m_pNumber[nCount]->SetNumber(aPosTexU[nCount]);
	}
}

//=================================================
// 加算処理
//=================================================
void CScore::AddScore(int nValue)
{
	// 各桁の数字を格納
	int aPosTexU[MAX_SCORE] = {};
	int nData = 100000;
	int aData =  10000;

	m_nScore += nValue;

	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{

		//桁ごとに分割する
		if (nCount == 0)
		{
			aPosTexU[nCount] = m_nScore / nData;//8桁目
		}
		else
		{
			aPosTexU[nCount] = m_nScore % nData / aData;//7桁目
			nData = nData / 10;
			aData = aData / 10;
		}
		m_pNumber[nCount]->SetNumber(aPosTexU[nCount]);
	}

}

//=================================================
// スコアの0をカウント
//=================================================
int  CScore::ZeroCount(int nScore)
{
	int nNum = nScore;	// スコアの０の部分をカウント
	int nKeepNum = 0;	// スコアの桁数

	while (nNum != 0)	// 割り切れなくなるまで繰り返す(０まで)
	{
		nNum /= 10;		// nNumを10で割っていく
		nKeepNum++;		// 桁数を加算

	}
	if (nScore == 0)
	{
		// 1桁目に0が入っているとき
		nKeepNum = 1;
	}
	return nKeepNum;	// スコアの桁数を返す
}