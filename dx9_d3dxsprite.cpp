#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <mmsystem.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "resource.h"


#include "MyAnimationSprite.h"
#include "MyObjectTT.h"
#include "MyFloor.h"
#include "MyBack.h"
#include "MyHp.h"
#include "MyBObject.h"
#include "MyBObject2.h"
#include "MyTopObject.h"
#include "MyStart.h"
#include "MyButton.h"
#include "MyToufu.h"
#include "MySetBut.h"
#include "MyBackBut.h"
#include "MyXBut.h"
#include "MyNumber.h"
#include "MyNext.h"
#include "MyCursor.h"


#include <stdio.h>
#include <MMSystem.h> //playsound함수사용위해
#include "Digitalv.h" //mci 사용위해

//사운드사용위해서(playsound, mci)
/*========================================*/
#pragma comment(lib, "winmm.lib" ) 

MCI_OPEN_PARMS m_mciOpenParms;
MCI_PLAY_PARMS m_mciPlayParms;
DWORD m_dwDeviceID;


MCI_OPEN_PARMS mciOpen;
MCI_PLAY_PARMS mciPlay;

MCI_OPEN_PARMS mciOpen2;
MCI_PLAY_PARMS mciPlay2;

//intro사운드 조절
int soundplayCheck;

//main사운드 조절
int soundplayCheck2;

//효과음 조절
bool isPlay = false;
bool isPlay2 = false;
bool isPlay3 = false;

bool buttonCheck[3] = { false, false, false };
bool buttonCheck2[3] = { false, false, false };
/*===========================================================*/

//-----------------------------------------------------------------------------
// GLOBALS
//-----------------------------------------------------------------------------
HWND                    g_hWnd          = NULL;
LPDIRECT3D9             g_pD3D          = NULL;
LPDIRECT3DDEVICE9       g_pd3dDevice    = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;

float  g_fElpasedTime;
double g_dCurTime;
double g_dLastTime;
float  g_fMoveSpeed = 50.0f;
float  g_fSpinX = 0.0f;
float  g_fSpinY = 0.0f;

bool isJumping = false;
bool isTopCheck = false;
bool checkAminOk = false;

int exGameState = 0;
int isEatToufu = 0;

DWORD tick; DWORD deltatime;

CMyAnimationSprite g_aniSprite;
CMyAnimationToufuTime g_aniToufuTime;
CMyFloorSprite g_aniFloor;
CMyBackSprite g_MyBackIntro;
CMyBackSprite g_MyBack;
CMyBackSprite g_MyBackSET;
CMyBackSprite g_MyBackOVER;
CMyBackSprite g_MyBackCLEAR;
CMyBackSprite g_MyBackINC;
CMyAnimationHp g_MyHp;
CMyAnimationBObejct g_MyBObject;
CMyAnimationBObejct2 g_MyBObject2;
CMyAnimationTObejct g_MyTObject;
CMyAnimationStart g_MyStart;
CMyAnimationButton g_MyButton;
CMyAnimationButton g_MyButton2;
CMyAnimationButton g_MyButton3;
CMySetButton g_MySetBt;
CMySetButton g_MySetBt2;
CMyBackButton g_MyBackBt;
CMyXButton g_MyXBt;
CMyXButton g_MyXBt2;
CMyAnimationNum g_MyNum;
CMyNext g_MyNext;
CMyCursor g_MyCursor;

CMyToufu g_MyToufu;



#define D3DFVF_CUSTOMVERTEX ( D3DFVF_XYZ | D3DFVF_TEX1 )

struct Vertex
{
    float x, y, z;
    float tu, tv;
};

Vertex g_quadVertices[] =
{
	{-1.0f, 1.0f, 0.0f,  0.0f,0.0f },
	{ 1.0f, 1.0f, 0.0f,  1.0f,0.0f },
	{-1.0f,-1.0f, 0.0f,  0.0f,1.0f },
	{ 1.0f,-1.0f, 0.0f,  1.0f,1.0f }
};

