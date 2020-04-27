#include "stdafx.h"
#include "ingameScene.h"

HRESULT inGameScene::init()
{
	ptPlayer = new player;
	ptPlayer->init();
	//
	//ptEnemy = new enemy;
	//ptEnemy->init();

	//백그라운드 렉트 - 이준
	rcIngameBg = RectMake(0, -96, 3880, 810);
	inGameBgImg1 = IMAGEMANAGER->findImage("백그라운드1");
	inGameBgImg2 = IMAGEMANAGER->findImage("백그라운드2");
	inGameBgImg3 = IMAGEMANAGER->findImage("백그라운드3");
	inGameBgImg4 = IMAGEMANAGER->findImage("백그라운드4");

	//인게임 로드 이미지 - 이준
	inGameTerrainImg = IMAGEMANAGER->findImage("지형타일");
	inGameTerrainMiniImg = IMAGEMANAGER->findImage("지형타일_미니");
	//inGameObjectImg = IMAGEMANAGER->findImage("오브젝트타일_병합");

	//윈사이즈 렉트 - 이준
	rcIngameWins = RectMake(0, 0, WINSIZEX, WINSIZEY);

	//메뉴관련 변수 - 이준 0413
	menuX = WINSIZEX / 2;
	menuY = -256;
	//메뉴 렉트 초기화 - 이준 0413
	rcMenuMain = RectMakeCenter(WINSIZEX / 2, -348, 372, 696);
	isMenu = false;
	isTouch_RS = false;
	isTouch_OP = false;
	isTouch_QT = false;

	//미니맵
	rcIngameMini = RectMake(WINSIZEX - 388, 0, 388, 81);
	rcIngameMcamera = RectMake(WINSIZEX - 388, 10, 128, 72);
	inGameMiniBgImg1 = IMAGEMANAGER->findImage("백그라운드1_미니");
	inGameMiniBgImg2 = IMAGEMANAGER->findImage("백그라운드2_미니");
	inGameMiniBgImg3 = IMAGEMANAGER->findImage("백그라운드3_미니");
	inGameMiniBgImg4 = IMAGEMANAGER->findImage("백그라운드4_미니");

	isCollision = false;
	playerGravity = 0.f;
	return S_OK;
}

void inGameScene::release()
{
	ptPlayer->release();
	//ptEnemy->release();
}

