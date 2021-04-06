#include "MyBack.h"
#include <ctime>  

CMyBackSprite::CMyBackSprite()
{
	m_nFrame = 0;
	m_interval = 0.0f;
	m_aniType = 0;
}


CMyBackSprite::~CMyBackSprite()
{
}

void CMyBackSprite::Create(LPDIRECT3DDEVICE9 pDevice, char* filename)
{
	char imgname[128];
	int aniIndex, nFrame;
	int left, top, width, height;
	float duration;

	FILE* fp = fopen(filename, "rt");

	if (fp == NULL)
		return;

	fscanf(fp, "%s", imgname);
	CMySprite::Create_back(pDevice, imgname, 1200, 480);

	fscanf(fp, "%d", &m_maxAni); //2

	for (int ani = 0; ani < m_maxAni; ++ani)
	{
		fscanf(fp, "%d %d", &aniIndex, &nFrame);

		//0번째 인덱스는 총 8프레임
		m_infoFrame[ani] = nFrame;

		for (int i = 0; i < nFrame; ++i)
		{
			fscanf(fp, "%d %d %d %d %d", &left, &top, &width, &height, &duration);
			SetRect(&m_rcFrame[aniIndex][i], left, top, width, height);
			m_fDuration[aniIndex][i] = duration;
		}
	}

	fclose(fp);
}

void CMyBackSprite::OnDraw(int selection)
{
	RECT srcRect = m_rcFrame[m_aniType][m_nFrame];
	srcRect.bottom = srcRect.top + m_rcFrame[m_aniType][m_nFrame].bottom;
	srcRect.right = srcRect.left + m_rcFrame[m_aniType][m_nFrame].right;

	D3DXVECTOR3 vCenter(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vPosition(0, 0, 0.0f);
	D3DXVECTOR3 vPosition2(0, -20, 0.0f);

	//INTRO
	if (selection == 1)
	{
		m_pDonutSprite[4]->Begin(D3DXSPRITE_ALPHABLEND);

		m_pDonutSprite[4]->Draw(m_pDonutTexture[4],
			&srcRect,
			&vCenter,
			&vPosition,
			D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

		m_pDonutSprite[4]->End();
	}

	//INGAME
	if (selection == 2)
	{
		m_pDonutSprite[13]->Begin(D3DXSPRITE_ALPHABLEND);

		m_pDonutSprite[13]->Draw(m_pDonutTexture[13],
			&srcRect,
			&vCenter,
			&vPosition,
			D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

		m_pDonutSprite[13]->End();
	}

	//OVER
	if (selection == 3)
	{
		m_pDonutSprite[19]->Begin(D3DXSPRITE_ALPHABLEND);

		m_pDonutSprite[19]->Draw(m_pDonutTexture[19],
			&srcRect,
			&vCenter,
			&vPosition2,
			D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

		m_pDonutSprite[19]->End();
	}

	//SETTING
	if (selection == 4)
	{
		m_pDonutSprite[14]->Begin(D3DXSPRITE_ALPHABLEND);

		m_pDonutSprite[14]->Draw(m_pDonutTexture[14],
			&srcRect,
			&vCenter,
			&vPosition2,
			D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

		m_pDonutSprite[14]->End();
	}

	//CLEAR
	if (selection == 5)
	{
		m_pDonutSprite[25]->Begin(D3DXSPRITE_ALPHABLEND);

		m_pDonutSprite[25]->Draw(m_pDonutTexture[25],
			&srcRect,
			&vCenter,
			&vPosition2,
			D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

		m_pDonutSprite[25]->End();
	}

	//설명
	if (selection == 6)
	{
		m_pDonutSprite[27]->Begin(D3DXSPRITE_ALPHABLEND);

		m_pDonutSprite[27]->Draw(m_pDonutTexture[27],
			&srcRect,
			&vCenter,
			&vPosition2,
			D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

		m_pDonutSprite[27]->End();
	}
}

void CMyBackSprite::OnUpdate(float time, int selection) 
{
	m_interval += time;
	if (m_interval > m_fDuration[m_aniType][m_nFrame])
	{
		m_interval = 0.0f;
		m_nFrame++;
		if (m_nFrame >= m_infoFrame[m_aniType]) m_nFrame = 0;
	}

	OnDraw(selection);
}
