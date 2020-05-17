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
	ptMap3 = new map3;
	ptMap3->init();
	ptBossMap = new bossMap;
	ptBossMap->init();
	ptEnemy = new enemy;
	ptEnemy->init();
	PlayerHpBar = new progressBar;
	PlayerHpBar->init("playerHpBar_front", "playerHpBar_back");
	skulCoolBar1 = new skillCooltime;
	skulCoolBar1->init("showCoolDown", "스컬스킬1");
	skulCoolBar2 = new skillCooltime;
	skulCoolBar2->init("showCoolDown", "스컬스킬2");
	soldierCoolBar1 = new skillCooltime;
	soldierCoolBar1->init("showCoolDown", "병사스킬1");

	samuraiCoolBar1 = new skillCooltime;
	samuraiCoolBar1->init("showCoolDown", "사무라이스킬1_icon");
	samuraiCoolBar2 = new skillCooltime;
	samuraiCoolBar2->init("showCoolDown", "사무라이스킬2_icon");

	PlayerHpBar->setPos(88, WINSIZEY - 48);
	skulCoolBar1->setPos(116 , WINSIZEY - 106);
	skulCoolBar2->setPos(178, WINSIZEY - 106);
	soldierCoolBar1->setPos(116 , WINSIZEY - 106);
	samuraiCoolBar1->setPos(116, WINSIZEY - 106);
	samuraiCoolBar2->setPos(178, WINSIZEY - 106);
	//백그라운드 렉트 - 이준
	//rcIngameBg = RectMake(0, -96, 3880, 810);
	//inGameBgImg1 = IMAGEMANAGER->findImage("백그라운드1");
	//inGameBgImg2 = IMAGEMANAGER->findImage("백그라운드2");
	//inGameBgImg3 = IMAGEMANAGER->findImage("백그라운드3");
	//inGameBgImg4 = IMAGEMANAGER->findImage("백그라운드4");

	//인게임 로드 이미지 - 이준
	//inGameTerrainImg = IMAGEMANAGER->findImage("지형타일");
	//inGameTerrainMiniImg = IMAGEMANAGER->findImage("지형타일_미니");
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
	//rcIngameMini = RectMake(WINSIZEX - 388, 0, 388, 81);
	//rcIngameMcamera = RectMake(WINSIZEX - 388, 10, 128, 72);
	//inGameMiniBgImg1 = IMAGEMANAGER->findImage("백그라운드1_미니");
	//inGameMiniBgImg2 = IMAGEMANAGER->findImage("백그라운드2_미니");
	//inGameMiniBgImg3 = IMAGEMANAGER->findImage("백그라운드3_미니");
	//inGameMiniBgImg4 = IMAGEMANAGER->findImage("백그라운드4_미니");

	isCollision = false;
	playerGravity = 0.f;

	isRun = false;

	DATA->setStage(START);
	DATA->setPlayerRuin(SKUL);

	skillCoolDown = IMAGEMANAGER->findImage("skillCoolDown");
	skillCoolDown2 = IMAGEMANAGER->findImage("skillCoolDown2");
	skillCount1 = skillIndex1 = 0;
	skillCount2 = skillIndex2 = 0;

	isChange = true;
	isPlayerChange = false;

	ptPlayer->setPtEnemy(ptEnemy);
	ptEnemy->setPtPlayer(ptPlayer);
	ptPlayer->setPtBoss(ptBossMap->getPtBoss());
	ptBossMap->getPtBoss()->setPtPlayer(ptPlayer);
	return S_OK;
}

void inGameScene::release()
{
	ptPlayer->release();
	ptMap1->release();
	ptMap2->release();
	ptMap3->release();
	ptBossMap->release();
	ptEnemy->release();
	PlayerHpBar->release();
}

