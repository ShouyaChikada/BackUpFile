//=================================================
//
//	explosion.cpp // 爆発の処理メイン
// 
//	Author:近田尚也
//
//=================================================
#include "explosion.h"

namespace Explosion
{
	float fAnimNum = 0.125f;	// アニメーションするテクスチャのサイズ
	int nDivideNum = 8;			// アニメーションを割る値
	int nMaxAnim = 7;			// アニメーションのマックス数
	int nDivide = 4;			// アニメーションカウンターを割る数
	int nNullNum = 0;			// 初期化用数値
};
//=================================================
// コンストラクタ
//=================================================
CExplosion::CExplosion()
{
	m_nCounterAnim = NULL;
	m_nPatternAnim = NULL;
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
	// 基底クラスの初期化
	CBillboard::Init();

	return S_OK;
}

//=================================================
// 破棄
//=================================================
void CExplosion::Uninit(void)
{
	// 基底クラスの破棄
	CBillboard::Uninit();
}

//=================================================
// 更新
//=================================================
void CExplosion::Update(void)
{
	// 基底クラスの破棄
	CBillboard::Update();

	// アニメーションカウンターを加算
	m_nCounterAnim++;

	// アニメーションカウンターが０だったら
	if ((m_nCounterAnim % Explosion::nDivide) == Explosion::nNullNum)
	{
		// アニメーションカウンターを０に
		m_nCounterAnim = Explosion::nNullNum;

		// アニメーションパターンを割り代入
		m_nPatternAnim = (m_nPatternAnim++) % Explosion::nDivideNum;

		// セットアニメーションに代入
		SetAnim((float)m_nPatternAnim, Explosion::fAnimNum);
	}

	// アニメーションパターンが超えたら
	if (m_nPatternAnim >= Explosion::nMaxAnim)
	{
		// 破棄
		Uninit();
	}
}

//=================================================
// 描画
//=================================================
void CExplosion::Draw(void)
{
	// 基底クラスの描画
	CBillboard::Draw();
}