void inGameScene::update()
{

	rcMenuButtonRS = RectMake(rcMenuMain.left + 100, rcMenuMain.top + 335, 173, 57);
	rcMenuButtonOP = RectMake(rcMenuMain.left + 100, rcMenuMain.top + 435, 173, 57);
	rcMenuButtonQT = RectMake(rcMenuMain.left + 100, rcMenuMain.top + 535, 173, 57);

	//함수 추가 - 이준
	this->load();
	this->miniLoad();

	//타일 렉트 초기화 - 이준
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			sIngameTile[i * TILEX + j].rc = RectMake(rcIngameBg.left + j * TILESIZE, rcIngameBg.top + i * TILESIZE, TILESIZE, TILESIZE);
			//미니맵 타일 렉트 초기화
			sIngameMiniTile[i * TILEX + j].rc = RectMake(rcIngameMini.left + j * (TILESIZE / 10 + 0.4f), rcIngameMini.top + i * (TILESIZE / 10 + 0.5f), TILESIZE / 10, TILESIZE / 10);
		}
	}

	//ESC 버튼 추가 - 이준0413
	if (INPUT->GetKeyDown(VK_F2))
	{
		isMenu = true;
	}
	if (isMenu)
	{
		rcMenuMain.bottom += 10;
		rcMenuMain.top += 10;
		if (rcMenuMain.top >= WINSIZEY / 2 - 388)
		{
			rcMenuMain.top = WINSIZEY / 2 - 388;
			rcMenuMain.bottom = rcMenuMain.top + 696;
		}

		if (PtInRect(&rcMenuButtonRS, _ptMouse))
		{
			isTouch_RS = true;
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				isMenu = false;
			}
		}
		else
		{
			isTouch_RS = false;
		}

		if (PtInRect(&rcMenuButtonQT, _ptMouse))
		{
			isTouch_QT = true;
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				SCENEMANAGER->loadScene("메뉴화면");
			}
		}
		else
		{
			isTouch_QT = false;
		}
	}
	else
	{
		rcMenuMain.bottom -= 12;
		rcMenuMain.top -= 12;

		if (rcMenuMain.bottom <= 0)
		{
			rcMenuMain.top = -696;
			rcMenuMain.bottom = 0;
		}
	}

	//지형 충돌
	RECT rcTemp;

	//카메라 이동
	if (INPUT->GetKey(VK_RIGHT))
	{
		if (ptPlayer->getRcPlayerCamera().right >= WINSIZEX)
		{
			if (ptPlayer->getRcPlayerCamera().right < rcIngameBg.right)
			{
			//ptPlayer->setCameraLeft(0);
				if (isCollision == false)
				{
					rcIngameBg.left -= 10;
					rcIngameBg.right -= 10;
					rcIngameMcamera.left += 1;
					rcIngameMcamera.right += 1;
				}
				ptPlayer->setCameraRight(WINSIZEX);
				ptPlayer->setPlayerX(WINSIZEX / 2);
			}
		}

		for (int i = 0; i < TILEY * TILEX; i++)
		{
			if (sIngameTile[i].isTouch)
			{
				if(IntersectRect(&rcTemp, &sIngameTile[i].rc, &ptPlayer->getRcRight()))
				{
					ptPlayer->setPlayerX(sIngameTile[i].rc.left - 40);
					//ptPlayer->setPlayerSpeed(0.f);
					isCollision = true;
				}
				else
				{
					isCollision = false;
				}
			}
		}
	}
	
	if (INPUT->GetKey(VK_LEFT))
	{
		if (ptPlayer->getRcPlayerCamera().left <= 0)
		{
			if (ptPlayer->getRcPlayerCamera().left > rcIngameBg.left)
			{
			//ptPlayer->setCameraRight(WINSIZEX);
				if (isCollision == false)
				{
					rcIngameBg.left += 10;
					rcIngameBg.right += 10;
					rcIngameMcamera.left -= 1;
					rcIngameMcamera.right -= 1;
				}
				ptPlayer->setCameraLeft(0);
				ptPlayer->setPlayerX(WINSIZEX / 2);
			}
		}

		for (int i = 0; i < TILEY * TILEX; i++)
		{
			if (sIngameTile[i].isTouch)
			{
				if (IntersectRect(&rcTemp, &sIngameTile[i].rc, &ptPlayer->getRcLeft()))
				{
					ptPlayer->setPlayerX(sIngameTile[i].rc.right + 40);
					//ptPlayer->setPlayerSpeed(0.f);
					isCollision = true;
				}
				else
				{
					isCollision = false;
				}
			}
		}
	}

	//바닥 충돌
	for (int i = 0; i < TILEY * TILEX; i++)
	{
		if (sIngameTile[i].isTouch && isCollision == false)
		{
			if(IntersectRect(&rcTemp, &sIngameTile[i].rc, &ptPlayer->getRcBottom()))
			{
				ptPlayer->setPlayerY(sIngameTile[i].rc.top - 23.f);
				ptPlayer->setJumpSpeed(0.f);
				ptPlayer->setGravity(0.f);
				ptPlayer->setState(PLAYER_IDLE);
				ptPlayer->setIsJump(false);
			}
			//else if(ptPlayer->getIsJump() == false)
			//{
			//	playerGravity += 0.7f;
			//	ptPlayer->setGravity(playerGravity);
			//}
		}
	}
	
	ptPlayer->update();
}

