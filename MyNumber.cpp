#include "MyNumber.h"

CMyAnimationNum::CMyAnimationNum()
{
	m_nFrame = 0;
	m_interval = 0.0f;
	m_aniType = 0;
}

CMyAnimationNum::~CMyAnimationNum()
{
}

void CMyAnimationNum::Create(LPDIRECT3DDEVICE9 pDevice, char* filename)
{
	char imgname[128];
	int aniIndex, nFrame;
	float duration;
	int left, top, width, height;

	FILE* fp = fopen(filename, "rt");

	if (fp == NULL)
		return;

	fscanf(fp, "%s", imgname);
	CMySprite::Create_Number(pDevice, imgname, 500, 100);

	fscanf(fp, "%d", &m_maxAni);

	for (int ani = 0; ani < m_maxAni; ++ani)
	{
		fscanf(fp, "%d %d", &aniIndex, &nFrame);

		//0��° �ε����� �� 3������...������ ���� ����. 
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

void CMyAnimationNum::OnDraw()
{
	RECT srcRect = m_rcFrame[m_aniType][m_nFrame];
	srcRect.bottom = srcRect.top + m_rcFrame[m_aniType][m_nFrame].bottom;
	srcRect.right = srcRect.left + m_rcFrame[m_aniType][m_nFrame].right;

	D3DXVECTOR3 vCenter(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vPosition(m_positionX, m_positionY, 0.0f);

	m_pDonutSprite[24]->Begin(D3DXSPRITE_ALPHABLEND);

	m_pDonutSprite[24]->Draw(m_pDonutTexture[24],
		&srcRect,
		&vCenter,
		&vPosition,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

	m_pDonutSprite[24]->End();
}

void CMyAnimationNum::OnUpdate(float time)
{
	m_interval += time;

	if (numState == 1)
	{
		m_aniType = 0;

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

	if (numState == 2)
	{
		m_aniType = 1;

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

	if (numState == 3)
	{
		m_aniType = 2;

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

	if (numState == 4)
	{
		m_aniType = 3;

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

	if (numState == 5)
	{
		m_aniType = 4;

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

	OnDraw();
}