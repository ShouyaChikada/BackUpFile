//=================================================
//
// [collider.cpp]	コライダー処理全般
// Author:chikada shouya
//
//=================================================
#include "collider.h"

namespace Collider
{
	float fHalf = 0.5f;	// オブジェクトサイズの半分
	float fMove = 0.3f;	// 移動量
};

//=================================================
// 静的メンバ変数
//=================================================
D3DXVECTOR3 CCollider::m_SourcePos = VEC3_NULL;
D3DXVECTOR3 CCollider::m_SourcePosOld = VEC3_NULL;
D3DXVECTOR3 CCollider::m_SourceSize = VEC3_NULL;

//=================================================
// コンストラクタ
//=================================================
CCollider::CCollider()
{
	
}

//=================================================
// デストラクタ
//=================================================
CCollider::~CCollider()
{

}

//=================================================
// 当たり判定
//=================================================
bool CCollider::Collision(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3* move, D3DXVECTOR3* size)
{
	if(m_SourcePos == nullptr)return false;
	if (m_SourcePosOld == nullptr)return false;
	if (m_SourceSize == nullptr)return false;

	if (posOld->y - (size->y * Collider::fHalf) < m_SourcePos.y + (m_SourceSize.y * Collider::fHalf) &&
		pos->y + (size->y * Collider::fHalf) > m_SourcePos.y - (m_SourceSize.y * Collider::fHalf))
	{
		// ---------------------- 前後の当たり判定 ----------------------
		if (posOld->x - (size->x * Collider::fHalf) < m_SourcePos.x + (m_SourceSize.x * Collider::fHalf) &&
			pos->x + (size->x * Collider::fHalf) > m_SourcePos.x - (m_SourceSize.x * Collider::fHalf))
		{
			// 手前からめり込む
			if (posOld->z + (size->z * Collider::fHalf) < m_SourcePos.z - (m_SourceSize.z * Collider::fHalf) &&
				pos->z + (size->z * Collider::fHalf) > m_SourcePos.z - (m_SourceSize.z * Collider::fHalf))
			{
				pos->z = m_SourcePos.z - (m_SourceSize.z * Collider::fHalf) - (size->z * Collider::fHalf) - Collider::fMove;
				//return true;
			}
			// 奥からめり込む
			else if (posOld->z - (size->z * Collider::fHalf) > m_SourcePos.z + (m_SourceSize.z * Collider::fHalf) &&
				pos->z - (size->z * Collider::fHalf) < m_SourcePos.z + (m_SourceSize.z * Collider::fHalf))
			{
				pos->z = m_SourcePos.z + (m_SourceSize.z * Collider::fHalf) + (size->z * Collider::fHalf) + Collider::fMove;
				//return true;
			}
		}
		// ---------------------- 左右の当たり判定 ----------------------
		if (posOld->z - (size->z * Collider::fHalf) < m_SourcePos.z + (m_SourceSize.z * Collider::fHalf) &&
			pos->z + (size->z * Collider::fHalf) > m_SourcePos.z - (m_SourceSize.z * Collider::fHalf))
		{
			//------------ (オブジェクトが動かない場合) -----------------
			// 左からめり込む
			if (posOld->x + (size->x * Collider::fHalf) < m_SourcePos.x - (m_SourceSize.x * Collider::fHalf) &&
				pos->x + (size->x * Collider::fHalf) > m_SourcePos.x - (m_SourceSize.x * Collider::fHalf))
			{
				pos->x = m_SourcePos.x - m_SourceSize.x * Collider::fHalf - size->x * Collider::fHalf - Collider::fMove;
				return true;
			}
			// 右からめり込む
			else if (posOld->x - (size->x * Collider::fHalf) > m_SourcePos.x + (m_SourceSize.x * Collider::fHalf) &&
				pos->x - (size->x * Collider::fHalf) < m_SourcePos.x + (m_SourceSize.x * Collider::fHalf))
			{
				pos->x = m_SourcePos.x + (m_SourceSize.x * Collider::fHalf) + (size->x * Collider::fHalf) + Collider::fMove;
				return true;
			}

			//-------------- (オブジェクトが動く場合) -------------------
			// 左からめり込む
			else if (pos->x + (size->x * Collider::fHalf) < m_SourcePosOld.x - (m_SourceSize.x * Collider::fHalf) &&
				pos->x + (size->x * Collider::fHalf) > m_SourcePos.x - (m_SourceSize.x * Collider::fHalf))
			{
				pos->x = m_SourcePos.x - (m_SourceSize.x * Collider::fHalf) - (size->x * Collider::fHalf) - Collider::fMove;
				return true;
			}
			// 右からめり込む(オブジェクトが動く場合)
			else if (pos->x - (size->x * Collider::fHalf) > m_SourcePosOld.x + (m_SourceSize.x * Collider::fHalf) &&
				pos->x - (size->x * Collider::fHalf) < m_SourcePos.x + (m_SourceSize.x * Collider::fHalf))
			{
				pos->x = m_SourcePos.x + (m_SourceSize.x * Collider::fHalf) + (size->x * Collider::fHalf) + Collider::fMove;
				return true;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	return false;
}