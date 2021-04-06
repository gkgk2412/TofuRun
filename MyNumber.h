#pragma once

#include "MySprite.h"
#include <stdio.h>

#define		MAX_ANI		6
#define MAX_ANI_FRAME	18

class CMyAnimationNum : public CMySprite
{
protected:
	RECT m_rcFrame[MAX_ANI][MAX_ANI_FRAME];
	float m_fDuration[MAX_ANI][MAX_ANI_FRAME];

	unsigned char m_maxAni; // �� �ִϸ��̼� ����
	unsigned short m_nFrame;
	float m_interval;
	int m_infoFrame[MAX_ANI];


public:
	float m_positionX = 550.0f;
	float m_positionY = 0.0f;

	int numState = 1;
	unsigned char m_aniType;

	CMyAnimationNum();
	virtual ~CMyAnimationNum();
	void Create(LPDIRECT3DDEVICE9 pDevice, char* filename);
	void OnDraw();
	void OnUpdate(float time);
};