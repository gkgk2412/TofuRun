#include "MyHp.h"

CMyAnimationHp::CMyAnimationHp()
{
	m_nFrame = 0;
	m_interval = 0.0f;
	m_aniType = 0;
}

CMyAnimationHp::~CMyAnimationHp()
{
}

void CMyAnimationHp::Create(LPDIRECT3DDEVICE9 pDevice, char* filename)
{
	char imgname[128];
	int aniIndex, nFrame;
	float duration;
	int left, top, width, height;

	FILE* fp = fopen(filename, "rt");

	if (fp == NULL)
		return;

	fscanf(fp, "%s", imgname);
	CMySprite::Create_Hp(pDevice, imgname, 600, 1000);

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

void CMyAnimationHp::OnDraw()
{
	RECT srcRect = m_rcFrame[m_aniType][m_nFrame];
	srcRect.bottom = srcRect.top + m_rcFrame[m_aniType][m_nFrame].bottom;
	srcRect.right = srcRect.left + m_rcFrame[m_aniType][m_nFrame].right;

	D3DXVECTOR3 vCenter(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vPosition(700.0f, 0.0f, 0.0f);

	m_pDonutSprite[5]->Begin(D3DXSPRITE_ALPHABLEND);

	m_pDonutSprite[5]->Draw(m_pDonutTexture[5],
		&srcRect,
		&vCenter,
		&vPosition,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

	m_pDonutSprite[5]->End();
}

void CMyAnimationHp::OnUpdate(float time)
{
	m_interval += time;

	if (!hitObject)
	{
		tigger = false;

		if (m_interval > m_fDuration[m_aniType][m_nFrame])
		{
			m_interval = 0.0f;
			m_nFrame++;

			if (m_nFrame >= m_infoFrame[m_aniType])
			{
				m_nFrame = 0;
				isDie = true;	
			}
		}
	}

	if (hitObject)
	{
		if (!tigger)
		{
			m_nFrame = m_nFrame + 1;
			m_fDuration[m_aniType][m_nFrame] = 1.0f;
			tigger = true;
		}

		hitObject = false;
	}

	if (isFire)
	{
		//체력올리기
		if (m_nFrame > 0)
		{
			m_nFrame = m_nFrame - 1;
		}
	}

	OnDraw();
}