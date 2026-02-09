//=================================================
//
// [meshdome.h]
// Author:chikada shouya
//
//=================================================
#ifndef _MESHDOME_H_
#define _MESHDOME_H_

#include "main.h"
#include "object.h"
#include <string>

#define MESHDOME_V_BLOCK (1)		//X方向のブロック数
#define MESHDOME_H_BLOCK (24)		//Z方向のブロック数
#define MESHDOME_MAX_VTX ((MESHDOME_V_BLOCK + 1) * (MESHDOME_H_BLOCK + 1))		//頂点数

class CMeshDome :public CObject
{
public:

	CMeshDome(int nPriority = 3);
	~CMeshDome();
	//プロトタイプ宣言
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static	CMeshDome* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius);

	// セッター
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }

	// ゲッター
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

	void GenerateSphereVertices(float radius, int slices, int stacks, std::vector<Vertex>& vertices);
	void RenderSphere(LPDIRECT3DDEVICE9 pDevice, const std::vector<Vertex>& vertices, int slices, int stacks);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;					//位置
	D3DXVECTOR3 m_rot;					//向き
	D3DXMATRIX m_mtxWorld;				//ワールドマトリックス
	float m_fRadius;						//半径
	int m_nIdx;
};

#endif