//-----------------------------------------------------------------------------
// PROTOTYPES
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void init(void);
void shutDown(void);
void render(void);

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	WNDCLASSEX winClass;
	MSG        uMsg;

	memset(&uMsg, 0, sizeof(uMsg));

	winClass.lpszClassName = "MY_WINDOWS_CLASS";
	winClass.cbSize = sizeof(WNDCLASSEX);
	winClass.style = CS_HREDRAW | CS_VREDRAW;
	winClass.lpfnWndProc = WindowProc;
	winClass.hInstance = hInstance;
	winClass.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_DIRECTX_ICON);
	winClass.hIconSm = LoadIcon(hInstance, (LPCTSTR)IDI_DIRECTX_ICON);
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winClass.lpszMenuName = NULL;
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;

	if (!RegisterClassEx(&winClass))
		return E_FAIL;

	g_hWnd = CreateWindowEx(NULL, "MY_WINDOWS_CLASS",
		"두부를 사자",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0, 1150, 480, NULL, NULL, hInstance, NULL);

	if (g_hWnd == NULL)
		return E_FAIL;

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	ShowCursor(false);


	init();

	//사운드
/*=====================================================================*/

	mciOpen.lpstrElementName = "./intro.mp3";
	mciOpen.lpstrDeviceType = "mpegvideo";

	mciOpen2.lpstrElementName = "./MainSound.mp3";
	mciOpen2.lpstrDeviceType = "mpegvideo";

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,
		(DWORD)(LPVOID)&mciOpen);

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,
		(DWORD)(LPVOID)&mciOpen2);

	soundplayCheck = mciOpen.wDeviceID;
	soundplayCheck2 = mciOpen2.wDeviceID;

	mciSendCommand(soundplayCheck, MCI_PLAY, MCI_DGV_PLAY_REPEAT,
		(DWORD)(LPVOID)&m_mciPlayParms);

	/*=====================================================================*/


	tick = GetTickCount();
	while (uMsg.message != WM_QUIT)
	{
		if (PeekMessage(&uMsg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&uMsg);
			DispatchMessage(&uMsg);
		}
		else
		{
			g_dCurTime = timeGetTime();
			g_fElpasedTime = (float)((g_dCurTime - g_dLastTime) * 0.001);
			g_dLastTime = g_dCurTime;

			DWORD curTick = GetTickCount();
			deltatime = curTick - tick;

			render();

			tick = curTick;
		}
	}

	shutDown();

	UnregisterClass("MY_WINDOWS_CLASS", winClass.hInstance);

	return uMsg.wParam;
}

