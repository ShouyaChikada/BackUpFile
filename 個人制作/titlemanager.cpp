//=================================================
//
//	titlemanager.cpp
// 
//	Author:近田尚也
//
//=================================================
#include "titlemanager.h"
#include "manager.h"
#include "texturemanager.h"

// コンストラクタ
CTitleManager::CTitleManager(int nPriolity) : CObject2D(nPriolity)
{
	FilePath = {};
}

// デストラクタ
CTitleManager::~CTitleManager()
{

}

// 生成
CTitleManager* CTitleManager::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, std::string aName)
{
	CTitleManager* pTitleManager = new CTitleManager;

	if (pTitleManager != nullptr)
	{
		pTitleManager->SetPosition(pos);
		pTitleManager->SetTexPath(aName);
		pTitleManager->Init();
		pTitleManager->SetSize(Size.x, Size.y);
		pTitleManager->FilePath = aName;
		pTitleManager->SetType(CObject2D::ANCHORTYPE_CENTER);

		return pTitleManager;
	}
	else
	{
		return nullptr;
	}
}

// 初期化
HRESULT CTitleManager::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

// 終了
void CTitleManager::Uninit(void)
{
	CObject2D::Uninit();
}

// 更新
void CTitleManager::Update(void)
{
	CObject2D::Update();

	/*if (FilePath == "data\\TEXTURE\\cloud.png")
	{

	}*/
}

// 描画
void CTitleManager::Draw(void)
{
	// FOGを消す
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);

	CObject2D::Draw();
}