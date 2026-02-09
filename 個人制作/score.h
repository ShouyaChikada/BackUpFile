//==============================================================
//
// [score.h]	// スコアのヘッダー
// Author: chikada shouya
//
//==============================================================
#ifndef _SCORE_H_ // このマクロ定義がされてなかったら
#define _SCORE_H_ // 2重インクルード防止のマクロ定義

#include"main.h"
#include"object.h"

// 前方宣言
class CNumber;

// マクロ定義
#define MAX_SCORE (6)

// スコアクラス
class CScore : public CObject
{
public:

	CScore(int nPriority = 4);
	~CScore();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScore* Create(D3DXVECTOR3 pos);

	void AddScore(int nValue);
	int ZeroCount(int nScore);

	// セッター
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetScore(int nScore);

	// ゲッター
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	int GetScore(void) { return m_nScore; }

private:
	static CNumber* m_pNumber[MAX_SCORE];	// ナンバーのポインタ(秒)
	D3DXVECTOR3 m_pos;						// 位置
	int m_nScore;							// スコアの総数
	int m_nAddScore;						// 加算用スコア
};

#endif