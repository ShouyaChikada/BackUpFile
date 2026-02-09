//=================================================
//
//	explosion.h // 爆発の処理ヘッダー
// 
//	Author:近田尚也
//
//=================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "billboard.h"

class CExplosion : public CBillboard
{
public:
	CExplosion();
	~CExplosion();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos = 現在の位置"></param>
	/// <param name="fWidth = 縦幅"></param>
	/// <param name="fHeight = 横幅"></param>
	/// <param name="fTex = テクスチャサイズ"></param>
	/// <param name="fAdd = テクスチャサイズの加算用変数"></param>
	/// <param name="TYPE_ANIMATION = ビルボードタイプ"></param>
	/// <returns></returns>
	static CExplosion* Create(D3DXVECTOR3 pos, D3DXVECTOR2 Tex, float fWidth, float fHeight, std::string FilePath, CBillboard::TYPE TYPE);

private:
	int m_nPatternAnim;	// アニメーションパターン用変数
	int m_nCounterAnim;	// アニメーションカウンター用変数
};

#endif