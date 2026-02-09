//=================================================
//
// [meteorock.h]	隕石(塵)のヘッダー
// Author:chikada shouya
//
//=================================================
#ifndef _CMETEOROCK_H_
#define _CMETEOROCK_H_

#include "rock.h"

class CMeshTrajectory;
class CCursor;

class CMeteoRock :public CRock
{
public:

	CMeteoRock();
	~CMeteoRock();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos = 現在の位置"></param>
	/// <returns></returns>
	static CMeteoRock* Create(D3DXVECTOR3 pos);

	void UpdateObjectPos(D3DXVECTOR3 pos ,D3DXVECTOR3 move);
	bool CollisionMeteo(D3DXVECTOR3 pos);

	// セッター
	void SetRotation(bool bRotation) { m_bRotation = bRotation; }
	void SetCheck0(bool bCheck) { m_bCheck0 = bCheck; }
	void SetCheck1(bool bCheck) { m_bCheck1 = bCheck; }
	void SetCheck2(bool bCheck) { m_bCheck2 = bCheck; }

	// ゲッター
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }
	bool GetDeath(void) { return m_bDeath; }
	bool GetSign0(void) { return m_bSign0; }
	bool GetSign1(void) { return m_bSign1; }
	bool GetCheck0(void) { return m_bCheck0; }
	bool GetCheck1(void) { return m_bCheck1; }
	bool GetCheck2(void) { return m_bCheck2; }
	bool GetSDeath(void) { return m_bsDeath; }
	bool GetRelease(void) { return m_bReleaseMove; }

private:
	CMeshTrajectory* m_pTrajectory;	// 軌跡用変数
	CCursor* m_pCursor;				// 隕石飛ばす矢印用変数
	D3DXVECTOR3 m_posOld;			// 前回の位置
	D3DXVECTOR3 m_Nextpos;			// 次の位置
	float m_fDistance;				// 距離
	float m_fRotValue;				// 回転値
	float m_fDistanceValue;			// 距離の加算
	float m_fAddValue;				// 回転する値の加算用変数
	float m_fPos;					
	float m_fMove;
	float m_fDiffX;
	float m_fDiffZ;
	int m_nCntValueTime;			// 加算する時間
	int m_nSpornTime;				// 生成されてから動くまでの時間
	bool m_bDeath;					// 消すかの判定
	bool m_bRelease[2];				// キーが離されているかどうか
	bool m_bTimeOut;
	bool m_bCheck0;
	bool m_bCheck1;
	bool m_bCheck2;
	bool m_bsDeath;
	bool m_bRotation;
	bool m_bSign0;					// 飛ぶ判定
	bool m_bSign1;					// 飛ぶ判定
	bool m_bCollision;				// 当たり判定
	bool m_bBillboardDeath;			// ビルボード破棄判定
	bool m_bReleaseMove;			// 離したかどうかの判定

};

#endif