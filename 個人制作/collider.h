//=================================================
//
// [collider.h]	コライダーヘッダー
// Author:chikada shouya
//
//=================================================
#ifndef _COLLIDER_H_
#define _COLLIDER_H_

class CCollider
{
public:
	CCollider();
	~CCollider();

	// 当たり判定
	static bool Collision(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3* move, D3DXVECTOR3* size);

	/// <summary>
	/// 当たり判定される側
	/// </summary>
	/// <param name="pos = 位置"></param>
	/// <param name="posOld = 目的の位置"></param>
	/// <param name="size = サイズ"></param>
	static void SetCollisionSource(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 size)
	{ m_SourcePos = pos; m_SourcePosOld = posOld; m_SourceSize = size; }

private:
	static D3DXVECTOR3 m_SourcePos;		// 判定される側の位置	
	static D3DXVECTOR3 m_SourcePosOld;	// 判定される側の前回の位置
	static D3DXVECTOR3 m_SourceSize;	// 判定される側のサイズ
};

#endif