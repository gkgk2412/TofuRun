#include "MyButton.h"

CMyAnimationButton::CMyAnimationButton()
{
	m_nFrame = 0;
	m_interval = 0.0f;
	m_aniType = 0;
}

CMyAnimationButton::~CMyAnimationButton()
{
}

void CMyAnimationButton::Create(LPDIRECT3DDEVICE9 pDevice, char* filename)
{
	char imgname[128];
	int aniIndex, nFrame;
	float duration;
	int left, top, width, height;

	FILE* fp = fopen(filename, "rt");

	if (fp == NULL)
		return;

	fscanf(fp, "%s", imgname);
	CMySprite::Create_button(pDevice, imgname, 200, 100);

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

void CMyAnimationButton::OnDraw(int selection)
{
	RECT srcRect = m_rcFrame[m_aniType][m_nFrame];
	srcRect.bottom = srcRect.top + m_rcFrame[m_aniType][m_nFrame].bottom;
	srcRect.right = srcRect.left + m_rcFrame[m_aniType][m_nFrame].right;

	m_rcCollision[0].left = (int)m_positionX;
	m_rcCollision[0].top = (int)m_positionY[0];
	m_rcCollision[0].right = m_rcCollision[0].left + m_rcFrame[m_aniType][m_nFrame].right;
	m_rcCollision[0].bottom = m_rcCollision[0].top + m_rcFrame[m_aniType][m_nFrame].bottom;

	m_rcCollision[1].left = (int)m_positionX;
	m_rcCollision[1].top = (int)m_positionY[1];
	m_rcCollision[1].right = m_rcCollision[1].left + m_rcFrame[m_aniType][m_nFrame].right;
	m_rcCollision[1].bottom = m_rcCollision[1].top + m_rcFrame[m_aniType][m_nFrame].bottom;

	m_rcCollision[2].left = (int)m_positionX;
	m_rcCollision[2].top = (int)m_positionY[2];
	m_rcCollision[2].right = m_rcCollision[2].left + m_rcFrame[m_aniType][m_nFrame].right;
	m_rcCollision[2].bottom = m_rcCollision[2].top + m_rcFrame[m_aniType][m_nFrame].bottom;

	D3DXVECTOR3 vCenter(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vPosition(m_positionX, m_positionY[0], 0.0f);
	D3DXVECTOR3 vPosition2(m_positionX, m_positionY[1], 0.0f);
	D3DXVECTOR3 vPosition3(m_positionX, m_positionY[2], 0.0f);

	if (selection == 0)
	{
		m_pDonutSprite[15]->Begin(D3DXSPRITE_ALPHABLEND);

		m_pDonutSprite[15]->Draw(m_pDonutTexture[15],
			&srcRect,
			&vCenter,
			&vPosition,
			D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

		m_pDonutSprite[15]->End();
	}

	if (selection == 1)
	{
		m_pDonutSprite[16]->Begin(D3DXSPRITE_ALPHABLEND);

		m_pDonutSprite[16]->Draw(m_pDonutTexture[16],
			&srcRect,
			&vCenter,
			&vPosition2,
			D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

		m_pDonutSprite[16]->End();
	}

	if (selection == 2)
	{
		m_pDonutSprite[17]->Begin(D3DXSPRITE_ALPHABLEND);

		m_pDonutSprite[17]->Draw(m_pDonutTexture[17],
			&srcRect,
			&vCenter,
			&vPosition3,
			D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

		m_pDonutSprite[17]->End();
	}
}

void CMyAnimationButton::OnUpdate(float time, int selection)
{
	m_interval += time;

	//1
	if (buttonState == 0)
	{
		if (m_interval > m_fDuration[m_aniType][m_nFrame])
		{
			m_interval = 0.0f;
			m_nFrame++;
			if (m_nFrame >= m_infoFrame[m_aniType])
			{
				m_nFrame = 0;
			}
		}
	}

	//gray
	if (buttonState == 1)
	{
		if (m_interval > m_fDuration[m_aniType][m_nFrame])
		{
			m_interval = 0.0f;
			m_nFrame++;
			if (m_nFrame >= m_infoFrame[m_aniType])
			{
				m_nFrame = 0;
			}
		}
	}

	//check
	if (buttonState == 2)
	{
		if (m_interval > m_fDuration[m_aniType][m_nFrame])
		{
			m_interval = 0.0f;
			m_nFrame++;
			if (m_nFrame >= m_infoFrame[m_aniType])
			{
				m_nFrame = 0;
			}
		}
	}

	OnDraw(selection);
}

BOOL CMyAnimationButton::isCollision(POINT pt, RECT col)
{
	return ::PtInRect(&col, pt);
}