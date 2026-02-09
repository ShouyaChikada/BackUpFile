//=================================================
//
//	effect.cpp
// 
// Author:chikada shouya
//
//=================================================
#include"effect.h"
#include "texturemanager.h"
#include "manager.h"

namespace Effect
{
	D3DXVECTOR2 SetSize = D3DXVECTOR2(1.0f, 1.0f);	// サイズ設定
	float fWidth = 15.0f;							// 横のサイズ
	float fHeight = 15.0f;							// 縦のサイズ
	int nNullNum = 0;								// 初期化数値
}
//=================================================
// コンストラクタ
//=================================================
CEffect::CEffect()
{
	m_move = VEC3_NULL;
	m_nLife = NULL;			//寿命
}

//=================================================
// デストラクタ
//=================================================
CEffect::~CEffect()
{
}

//=================================================
// 生成
//=================================================
CEffect* CEffect::Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife, std::string FilePath)
{
	CEffect* pEffect = nullptr;
	pEffect = new CEffect;

	if (pEffect != nullptr)
	{
		pEffect->SetPosition(pos);
		pEffect->SetPath(FilePath);
		pEffect->SetTex(Effect::SetSize);
		pEffect->m_move = move;
		pEffect->m_nLife = nLife;
		pEffect->SetWidth(Effect::fWidth);
		pEffect->SetHeight(Effect::fHeight);
		pEffect->SetColor(col);
		pEffect->Init();
		return pEffect;
		
	}
	else
	{
		return nullptr;
	}
}

//=================================================
// 初期化
//=================================================
HRESULT CEffect::Init(void)
{
	CBillboard::Init();
	return S_OK;
}

//=================================================
// 終了処理
//=================================================
void CEffect::Uninit(void)
{
	CBillboard::Uninit();
}

//=================================================
//  更新処理
//=================================================
void CEffect::Update(void)
{
	// 位置の取得
	D3DXVECTOR3 pos = GetPosition();
	
	// 移動量を位置に加算
	pos += m_move;

	// ライフの現象
	m_nLife--;

	// ライフが0以下だったら
	if (m_nLife <= Effect::nNullNum)
	{
		// 破棄
 		Uninit();
	}
	else
	{
		// 位置の保存
		SetPosition(pos);
	}
}

//=================================================
// 描画処理
//=================================================
void CEffect::Draw(void)
{
	// FOGを消す
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//αテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// 加算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 描画
	CBillboard::Draw();

	// 設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//αテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}