#pragma once

#include "MySprite.h"
#include <stdio.h>

#define		MAX_ANI			6
#define		MAX_ANI_FRAME	18
#define		MAX_OBJECT      3

class CMyAnimationBObejct2 : public CMySprite
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
	RECT m_rcCollision[MAX_OBJECT];
	int left, top, width, height;
	float bottomCol, leftCol, rightCol;

	float m_positionX[MAX_OBJECT] = { 450, 900, 0 };

	float m_positionY = 290;

	void Move(DWORD deltaTime, float speed)
	{
		for (int i = 0; i < 3; ++i)
		{
			m_positionX[i] -= (speed * deltaTime / 1000);
		}
	}

	CMyAnimationBObejct2();
	virtual ~CMyAnimationBObejct2();
	void Create(LPDIRECT3DDEVICE9 pDevice, char* filename);
	void OnDraw();
	void OnUpdate(float time);
};

