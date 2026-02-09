//=================================================
//
// [debugproc.cpp]
// Author:chikada shouya
//
//=================================================
#include "debugproc.h"
#include "manager.h"

namespace DebugProc
{
	int nStartLine = 20;	// 書き始める最初の行
	int nColorR = 0;		// デバッグ表示カラー(R値)
	int nColorG = 255;		// デバッグ表示カラー(G値)
	int nColorB = 0;		// デバッグ表示カラー(B値)
	int nColorA = 255;		// デバッグ表示カラー(α値)
};

//=================================================
//静的メンバ変数
//=================================================
LPD3DXFONT CDebugProc::m_pFont = NULL;
char CDebugProc::m_aStr[nMaxIdx] = {};
int CDebugProc::m_nCountFPS = NULL;
int CDebugProc::m_nowIndx = NULL;
bool CDebugProc::m_Enable = true;

//=================================================
// コンストラクタ
//=================================================


CDebugProc::CDebugProc()
{
	
}

//=================================================
// デストラクタ
//=================================================
CDebugProc::~CDebugProc()
{

}

//=================================================
// 初期化
//=================================================
void CDebugProc::Init(void)
{
	m_nowIndx = NULL;

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
		
	//デバッグ表示用フォントの生成
	D3DXCreateFont(pDevice, DebugProc::nStartLine, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &m_pFont);
		
	memset(m_aStr, NULL, sizeof(m_aStr));
}

//=================================================
// 終了
//=================================================
void CDebugProc::Uninit(void)
{
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
}

//=================================================
// 追加
//=================================================
void CDebugProc::Print(const char* fmt, ...)
{
#if 1
	va_list args;//va_listマクロを使用

	va_start(args, fmt);

	if (m_nowIndx > nMaxIdx)
	{
		m_nowIndx = 0;
		return;
	}
	m_nowIndx  += vsprintf(&m_aStr[m_nowIndx], fmt, args);//vsprintfを使用する場合は　　#define _CRT_SECURE_WARNINGS
	
	va_end(args);

#endif
}

//=================================================
// 描画
//=================================================
void CDebugProc::Draw(int aWidth,int aHeight)
{
#ifdef _DEBUG

	if (m_Enable == true)
	{
		RECT rect = { aWidth,aHeight, SCREEN_WIDTH,SCREEN_HEIGHT };

		//テキストの描画
		m_pFont->DrawText(NULL, &m_aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(DebugProc::nColorR, DebugProc::nColorG, DebugProc::nColorB, DebugProc::nColorA));

		// バッファをクリア
		memset(&m_aStr[0], NULL, sizeof(m_aStr));
	}

#endif
}