#include "MyObjectTT.h"

CMyAnimationToufuTime::CMyAnimationToufuTime()
{
	m_nFrame = 0;
	m_interval = 0.0f;
	m_aniType = 0;
}

CMyAnimationToufuTime::~CMyAnimationToufuTime()
{
}

void CMyAnimationToufuTime::Create(LPDIRECT3DDEVICE9 pDevice, char* filename)
{
	char imgname[128];
	int aniIndex, nFrame;
	float duration;
	int left, top, width, height;

	FILE* fp = fopen(filename, "rt");

	if (fp == NULL)
		return;

	fscanf(fp, "%s", imgname);
	CMySprite::Create_toufuTime(pDevice, imgname, 400, 500);

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

void CMyAnimationToufuTime::OnDraw()
{
	RECT srcRect = m_rcFrame[m_aniType][m_nFrame];
	srcRect.bottom = srcRect.top + m_rcFrame[m_aniType][m_nFrame].bottom;
	srcRect.right = srcRect.left + m_rcFrame[m_aniType][m_nFrame].right;

	D3DXVECTOR3 vCenter(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vPosition(10.0f, 5.0f, 0.0f);

	m_pDonutSprite[1]->Begin(D3DXSPRITE_ALPHABLEND);

	m_pDonutSprite[1]->Draw(m_pDonutTexture[1],
		&srcRect,
		&vCenter,
		&vPosition,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

	m_pDonutSprite[1]->End();
}

void CMyAnimationToufuTime::OnUpdate(float time)
{
	m_interval += time;

	if (!checkBounsTime)
	{
		if (m_interval > m_fDuration[m_aniType][m_nFrame])
		{
			m_interval = 0.0f;
			m_nFrame++;

			if (m_nFrame >= m_infoFrame[m_aniType])
			{
				m_nFrame = 0;
				checkBounsTime = true;
			}
		}
	}

	OnDraw();
}