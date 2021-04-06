#include "MyBObject2.h"
#include <ctime>

CMyAnimationBObejct2::CMyAnimationBObejct2()
{
	m_nFrame = 0;
	m_interval = 0.0f;
	m_aniType = 0;
}

CMyAnimationBObejct2::~CMyAnimationBObejct2()
{
}

void CMyAnimationBObejct2::Create(LPDIRECT3DDEVICE9 pDevice, char* filename)
{
	char imgname[128];
	int aniIndex, nFrame;
	float duration;
	int left, top, width, height;

	FILE* fp = fopen(filename, "rt");

	if (fp == NULL)
		return;

	fscanf(fp, "%s", imgname);
	CMySprite::Create_BObject2(pDevice, imgname, 80, 70);

	fscanf(fp, "%d", &m_maxAni);

	for (int ani = 0; ani < m_maxAni; ++ani)
	{
		fscanf(fp, "%d %d", &aniIndex, &nFrame);

		//0번째 인덱스는 총 3프레임...프레임 별로 저장. 
		m_infoFrame[ani] = nFrame;

		for (int i = 0; i < nFrame; ++i)
		{
			fscanf(fp, "%d %d %d %d %f", &left, &top, &width, &height, &duration);
			SetRect(&m_rcFrame[aniIndex][i], left, top, width, height);
			m_fDuration[aniIndex][i] = duration;
		}
	}

	fclose(fp);
}

void CMyAnimationBObejct2::OnDraw()
{
	RECT srcRect = m_rcFrame[m_aniType][m_nFrame];
	srcRect.bottom = srcRect.top + m_rcFrame[m_aniType][m_nFrame].bottom;
	srcRect.right = srcRect.left + m_rcFrame[m_aniType][m_nFrame].right;

	//콜라이더
	for (int i = 0; i < 3; i++)
	{
		m_rcCollision[i].left = (int)m_positionX[i]+10;
		m_rcCollision[i].top = (int)m_positionY+30;
		m_rcCollision[i].right = m_rcCollision[i].left + m_rcFrame[m_aniType][m_nFrame].right - 50;
		m_rcCollision[i].bottom = m_rcCollision[i].top + m_rcFrame[m_aniType][m_nFrame].bottom;
	}

	D3DXVECTOR3 vCenter(0.0f, 0.0f, 0.0f);

	D3DXVECTOR3 vPosition(m_positionX[0], m_positionY, 0.0f);
	D3DXVECTOR3 vPosition2(m_positionX[1], m_positionY, 0.0f);
	D3DXVECTOR3 vPosition3(m_positionX[2], m_positionY, 0.0f);


	m_pDonutSprite[8]->Begin(D3DXSPRITE_ALPHABLEND);
	m_pDonutSprite[9]->Begin(D3DXSPRITE_ALPHABLEND);
	m_pDonutSprite[10]->Begin(D3DXSPRITE_ALPHABLEND);

	m_pDonutSprite[8]->Draw(m_pDonutTexture[8],
		&srcRect,
		&vCenter,
		&vPosition,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

	m_pDonutSprite[9]->Draw(m_pDonutTexture[9],
		&srcRect,
		&vCenter,
		&vPosition2,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

	m_pDonutSprite[10]->Draw(m_pDonutTexture[10],
		&srcRect,
		&vCenter,
		&vPosition3,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

	m_pDonutSprite[8]->End();
	m_pDonutSprite[9]->End();
	m_pDonutSprite[10]->End();

	bottomCol = m_rcFrame[0][0].bottom;
	leftCol = m_rcFrame[0][0].left;
	rightCol = m_rcFrame[0][0].right;
}

void CMyAnimationBObejct2::OnUpdate(float timeE)
{
	m_interval += timeE;

	if (m_interval > m_fDuration[m_aniType][m_nFrame])
	{
		m_interval = 0.0f;
		m_nFrame++;

		if (m_nFrame >= m_infoFrame[m_aniType])
		{
			m_nFrame = 0;
		}
	}

	srand(time(NULL));

	//for (int i = 0; i < 2; ++i)
	//{
	//	if (m_positionX[i] <= -150.0f)
	//	{
	//		int randTemp = rand() % (1395 + 1 - 1195) + 1195;
	//		m_positionX[i] = randTemp;
	//	}
	//}

	for (int i = 0; i < 2; ++i)
	{
		if (m_positionX[i] <= -150.0f)
			m_positionX[i] = 1195.0f;
	}
	

	OnDraw();
}