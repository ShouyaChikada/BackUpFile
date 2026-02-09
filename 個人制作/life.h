//=================================================
//
// [Life.h]	// ライフのヘッダー
// Author:chikada shouya
//
//=================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "object2D.h"

class CLife :  public CObject2D
{
public:
	CLife(int nPriolity = 6);
	~CLife();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CLife* Create(D3DXVECTOR3 pos);

private:
	float m_fEaseWidth;		// イージング用の横
	float m_fEaseHeight;	// イージング用の高さ
	float m_fCountFrame;	// イージング用カウントフレーム計算変数
	float m_fMaxFrame;		// イージング用マックスフレーム変数
	bool m_bEasing;			// イージングが終了しているかどうか
};

#endif