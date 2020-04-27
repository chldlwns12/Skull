#include "stdafx.h"
#include "ingameScene.h"

HRESULT inGameScene::init()
{
	ptPlayer = new player;
	ptPlayer->init();
	//
	//ptEnemy = new enemy;
	//ptEnemy->init();

	//��׶��� ��Ʈ - ����
	rcIngameBg = RectMake(0, -96, 3880, 810);
	inGameBgImg1 = IMAGEMANAGER->findImage("��׶���1");
	inGameBgImg2 = IMAGEMANAGER->findImage("��׶���2");
	inGameBgImg3 = IMAGEMANAGER->findImage("��׶���3");
	inGameBgImg4 = IMAGEMANAGER->findImage("��׶���4");

	//�ΰ��� �ε� �̹��� - ����
	inGameTerrainImg = IMAGEMANAGER->findImage("����Ÿ��");
	inGameTerrainMiniImg = IMAGEMANAGER->findImage("����Ÿ��_�̴�");
	//inGameObjectImg = IMAGEMANAGER->findImage("������ƮŸ��_����");

	//�������� ��Ʈ - ����
	rcIngameWins = RectMake(0, 0, WINSIZEX, WINSIZEY);

	//�޴����� ���� - ���� 0413
	menuX = WINSIZEX / 2;
	menuY = -256;
	//�޴� ��Ʈ �ʱ�ȭ - ���� 0413
	rcMenuMain = RectMakeCenter(WINSIZEX / 2, -348, 372, 696);
	isMenu = false;
	isTouch_RS = false;
	isTouch_OP = false;
	isTouch_QT = false;

	//�̴ϸ�
	rcIngameMini = RectMake(WINSIZEX - 388, 0, 388, 81);
	rcIngameMcamera = RectMake(WINSIZEX - 388, 10, 128, 72);
	inGameMiniBgImg1 = IMAGEMANAGER->findImage("��׶���1_�̴�");
	inGameMiniBgImg2 = IMAGEMANAGER->findImage("��׶���2_�̴�");
	inGameMiniBgImg3 = IMAGEMANAGER->findImage("��׶���3_�̴�");
	inGameMiniBgImg4 = IMAGEMANAGER->findImage("��׶���4_�̴�");

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

	//�Լ� �߰� - ����
	this->load();
	this->miniLoad();

	//Ÿ�� ��Ʈ �ʱ�ȭ - ����
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			sIngameTile[i * TILEX + j].rc = RectMake(rcIngameBg.left + j * TILESIZE, rcIngameBg.top + i * TILESIZE, TILESIZE, TILESIZE);
			//�̴ϸ� Ÿ�� ��Ʈ �ʱ�ȭ
			sIngameMiniTile[i * TILEX + j].rc = RectMake(rcIngameMini.left + j * (TILESIZE / 10 + 0.4f), rcIngameMini.top + i * (TILESIZE / 10 + 0.5f), TILESIZE / 10, TILESIZE / 10);
		}
	}

	//ESC ��ư �߰� - ����0413
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
				SCENEMANAGER->loadScene("�޴�ȭ��");
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

	//���� �浹
	RECT rcTemp;

	//ī�޶� �̵�
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

	//�ٴ� �浹
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
	//��� �̹��� ���� - ����
	inGameBgImg1->render(getMemDC(), rcIngameBg.left, rcIngameBg.top);
	inGameBgImg2->render(getMemDC(), rcIngameBg.left, rcIngameBg.top);
	inGameBgImg3->render(getMemDC(), rcIngameBg.left, rcIngameBg.top);
	inGameBgImg4->render(getMemDC(), rcIngameBg.left, rcIngameBg.top);
	//�̴ϸ� �̹��� ����
	inGameMiniBgImg1->render(getMemDC(), rcIngameMini.left, rcIngameMini.top);
	inGameMiniBgImg2->render(getMemDC(), rcIngameMini.left, rcIngameMini.top);
	inGameMiniBgImg3->render(getMemDC(), rcIngameMini.left, rcIngameMini.top);
	inGameMiniBgImg4->render(getMemDC(), rcIngameMini.left, rcIngameMini.top);

	FrameRect(getMemDC(), rcIngameMini, RGB(0, 0, 0));
	FrameRect(getMemDC(), rcIngameMcamera, RGB(255, 0, 0));
	//Ÿ�Ͽ� �̹��� ���� - ����
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
	//Ÿ�� �����ֱ� - ����
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

	IMAGEMANAGER->findImage("�ΰ��Ӹ޴�ȭ��")->render(getMemDC(), rcMenuMain.left, rcMenuMain.top);

	if (isTouch_RS)
	{
		IMAGEMANAGER->findImage("�ΰ���_��ӹ�ưOn")->render(getMemDC(), rcMenuButtonRS.left, rcMenuButtonRS.top);
	}
	else
	{
		IMAGEMANAGER->findImage("�ΰ���_��ӹ�ư")->render(getMemDC(), rcMenuButtonRS.left, rcMenuButtonRS.top);
	}

	if (isTouch_OP)
	{
		IMAGEMANAGER->findImage("�ΰ���_�ɼǹ�ưOn")->render(getMemDC(), rcMenuButtonOP.left, rcMenuButtonOP.top);
	}
	else
	{
		IMAGEMANAGER->findImage("�ΰ���_�ɼǹ�ư")->render(getMemDC(), rcMenuButtonOP.left, rcMenuButtonOP.top);
	}
	
	if (isTouch_QT)
	{
		IMAGEMANAGER->findImage("�ΰ���_�������ưOn")->render(getMemDC(), rcMenuButtonQT.left, rcMenuButtonQT.top);
	}
	else
	{
		IMAGEMANAGER->findImage("�ΰ���_�������ư")->render(getMemDC(), rcMenuButtonQT.left, rcMenuButtonQT.top);
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
