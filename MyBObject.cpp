#include "MyBObject.h"

CMyAnimationBObejct::CMyAnimationBObejct()
{
	m_nFrame = 0;
	m_interval = 0.0f;
	m_aniType = 0;
}

CMyAnimationBObejct::~CMyAnimationBObejct()
{
}

void CMyAnimationBObejct::Create(LPDIRECT3DDEVICE9 pDevice, char* filename)
{
	char imgname[128];
	int aniIndex, nFrame;
	float duration;
	int left, top, width, height;

	FILE* fp = fopen(filename, "rt");

	if (fp == NULL)
		return;

	fscanf(fp, "%s", imgname);
	CMySprite::Create_BObject(pDevice, imgname, 200, 150);

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

void CMyAnimationBObejct::OnDraw()
{
	RECT srcRect = m_rcFrame[m_aniType][m_nFrame];
	srcRect.bottom = srcRect.top + m_rcFrame[m_aniType][m_nFrame].bottom;
	srcRect.right = srcRect.left + m_rcFrame[m_aniType][m_nFrame].right;

	m_rcCollision[0].left = (int)m_positionX + 10;
	m_rcCollision[0].top = (int)m_positionY + 30;
	m_rcCollision[0].right = m_rcCollision[0].left + m_rcFrame[m_aniType][m_nFrame].right - 50;
	m_rcCollision[0].bottom = m_rcCollision[0].top + m_rcFrame[m_aniType][m_nFrame].bottom;

	m_rcCollision[1].left = (int)m_positionX2 + 10;
	m_rcCollision[1].top = (int)m_positionY + 30;
	m_rcCollision[1].right = m_rcCollision[1].left + m_rcFrame[m_aniType][m_nFrame].right - 50;
	m_rcCollision[1].bottom = m_rcCollision[1].top + m_rcFrame[m_aniType][m_nFrame].bottom;

	D3DXVECTOR3 vCenter(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vPosition(m_positionX, m_positionY, 0.0f);
	D3DXVECTOR3 vPosition2(m_positionX2, m_positionY, 0.0f);

	m_pDonutSprite[6]->Begin(D3DXSPRITE_ALPHABLEND);
	m_pDonutSprite[7]->Begin(D3DXSPRITE_ALPHABLEND);

	m_pDonutSprite[6]->Draw(m_pDonutTexture[6],
		&srcRect,
		&vCenter,
		&vPosition,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

	m_pDonutSprite[7]->Draw(m_pDonutTexture[7],
		&srcRect,
		&vCenter,
		&vPosition2,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

	m_pDonutSprite[6]->End();
	m_pDonutSprite[7]->End();

	bottomCol = m_rcFrame[0][0].bottom;
	leftCol = m_rcFrame[0][0].left;
	rightCol = m_rcFrame[0][0].right;
}

void CMyAnimationBObejct::OnUpdate(float time)
{
	m_interval += time;

	if (m_interval > m_fDuration[m_aniType][m_nFrame])
	{
		m_interval = 0.0f;
		m_nFrame++;

		if (m_nFrame >= m_infoFrame[m_aniType])
		{
			m_nFrame = 0;
		}
	}

	if (m_positionX <= -150.0f)
		m_positionX = 1195.0f;

	if (m_positionX2 <= -150.0f)
		m_positionX2 = 1195.0f;

	OnDraw();
}