#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#define  MAX_SPRITE 30

class CMySprite
{
protected:
	LPDIRECT3DTEXTURE9 m_pDonutTexture[MAX_SPRITE];
	LPD3DXSPRITE       m_pDonutSprite[MAX_SPRITE];

public:	   
	CMySprite();
	virtual ~CMySprite();

	bool hitObject = false;
	bool isFire = false;
	int gameState = 0;
	bool isDie = false;


	bool isToufu = false;

	virtual void Create(LPDIRECT3DDEVICE9 pDevice, char *filename, int width, int height);
	virtual void Create_toufuTime(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height);
	virtual void Create_floor(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height);
	virtual void Create_back(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height);
	virtual void Create_Hp(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height);
	virtual void Create_BObject(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height);
	virtual void Create_BObject2(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height);
	virtual void Create_TObject(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height);
	virtual void Create_Start(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height);
	virtual void Create_button(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height);
	virtual void Create_Toufu(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height);
	virtual void Create_Setbutton(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height);
	virtual void Create_Backbutton(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height);
	virtual void Create_Xbutton(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height);
	virtual void Create_Number(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height);
	virtual void Create_Next(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height);
	virtual void Create_Cursor(LPDIRECT3DDEVICE9 pDevice, char* filename, int width, int height);
	virtual void OnDraw() {}
	virtual void OnUpdate(float time) {}
};

