#pragma once

#include "MySprite.h"
#include <stdio.h>

#define		MAX_ANI		6
#define MAX_ANI_FRAME	18

class CMyBackButton : public CMySprite
{
protected:
	RECT m_rcFrame[MAX_ANI][MAX_ANI_FRAME];
	float m_fDuration[MAX_ANI][MAX_ANI_FRAME];

	unsigned char m_maxAni; // 총 애니메이션 개수
	unsigned short m_nFrame;
	float m_interval;
	int m_infoFrame[MAX_ANI];


public:
	RECT  m_rcCollision;
	BOOL isCollision(POINT pt);
	float bottomCol, leftCol, rightCol;

	float m_positionX = 10.0f;
	float m_positionY = 10.0f;

	int buttonState = 0;
	unsigned char m_aniType;

	CMyBackButton();
	virtual ~CMyBackButton();
	void Create(LPDIRECT3DDEVICE9 pDevice, char* filename);
	void OnDraw();
	void OnUpdate(float time);
};

