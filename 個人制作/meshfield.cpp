//=================================================
//
// [meshfield.cpp]
// Author:chikada shouya
//
//=================================================
#include "meshfield.h"
#include "manager.h"
#include "texturemanager.h"
#include "input.h"

using namespace std;

namespace
{
	int V_Block = 1;																// X方向のブロック数
	int H_Block = 24;																// Z方向のブロック数
	int IndexNum = V_Block * H_Block * 2 + (H_Block - 1) * 12;						//ポリゴン数
	int MaxVtx = (V_Block + 1) * (H_Block + 1);										// 頂点数
	int PrimitveNum = V_Block * H_Block * 2 + (H_Block + (H_Block - 1) * 4);		// インデックス数
}

//=================================================
// コンストラクタ
//=================================================
CMeshField::CMeshField(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = NULL;
	m_rot = VEC3_NULL;
	m_pos = VEC3_NULL;
	m_fRadius = NULL;
	m_nIdx = NULL;
	m_pIdxBuff = nullptr;
}

//=================================================
// デストラクタ
//=================================================
CMeshField::~CMeshField()
{

}

//=================================================
// 生成
//=================================================
CMeshField* CMeshField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, std::string TexPath)
{
	CMeshField* pMeshField = nullptr;
	pMeshField = new CMeshField;

	if (pMeshField != nullptr)
	{
		pMeshField->SetPosition(pos);
		pMeshField->SetRot(rot);
		pMeshField->SetTexPath(TexPath);
		pMeshField->Init();
		return pMeshField;
	}
	else
	{
		return nullptr;
	}
}

//=================================================
// 初期化処理
//=================================================
HRESULT CMeshField::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_nIdx = CTextureManager::Instance()->Register(m_TexPath);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MaxVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff, NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * IndexNum,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	VERTEX_3D* pVtx = nullptr;

	int index = 0;
	float fAngle = 0.0f;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_fRadius, 0.0f, m_fRadius);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, m_fRadius);
	pVtx[2].pos = D3DXVECTOR3(m_fRadius, 0.0f, m_fRadius);
	pVtx[3].pos = D3DXVECTOR3(-m_fRadius, 0.0f, 0.0f);
	pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(m_fRadius, 0.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(-m_fRadius, 0.0f, -m_fRadius);
	pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -m_fRadius);
	pVtx[8].pos = D3DXVECTOR3(m_fRadius, 0.0f, -m_fRadius);

	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		//法線の設定
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//カラー設定
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	//テクスチャ設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

	//アンロック
	m_pVtxBuff->Unlock();

	//頂点情報の設定
	WORD* pIdx;

	//インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//インデックスの設定
	pIdx[0] = 3;
	pIdx[1] = 0;

	pIdx[2] = 4;
	pIdx[3] = 1;

	pIdx[4] = 5;
	pIdx[5] = 2;

	pIdx[6] = 2;
	pIdx[7] = 6;

	pIdx[8] = 7;
	pIdx[9] = 8;

	//インデックスバッファのアンロック
	m_pIdxBuff->Unlock();

	return S_OK;
}
//=================================================
// 終了処理
//=================================================
void CMeshField::Uninit(void)
{
	//頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//インデックスバッファの開放
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	CObject::Release();
}

//=================================================
// 更新処理
//=================================================
void CMeshField::Update(void)
{

}
//=================================================
// 描画処理
//=================================================
void CMeshField::Draw(void)
{

	CTextureManager* pTex = CManager::GetTexManager()->Instance();

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, CTextureManager::Instance()->GetAddress(m_nIdx));

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0, 0, MaxVtx, 0, PrimitveNum); //頂点情報構造体のサイズ
}