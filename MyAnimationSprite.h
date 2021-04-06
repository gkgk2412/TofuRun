#pragma once

#include "MySprite.h"
#include <stdio.h>

#define		MAX_ANI		10
#define MAX_ANI_FRAME	12
#define COOKIEPOSITION  255

class CMyAnimationSprite : public CMySprite
{
protected:
	RECT m_rcFrame[MAX_ANI][MAX_ANI_FRAME];
	float m_fDuration[MAX_ANI][MAX_ANI_FRAME];
	RECT rcCollision;

	unsigned char m_maxAni; // 총 애니메이션 개수
	unsigned short m_nFrame;
	float m_interval;
	int m_infoFrame[MAX_ANI];

	//left, right, top, bottom
	int left, width, top, height;
	RECT  m_rcCollision;

public:
	CMyAnimationSprite();
	virtual ~CMyAnimationSprite();
	unsigned char m_aniType;
	//character position
	float m_positionX = 200.0f;
	float m_positionY = 255.0f;

	bool checkPoint = false;

	//characater state
	int charState = 0;
	int checkBounsFrame = 0;
	int checkBounsFrame2 = 0;

	D3DXMATRIX* D3DXMatrixScaling(

		D3DXMATRIX* pOut,
		FLOAT sx,
		FLOAT sy,
		FLOAT sz
	);

	void Create(LPDIRECT3DDEVICE9 pDevice, char *filename);
	void OnDraw();
	void OnUpdate(float time);

	BOOL isTrigger(RECT rect);
};


