#include "MyStart.h"

CMyAnimationStart::CMyAnimationStart()
{
	m_nFrame = 0;
	m_interval = 0.0f;
	m_aniType = 0;
}

CMyAnimationStart::~CMyAnimationStart()
{
}

void CMyAnimationStart::Create(LPDIRECT3DDEVICE9 pDevice, char* filename)
{
	char imgname[128];
	int aniIndex, nFrame;
	float duration;
	int left, top, width, height;

	FILE* fp = fopen(filename, "rt");

	if (fp == NULL)
		return;

	fscanf(fp, "%s", imgname);
	CMySprite::Create_Start(pDevice, imgname, 1200, 480);

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

void CMyAnimationStart::OnDraw()
{
	RECT srcRect = m_rcFrame[m_aniType][m_nFrame];
	srcRect.bottom = srcRect.top + m_rcFrame[m_aniType][m_nFrame].bottom;
	srcRect.right = srcRect.left + m_rcFrame[m_aniType][m_nFrame].right;

	m_rcCollision.left = (int)m_positionX;
	m_rcCollision.top = (int)m_positionY;
	m_rcCollision.right = m_rcCollision.left + m_rcFrame[m_aniType][m_nFrame].right;
	m_rcCollision.bottom = m_rcCollision.top + m_rcFrame[m_aniType][m_nFrame].bottom;

	D3DXVECTOR3 vCenter(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vPosition(m_positionX, m_positionY, 0.0f);

	m_pDonutSprite[12]->Begin(D3DXSPRITE_ALPHABLEND);

	m_pDonutSprite[12]->Draw(m_pDonutTexture[12],
		&srcRect,
		&vCenter,
		&vPosition,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

	m_pDonutSprite[12]->End();

}

void CMyAnimationStart::OnUpdate(float time)
{
	m_interval += time;

	//작은 사이즈
	if (State == 0)
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

		m_positionX = 440.0f;
	}

	//큰사이즈
	if (State == 1)
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

		m_positionX = 420.0f;
	}

	OnDraw();
}

BOOL CMyAnimationStart::isCollision(POINT pt)
{
	return ::PtInRect(&m_rcCollision, pt);
}