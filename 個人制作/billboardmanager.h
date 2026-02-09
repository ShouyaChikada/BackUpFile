//=================================================
//
//	BillboardManager.h	// ビルボード専用マネージャー
// 
//	Author:近田尚也
//
//=================================================
#ifndef _BILLBOARDMANAGER_H_
#define _BILLBOARDMANAGER_H_

#include "main.h"
#include "billboard.h"

class CBillboardManager
{
public:
	~CBillboardManager();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos = 現在の位置"></param>
	/// <param name="fWidth = ビルボードの横幅"></param>
	/// <param name="fHeight = ビルボードの縦幅"></param>
	/// <param name="FilePath = テクスチャネーム"></param>
	/// <param name="type = ビルボードタイプ"></param>
	/// <returns></returns>
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Tex, float fWidth, float fHeight, std::string FilePath, CBillboard::TYPE type);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ゲッター
	CBillboard* GetBillboard(void) { return m_pBillboard; }

	static CBillboardManager* Instance(void);

private:
	CBillboardManager();
	static CBillboardManager* m_pInstance;		// シングルトン変数
	CBillboard* m_pBillboard;
};
#endif