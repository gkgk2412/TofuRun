#include "MyAnimationSprite.h"

CMyAnimationSprite::CMyAnimationSprite()
{
	m_nFrame = 0;
	m_interval = 0.0f;
	m_aniType = 0;
}

CMyAnimationSprite::~CMyAnimationSprite()
{
}

void CMyAnimationSprite::Create(LPDIRECT3DDEVICE9 pDevice, char* filename)
{
	char imgname[128];
	int aniIndex, nFrame;
	float duration;

	FILE* fp = fopen(filename, "rt");

	if (fp == NULL)
		return;

	fscanf(fp, "%s", imgname);
	CMySprite::Create(pDevice, imgname, 500, 438);

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

void CMyAnimationSprite::OnDraw()
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

	m_pDonutSprite[0]->Begin(D3DXSPRITE_ALPHABLEND);
	
	m_pDonutSprite[0]->Draw(m_pDonutTexture[0],
		&srcRect,
		&vCenter,
		&vPosition,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

	m_pDonutSprite[0]->End();
}

void CMyAnimationSprite::OnUpdate(float time)
{
	m_interval += time;

	//달리기
	if (charState == 0)
	{
		if (m_interval > m_fDuration[m_aniType][m_nFrame])
		{
			m_interval = 0.0f;
			m_nFrame++;
			if (m_nFrame >= m_infoFrame[m_aniType]) m_nFrame = 0;
		}

		m_positionX = 200.0f;
		m_positionY = COOKIEPOSITION;
	}

	//점프
	if (charState == 1)
	{
		if (m_interval > m_fDuration[m_aniType][m_nFrame])
		{
			m_interval = 0.0f;
			m_nFrame++;
			if (m_nFrame >= m_infoFrame[m_aniType]) m_nFrame = 0;
		}

		if(!checkPoint)
			m_positionY -= 0.28f;

		if (m_positionY <= 110.0f)
			checkPoint = true;

		if(checkPoint)
			m_positionY += 0.055f;

		if (m_positionY >= COOKIEPOSITION)
		{
			m_positionY = COOKIEPOSITION;
			charState = 0;
			m_aniType = 0;
			checkPoint = false;
		}
	}

	//슬라이드
	if (charState == 2)
	{
		if (m_interval > m_fDuration[m_aniType][m_nFrame])
		{
			m_interval = 0.0f;
			m_nFrame++;
			if (m_nFrame >= m_infoFrame[m_aniType]) m_nFrame = 0;
		}
	}

	//2단점프
	if (charState == 3)
	{
		if (m_interval > m_fDuration[m_aniType][m_nFrame])
		{
			m_interval = 0.0f;
			m_nFrame++;
			if (m_nFrame >= m_infoFrame[m_aniType]) m_nFrame = 0;
		}

		m_positionY += 0.07f;

		if (m_positionY >= 220.0f)
		{
			charState = 4;
			m_aniType = 4;
		}
	}

	//2단점프 내려올때
	if (charState == 4)
	{
		if (m_interval > m_fDuration[m_aniType][m_nFrame])
		{
			m_interval = 0.0f;
			m_nFrame++;
			if (m_nFrame >= m_infoFrame[m_aniType]) m_nFrame = 0;
		}

		m_positionY += 0.08f;

		if (m_positionY >= COOKIEPOSITION)
		{
			m_positionY = COOKIEPOSITION;
			charState = 0;
			m_aniType = 0;
			checkPoint = false;
		}
	}

	//광속질주
	if (charState == 5)
	{
		if (m_interval > m_fDuration[m_aniType][m_nFrame])
		{
			m_interval = 0.0f;
			m_nFrame++;

			if (m_nFrame >= m_infoFrame[m_aniType])
			{
				m_nFrame = 0;
				++checkBounsFrame;
			}
		}
		m_positionX = 160.0f;

		if (m_positionY != COOKIEPOSITION)
		{
			m_positionY += 0.08f;

			if (m_positionY >= COOKIEPOSITION)
			{
				m_positionY = COOKIEPOSITION;
			}
		}
	}


	//부딪힘
	if (charState == 6)
	{
		if (m_interval > m_fDuration[m_aniType][m_nFrame])
		{
			m_interval = 0.0f;
			m_nFrame++;

			if (m_nFrame >= m_infoFrame[m_aniType])
			{
				m_nFrame = 0;

				//무적달리기상태로 전환
				charState = 7;
				m_aniType = 7;
			}
		}
	}

	//무적달리기
	if (charState == 7)
	{
		if (m_interval > m_fDuration[m_aniType][m_nFrame])
		{
			m_interval = 0.0f;
			m_nFrame++;
			if (m_nFrame >= m_infoFrame[m_aniType])
			{
				m_nFrame = 0;
				++checkBounsFrame;
				++checkBounsFrame2;
			}
		}

		m_positionX = 200.0f;
		m_positionY = COOKIEPOSITION;
	}

	//사망
	if (charState == 8)
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

		m_positionX = 200.0f;
		m_positionY = 305.0f;
	}
	OnDraw();
}


BOOL CMyAnimationSprite::isTrigger(RECT rect)
{
	if (m_rcCollision.left < rect.right &&
		m_rcCollision.top < rect.bottom &&
		m_rcCollision.right > rect.left &&
		m_rcCollision.bottom > rect.top)
		return true;
	return false;
}