#pragma once

#include "MySprite.h"
#include <stdio.h>

#define		MAX_ANI		6
#define MAX_ANI_FRAME	18

class CMyAnimationButton : public CMySprite
{
protected:
	RECT m_rcFrame[MAX_ANI][MAX_ANI_FRAME];
	float m_fDuration[MAX_ANI][MAX_ANI_FRAME];

	unsigned char m_maxAni; // 총 애니메이션 개수
	unsigned short m_nFrame;
	float m_interval;
	int m_infoFrame[MAX_ANI];


public:
	RECT  m_rcCollision[3];
	BOOL isCollision(POINT pt, RECT col);
	//BOOL isCollision2(POINT pt);
	//BOOL isCollision3(POINT pt);

	float m_positionX = 640.0f;
	float m_positionY[3] = { 135.0f, 235.0f, 335.0f };

	int buttonState = 0;
	unsigned char m_aniType;

	CMyAnimationButton();
	virtual ~CMyAnimationButton();
	void Create(LPDIRECT3DDEVICE9 pDevice, char* filename);
	void OnDraw(int selection);
	void OnUpdate(float time, int selection);
};

