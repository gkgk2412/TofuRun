#pragma once

#include "MySprite.h"
#include <stdio.h>

#define		MAX_ANI		6
#define MAX_ANI_FRAME	18

class CMyAnimationTObejct : public CMySprite
{
protected:
	RECT m_rcFrame[MAX_ANI][MAX_ANI_FRAME];
	float m_fDuration[MAX_ANI][MAX_ANI_FRAME];
	unsigned char m_aniType;
	unsigned char m_maxAni; // 총 애니메이션 개수
	unsigned short m_nFrame;
	float m_interval;
	int m_infoFrame[MAX_ANI];

public:
	RECT m_rcCollision[1];
	int left, top, width, height;
	float bottomCol, leftCol, rightCol;

	float m_positionX = 50.0f;

	float m_positionY = 0.0f;

	void Move(DWORD deltaTime, float speed)
	{
		m_positionX -= (speed * deltaTime / 1000);
	}

	CMyAnimationTObejct();
	virtual ~CMyAnimationTObejct();
	void Create(LPDIRECT3DDEVICE9 pDevice, char* filename);
	void OnDraw();
	void OnUpdate(float time);
};

