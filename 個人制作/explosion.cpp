//=================================================
//
//	explosion.cpp // 爆発の処理メイン
// 
//	Author:近田尚也
//
//=================================================
#include "explosion.h"

//=================================================
// コンストラクタ
//=================================================
CExplosion::CExplosion()
{
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
}

//=================================================
// デストラクタ
//=================================================
CExplosion::~CExplosion()
{

}

//=================================================
// 生成処理
//=================================================
CExplosion* CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Tex, float fWidth, float fHeight, std::string FilePath, CBillboard::TYPE TYPE)
{
	CExplosion* pExplosion = nullptr;
	pExplosion = new CExplosion;

	if (pExplosion != nullptr)
	{
		pExplosion->SetPosition(pos);
		pExplosion->SetTex(Tex);
		pExplosion->SetPath(FilePath);
		pExplosion->SetWidth(fWidth);
		pExplosion->SetHeight(fHeight);
		pExplosion->SetType(TYPE);
		pExplosion->Init();

		return pExplosion;
	}

	return nullptr;
}

//=================================================
// 初期化
//=================================================
HRESULT CExplosion::Init(void)
{
	// 親クラスの初期化
	CBillboard::Init();
	return S_OK;
}

//=================================================
// 破棄
//=================================================
void CExplosion::Uninit(void)
{
	// 親クラスの破棄
	CBillboard::Uninit();
}

//=================================================
// 更新
//=================================================
void CExplosion::Update(void)
{
	// 親クラスの破棄
	CBillboard::Update();

	m_nCounterAnim++;

	if ((m_nCounterAnim % 4) == 0)
	{
		m_nCounterAnim = 0;

		m_nPatternAnim = (m_nPatternAnim + 1) % 8;

		SetAnim((float)m_nPatternAnim, 0.125f);
	}

	if (m_nPatternAnim >= 7)
	{
		Uninit();
	}
}

//=================================================
// 描画
//=================================================
void CExplosion::Draw(void)
{
	// 親クラスの描画
	CBillboard::Draw();
}