#pragma once

#include "MySprite.h"
#include <stdio.h>

#define		MAX_ANI		6
#define MAX_ANI_FRAME	12

class CMyFloorSprite : public CMySprite
{
protected:
	RECT m_rcFrame[MAX_ANI][MAX_ANI_FRAME];
	unsigned char m_maxAni; // �� �ִϸ��̼� ����
	unsigned short m_nFrame;
	float m_interval;

	int m_infoFrame[MAX_ANI];
	unsigned char m_aniType;

	float m_fDuration[MAX_ANI][MAX_ANI_FRAME];

public:
	CMyFloorSprite();
	virtual ~CMyFloorSprite();
	float positionX = 0.0f;
	float positionX2 = 1150.0f;

	void Move(DWORD deltaTime, float speed)
	{
		positionX -= (speed * deltaTime / 1000);
		positionX2 -= (speed * deltaTime / 1000);
	}

	void Create(LPDIRECT3DDEVICE9 pDevice, char* filename);
	void OnDraw();
	void OnUpdate(float time);
};

