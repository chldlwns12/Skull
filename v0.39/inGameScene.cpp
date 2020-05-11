#include "stdafx.h"
#include "ingameScene.h"

HRESULT inGameScene::init()
{
	ptPlayer = new player;
	ptPlayer->init();
	ptMap1 = new map1;
	ptMap1->init();
	ptMap2 = new map2;
	ptMap2->init();
	ptEnemy = new enemy;
	ptEnemy->init();
	PlayerHpBar = new progressBar;
	PlayerHpBar->init("playerHpBar_front", "playerHpBar_back");
	
	PlayerHpBar->setPos(93, WINSIZEY - 46);

	//��׶��� ��Ʈ - ����
	//rcIngameBg = RectMake(0, -96, 3880, 810);
	//inGameBgImg1 = IMAGEMANAGER->findImage("��׶���1");
	//inGameBgImg2 = IMAGEMANAGER->findImage("��׶���2");
	//inGameBgImg3 = IMAGEMANAGER->findImage("��׶���3");
	//inGameBgImg4 = IMAGEMANAGER->findImage("��׶���4");

	//�ΰ��� �ε� �̹��� - ����
	//inGameTerrainImg = IMAGEMANAGER->findImage("����Ÿ��");
	//inGameTerrainMiniImg = IMAGEMANAGER->findImage("����Ÿ��_�̴�");
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
	//rcIngameMini = RectMake(WINSIZEX - 388, 0, 388, 81);
	//rcIngameMcamera = RectMake(WINSIZEX - 388, 10, 128, 72);
	//inGameMiniBgImg1 = IMAGEMANAGER->findImage("��׶���1_�̴�");
	//inGameMiniBgImg2 = IMAGEMANAGER->findImage("��׶���2_�̴�");
	//inGameMiniBgImg3 = IMAGEMANAGER->findImage("��׶���3_�̴�");
	//inGameMiniBgImg4 = IMAGEMANAGER->findImage("��׶���4_�̴�");

	isCollision = false;
	playerGravity = 0.f;

	isRun = false;

	DATA->setStage(START);

	isChange = true;
	return S_OK;
}

void inGameScene::release()
{
	ptPlayer->release();
	ptMap1->release();
	ptMap2->release();
	ptEnemy->release();
	PlayerHpBar->release();
}

void inGameScene::update()
{
	if (DATA->getStage() == START && isChange == true)
	{
		DATA->setPixelGroundImg(IMAGEMANAGER->findImage("��1_�ٴ�"));
		DATA->setPixelGroundX(0);
		DATA->setPixelGroundY(0);
		DATA->setPixelGroundRc(RectMake(DATA->getPixelGround().x, DATA->getPixelGround().y, 1940, 720));
		isChange = false;
	}

	if (DATA->getStage() == STAGE_1 && isChange == false)
	{
		DATA->setPixelGroundImg(IMAGEMANAGER->findImage("��1_����3"));
		DATA->setPixelGroundX(0);
		DATA->setPixelGroundY(590);
		DATA->setPixelGroundRc(RectMake(DATA->getPixelGround().x, DATA->getPixelGround().y, 311, 4661));
		isChange = true;
	}

	if (DATA->getStage() == STAGE_1_2 && isChange == true)
	{
		DATA->setPixelGroundImg(IMAGEMANAGER->findImage("�Ʒ���_�ٴ�"));
		DATA->setPixelGroundX(0);
		DATA->setPixelGroundY(0);
		DATA->setPixelGroundRc(RectMake(DATA->getPixelGround().x, DATA->getPixelGround().y, 1588, 720));

		isChange = false;
	}

	if (DATA->getStage() == STAGE_2 && isChange == false)
	{
		DATA->setPixelGroundImg(IMAGEMANAGER->findImage("��2_�ٴ�"));
		DATA->setPixelGroundX(0);
		DATA->setPixelGroundY(0);
		DATA->setPixelGroundRc(RectMake(DATA->getPixelGround().x, DATA->getPixelGround().y, 2600, 810));
		isChange = true;
	}

	if (DATA->getStage() == STAGE_3 && isChange == true)
	{
		DATA->setPixelGroundImg(IMAGEMANAGER->findImage("��3_�ٴ�"));
		DATA->setPixelGroundX(0);
		DATA->setPixelGroundY(0);
		DATA->setPixelGroundRc(RectMake(DATA->getPixelGround().x, DATA->getPixelGround().y, 1666, 720));
		isChange = false;
	}

	rcMenuButtonRS = RectMake(rcMenuMain.left + 100, rcMenuMain.top + 335, 173, 57);
	rcMenuButtonOP = RectMake(rcMenuMain.left + 100, rcMenuMain.top + 435, 173, 57);
	rcMenuButtonQT = RectMake(rcMenuMain.left + 100, rcMenuMain.top + 535, 173, 57);
	
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

	if (DATA->getStage() == STAGE_1 || DATA->getStage() == START || DATA->getStage() == STAGE_1_2)
	{
		ptMap1->update();
	}
	else if (DATA->getStage() == STAGE_2)
	{
		ptMap2->update();
		ptEnemy->update();
	}
	ptPlayer->update();

	PlayerHpBar->setGauge(ptPlayer->getPlayerMexHp(), ptPlayer->getPlayerCurrentHp());
}

