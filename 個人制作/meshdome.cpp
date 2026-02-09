//=================================================
//
// [meshdome.cpp]
// Author:chikada shouya
//
//=================================================
#include "meshdome.h"
#include "manager.h"
#include "texturemanager.h"

using namespace std;

//=================================================
// コンストラクタ
//=================================================
CMeshDome::CMeshDome(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = NULL;
	m_rot = VEC3_NULL;
	m_pos = VEC3_NULL;
	m_fRadius = NULL;
	m_nIdx = NULL;
}

//=================================================
// デストラクタ
//=================================================
CMeshDome::~CMeshDome()
{

}

//=================================================
// 生成
//=================================================
CMeshDome* CMeshDome::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius)
{
	CMeshDome* pMeshDome = nullptr;
	pMeshDome = new CMeshDome;

	if (pMeshDome != nullptr)
	{
		pMeshDome->m_pos = pos;
		pMeshDome->m_rot = rot;
		pMeshDome->m_fRadius = fRadius;
		pMeshDome->Init();
		return pMeshDome;
	}
	else
	{
		return nullptr;
	}
}

//=================================================
// 初期化処理
//=================================================
HRESULT CMeshDome::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CTextureManager* pTex = CManager::GetTexManager()->Instance();
	m_nIdx = pTex->Register("data\\TEXTURE\\sea02s.jpg");

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHDOME_MAX_VTX,
		D3DUSAGE_WRITEONLY,
		D3DFVF_VERTEX,
		D3DPOOL_MANAGED,
		&m_pVtxBuff, NULL);

	return S_OK;
}

//=================================================
// 終了処理
//=================================================
void CMeshDome::Uninit(void)
{
	//頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	CObject::Release();
}

//=================================================
// 更新処理
//=================================================
void CMeshDome::Update(void)
{


}

//=================================================
// 描画処理
//=================================================
void CMeshDome::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// FOGを消す
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	vector<Vertex> vertices;

	GenerateSphereVertices(m_fRadius, 6, 6, vertices);  // 半径1.0、20分割

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// スフィアの描画
	RenderSphere(pDevice, vertices, 6, 6);

	pDevice->Present(NULL, NULL, NULL, NULL);

}

//=================================================
// スフィア用緯度と経度に基づいて頂点を計算
//=================================================
void CMeshDome::GenerateSphereVertices(float radius, int slices, int stacks, vector<Vertex>& vertices)
{
	for (int i = 0; i <= stacks; ++i)
	{
		float phi = D3DX_PI * i / stacks;  // 緯度
		for (int j = 0; j <= slices; ++j)
		{
			float theta = 2.0f * D3DX_PI * j / slices;  // 経度

			Vertex v = {};
			v.x = radius * sinf(phi) * cosf(theta);
			v.y = radius * cosf(phi);
			v.z = radius * sinf(phi) * sinf(theta);
			v.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // 白色
			vertices.push_back(v);
		}
	}
}

//=================================================
// スフィアの描画
//=================================================
void CMeshDome::RenderSphere(LPDIRECT3DDEVICE9 pDevice, const vector<Vertex>& vertices, int slices, int stacks)
{

	for (int i = 0; i < stacks; ++i)
	{
		for (int j = 0; j < slices; ++j)
		{
			vector<Vertex> fan = {};

			// 三角形ファンの中心
			fan.push_back(vertices[i * (slices + 1) + j]);

			// 周囲の頂点
			fan.push_back(vertices[(i + 1) * (slices + 1) + j]);
			fan.push_back(vertices[(i + 1) * (slices + 1) + (j + 1)]);
			fan.push_back(vertices[i * (slices + 1) + (j + 1)]);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

			// 描画ループ
			pDevice->SetFVF(D3DFVF_VERTEX);

			//テクスチャの設定
			pDevice->SetTexture(0, CTextureManager::Instance()->GetAddress(m_nIdx));

			// 描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, fan.size() - 2, fan.data(), sizeof(Vertex));

		}
	}
}