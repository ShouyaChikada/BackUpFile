//=================================================
//
//	energy.h スタミナのヘッダー
// 
//	Author:近田尚也
//
//=================================================
#ifndef _ENERGY_H_
#define _ENERGY_H_

#include "main.h"
#include "object2D.h"

class CEnergy : public CObject2D
{
public:
	// タイプ
	typedef enum
	{
		ENERGY_NONE = 0,	// 何もないタイプ
		ENERGY_GAUGE,		// ゲージタイプ
		ENERGY_MOVE,		// テクスチャが動くタイプ
		ENERGY_MAX
	}ENERGY;

	CEnergy(int nPriority = 6);
	~CEnergy();
	//プロトタイプ宣言
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetEnergyType(ENERGY type) { m_Type = type; }
	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos = 現在の位置"></param>
	/// <param name="fWidth = 横幅"></param>
	/// <param name="fHeight = 縦幅"></param>
	/// <param name="FilePath = テクスチャネーム"></param>
	/// <param name="type = 2Dオブジェクトの生成タイプ"></param>
	/// <returns></returns>
	static CEnergy* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, std::string FilePath, CObject2D::ANCHORTYPE type, ENERGY Energy);

private:
	ENERGY m_Type;		// ゲージや他のUIの種類補間用変数
	int m_nCharge;		// スタミナの保存用変数
	float m_fCol;		// スタミナゲージのカラー用変数
	float m_fPosTexU;	// テクスチャを動かす用変数
	bool m_bColChange;	// カラーチェンジ判別変数
};
#endif