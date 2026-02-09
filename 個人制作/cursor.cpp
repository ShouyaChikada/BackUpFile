//=================================================
//
// [cursor.cpp]	// 隕石を飛ばす方向矢印の処理全般
// Author:chikada shouya
//
//=================================================
#include "cursor.h"

//=================================================
// コンストラクタ
//=================================================
CCursor::CCursor()
{
	m_bLook = false;
}

//=================================================
// デストラクタ
//=================================================
CCursor::~CCursor()
{

}

//=================================================
// 生成
//=================================================
CCursor* CCursor::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius)
{
	CCursor* pCursor = nullptr;
	pCursor = new CCursor;

	if (pCursor != nullptr)
	{
		pCursor->SetPosition(pos);
		pCursor->SetRot(rot);
		pCursor->SetRadius(fRadius);
		pCursor->SetTexPath("data\\TEXTURE\\UP.png");
		pCursor->Init();
		return pCursor;
	}
	else
	{
		return nullptr;
	}
}

//=================================================
// 初期化
//=================================================
HRESULT CCursor::Init(void)
{
	// 基底クラスの初期化
	CMeshField::Init();

	return S_OK;
}

//=================================================
// 破棄
//=================================================
void CCursor::Uninit(void)
{
	// 基底クラスの破棄
	CMeshField::Uninit();
}

//=================================================
// 更新
//=================================================
void CCursor::Update(void)
{
	// 基底クラスの更新
	CMeshField::Update();
}

//=================================================
// 描画
//=================================================
void CCursor::Draw(void)
{
	// 基底クラスの描画
	if(m_bLook)CMeshField::Draw();
}
