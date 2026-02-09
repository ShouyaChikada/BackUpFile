//=================================================
//
// [meshtrajectory.cpp]	// 軌跡の処理全般
// Author:chikada shouya
//
//=================================================
#include "meshtrajectory.h"
#include "manager.h"
#include "texturemanager.h"
#include "cmeteorock.h"
#include "effect.h"
#include "debugproc.h"

namespace MeshTrajectory
{
	int X_Block = 6;																// X方向のブロック数
	int Z_Block = 6;																// Z方向のブロック数
	int VtxNum = ((X_Block + 1) * (Z_Block + 1));									// 頂点数
	int IndexNum = X_Block * Z_Block * 2 + (Z_Block - 1) * 12;						// ポリゴン数
	int PrimitveNum = X_Block * Z_Block * 2 + (Z_Block + (Z_Block - 1) * 4);		// インデックス数
	int nMaxIdx = 16;																// インデックスの最大数	
	int nPullOut = 2;																// 引く変数
	float fTrajWidth = 10.0f;														// 軌跡をつけるときの幅
	float fColor = 0.3f;															// カラーの引数用変数
};

//=================================================
// コンストラクタ
//=================================================
CMeshTrajectory::CMeshTrajectory(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;

	m_rot = VEC3_NULL;
	m_pos = VEC3_NULL;
	m_move = VEC3_NULL;

	m_nIdx = NULL;
}

//=================================================
// デストラクタ
//=================================================
CMeshTrajectory::~CMeshTrajectory()
{

}

//=================================================
// 生成
//=================================================
CMeshTrajectory* CMeshTrajectory::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col)
{
	CMeshTrajectory* pMeshTrajectory = nullptr;
	pMeshTrajectory = new CMeshTrajectory;

	if (pMeshTrajectory != nullptr)
	{
		pMeshTrajectory->SetPosition(pos);
		pMeshTrajectory->SetRot(rot);
		pMeshTrajectory->SetColor(col);
		pMeshTrajectory->Init();
		return pMeshTrajectory;
	}
	else
	{
		return nullptr;
	}
}

//=================================================
// 初期化処理
//=================================================
HRESULT CMeshTrajectory::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_nIdx = CTextureManager::Instance()->Register("data\\TEXTURE\\Afterimage.jpg");

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MeshTrajectory::VtxNum,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff, NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MeshTrajectory::IndexNum,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	VERTEX_3D* pVtx = nullptr;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	
	for (int nCnt = 0; nCnt < MeshTrajectory::nMaxIdx / MeshTrajectory::nPullOut; nCnt++)
	{
		// 頂点座標の設定
		pVtx[nCnt * MeshTrajectory::nPullOut].pos = D3DXVECTOR3((m_pos.x + MeshTrajectory::fTrajWidth), m_pos.y, m_pos.z + (nCnt * MeshTrajectory::fTrajWidth));
		pVtx[(nCnt * MeshTrajectory::nPullOut) + 1].pos = D3DXVECTOR3((m_pos.x - MeshTrajectory::fTrajWidth), m_pos.y, m_pos.z + (nCnt * MeshTrajectory::fTrajWidth));

		//法線の設定
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCnt + MeshTrajectory::X_Block].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}

	for (int nCnt = 0; nCnt < MeshTrajectory::nMaxIdx; nCnt++)
	{

		//カラー設定
		pVtx[nCnt].col = m_col;
		
		if (nCnt >= MeshTrajectory::nMaxIdx)
		{
			//カラー設定
			pVtx[nCnt].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, 0.0f);
		}
		else if (nCnt >= MeshTrajectory::nMaxIdx - MeshTrajectory::nPullOut)
		{
			//カラー設定
			pVtx[nCnt].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, MeshTrajectory::fColor);
		}
		else if (nCnt >= MeshTrajectory::nMaxIdx - MeshTrajectory::nPullOut - MeshTrajectory::nPullOut)
		{
			//カラー設定
			pVtx[nCnt].col = D3DXCOLOR(m_col.r,m_col.g,m_col.b,MeshTrajectory::fColor * MeshTrajectory::nPullOut);
		}
	}

	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
	pVtx[14].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[15].tex = D3DXVECTOR2(1.0f,1.0f);



	// アンロック
	m_pVtxBuff->Unlock();

	// 頂点情報の設定
	WORD* pIdx = nullptr;

	//インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);


	//インデックスの設定
	for (int nCnt = 0; nCnt < MeshTrajectory::nMaxIdx / MeshTrajectory::nPullOut; nCnt++)
	{
		pIdx[nCnt * MeshTrajectory::nPullOut] = (nCnt * MeshTrajectory::nPullOut) + 1;
		pIdx[(nCnt * MeshTrajectory::nPullOut) + 1] = nCnt * MeshTrajectory::nPullOut;
	}

	pIdx[16] = 1;

	//インデックスバッファのアンロック
	m_pIdxBuff->Unlock();

	return S_OK;
}

