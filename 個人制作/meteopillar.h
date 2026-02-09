//=================================================
//
// [meteopillar.h]	隕石(柱)のヘッダー
// Author:chikada shouya
//
//=================================================
#ifndef _CMETEOPILLAR_H_
#define _CMETEOPILLAR_H_

#include "rock.h"

constexpr int nMaxNum = 2;// 飛んでくる柱の処理用数

class CMeteoPillar : public CRock
{
public:
	typedef enum
	{
		ROT_NONE = 0,
		ROT_X,
		ROT_Y,
		ROT_Z,
		ROT_MAX,
	}ROT;

	CMeteoPillar();
	~CMeteoPillar();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMeteoPillar* Create(D3DXVECTOR3 pos, ROT rot);

	void MovePillar(void);

	// セッター
	void SetRotSize(ROT Rot);

	// ゲッター
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }
	bool GetDeath(void) { return m_bDeath; }

private:
	D3DXVECTOR3 m_posOld;
	bool m_bChange[nMaxNum];		// 柱の4方向
	bool m_bDeath;			// 死の判定
	int m_nMoveCntTime;	// 移動するまでのカウント
};

#endif

