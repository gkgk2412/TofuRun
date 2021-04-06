#include "MySprite.h"

CMySprite::CMySprite()
{
	for(int i = 0; i < MAX_SPRITE; ++i)
	{
		m_pDonutTexture[i] = NULL;
		m_pDonutSprite[i] = NULL;
	}
}

CMySprite::~CMySprite()
{

	for (int i = 0; i < MAX_SPRITE; ++i)
	{
		if (m_pDonutSprite[i] != NULL)
			m_pDonutSprite[i]->Release();

		if (m_pDonutTexture[i] != NULL)
			m_pDonutTexture[i]->Release();
	}
}

//캐릭터
void CMySprite::Create(LPDIRECT3DDEVICE9 pDevice, char *filename, int width, int height)
{
	D3DXIMAGE_INFO d3dxImageInfo;

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(0.0f,0.0f, 0.0f, 0.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[0]);


	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	D3DXCreateSprite(pDevice, &m_pDonutSprite[0]);
}

//두부시간 
void CMySprite::Create_toufuTime(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height)
{
	D3DXIMAGE_INFO d3dxImageInfo;

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(0.0f, 0.0f, 0.0f, 0.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[1]);


	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	D3DXCreateSprite(pDevice, &m_pDonutSprite[1]);
}

//바닥
void CMySprite::Create_floor(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height)
{
	D3DXIMAGE_INFO d3dxImageInfo;

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[2]);

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[3]);

	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	D3DXCreateSprite(pDevice, &m_pDonutSprite[2]);
	D3DXCreateSprite(pDevice, &m_pDonutSprite[3]);
}

//게임배경
void CMySprite::Create_back(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height)
{
	D3DXIMAGE_INFO d3dxImageInfo;

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[4]);
	
	D3DXCreateTextureFromFileEx(pDevice,
			filename,
			width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
			height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
			1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
			D3DPOOL_DEFAULT,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
			&d3dxImageInfo,
			NULL,
			&m_pDonutTexture[13]);

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[14]);

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[19]);

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[25]);

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[27]);


	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	D3DXCreateSprite(pDevice, &m_pDonutSprite[4]);
	D3DXCreateSprite(pDevice, &m_pDonutSprite[13]);
	D3DXCreateSprite(pDevice, &m_pDonutSprite[14]);
	D3DXCreateSprite(pDevice, &m_pDonutSprite[19]);
	D3DXCreateSprite(pDevice, &m_pDonutSprite[25]);
	D3DXCreateSprite(pDevice, &m_pDonutSprite[27]);
}

//Hp
void CMySprite::Create_Hp(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height)
{
	D3DXIMAGE_INFO d3dxImageInfo;

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[5]);

	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	D3DXCreateSprite(pDevice, &m_pDonutSprite[5]);
}

//장애물
void CMySprite::Create_BObject(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height)
{
	D3DXIMAGE_INFO d3dxImageInfo;

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[6]);

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[7]);

	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	D3DXCreateSprite(pDevice, &m_pDonutSprite[6]);
	D3DXCreateSprite(pDevice, &m_pDonutSprite[7]);
}

//장애물2
void CMySprite::Create_BObject2(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height)
{
	D3DXIMAGE_INFO d3dxImageInfo;

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[8]);

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[9]);


	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[10]);

	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	D3DXCreateSprite(pDevice, &m_pDonutSprite[8]);
	D3DXCreateSprite(pDevice, &m_pDonutSprite[9]);
	D3DXCreateSprite(pDevice, &m_pDonutSprite[10]);
}

//위쪽장애물
void CMySprite::Create_TObject(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height)
{
	D3DXIMAGE_INFO d3dxImageInfo;

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[11]);
	
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	D3DXCreateSprite(pDevice, &m_pDonutSprite[11]);
	
}

//start
void CMySprite::Create_Start(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height)
{
	D3DXIMAGE_INFO d3dxImageInfo;

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[12]);

	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	D3DXCreateSprite(pDevice, &m_pDonutSprite[12]);
}

//button
void CMySprite::Create_button(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height)
{
	D3DXIMAGE_INFO d3dxImageInfo;

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[15]);

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[16]);

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[17]);

	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	D3DXCreateSprite(pDevice, &m_pDonutSprite[15]);
	D3DXCreateSprite(pDevice, &m_pDonutSprite[16]);
	D3DXCreateSprite(pDevice, &m_pDonutSprite[17]);
}

//두부
void CMySprite::Create_Toufu(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height)
{
	D3DXIMAGE_INFO d3dxImageInfo;

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[18]);

	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	D3DXCreateSprite(pDevice, &m_pDonutSprite[18]);
}

//설정버튼
void CMySprite::Create_Setbutton(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height)
{
	D3DXIMAGE_INFO d3dxImageInfo;

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[20]);

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[21]);

	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	D3DXCreateSprite(pDevice, &m_pDonutSprite[20]);
	D3DXCreateSprite(pDevice, &m_pDonutSprite[21]);
}


//설정버튼
void CMySprite::Create_Backbutton(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height)
{
	D3DXIMAGE_INFO d3dxImageInfo;

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[22]);

	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	D3DXCreateSprite(pDevice, &m_pDonutSprite[22]);
}

//X버튼
void CMySprite::Create_Xbutton(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height)
{
	D3DXIMAGE_INFO d3dxImageInfo;

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[23]);

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[26]);

	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	D3DXCreateSprite(pDevice, &m_pDonutSprite[23]);
	D3DXCreateSprite(pDevice, &m_pDonutSprite[26]);
}

//두부 개수
void CMySprite::Create_Number(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height)
{
	D3DXIMAGE_INFO d3dxImageInfo;

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[24]);

	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	D3DXCreateSprite(pDevice, &m_pDonutSprite[24]);
}

//next
void CMySprite::Create_Next(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height)
{
	D3DXIMAGE_INFO d3dxImageInfo;

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[28]);

	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	D3DXCreateSprite(pDevice, &m_pDonutSprite[28]);
}

//next
void CMySprite::Create_Cursor(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height)
{
	D3DXIMAGE_INFO d3dxImageInfo;

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[29]);

	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	D3DXCreateSprite(pDevice, &m_pDonutSprite[29]);
}