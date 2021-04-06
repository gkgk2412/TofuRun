#include "MySetBut.h"

CMySetButton::CMySetButton()
{
	m_nFrame = 0;
	m_interval = 0.0f;
	m_aniType = 0;
}

CMySetButton::~CMySetButton()
{
}

void CMySetButton::Create(LPDIRECT3DDEVICE9 pDevice, char* filename)
{
	char imgname[128];
	int aniIndex, nFrame;
	float duration;
	int left, top, width, height;

	FILE* fp = fopen(filename, "rt");

	if (fp == NULL)
		return;

	fscanf(fp, "%s", imgname);
	CMySprite::Create_Setbutton(pDevice, imgname, 200, 200);

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

void CMySetButton::OnDraw(int selection)
{
	RECT srcRect = m_rcFrame[m_aniType][m_nFrame];
	srcRect.bottom = srcRect.top + m_rcFrame[m_aniType][m_nFrame].bottom;
	srcRect.right = srcRect.left + m_rcFrame[m_aniType][m_nFrame].right;

	m_rcCollision[0].left = (int)m_positionX[0];
	m_rcCollision[0].top = (int)m_positionY[0];
	m_rcCollision[0].right = m_rcCollision[0].left + m_rcFrame[m_aniType][m_nFrame].right;
	m_rcCollision[0].bottom = m_rcCollision[0].top + m_rcFrame[m_aniType][m_nFrame].bottom;

	m_rcCollision[1].left = (int)m_positionX[1];
	m_rcCollision[1].top = (int)m_positionY[1];
	m_rcCollision[1].right = m_rcCollision[1].left + m_rcFrame[m_aniType][m_nFrame].right;
	m_rcCollision[1].bottom = m_rcCollision[1].top + m_rcFrame[m_aniType][m_nFrame].bottom;

	D3DXVECTOR3 vCenter(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vPosition(m_positionX[0], m_positionY[0], 0.0f);
	D3DXVECTOR3 vPosition2(m_positionX[1], m_positionY[1], 0.0f);

	if (selection == 0)
	{
		m_pDonutSprite[20]->Begin(D3DXSPRITE_ALPHABLEND);

		m_pDonutSprite[20]->Draw(m_pDonutTexture[20],
			&srcRect,
			&vCenter,
			&vPosition,
			D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

		m_pDonutSprite[20]->End();
	}

	if (selection == 1)
	{
		m_pDonutSprite[21]->Begin(D3DXSPRITE_ALPHABLEND);

		m_pDonutSprite[21]->Draw(m_pDonutTexture[21],
			&srcRect,
			&vCenter,
			&vPosition2,
			D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

		m_pDonutSprite[21]->End();
	}

	bottomCol = m_rcFrame[0][0].bottom;
	leftCol = m_rcFrame[0][0].left;
	rightCol = m_rcFrame[0][0].right;
}

void CMySetButton::OnUpdate(float time, int selection)
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
	OnDraw(selection);
}

BOOL CMySetButton::isCollision(POINT pt, RECT col)
{
	return ::PtInRect(&col, pt);
}
