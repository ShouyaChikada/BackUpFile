//=================================================
//
// [debugproc.h]
// Author:chikada shouya
//
//=================================================
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

#include "main.h"

constexpr int nMaxIdx = 1024;	// 文字数の最大値

class CDebugProc
{
public:

	CDebugProc();
	~CDebugProc();
	void Init(void);
	void Uninit(void);

	static void Print(const char* fmt,...);
	static void Draw(int aWidth, int aHeight);
	static void End(void) { m_nowIndx = 0; };
	static bool GetEnable(void) { return m_Enable; };
	static void SetEnable(bool Enable) { m_Enable = Enable; };
private:

	static LPD3DXFONT m_pFont;		//フォントへのポインタ
	static char m_aStr[nMaxIdx];		//文字列を格納するバッファ
	static int m_nowIndx;
	static bool m_Enable;
	static int m_nCountFPS;
};

#endif 