//-----------------------------------------------------------------------------
// Name: WindowProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND   hWnd,
	UINT   msg,
	WPARAM wParam,
	LPARAM lParam)
{
	static POINT ptLastMousePosit;
	static POINT ptCurrentMousePosit;
	static bool bMousing;

	switch (msg)
	{
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
		{/*
			PostQuitMessage(0);
			break;*/

			if (g_MyHp.gameState == 3)
			{
				g_MyHp.gameState = exGameState;
			}

			else
			{
				//옵션창
				exGameState = g_MyHp.gameState;
				g_MyHp.gameState = 3;
			}

			break;
		}


		case VK_SPACE:
		{
			if (g_MyHp.gameState == 1)
			{
				//점프상태로 전환
				if (g_aniSprite.charState != 1 && g_aniSprite.charState != 3 && g_aniSprite.charState != 5)
				{
					g_aniSprite.charState = 1;
					g_aniSprite.m_aniType = 1;

					if (!buttonCheck[2])
						sndPlaySoundA("./jump.wav", SND_ASYNC | SND_NODEFAULT | SND_ASYNC); //점프
				}

				//2단 점프상태로 전환
				else if (g_aniSprite.charState == 1)
				{
					if (g_aniSprite.charState != 3)
					{
						if (!buttonCheck[2])
							sndPlaySoundA("./jump.wav", SND_ASYNC | SND_NODEFAULT | SND_ASYNC); //점프

						g_aniSprite.charState = 3;
						g_aniSprite.m_aniType = 3;
						g_aniSprite.m_positionY -= 100;
					}
				}

			}

			break;
		}

		case VK_DOWN:
		{
			//슬라이드 상태로 전환
			if (g_aniSprite.charState == 0 || g_aniSprite.charState == 7)
			{
				g_aniSprite.charState = 2;
				g_aniSprite.m_aniType = 2;
				g_aniSprite.m_positionY += 45;

				if (!buttonCheck[2])
					sndPlaySoundA("./Slide.wav", SND_ASYNC | SND_NODEFAULT | SND_ASYNC); //슬라이드					
			}
			break;
		}

		}
	}
	break;

	case WM_KEYUP:
	{
	case VK_DOWN:
	{
		//달리기상태로 전환
		if (g_aniSprite.charState == 2)
		{
			g_aniSprite.charState = 0;
			g_aniSprite.m_aniType = 0;
			g_aniSprite.m_positionY = COOKIEPOSITION;
		}

		break;
	}

	case VK_ESCAPE:
	{
		/*
		PostQuitMessage(0);
		break;*/
		break;
	}

	}

	case WM_LBUTTONDOWN:
	{
		ptLastMousePosit.x = ptCurrentMousePosit.x = LOWORD(lParam);
		ptLastMousePosit.y = ptCurrentMousePosit.y = HIWORD(lParam);
		bMousing = true;

		POINT pt;
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);

		if (g_MyHp.gameState == 3)
		{			
			//ALL
			if (g_MyButton.isCollision(pt, g_MyButton.m_rcCollision[0]) == TRUE)
			{
				if (!buttonCheck[2])
					sndPlaySoundA("./click.wav", SND_ASYNC | SND_NODEFAULT | SND_ASYNC);

				g_MyButton.buttonState = 1;
				g_MyButton.m_aniType = 1;

				if (buttonCheck[0])
					buttonCheck2[0] = true;
				else
					buttonCheck2[0] = false;
			}

			//MAIN
			if (g_MyButton2.isCollision(pt, g_MyButton.m_rcCollision[1]) == TRUE)
			{
				if (!buttonCheck[0])
				{
					if (!buttonCheck[2])
						sndPlaySoundA("./click.wav", SND_ASYNC | SND_NODEFAULT | SND_ASYNC);

					g_MyButton2.buttonState = 1;
					g_MyButton2.m_aniType = 1;

					if (buttonCheck[1])
						buttonCheck2[1] = true;
					else
						buttonCheck2[1] = false;
				}
			}

			//EFFECT
			if (g_MyButton3.isCollision(pt, g_MyButton.m_rcCollision[2]) == TRUE)
			{
				if (!buttonCheck[0])
				{
					if (!buttonCheck[2])
						sndPlaySoundA("./click.wav", SND_ASYNC | SND_NODEFAULT | SND_ASYNC);

					g_MyButton3.buttonState = 1;
					g_MyButton3.m_aniType = 1;

					if (buttonCheck[2])
						buttonCheck2[2] = true;
					else
						buttonCheck2[2] = false;
				}
			}
		}
	}

	break;

	case WM_LBUTTONUP:
	{
		POINT pt;
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);

		if (g_MyHp.gameState == 0)
		{
			if (g_MyStart.isCollision(pt) == TRUE)
			{
				g_MyHp.gameState = 5;

				if (g_MyHp.gameState == 5)
				{
					mciSendCommandW(soundplayCheck2, MCI_PLAY, MCI_DGV_PLAY_REPEAT,
						(DWORD)(LPVOID)&m_mciPlayParms);

					//all main 둘 중 하나라도 켜져있으면
					if (buttonCheck[0] || buttonCheck[1])
					{
						mciSendCommandW(soundplayCheck2, MCI_PAUSE, 0, NULL);
					}
				
				}
			}

			if (g_MySetBt.isCollision(pt, g_MySetBt.m_rcCollision[0]) == TRUE)
			{
				if (!buttonCheck[2])
					sndPlaySoundA("./click2.wav", SND_ASYNC | SND_NODEFAULT | SND_ASYNC);

				exGameState = g_MyHp.gameState;
				g_MyHp.gameState = 3;				
			}
		}

		if (g_MyHp.gameState == 2)
		{
			if (g_MySetBt2.isCollision(pt, g_MySetBt.m_rcCollision[1]) == TRUE)
			{
				if (!buttonCheck[2])
					sndPlaySoundA("./click2.wav", SND_ASYNC | SND_NODEFAULT | SND_ASYNC);

				exGameState = g_MyHp.gameState;
				g_MyHp.gameState = 3;
			}

			//X BT
			if (g_MyXBt.isCollision(pt, g_MyXBt.m_rcCollision[0]) == TRUE)
			{
				if (!buttonCheck[2])
					sndPlaySoundA("./click2.wav", SND_ASYNC | SND_NODEFAULT | SND_ASYNC);

				PostQuitMessage(0);
			}
		}

		if (g_MyHp.gameState == 3)
		{
			if (g_MyButton.isCollision(pt, g_MyButton.m_rcCollision[0]) == TRUE)
			{
				//check
				if (!buttonCheck[0] && !buttonCheck2[0])
				{
					g_MyButton.buttonState = 2;
					g_MyButton.m_aniType = 2;
					buttonCheck[0] = true; //check

					g_MyButton2.buttonState = 2;
					g_MyButton2.m_aniType = 2;
					buttonCheck[1] = true; //check

					g_MyButton3.buttonState = 2;
					g_MyButton3.m_aniType = 2;
					buttonCheck[2] = true; //check


					//all sound mute
					//intro
					if(exGameState == 0)
						mciSendCommandW(soundplayCheck, MCI_PAUSE, 0, NULL);

					//main
					if(exGameState == 1 || exGameState == 5)
						mciSendCommandW(soundplayCheck2, MCI_PAUSE, 0, NULL);
				}
			
				//empty
				if (buttonCheck[0] && buttonCheck2[0])
				{
					g_MyButton.buttonState = 0;
					g_MyButton.m_aniType = 0;
					buttonCheck[0] = false;

					g_MyButton2.buttonState = 0;
					g_MyButton2.m_aniType = 0;
					buttonCheck[1] = false; //empty

					g_MyButton3.buttonState = 0;
					g_MyButton3.m_aniType = 0;
					buttonCheck[2] = false; //empty

					//all sound PLAY
					//intro
					if (exGameState == 0)
						mciSendCommandW(soundplayCheck, MCI_RESUME, 0, NULL);

					//main
					if (exGameState == 1 || exGameState == 5)
						mciSendCommandW(soundplayCheck2, MCI_RESUME, 0, NULL);
				}				
			}

			if (g_MyButton2.isCollision(pt, g_MyButton.m_rcCollision[1]) == TRUE)
			{
				if (!buttonCheck[0])
				{
					//check
					if (!buttonCheck[1] && !buttonCheck2[1])
					{
						g_MyButton2.buttonState = 2;
						g_MyButton2.m_aniType = 2;
						buttonCheck[1] = true; //check

						//all sound mute
						//intro
						if (exGameState == 0)
							mciSendCommandW(soundplayCheck, MCI_PAUSE, 0, NULL);

						//main
						if (exGameState == 1 || exGameState == 5)
							mciSendCommandW(soundplayCheck2, MCI_PAUSE, 0, NULL);
					}

					//empty
					if (buttonCheck[1] && buttonCheck2[1])
					{
						g_MyButton2.buttonState = 0;
						g_MyButton2.m_aniType = 0;
						buttonCheck[1] = false;

						//all sound PLAY
						//intro
						if (exGameState == 0)
							mciSendCommandW(soundplayCheck, MCI_RESUME, 0, NULL);

						//main
						if (exGameState == 1 || exGameState == 5)
							mciSendCommandW(soundplayCheck2, MCI_RESUME, 0, NULL);
					}
				}
				
			}

			if (g_MyButton3.isCollision(pt, g_MyButton.m_rcCollision[2]) == TRUE)
			{
				if (!buttonCheck[0])
				{
					//check
					if (!buttonCheck[2] && !buttonCheck2[2])
					{
						g_MyButton3.buttonState = 2;
						g_MyButton3.m_aniType = 2;
						buttonCheck[2] = true; //check
					}

					//empty
					if (buttonCheck[2] && buttonCheck2[2])
					{
						g_MyButton3.buttonState = 0;
						g_MyButton3.m_aniType = 0;
						buttonCheck[2] = false;
					}
				}

			}

			//back BT
			if (g_MyBackBt.isCollision(pt) == TRUE)
			{
				g_MyHp.gameState = exGameState;

				if (!buttonCheck[2])
					sndPlaySoundA("./click2.wav", SND_ASYNC | SND_NODEFAULT | SND_ASYNC);
			}
		}

		if (g_MyHp.gameState == 4)
		{
			//X BT
			if (g_MyXBt2.isCollision(pt, g_MyXBt.m_rcCollision[1]) == TRUE)
			{
				if (!buttonCheck[2])
					sndPlaySoundA("./click2.wav", SND_ASYNC | SND_NODEFAULT | SND_ASYNC);

				PostQuitMessage(0);
			}
		}

		if (g_MyHp.gameState == 5)
		{
			if (g_MyNext.isCollision(pt) == TRUE)
			{
				if (!buttonCheck[2])
					sndPlaySoundA("./click2.wav", SND_ASYNC | SND_NODEFAULT | SND_ASYNC);

				g_MyHp.gameState = 1;

				if (g_MyHp.gameState == 1)
				{
					mciSendCommandW(soundplayCheck2, MCI_PLAY, MCI_DGV_PLAY_REPEAT,
						(DWORD)(LPVOID)&m_mciPlayParms);

					//all main 둘 중 하나라도 켜져있으면
					if (buttonCheck[0] || buttonCheck[1])
					{
						mciSendCommandW(soundplayCheck2, MCI_PAUSE, 0, NULL);
					}

				}
			}
		}

		bMousing = false;
	}
	break;

	case WM_MOUSEMOVE:
	{
		ptCurrentMousePosit.x = LOWORD(lParam);
		ptCurrentMousePosit.y = HIWORD(lParam);

		if (bMousing)
		{
			g_fSpinX -= (ptCurrentMousePosit.x - ptLastMousePosit.x);
			g_fSpinY -= (ptCurrentMousePosit.y - ptLastMousePosit.y);
		}

		POINT pt;
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);

		if (g_MyHp.gameState == 0)
		{
			if (g_MyStart.isCollision(pt) == TRUE)
			{
				//size up
				g_MyStart.State = 1;
				g_MyStart.m_aniType = 1;
				if (!isPlay)
				{
					if (!buttonCheck[2])
						sndPlaySoundA("./jumpsound.wav", SND_ASYNC | SND_NODEFAULT | SND_ASYNC); //점프
					isPlay = true;
				}
			}

			else
			{
				g_MyStart.State = 0;
				g_MyStart.m_aniType = 0;
				isPlay = false;
			}
		}
		
		g_MyCursor.m_positionX = pt.x;
		g_MyCursor.m_positionY = pt.y;

		ptLastMousePosit.x = ptCurrentMousePosit.x;
		ptLastMousePosit.y = ptCurrentMousePosit.y;
	}
	break;

	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}

	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	break;

	default:
	{
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	break;
	}

	return 0;
}