void inGameScene::render()
{
	////��� �̹��� ���� - ����
	//inGameBgImg1->render(getMemDC(), rcIngameBg.left, rcIngameBg.top);
	//inGameBgImg2->render(getMemDC(), rcIngameBg.left, rcIngameBg.top);
	//inGameBgImg3->render(getMemDC(), rcIngameBg.left, rcIngameBg.top);
	//inGameBgImg4->render(getMemDC(), rcIngameBg.left, rcIngameBg.top);
	////�̴ϸ� �̹��� ����
	//inGameMiniBgImg1->render(getMemDC(), rcIngameMini.left, rcIngameMini.top);
	//inGameMiniBgImg2->render(getMemDC(), rcIngameMini.left, rcIngameMini.top);
	//inGameMiniBgImg3->render(getMemDC(), rcIngameMini.left, rcIngameMini.top);
	//inGameMiniBgImg4->render(getMemDC(), rcIngameMini.left, rcIngameMini.top);
	if (DATA->getStage() == STAGE_1 || DATA->getStage() == START || DATA->getStage() == STAGE_1_2)
	{
		ptMap1->render();
	}
	else if (DATA->getStage() == STAGE_2)
	{
		ptMap2->render();
		ptEnemy->render();
	}
	ptPlayer->render();
	IMAGEMANAGER->findImage("�÷��̾�UIâ")->render(getMemDC(), 0, WINSIZEY - 135);
	IMAGEMANAGER->findImage("ū������")->render(getMemDC(), 15, WINSIZEY - 130);
	IMAGEMANAGER->findImage("������")->render(getMemDC(), 0, WINSIZEY - 135);
	IMAGEMANAGER->findImage("UIâ_space")->render(getMemDC(), 0, WINSIZEY - 135);
	IMAGEMANAGER->findImage("���ý�ų1")->render(getMemDC(), 120, WINSIZEY - 104);
	IMAGEMANAGER->findImage("��ųĭ")->render(getMemDC(), 179, WINSIZEY - 106);
	IMAGEMANAGER->findImage("���ý�ų2")->render(getMemDC(), 180, WINSIZEY - 104);
	IMAGEMANAGER->findImage("A_button")->render(getMemDC(), 133, WINSIZEY - 117);
	IMAGEMANAGER->findImage("S_button")->render(getMemDC(), 193, WINSIZEY - 117);
	PlayerHpBar->render();


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

}

//void inGameScene::load()
//{
//	HANDLE file;
//	DWORD read;
//
//	file = CreateFile("save.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
//		FILE_ATTRIBUTE_NORMAL, NULL);
//	ReadFile(file, sIngameTile, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
//	CloseHandle(file);
//
//}
//void inGameScene::miniLoad()
//{
//	HANDLE file;
//	DWORD read;
//
//	file = CreateFile("savemini.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
//		FILE_ATTRIBUTE_NORMAL, NULL);
//	ReadFile(file, sIngameMiniTile, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
//	CloseHandle(file);
//}