void inGameScene::render()
{
	//배경 이미지 렌더 - 이준
	inGameBgImg1->render(getMemDC(), rcIngameBg.left, rcIngameBg.top);
	inGameBgImg2->render(getMemDC(), rcIngameBg.left, rcIngameBg.top);
	inGameBgImg3->render(getMemDC(), rcIngameBg.left, rcIngameBg.top);
	inGameBgImg4->render(getMemDC(), rcIngameBg.left, rcIngameBg.top);
	//미니맵 이미지 렌더
	inGameMiniBgImg1->render(getMemDC(), rcIngameMini.left, rcIngameMini.top);
	inGameMiniBgImg2->render(getMemDC(), rcIngameMini.left, rcIngameMini.top);
	inGameMiniBgImg3->render(getMemDC(), rcIngameMini.left, rcIngameMini.top);
	inGameMiniBgImg4->render(getMemDC(), rcIngameMini.left, rcIngameMini.top);

	FrameRect(getMemDC(), rcIngameMini, RGB(0, 0, 0));
	FrameRect(getMemDC(), rcIngameMcamera, RGB(255, 0, 0));
	//타일에 이미지 렌더 - 이준
	RECT rcTemp3;

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (IntersectRect(&rcTemp3, &rcIngameWins, &sIngameTile[i].rc))
		{
			inGameTerrainImg->frameRender(getMemDC(), sIngameTile[i].rc.left, sIngameTile[i].rc.top,
				sIngameTile[i].terrainFrameX, sIngameTile[i].terrainFrameY);


			//inGameObjectImg->frameRender(getMemDC(), sIngameTile[i].rc.left, sIngameTile[i].rc.top,
			//	sIngameTile[i].objFrameX, sIngameTile[i].objFrameY);
		}
		if (IntersectRect(&rcTemp3, &rcIngameMcamera, &sIngameMiniTile[i].rc))
		{
			inGameTerrainMiniImg->frameRender(getMemDC(), sIngameMiniTile[i].rc.left, sIngameMiniTile[i].rc.top,
				sIngameMiniTile[i].terrainFrameX, sIngameMiniTile[i].terrainFrameY);
		}
	}
	//타일 보여주기 - 이준
	if (INPUT->GetToggleKey(VK_F1))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			FrameRect(getMemDC(), sIngameTile[i].rc, RGB(0, 0, 0));
		}
	}
	if (INPUT->GetToggleKey(VK_F3))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			FrameRect(getMemDC(), sIngameMiniTile[i].rc, RGB(0, 255, 0));
		}
	}

	IMAGEMANAGER->findImage("인게임메뉴화면")->render(getMemDC(), rcMenuMain.left, rcMenuMain.top);

	if (isTouch_RS)
	{
		IMAGEMANAGER->findImage("인게임_계속버튼On")->render(getMemDC(), rcMenuButtonRS.left, rcMenuButtonRS.top);
	}
	else
	{
		IMAGEMANAGER->findImage("인게임_계속버튼")->render(getMemDC(), rcMenuButtonRS.left, rcMenuButtonRS.top);
	}

	if (isTouch_OP)
	{
		IMAGEMANAGER->findImage("인게임_옵션버튼On")->render(getMemDC(), rcMenuButtonOP.left, rcMenuButtonOP.top);
	}
	else
	{
		IMAGEMANAGER->findImage("인게임_옵션버튼")->render(getMemDC(), rcMenuButtonOP.left, rcMenuButtonOP.top);
	}
	
	if (isTouch_QT)
	{
		IMAGEMANAGER->findImage("인게임_나가기버튼On")->render(getMemDC(), rcMenuButtonQT.left, rcMenuButtonQT.top);
	}
	else
	{
		IMAGEMANAGER->findImage("인게임_나가기버튼")->render(getMemDC(), rcMenuButtonQT.left, rcMenuButtonQT.top);
	}
	
	ptPlayer->render();
	//ptEnemy->render();
}

void inGameScene::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("save.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, sIngameTile, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);

}
void inGameScene::miniLoad()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("savemini.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, sIngameMiniTile, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);
}