//-----------------------------------------------------------------------------
// Name: init()
// Desc: 6
//-----------------------------------------------------------------------------
void init( void )
{
    g_pD3D = Direct3DCreate9( D3D_SDK_VERSION );

	D3DCAPS9 d3dCaps;
	g_pD3D->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dCaps );

    D3DDISPLAYMODE d3ddm;
    g_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm );

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
	
    d3dpp.Windowed               = TRUE;
	d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat       = d3ddm.Format;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_IMMEDIATE;

    g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd,
                          D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                          &d3dpp, &g_pd3dDevice );

	
	g_pd3dDevice->CreateVertexBuffer( 4*sizeof(Vertex), D3DUSAGE_WRITEONLY, 
                                      D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, 
                                      &g_pVertexBuffer, NULL );
    void *pVertices = NULL;

    g_pVertexBuffer->Lock( 0, sizeof(g_quadVertices), (void**)&pVertices, 0 );
    memcpy( pVertices, g_quadVertices, sizeof(g_quadVertices) );
    g_pVertexBuffer->Unlock();

    D3DXMATRIX matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DXToRadian( 45.0f ), 
                                640.0f / 480.0f, 0.1f, 100.0f );
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );

	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	g_aniSprite.charState = 0;

	//INTRO
	g_MyHp.gameState = 0;

	g_MyBack.Create(g_pd3dDevice, "backGround_IN.txt");
	g_MyBackIntro.Create(g_pd3dDevice, "backGround.txt");
	g_aniSprite.Create(g_pd3dDevice, "DCookie.txt");
	g_aniToufuTime.Create(g_pd3dDevice, "TOUFU_TIME.txt");
	g_aniFloor.Create(g_pd3dDevice, "floor.txt");
	g_MyHp.Create(g_pd3dDevice, "hpBar.txt");
	g_MyBObject.Create(g_pd3dDevice, "bottomObject.txt");
	g_MyBObject2.Create(g_pd3dDevice, "bottomObject2.txt");
	g_MyTObject.Create(g_pd3dDevice, "topObject.txt");
	g_MyStart.Create(g_pd3dDevice, "start.txt");
	g_MyBackSET.Create(g_pd3dDevice, "SETTING.txt");
	g_MyBackOVER.Create(g_pd3dDevice, "GAMEOVER.txt");
	g_MyBackCLEAR.Create(g_pd3dDevice, "GAMECLEAR.txt");
	g_MyBackINC.Create(g_pd3dDevice, "GAMEINC.txt");
	g_MyButton.Create(g_pd3dDevice, "BUTTON.txt");
	g_MyButton2.Create(g_pd3dDevice, "BUTTON.txt");
	g_MyButton3.Create(g_pd3dDevice, "BUTTON.txt");

	g_MyNext.Create(g_pd3dDevice, "next.txt");

	g_MySetBt.Create(g_pd3dDevice, "SETTINGbutton.txt");
	g_MySetBt2.Create(g_pd3dDevice, "SETTINGbutton.txt");
	g_MyBackBt.Create(g_pd3dDevice, "backbt.txt");
	g_MyXBt.Create(g_pd3dDevice, "xButton.txt");
	g_MyXBt2.Create(g_pd3dDevice, "xButton.txt");
	g_MyNum.Create(g_pd3dDevice, "number.txt");


	g_MyToufu.Create(g_pd3dDevice, "toufu.txt");
	g_MyCursor.Create(g_pd3dDevice, "CURSOR.txt");
}

