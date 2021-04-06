#include "MyCursor.h"
#include <ctime>

CMyCursor::CMyCursor()
{
	m_nFrame = 0;
	m_interval = 0.0f;
	m_aniType = 0;
}

CMyCursor::~CMyCursor()
{
}

void CMyCursor::Create(LPDIRECT3DDEVICE9 pDevice, char* filename)
{
	char imgname[128];
	int aniIndex, nFrame;
	float duration;
	int left, top, width, height;

	FILE* fp = fopen(filename, "rt");

	if (fp == NULL)
		return;

	fscanf(fp, "%s", imgname);
	CMySprite::Create_Cursor(pDevice, imgname, 50, 50);

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

void CMyCursor::OnDraw()
{
	RECT srcRect = m_rcFrame[m_aniType][m_nFrame];
	srcRect.bottom = srcRect.top + m_rcFrame[m_aniType][m_nFrame].bottom;
	srcRect.right = srcRect.left + m_rcFrame[m_aniType][m_nFrame].right;

	D3DXVECTOR3 vCenter(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vPosition(m_positionX, m_positionY, 0.0f);

	m_pDonutSprite[29]->Begin(D3DXSPRITE_ALPHABLEND);

	m_pDonutSprite[29]->Draw(m_pDonutTexture[29],
		&srcRect,
		&vCenter,
		&vPosition,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

	m_pDonutSprite[29]->End();
}

void CMyCursor::OnUpdate(float Etime)
{
	m_interval += Etime;

	if (m_interval > m_fDuration[m_aniType][m_nFrame])
	{
		m_interval = 0.0f;
		m_nFrame++;

		if (m_nFrame >= m_infoFrame[m_aniType])
		{
			m_nFrame = 0;
		}
	}

	OnDraw();
}