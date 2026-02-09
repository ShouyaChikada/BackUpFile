//=================================================
//
// [meshfield.h]
// Author:chikada shouya
//
//=================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"
#include "object.h"
#include <string>

class CMeshField :public CObject
{
public:

	CMeshField(int nPriority = 6);
	~CMeshField();
	
	//プロトタイプ宣言
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static	CMeshField* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, std::string TexPath);

	// セッター
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetRadius(float Radius) { m_fRadius = Radius; }
	void SetTexPath(std::string TexPath) { m_TexPath = TexPath; }
	
	// ゲッター
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	float GetRadius(void) { return m_fRadius; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//	頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	//	インデックスバッファへのポインタ
	D3DXVECTOR3 m_pos;					//	位置
	D3DXVECTOR3 m_rot;					//	向き
	D3DXMATRIX m_mtxWorld;				//	ワールドマトリックス
	std::string m_TexPath;				// テクスチャパス
	float m_fRadius;					//	半径
	int m_nIdx;							// テクスチャ読み込み用インデックス
};

#endif