//-----------------------------------------------------------------------------
// Name: shutDown()
// Desc: 
//-----------------------------------------------------------------------------
void shutDown( void )
{
    if( g_pVertexBuffer != NULL ) 
        g_pVertexBuffer->Release(); 

    if( g_pd3dDevice != NULL )
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )
        g_pD3D->Release();
}

//-----------------------------------------------------------------------------
// Name: render()
// Desc: 
//-----------------------------------------------------------------------------
void render(void)
{
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0);

	g_pd3dDevice->BeginScene();

	//intro
	if (g_MyHp.gameState == 0)
	{		
		g_MyBackIntro.OnUpdate(g_fElpasedTime, 1);
		g_MyStart.OnUpdate(g_fElpasedTime);
		g_MySetBt.OnUpdate(g_fElpasedTime, 0);
	}

	//ingame
	if (g_MyHp.gameState == 1)
	{
		g_MyBack.OnUpdate(g_fElpasedTime, 2);
		g_aniSprite.OnUpdate(g_fElpasedTime);
		g_MyTObject.OnUpdate(g_fElpasedTime);		
		g_aniFloor.OnUpdate(g_fElpasedTime);		
		g_MyBObject.OnUpdate(g_fElpasedTime);
		g_MyBObject2.OnUpdate(g_fElpasedTime);
		g_aniToufuTime.OnUpdate(g_fElpasedTime);
		g_MyNum.OnUpdate(g_fElpasedTime);

		if (!g_MyHp.isDie)
		{
			g_MyHp.OnUpdate(g_fElpasedTime);
			g_MyToufu.OnUpdate(g_fElpasedTime);

			g_MyBObject.Move(deltatime, 180.0f);
			g_MyBObject2.Move(deltatime, 180.0f);
			g_aniFloor.Move(deltatime, 180.0f);
			g_MyTObject.Move(deltatime, 180.0f);

			g_MyToufu.Move(deltatime, 180.0f);
		}

		if (g_MyHp.isDie)
		{
			g_MyHp.OnUpdate(g_fElpasedTime);
			g_MyToufu.OnUpdate(g_fElpasedTime);
		}

		if (g_aniToufuTime.checkBounsTime)
		{
			//광속질주상태로 전환
			g_aniSprite.charState = 5;
			g_aniSprite.m_aniType = 5;
			g_aniSprite.checkPoint = false;
			g_MyHp.isFire = true;

			g_aniFloor.Move(deltatime, 200.0f);
			g_MyBObject.Move(deltatime, 200.0f);
			g_MyBObject2.Move(deltatime, 200.0f);
			g_MyTObject.Move(deltatime, 200.0f);

			g_MyToufu.Move(deltatime, 200.0f);
		}

		if (g_aniSprite.checkBounsFrame >= 27)
		{
			g_MyHp.isFire = false;
			g_aniToufuTime.checkBounsTime = false;
			isPlay = false;

			//무적달리기상태로 전환
			g_aniSprite.charState = 7;
			g_aniSprite.m_aniType = 7;

			if (g_aniSprite.checkBounsFrame >= 31)
			{
				//달리기상태로 전환
				g_aniSprite.charState = 0;
				g_aniSprite.m_aniType = 0;
				g_aniSprite.checkBounsFrame = 0;
				g_aniSprite.checkBounsFrame2 = 0;
			}
		}

		if (g_aniSprite.charState == 5)
		{
			if (!isPlay)
			{
				if (!buttonCheck[2])
					sndPlaySoundA("./fire.wav", SND_ASYNC | SND_NODEFAULT | SND_ASYNC);
				isPlay = true;
			}
		}

		if (g_aniSprite.charState != 5 && g_aniSprite.charState != 7)
		{
			if (g_aniSprite.isTrigger(g_MyBObject2.m_rcCollision[0]) == TRUE ||
				g_aniSprite.isTrigger(g_MyBObject2.m_rcCollision[1]) == TRUE ||
				g_aniSprite.isTrigger(g_MyBObject2.m_rcCollision[2]) == TRUE ||
				g_aniSprite.isTrigger(g_MyBObject.m_rcCollision[0]) == TRUE ||
				g_aniSprite.isTrigger(g_MyBObject.m_rcCollision[1]) == TRUE ||
				g_aniSprite.isTrigger(g_MyTObject.m_rcCollision[0]) == TRUE)
			{
				if (!g_MyHp.hitObject)
				{
					g_MyHp.hitObject = true;
					g_aniSprite.checkPoint = false;
					if (!isPlay2)
					{
						if (!buttonCheck[2])
							sndPlaySoundA("./hit.wav", SND_ASYNC | SND_NODEFAULT | SND_ASYNC);
						isPlay2 = true;
					}
				}

				if (g_MyHp.hitObject)
				{
					g_aniSprite.charState = 6;
					g_aniSprite.m_aniType = 6;
				}
			}
		}

		if (g_MyHp.hitObject == false)
			isPlay2 = false;

		if (g_aniSprite.checkBounsFrame2 >= 10)
		{
			g_aniSprite.charState = 0;
			g_aniSprite.m_aniType = 0;
			g_aniSprite.m_positionY = COOKIEPOSITION;

			g_aniSprite.checkBounsFrame = 0;
			g_aniSprite.checkBounsFrame2 = 0;
		}

		if (g_MyHp.isDie)
		{
			if (!buttonCheck[2])
				sndPlaySoundA("./end.wav", SND_ASYNC | SND_NODEFAULT | SND_ASYNC);

			g_MyHp.gameState = 2;
		}

		//두부랑 충돌
		if (g_aniSprite.isTrigger(g_MyToufu.m_rcCollision[0]) == TRUE)
		{
			if (!buttonCheck[2])
			{
				if (!isPlay3)
				{
					sndPlaySoundA("./Toufu.wav", SND_ASYNC | SND_NODEFAULT | SND_ASYNC);
					isPlay = true;
				}
			}		

			if(g_MyNum.numState == 1)
				g_MyNum.numState = 2;
			
			if (g_MyNum.numState == 2 && isEatToufu == 1)
				g_MyNum.numState = 3;		

			if (g_MyNum.numState == 3 && isEatToufu == 2)
				g_MyNum.numState = 4;

			if (g_MyNum.numState == 4 && isEatToufu == 3)
				g_MyNum.numState = 5;

			//두부 사라짐	
			g_MyToufu.isToufu = true;
		}

		//두부랑 충돌하지 않음
		if (g_aniSprite.isTrigger(g_MyToufu.m_rcCollision[0]) == FALSE)
		{
			if (g_MyNum.numState == 2)
				isEatToufu = 1;			
			if (g_MyNum.numState == 3)
				isEatToufu = 2;			
			if (g_MyNum.numState == 4)
				isEatToufu = 3; 

			//클리어
			if (g_MyNum.numState == 5)
			{
				if (!buttonCheck[2])
					sndPlaySoundA("./end.wav", SND_ASYNC | SND_NODEFAULT | SND_ASYNC);

				g_MyHp.gameState = 4;
			}
		}

		if (g_aniSprite.isTrigger(g_MyToufu.m_rcCollision[0]) == TRUE)
		{
			isPlay = false;
		}
	}

	//게임오버
	if (g_MyHp.gameState == 2)
	{
		mciSendCommandW(soundplayCheck2, MCI_CLOSE, 0, NULL);
		g_MyBackOVER.OnUpdate(g_fElpasedTime, 3);
		g_MySetBt2.OnUpdate(g_fElpasedTime, 1);
		g_MyXBt.OnUpdate(g_fElpasedTime,0);
	}

	//setting 
	if (g_MyHp.gameState == 3)
	{
		g_MyBackSET.OnUpdate(g_fElpasedTime, 4);
		g_MyButton.OnUpdate(g_fElpasedTime, 0);
		g_MyButton2.OnUpdate(g_fElpasedTime, 1);
		g_MyButton3.OnUpdate(g_fElpasedTime, 2);
		
		g_MyBackBt.OnUpdate(g_fElpasedTime);
	}

	//clear
	if (g_MyHp.gameState == 4)
	{
		mciSendCommandW(soundplayCheck2, MCI_CLOSE, 0, NULL);
		g_MyBackCLEAR.OnUpdate(g_fElpasedTime, 5);
		g_MyXBt.OnUpdate(g_fElpasedTime,1);
	}

	//설명
	if (g_MyHp.gameState == 5)
	{
		mciSendCommandW(soundplayCheck, MCI_CLOSE, 0, NULL);
		g_MyBackINC.OnUpdate(g_fElpasedTime, 6);
		g_MyNext.OnUpdate(g_fElpasedTime);
	}

	//cursor
	if(g_MyHp.gameState != 1)
		g_MyCursor.OnUpdate(g_fElpasedTime);

	g_pd3dDevice->EndScene();

	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}