//=================================================
//
//	billboard.h
// 
//	Author:近田尚也
//
//=================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"
#include "object.h"

//マクロ

class CBillboard :public CObject
{
public:

	// タイプ
	typedef enum
	{
		TYPE_NONE = 0,	// 何もないタイプ
		TYPE_BLINKING,	// 点滅するタイプ
		TYPE_SBLINKING,
		TYPE_MAX
	}TYPE;

	CBillboard(int nPriority = 5);
	~CBillboard();
	//プロトタイプ宣言
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetAnim(float fTex, float fAdd);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos = 現在の位置"></param>
	/// <param name="fWidth = ビルボードの横幅"></param>
	/// <param name="fHeight = ビルボードの縦幅"></param>
	/// <param name="FilePath = テクスチャネーム"></param>
	/// <param name="type = ビルボードタイプ"></param>
	/// <returns></returns>
	static CBillboard* Create(D3DXVECTOR3 pos,  D3DXVECTOR2 Tex, float fWidth, float fHeight, std::string FilePath, TYPE type);

	// ゲッター
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	bool GetFinish(void) { return m_bFinish; }

	// セッター
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetColor(D3DXCOLOR col) { m_col = col; }
	void SetPath(std::string Path) { m_Path = Path; }
	void SetType(TYPE type) { m_Type = type; }
	void SetWidth(float fWidth) { m_fWidth = fWidth; }
	void SetHeight(float fHeight) { m_fHeight = fHeight; }
	void SetTex(D3DXVECTOR2 Tex) { m_Tex = Tex; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファ
	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス
	D3DXVECTOR3 m_pos;					// 位置
	D3DXVECTOR3 m_rot;					// 向き
	D3DXVECTOR3 m_dir;					// 向き格納
	D3DXVECTOR2 m_Tex;					// テクスチャのサイズ
	D3DXCOLOR m_col;					// カラー
	TYPE m_Type;						// ビルボードタイプ
	std::string m_Path;					// テクスチャパス
	bool m_bTest;						// 判定のテスト
	bool m_bUse;						// 使用しているかどうかの判定
	bool m_bBlinking;					// 点滅してる判定
	bool m_bFinish;						// アニメーションの終了判定
	float m_fWidth;						// 縦幅
	float m_fHeight;					// 横幅
	int m_nIdx;							// インデックス用変数
	int m_nDeleteTime;					// 消えるまでの時間用変数
};
#endif