//=================================================
// 終了処理
//=================================================
void CMeshTrajectory::Uninit(void)
{
	// 頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// インデックスバッファの開放
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	// 破棄
	CObject::Release();
}

//=================================================
// 更新処理
//=================================================
void CMeshTrajectory::Update(void)
{

}

//=================================================
// 描画処理
//=================================================
void CMeshTrajectory::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// FOGを消す
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);

	// 計算用マトリックス
	D3DXMATRIX mtxRot;

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// 通常のアルファブレンド設定
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Zバッファへの書込みを無効にする
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	// テクスチャの設定
	pDevice->SetTexture(0, CTextureManager::Instance()->GetAddress(m_nIdx));

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0, 0, MeshTrajectory::VtxNum, 0, MeshTrajectory::PrimitveNum); //頂点情報構造体のサイズ

	// Zバッファへの書込みを無効にする
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//CDebugProc::Print("-------------{ 軌跡 }-------------\n");
	//CDebugProc::Print("軌跡 : { %.2f %.2f %.2f }\n", m_pos.x, m_pos.y, m_pos.z);
}

//=================================================
// 軌跡用の処理
//=================================================
void CMeshTrajectory::SetTrajectory(D3DXVECTOR3 pos, bool bCheck0, bool bCheck1, float fRotValue)
{
	VERTEX_3D* pVtx = nullptr;

	// キーボード
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

	int nData0 = 14;
	int nData1 = 15;

	if (m_pVtxBuff != nullptr)
	{
		//頂点バッファをロック
 		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < MeshTrajectory::nMaxIdx / MeshTrajectory::nPullOut; nCnt++)
		{
			if (nData0 == 0)
			{
				if ((bCheck0 == true && bCheck1 == false))
				{
					// 今の塵の座標を代入
					pVtx[0].pos = D3DXVECTOR3(pos.x + sinf(fRotValue) * MeshTrajectory::fTrajWidth, pos.y, pos.z + cosf(fRotValue) * MeshTrajectory::fTrajWidth);
				}
				else if (bCheck1 == true && bCheck0 == false)
				{
					// 今の塵の座標を代入
					pVtx[0].pos = D3DXVECTOR3(pos.x - sinf(fRotValue) * MeshTrajectory::fTrajWidth, pos.y, pos.z - cosf(fRotValue) * MeshTrajectory::fTrajWidth);
				}
				else if (bCheck0 == false && bCheck1 == false)
				{
					// 今の塵の座標を代入
					pVtx[0].pos = D3DXVECTOR3(pos.x + MeshTrajectory::fTrajWidth, pos.y, pos.z);
				}
			}
			else
			{
				// １つ前の位置を代入
				pVtx[nData0].pos = pVtx[nData0 - MeshTrajectory::nPullOut].pos;
			}

			if (nData1 == 1)
			{
				if ((bCheck0 == true && bCheck1 == false))
				{
					// 今の塵の座標を代入
					pVtx[1].pos = D3DXVECTOR3(pos.x - sinf(fRotValue) * MeshTrajectory::fTrajWidth, pos.y, pos.z - cosf(fRotValue) * MeshTrajectory::fTrajWidth);
				}
				else if (bCheck1 == true && bCheck0 == false)
				{
					// 今の塵の座標を代入
					pVtx[1].pos = D3DXVECTOR3(pos.x + sinf(fRotValue) * MeshTrajectory::fTrajWidth, pos.y, pos.z + cosf(fRotValue) * MeshTrajectory::fTrajWidth);
				}
				else if (bCheck0 == false && bCheck1 == false)
				{
					// 今の塵の座標を代入
					pVtx[1].pos = D3DXVECTOR3(pos.x - MeshTrajectory::fTrajWidth, pos.y, pos.z);
				}
			}
			else
			{
				// １つ前の位置を代入
				pVtx[nData1].pos = pVtx[nData1 - MeshTrajectory::nPullOut].pos;

			}

			nData0 -= MeshTrajectory::nPullOut;
			nData1 -= MeshTrajectory::nPullOut;
		}

		//アンロック
		m_pVtxBuff->Unlock();

#ifndef _DEBUG

		if (pInputKeyboard->GetPress(DIK_F2) == true)
		{
			for (int nCnt = 0; nCnt < MeshTrajectory::nMaxIdx; nCnt++)
			{
				// 軌跡の頂点に合わせて生成
				CEffect::Create(pVtx[nCnt].pos, COLOR_NULL, VEC3_NULL, (int)MeshTrajectory::fTrajWidth, "data\\TEXTURE\\effect000.jpg");
			}
		}

#endif
	}
}