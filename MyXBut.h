#pragma once

#include "MySprite.h"
#include <stdio.h>

#define		MAX_ANI		6
#define MAX_ANI_FRAME	18

class CMyXButton : public CMySprite
{
protected:
	RECT m_rcFrame[MAX_ANI][MAX_ANI_FRAME];
	float m_fDuration[MAX_ANI][MAX_ANI_FRAME];

	unsigned char m_maxAni; // 총 애니메이션 개수
	unsigned short m_nFrame;
	float m_interval;
	int m_infoFrame[MAX_ANI];


public:
	RECT  m_rcCollision[2];
	BOOL isCollision(POINT pt, RECT col);
	float bottomCol, leftCol, rightCol;

	float m_positionX[2] = { 10.0f, 10.0f };
	float m_positionY[2] = { 10.0f, 10.0f };

	int buttonState = 0;
	unsigned char m_aniType;

	CMyXButton();
	virtual ~CMyXButton();
	void Create(LPDIRECT3DDEVICE9 pDevice, char* filename);
	void OnDraw(int selection);
	void OnUpdate(float time, int selection);
};