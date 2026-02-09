//=================================================
//
//	titlemanager.h
// 
//	Author:ãﬂìcèÆñÁ
//
//=================================================
#ifndef _TITLEMANAGER_H_
#define _TITLEMANAGER_H_

#include "object2D.h"
#include <string>

class CTitleManager : public CObject2D
{
public:
	CTitleManager(int nPriolity = 4);
	~CTitleManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTitleManager* Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, std::string aName);

private:
	std::string FilePath;
};


#endif