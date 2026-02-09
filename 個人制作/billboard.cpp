//=============================================
//
// billboard.cpp ビルボードの処理メイン
// author chikada shouya
//
//=============================================
#include "billboard.h"
#include "player.h"
#include "input.h"
#include "manager.h"

namespace
{
	int nVtx = 4;			// 頂点数
	int nDeleteNum = 180;	// 数字の初期化
}

//=============================================
// コンストラクタ
//=============================================
CBillboard::CBillboard(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = NULL;
	m_pos = VEC3_NULL;
	m_rot = VEC3_NULL;
	m_dir = VEC3_NULL;
	m_Tex = VEC2_NULL;
	m_col = COLOR_NULL;
	m_bTest = false;
	m_bUse = false;
	m_bBlinking = false;
	m_bFinish = false;
	m_fWidth = NULL;
	m_fHeight = NULL;
	m_nIdx = NULL;
	m_nDeleteTime = NULL;
	m_Path = {};
	m_Type = TYPE_NONE;
}

//=============================================
// デストラクタ
//=============================================
CBillboard::~CBillboard()
{

}

//=============================================
// オブジェクト3D生成
//=============================================
CBillboard* CBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Tex, float fWidth, float fHeight, std::string FilePath, TYPE type)
{
	CBillboard* pBillboard = nullptr;
	pBillboard = new CBillboard;

	// ローカルポインタがnullptrじゃなかったら
	if (pBillboard != nullptr)
	{
		pBillboard->SetPosition(pos);
		pBillboard->SetTex(Tex);
		pBillboard->SetWidth(fWidth);
		pBillboard->SetHeight(fHeight);
		pBillboard->SetPath(FilePath);
		pBillboard->SetType(type);
		pBillboard->Init();
		return pBillboard;
	}
	else
	{
		return nullptr;
	}
}

//=============================================
// 初期化処理
//=============================================
HRESULT CBillboard::Init(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_nIdx = CTextureManager::Instance()->Register(m_Path);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * nVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff, NULL);

	// 表示時間の設定(3秒)
	m_nDeleteTime = nDeleteNum;
	

	VERTEX_3D* pVtx = nullptr;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, +m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_fWidth, +m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, -m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+m_fWidth, -m_fHeight, 0.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_Tex.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, m_Tex.y);
	pVtx[3].tex = D3DXVECTOR2(m_Tex.x, m_Tex.y);
	
	//アンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================
// 終了処理
//=============================================
void CBillboard::Uninit(void)
{
	//頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//自分の破棄
	CObject::Release();
}

//=============================================
// 更新処理
//=============================================
void CBillboard::Update(void)
{
	VERTEX_3D* pVtx = nullptr;

	if (m_Type == TYPE_BLINKING)
	{
		if (m_nDeleteTime > 0)
		{

			if (m_bBlinking == false)
			{//フェードイン状態
				m_col.a -= 0.07f;	//ポリゴンを透明にしていく

				if (m_col.a <= 0.0f)
				{
					m_col.a = 0.0f;
					m_bBlinking = true;	//何もしていない状態に
				}
			}
			else if (m_bBlinking == true)
			{//フェードアウト状態
				m_col.a += 0.07f;	//ポリゴンを不透明にしていく

				if (m_col.a >= 0.5f)
				{
					m_col.a = 0.5f;
					m_bBlinking = false;	//フェードイン状態に
				}
			}

			//頂点バッファをロック
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			pVtx[0].col = m_col;
			pVtx[1].col = m_col;
			pVtx[2].col = m_col;
			pVtx[3].col = m_col;

			//アンロック
			m_pVtxBuff->Unlock();
		}
		else if (m_nDeleteTime <= 0)
		{
			Uninit();
		}

		m_nDeleteTime--;
	}

	if (m_Type == TYPE_SBLINKING)
	{
		
		if (m_bBlinking == false)
		{//フェードイン状態
			m_col.a -= 0.07f;	//ポリゴンを透明にしていく

			if (m_col.a <= 0.0f)
			{
				m_col.a = 0.0f;
				m_bBlinking = true;	//何もしていない状態に
			}
		}
		else if (m_bBlinking == true)
		{//フェードアウト状態
			m_col.a += 0.07f;	//ポリゴンを不透明にしていく

			if (m_col.a >= 0.5f)
			{
				m_col.a = 0.5f;
				m_bBlinking = false;	//フェードイン状態に
			}
		}

		//頂点バッファをロック
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		//アンロック
		m_pVtxBuff->Unlock();
		
	}
}

//=============================================
// 描画処理
//=============================================
void CBillboard::Draw(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// Z
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);	// Zの比較
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);		// Zバッファに書き込まない

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	D3DXMATRIX mtxView;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);	//ビューマトリックスの取得

	//カメラの逆行列を設定
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, CTextureManager::Instance()->GetAddress(m_nIdx));

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0, 2); //頂点情報構造体のサイズ

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//ライトを有効に戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);	// Zの比較方法変更
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);		// Zバッファに書き込む
}

//=============================================
// アニメーションの設定
//=============================================
void CBillboard::SetAnim(float fTex, float fAdd)
{
	VERTEX_2D* pVtx;

	// ロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(fTex * fAdd, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((fTex * fAdd)+ fAdd, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(fTex * fAdd, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((fTex * fAdd) + fAdd, 1.0f);

	// アンロック
	m_pVtxBuff->Unlock();
}