void inGameScene::update()
{
	if (DATA->getStage() == START && isChange == true)
	{
		DATA->setPixelGroundImg(IMAGEMANAGER->findImage("맵1_바닥"));
		DATA->setPixelGroundX(0);
		DATA->setPixelGroundY(0);
		DATA->setPixelGroundRc(RectMake(DATA->getPixelGround().x, DATA->getPixelGround().y, 1940, 720));
		isChange = false;
	}

	if (DATA->getStage() == STAGE_1 && isChange == false)
	{
		DATA->setPixelGroundImg(IMAGEMANAGER->findImage("맵1_성벽3"));
		DATA->setPixelGroundX(0);
		DATA->setPixelGroundY(590);
		DATA->setPixelGroundRc(RectMake(DATA->getPixelGround().x, DATA->getPixelGround().y, 311, 4661));
		isChange = true;
	}

	if (DATA->getStage() == STAGE_1_2 && isChange == true)
	{
		DATA->setPixelGroundImg(IMAGEMANAGER->findImage("아래맵_바닥"));
		DATA->setPixelGroundX(0);
		DATA->setPixelGroundY(0);
		DATA->setPixelGroundRc(RectMake(DATA->getPixelGround().x, DATA->getPixelGround().y, 1588, 720));

		isChange = false;
	}

	if (DATA->getStage() == STAGE_3 && isChange == false)
	{
		DATA->setPixelGroundImg(IMAGEMANAGER->findImage("맵3_바닥"));
		DATA->setPixelGroundX(0);
		DATA->setPixelGroundY(0);
		DATA->setPixelGroundRc(RectMake(DATA->getPixelGround().x, DATA->getPixelGround().y, 1666, 720));
		isChange = true;
	}

	if (DATA->getStage() == STAGE_2 && isChange == true)
	{
		DATA->setPixelGroundImg(IMAGEMANAGER->findImage("맵2_바닥"));
		DATA->setPixelGroundX(0);
		DATA->setPixelGroundY(0);
		DATA->setPixelGroundRc(RectMake(DATA->getPixelGround().x, DATA->getPixelGround().y, 2600, 810));

		//ptEnemy->setEnemy(ENEMY_SOLDIER, 1200, 610);
		isChange = false;
	}


	if (DATA->getStage() == BOSS_STAGE && isChange == false)
	{
		DATA->setPixelGroundImg(IMAGEMANAGER->findImage("보스맵픽셀"));
		DATA->setPixelGroundX(0);
		DATA->setPixelGroundY(0);
		DATA->setPixelGroundRc(RectMake(DATA->getPixelGround().x, DATA->getPixelGround().y, 1875, 720));
		isChange = true;
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

	if (DATA->getStage() == STAGE_1 || DATA->getStage() == START || DATA->getStage() == STAGE_1_2)
	{
		ptMap1->update();
		//ptEnemy->update();
	}
	else if (DATA->getStage() == STAGE_2)
	{
		ptMap2->update();
		ptEnemy->update();
	}
	else if (DATA->getStage() == STAGE_3)
	{
		ptMap3->update();
	}
	else if (DATA->getStage() == BOSS_STAGE)
	{
		ptBossMap->update();
	}
	ptPlayer->update();

	PlayerHpBar->setGauge(ptPlayer->getPlayerMexHp(), ptPlayer->getPlayerCurrentHp());
	skulCoolBar1->setGauge(ptPlayer->getSkillCooldowsMax(), ptPlayer->getSkulCooldown1());
	skulCoolBar2->setGauge(ptPlayer->getSkillCooldowsMax(), ptPlayer->getSkulCooldown2());
	soldierCoolBar1->setGauge(ptPlayer->getSkillCooldowsMax(), ptPlayer->getSoldierCooldown1());
	samuraiCoolBar1->setGauge(ptPlayer->getSkillCooldowsMax(), ptPlayer->getSamuraiCooldown1());
	samuraiCoolBar2->setGauge(ptPlayer->getSkillCooldowsMax(), ptPlayer->getSamuraiCooldown2());

	if (ptPlayer->getSkulSkill1() == true || ptPlayer->getSoldierSkill1() == true ||
		ptPlayer->getSamuraiSkill1() == true || ptPlayer->getSamuraiSkill2() == true)
	{
		skillCount1 = 0;
		skillIndex1 = 0;
	}
	if (ptPlayer->getSkulSkill2() == true || ptPlayer->getSamuraiSkill2() == true)
	{
		skillCount2 = 0;
		skillIndex2 = 0;
	}

	if (DATA->getPlayerRuin() == SKUL)
	{
		if (ptPlayer->getSkulSkill1() == false)
		{
			skillCount1++;
			skillCoolDown->setFrameY(0);
			if (skillCount1 % 4 == 0)
			{
				skillIndex1++;
				if (skillIndex1 > 13)
				{
					skillIndex1 = 13;
				}
				skillCoolDown->setFrameX(skillIndex1);
			}
		}

		if (ptPlayer->getSkulSkill2() == false)
		{
			skillCount2++;
			skillCoolDown2->setFrameY(0);
			if (skillCount2 % 4 == 0)
			{
				skillIndex2++;
				if (skillIndex2 > 13)
				{
					skillIndex2 = 13;
				}
				skillCoolDown2->setFrameX(skillIndex2);
			}
		}
	}
	else if (DATA->getPlayerRuin() == SOLDIER)
	{
		if (ptPlayer->getSoldierSkill1() == false)
		{
			skillCount1++;
			skillCoolDown->setFrameY(0);
			if (skillCount1 % 4 == 0)
			{
				skillIndex1++;
				if (skillIndex1 > 13)
				{
					skillIndex1 = 13;
				}
				skillCoolDown->setFrameX(skillIndex1);
			}
		}
	}
	else if (DATA->getPlayerRuin() == SAMURAI)
	{
		if (ptPlayer->getSamuraiSkill1() == false)
		{
			skillCount1++;
			skillCoolDown->setFrameY(0);
			if (skillCount1 % 4 == 0)
			{
				skillIndex1++;
				if (skillIndex1 > 13)
				{
					skillIndex1 = 13;
				}
				skillCoolDown->setFrameX(skillIndex1);
			}
		}

		if (ptPlayer->getSamuraiSkill2() == false)
		{
			skillCount2++;
			skillCoolDown2->setFrameY(0);
			if (skillCount2 % 4 == 0)
			{
				skillIndex2++;
				if (skillIndex2 > 13)
				{
					skillIndex2 = 13;
				}
				skillCoolDown2->setFrameX(skillIndex2);
			}
		}
	}
}

void inGameScene::render()
{
	////배경 이미지 렌더 - 이준
	//inGameBgImg1->render(getMemDC(), rcIngameBg.left, rcIngameBg.top);
	//inGameBgImg2->render(getMemDC(), rcIngameBg.left, rcIngameBg.top);
	//inGameBgImg3->render(getMemDC(), rcIngameBg.left, rcIngameBg.top);
	//inGameBgImg4->render(getMemDC(), rcIngameBg.left, rcIngameBg.top);
	////미니맵 이미지 렌더
	//inGameMiniBgImg1->render(getMemDC(), rcIngameMini.left, rcIngameMini.top);
	//inGameMiniBgImg2->render(getMemDC(), rcIngameMini.left, rcIngameMini.top);
	//inGameMiniBgImg3->render(getMemDC(), rcIngameMini.left, rcIngameMini.top);
	//inGameMiniBgImg4->render(getMemDC(), rcIngameMini.left, rcIngameMini.top);
	if (DATA->getStage() == STAGE_1 || DATA->getStage() == START || DATA->getStage() == STAGE_1_2)
	{
		ptMap1->render();
		//ptEnemy->render();
	}
	else if (DATA->getStage() == STAGE_2)
	{
		ptMap2->render();
		ptEnemy->render();
	}
	else if (DATA->getStage() == STAGE_3)
	{
		ptMap3->render();
	}
	else if (DATA->getStage() == BOSS_STAGE)
	{
		ptBossMap->render();
	}
	ptPlayer->render();
	IMAGEMANAGER->findImage("플레이어UI창")->render(getMemDC(), 0, WINSIZEY - 134);
	if (DATA->getPlayerRuin() == SKUL)
	{
		IMAGEMANAGER->findImage("스컬큰프로필")->render(getMemDC(), 15, WINSIZEY - 132);
	}
	if (DATA->getPlayerRuin() == SOLDIER)
	{
		IMAGEMANAGER->findImage("병사큰프로필")->render(getMemDC(), 15, WINSIZEY - 132);
	}
	if (DATA->getPlayerRuin() == SAMURAI)
	{
		IMAGEMANAGER->findImage("사무라이큰프로필")->render(getMemDC(), 15, WINSIZEY - 132);
	}

	IMAGEMANAGER->findImage("작은원")->render(getMemDC(), 0, WINSIZEY - 134);

	if (DATA->getPlayerRuin() == SKUL)
	{
		if (DATA->getHaveRuin()[1] == SOLDIER || DATA->getHaveRuin()[0] == SOLDIER)
		{
			IMAGEMANAGER->findImage("병사작은프로필")->render(getMemDC(), 17, WINSIZEY - 66);
		}
		if (DATA->getHaveRuin()[1] == SAMURAI || DATA->getHaveRuin()[0] == SAMURAI)
		{
			IMAGEMANAGER->findImage("사무라이작은프로필")->render(getMemDC(), 17, WINSIZEY - 66);
		}
	}
	if (DATA->getPlayerRuin() == SOLDIER)
	{
		if (DATA->getHaveRuin()[0] == SKUL || DATA->getHaveRuin()[1] == SKUL)
		{
			IMAGEMANAGER->findImage("스컬작은프로필")->render(getMemDC(), 17, WINSIZEY - 66);
		}
		if (DATA->getHaveRuin()[0] == SAMURAI || DATA->getHaveRuin()[1] == SAMURAI)
		{
			IMAGEMANAGER->findImage("사무라이작은프로필")->render(getMemDC(), 17, WINSIZEY - 66);
		}
	}
	if (DATA->getPlayerRuin() == SAMURAI)
	{
		if (DATA->getHaveRuin()[0] == SKUL || DATA->getHaveRuin()[1] == SKUL)
		{
			IMAGEMANAGER->findImage("스컬작은프로필")->render(getMemDC(), 17, WINSIZEY - 66);
		}
		if (DATA->getHaveRuin()[0] == SOLDIER || DATA->getHaveRuin()[1] == SOLDIER)
		{
			IMAGEMANAGER->findImage("병사작은프로필")->render(getMemDC(), 17, WINSIZEY - 66);
		}
	}
	//IMAGEMANAGER->findImage("스컬스킬1")->render(getMemDC(), 120, WINSIZEY - 104);
	//IMAGEMANAGER->findImage("스컬스킬2")->render(getMemDC(), 180, WINSIZEY - 104);

	IMAGEMANAGER->findImage("UI창_space")->render(getMemDC(), 0, WINSIZEY - 134);
	if (DATA->getPlayerRuin() == SKUL)
	{
		skulCoolBar1->render(true);
	}
	else if (DATA->getPlayerRuin() == SOLDIER)
	{
		soldierCoolBar1->render(true);
	}
	else if (DATA->getPlayerRuin() == SAMURAI)
	{
		samuraiCoolBar1->render(true);
	}
	IMAGEMANAGER->findImage("A_button")->render(getMemDC(), 130, WINSIZEY - 117);
	if (DATA->getPlayerRuin() == SKUL || DATA->getPlayerRuin() == SAMURAI)
	{
		IMAGEMANAGER->findImage("스킬칸")->render(getMemDC(), 176, WINSIZEY - 108);
		if (DATA->getPlayerRuin() == SKUL)
		{
			skulCoolBar2->render(true);
		}
		else if (DATA->getPlayerRuin() == SAMURAI)
		{
			samuraiCoolBar2->render(true);
		}
		IMAGEMANAGER->findImage("S_button")->render(getMemDC(), 190, WINSIZEY - 117);
	}
	PlayerHpBar->render();
	
	skillCoolDown->frameRender(getMemDC(), 75, WINSIZEY - 212);
	skillCoolDown2->frameRender(getMemDC(), 133, WINSIZEY - 212);
		

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
		
	char str8[100];
	char str9[100];

	sprintf(str8, "Index1 : %d", skillIndex1);
	TextOut(getMemDC(), 10, 230, str8, strlen(str8));
	sprintf(str9, "Index2 : %d", skillIndex2);
	TextOut(getMemDC(), 10, 250, str9, strlen(str9));
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
