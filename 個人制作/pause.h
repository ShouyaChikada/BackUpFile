//=================================================
//
//	pause.cpp
// 
// Author:近田 尚也
//
//=================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"
#include "object2D.h"


class CPause :	public CObject2D
{
public:

	CPause(int nPriolity = 16);
	~CPause();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	static CPause* Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fX, float fY, std::string aName);

	/// <summary>
	/// イージング用関数
	/// </summary>
	/// <param name="bEasing = イージング判定"></param>
	/// <param name="fXMin = X軸の最小"></param>
	/// <param name="fXMax = X軸の最大"></param>
	/// <param name="fYMin = Y軸の最小"></param>
	/// <param name="fYMax = Y軸の最大"></param>
	void Easing(bool bEasing, float fXMin, float fXMax, float fYMin, float fYMax);

private:
	bool m_bEasing;			// イージング判定用変数
	float m_fCountFrame;	// イージングフレーム用変数
	float m_fMaxFrame;		// イージングマックスフレーム用変数
	float m_fX;				// サイズ(X)
	float m_fY;				// サイズ(Y)
};

#endif