#pragma once

#include "MySprite.h"
#include <stdio.h>

#define		MAX_ANI		6
#define MAX_ANI_FRAME	18

class CMyAnimationStart : public CMySprite
{
protected:
	RECT m_rcFrame[MAX_ANI][MAX_ANI_FRAME];
	float m_fDuration[MAX_ANI][MAX_ANI_FRAME];

	unsigned char m_maxAni; // 총 애니메이션 개수
	unsigned short m_nFrame;
	float m_interval;
	int m_infoFrame[MAX_ANI];
	RECT  m_rcCollision;

public:
	BOOL isCollision(POINT pt);
	float m_positionX = 440.0f, m_positionY = 280.0f;

	int State = 0;
	unsigned char m_aniType;

	CMyAnimationStart();
	virtual ~CMyAnimationStart();
	void Create(LPDIRECT3DDEVICE9 pDevice, char* filename);
	void OnDraw();
	void OnUpdate(float time);
};

