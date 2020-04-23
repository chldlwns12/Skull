#include "stdafx.h"
#include "ingameScene.h"

HRESULT inGameScene::init()
{
	//ptPlayer = new player;
	//ptPlayer->init();
	//
	//ptEnemy = new enemy;
	//ptEnemy->init();

	//백그라운드 렉트 - 이준
	rcIngameBg = RectMake(0, 0, 1940, 810);
	inGameBgImg1 = IMAGEMANAGER->findImage("백그라운드1");
	inGameBgImg2 = IMAGEMANAGER->findImage("백그라운드2");
	inGameBgImg3 = IMAGEMANAGER->findImage("백그라운드3");
	inGameBgImg4 = IMAGEMANAGER->findImage("백그라운드4");

	//인게임 로드 이미지 - 이준
	inGameTerrainImg = IMAGEMANAGER->findImage("지형타일");
	//inGameObjectImg = IMAGEMANAGER->findImage("오브젝트타일_병합");

	//윈사이즈 렉트 - 이준
	rcIngameWins = RectMake(0, 0, WINSIZEX, WINSIZEY);

	//메뉴관련 변수 - 이준 0413
	menuX = WINSIZEX / 2;
	menuY = -256;
	//메뉴 렉트 초기화 - 이준 0413
	rcMenuMain = RectMakeCenter(WINSIZEX / 2, -348, 372, 696);
	isMenu = false;
	//isTouch_RS = false;
	//isTouch_EX = false;

	return S_OK;
}

void inGameScene::release()
{
	//ptPlayer->release();
	//ptEnemy->release();
}

void inGameScene::update()
{

	//rcMenuButtonRS = RectMake(rcMenuMain.left + 240, rcMenuMain.top + 220, 170, 62);
	//rcMenuButtonEX = RectMake(rcMenuMain.left + 240, rcMenuMain.top + 320, 170, 62);

	//함수 추가 - 이준
	this->load();

	//타일 렉트 초기화 - 이준
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			sIngameTile[i * TILEX + j].rc = RectMake(rcIngameBg.left + j * TILESIZE, rcIngameBg.top + i * TILESIZE, TILESIZE, TILESIZE);
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

		//if (PtInRect(&rcMenuButtonRS, _ptMouse))
		//{
		//	isTouch_RS = true;
		//	if (INPUT->GetKeyDown(VK_LBUTTON))
		//	{
		//		isMenu = false;
		//	}
		//}
		//else
		//{
		//	isTouch_RS = false;
		//}
		//
		//if (PtInRect(&rcMenuButtonEX, _ptMouse))
		//{
		//	isTouch_EX = true;
		//	if (INPUT->GetKeyDown(VK_LBUTTON))
		//	{
		//		SCENEMANAGER->loadScene("메뉴");
		//	}
		//}
		//else
		//{
		//	isTouch_EX = false;
		//}
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
	//if (!isMenu)
	//{
		//ptPlayer->update();
		//ptEnemy->update();
	//}
}

void inGameScene::render()
{
	//배경 이미지 렌더 - 이준
	inGameBgImg1->render(getMemDC(), rcIngameBg.left, rcIngameBg.top);
	inGameBgImg2->render(getMemDC(), rcIngameBg.left, rcIngameBg.top);
	inGameBgImg3->render(getMemDC(), rcIngameBg.left, rcIngameBg.top);
	inGameBgImg4->render(getMemDC(), rcIngameBg.left, rcIngameBg.top);
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
	}
	//타일 보여주기 - 이준
	if (INPUT->GetToggleKey(VK_F1))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			FrameRect(getMemDC(), sIngameTile[i].rc, RGB(0, 0, 0));
		}
	}

	IMAGEMANAGER->findImage("인게임메뉴화면")->render(getMemDC(), rcMenuMain.left, rcMenuMain.top);

	//if (isTouch_RS)
	//{
	//	IMAGEMANAGER->findImage("인게임_계속버튼On")->render(getMemDC(), rcMenuButtonRS.left, rcMenuButtonRS.top);
	//}
	//else
	//{
	//	IMAGEMANAGER->findImage("인게임_계속버튼")->render(getMemDC(), rcMenuButtonRS.left, rcMenuButtonRS.top);
	//}
	//
	//if (isTouch_EX)
	//{
	//	IMAGEMANAGER->findImage("인게임_나가기버튼On")->render(getMemDC(), rcMenuButtonEX.left, rcMenuButtonEX.top);
	//}
	//else
	//{
	//	IMAGEMANAGER->findImage("인게임_나가기버튼")->render(getMemDC(), rcMenuButtonEX.left, rcMenuButtonEX.top);
	//}

	//ptPlayer->render();
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

