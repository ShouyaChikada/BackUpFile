//=================================================
//
// [cursor.h]	// 隕石を飛ばす方向矢印のヘッダー
// Author:chikada shouya
//
//=================================================
#ifndef _CURSOR_H_
#define _CURSOR_H_

#include "meshfield.h"

class CCursor :	public CMeshField
{
public:
	CCursor();
	~CCursor();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw();

	static CCursor* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Radius);

	// セッター
	void SetLook(bool bLook) { m_bLook = bLook; }

private:
	bool m_bLook;	// 見える見えない判定
};

#endif