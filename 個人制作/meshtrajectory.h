//=================================================
//
// [meshtrajectory.h]	// 軌跡のヘッダー
// Author:chikada shouya
//
//=================================================
#ifndef _MESHTRAJECTORY_H_
#define _MESHTRAJECTORY_H_

#include "main.h"
#include "object.h"

class CMeshTrajectory : public CObject
{
public:

	static constexpr int RAJECTORY_X_BLOCK = 6;
	const D3DXVECTOR3 a = {};
	CMeshTrajectory(int nPriority = 6);
	~CMeshTrajectory();

	//プロトタイプ宣言
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMeshTrajectory* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col);
	
	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos = 現在の位置"></param>
	/// <param name="bCheck0 = 判定1"></param>
	/// <param name="bCheck1 = 判定2"></param>
	/// <param name="fRotValue = 回転軸"></param>
	void SetTrajectory(D3DXVECTOR3 pos, bool bCheck0,bool bCheck1,float fRotValue);

	// セッター
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetColor(D3DXCOLOR col) { m_col = col; }
	
	// ゲッター
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXCOLOR GetCol(void) { return m_col; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		// インデックスバッファへのポインタ
	D3DXVECTOR3 m_pos;						// 位置
	D3DXVECTOR3 m_rot;						// 向き
	D3DXVECTOR3 m_move;						// 移動量
	D3DXCOLOR m_col;						// カラー
	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス
	int m_nIdx;								// インデックス番号

};
#endif