#include "stdafx.h"
#include "map3.h"

HRESULT map3::init()
{
	backGroundImg1 = IMAGEMANAGER->findImage("백그라운드1");
	backGroundImg2 = IMAGEMANAGER->findImage("백그라운드2");
	backGroundImg3 = IMAGEMANAGER->findImage("백그라운드3");
	backGroundImg4 = IMAGEMANAGER->findImage("백그라운드4");
	object = IMAGEMANAGER->findImage("맵3_오브젝트");
	DoorImg = IMAGEMANAGER->findImage("시작문");
	F_buttonImg = IMAGEMANAGER->findImage("F상호작용");
	InputImg = IMAGEMANAGER->findImage("들어가기");
	lookImg = IMAGEMANAGER->findImage("살펴보기");
	nomalRuin = IMAGEMANAGER->findImage("노멀뼈무덤");
	uniqueRuin = IMAGEMANAGER->findImage("유니크뼈무덤");
	soldierRuin = IMAGEMANAGER->findImage("병사해골");
	samuraiRuin = IMAGEMANAGER->findImage("사무라이해골");
	inforSkul = IMAGEMANAGER->findImage("일반해골설명");
	inforSoldier = IMAGEMANAGER->findImage("병사해골설명");
	inforSamurai = IMAGEMANAGER->findImage("사무라이해골설명");
	putImg = IMAGEMANAGER->findImage("줍기");

	rcBg1 = RectMake(0, 0, 1666, 720);
	rcBg2 = RectMake(0, 0, 1666, 720);
	rcBg3 = RectMake(0, 0, 1666, 720);
	rcBg4 = RectMake(0, 0, 1666, 720);

	tileX = tileY = 0;
	//playerX = 0.f;
	isDoor = false;
	isRuin = false;
	isNomal = false;
	isUnique = false;
	isLook = false;
	isItem = false;

	random = RANDOM->Range(1,100);

	doorCount = doorIndex = 0;
	ruinCount = ruinIndex = 0;

	itemY = rcBg4.top + 550;

	itemGravity = 0.f;
	itemSpeed = 20.f;
	isGround = false;
	return S_OK;
}

void map3::release()
{
}

void map3::update()
{
	rcDoor = RectMake(rcBg4.left + 1150, rcBg4.top + 180, 370, 248);
	//rcItem = RectMakeCenter(itemX, itemY, 38, 40);

	itemX = rcBg4.left + 820;

	if (isNomal)
	{
		rcItem = RectMakeCenter(itemX, itemY, 38, 40);
	}
	if (isUnique)
	{
		rcItem = RectMakeCenter(itemX, itemY, 66, 34);
	}

	if (random % 2 == 0)		//노멀
	{
		//162,106
		rcRuin = RectMake(rcBg4.left + 760, rcBg4.top + 495, 162, 106);
		isNomal = true;
	}
	else if (random % 2 == 1)	//유니크
	{
		//368,222
		rcRuin = RectMake(rcBg4.left + 640, rcBg4.top + 370, 368, 222);
		isUnique = true;
	}

	if (INPUT->GetKey(VK_RIGHT))
	{
		if (DATA->getPlayerCamera().rcCamera.right >= WINSIZEX)
		{
			if (DATA->getPlayerCamera().rcCamera.right <= rcBg4.right)
			{
				rcBg1.left--;
				rcBg1.right--;
				rcBg2.left -= 3;
				rcBg2.right -= 3;
				rcBg3.left -= 5;
				rcBg3.right -= 5;
				rcBg4.left -= 8;
				rcBg4.right -= 8;
				tileX -= 8;
				DATA->setPixelGroundX(tileX);
				DATA->setPlayerCameraIsRight(true);
			}
			else
			{
				DATA->setPlayerCameraIsRight(false);
			}
		}
		else
		{
			DATA->setPlayerCameraIsRight(false);
		}
	}
	if (INPUT->GetKey(VK_LEFT))
	{
		if (DATA->getPlayerCamera().rcCamera.left <= 0)
		{
			if (DATA->getPlayerCamera().rcCamera.left >= rcBg4.left)
			{
				rcBg1.left++;
				rcBg1.right++;
				rcBg2.left += 3;
				rcBg2.right += 3;
				rcBg3.left += 5;
				rcBg3.right += 5;
				rcBg4.left += 8;
				rcBg4.right += 8;
				tileX += 8;
				DATA->setPixelGroundX(tileX);
				DATA->setPlayerCameraIsLeft(true);
			}
			else
			{
				DATA->setPlayerCameraIsLeft(false);
			}
		}
		else
		{
			DATA->setPlayerCameraIsLeft(false);
		}
	}

	if (DATA->getPlayer().isDash == true || DATA->getPlayer().isSoldierSkill || DATA->getPlayer().isSamuraiSkill1)// || DATA->getPlayer().isSamuraiSkill2)
	{
		if (DATA->getPlayer().isLeft == false)
		{
			if (DATA->getPlayerCamera().rcCamera.right >= WINSIZEX)
			{
				if (DATA->getPlayerCamera().rcCamera.right <= rcBg4.right)
				{
					rcBg1.left -= 2;
					rcBg1.right -= 2;
					rcBg2.left -= 6;
					rcBg2.right -= 6;
					rcBg3.left -= 10;
					rcBg3.right -= 10;
					rcBg4.left -= 16;
					rcBg4.right -= 16;
					tileX -= 16;
					DATA->setPixelGroundX(tileX);
					DATA->setPlayerCameraIsRight(true);
				}
				else
				{
					DATA->setPlayerCameraIsRight(false);
				}
			}
			else
			{
				DATA->setPlayerCameraIsRight(false);
			}
		}

		if (DATA->getPlayer().isLeft == true)
		{
			if (DATA->getPlayerCamera().rcCamera.left <= 0)
			{
				if (DATA->getPlayerCamera().rcCamera.left >= rcBg4.left)
				{
					rcBg1.left += 2;
					rcBg1.right += 2;
					rcBg2.left += 6;
					rcBg2.right += 6;
					rcBg3.left += 10;
					rcBg3.right += 10;
					rcBg4.left += 16;
					rcBg4.right += 16;
					tileX += 16;
					DATA->setPixelGroundX(tileX);
					DATA->setPlayerCameraIsLeft(true);
				}
				else
				{
					DATA->setPlayerCameraIsLeft(false);
				}
			}
			else
			{
				DATA->setPlayerCameraIsLeft(false);
			}
		}
	}

	RECT rcTemp;
	if (IntersectRect(&rcTemp, &rcDoor, &DATA->getPlayerRc()))
	{
		isDoor = true;
		if (INPUT->GetKeyDown('F'))
		{
			DATA->setStage(STAGE_4);
		}
	}
	else
	{
		isDoor = false;
	}

	if (IntersectRect(&rcTemp, &rcRuin, &DATA->getPlayerRc()) && isLook == false)
	{
		isRuin = true;
		if (INPUT->GetKeyDown('F'))
		{
			isLook = true;
		}
	}
	else
	{
		isRuin = false;
	}
	RECT rcTemp2;
	if (IntersectRect(&rcTemp2, &rcItem, &DATA->getPlayerRc()) && isLook == true)
	{
		if (DATA->getPlayerRuin() == SKUL)
		{
			isItem = true;
		}
		if (INPUT->GetKeyDown('F'))
		{
			if (isNomal)
			{
				DATA->setPlayerRuin(SOLDIER);
				isItem = false;
			}
			if (isUnique)//사무라이 이미지 추가하면 if로 나눠야함
			{
				DATA->setPlayerRuin(SAMURAI);
				isItem = false;
			}
		}
	}
	else
	{
		isItem = false;
	}

	this->animation();
	
	if (isLook && ruinIndex > 7)
	{

		if (WINSIZEY - 140 < rcItem.bottom)
		{
			itemGravity = 0.f;
			itemSpeed = 0.f;
		
			isGround = true;
		}

		if (isGround)
		{
			itemGravity += 0.1f;
		
			itemY += -sinf(PI / 2) * 1.5f + itemGravity;
		}
		else
		{
			itemGravity += 0.8f;
		
			itemX += cosf(PI / 2) * itemSpeed;
			itemY += -sinf(PI / 2) * itemSpeed +itemGravity;
		}
	}
}

void map3::render()
{
	if (DATA->getStage() == STAGE_3)
	{
		backGroundImg1->render(getMemDC(), rcBg1.left, rcBg1.top);
		backGroundImg2->render(getMemDC(), rcBg2.left, rcBg2.top);
		backGroundImg3->render(getMemDC(), rcBg3.left, rcBg3.top);
		backGroundImg4->render(getMemDC(), rcBg4.left, rcBg4.top);
		object->render(getMemDC(), DATA->getPixelGround().x, DATA->getPixelGround().y);
		DATA->getPixelGround().img->render(getMemDC(), DATA->getPixelGround().x, DATA->getPixelGround().y);

		DoorImg->frameRender(getMemDC(), rcDoor.left, rcDoor.top);
		if (isDoor)
		{
			F_buttonImg->render(getMemDC(), rcDoor.left + 140, rcDoor.bottom + 20);
			InputImg->render(getMemDC(), rcDoor.left + 170, rcDoor.bottom + 20);
		}

		if (isNomal)
		{
			nomalRuin->frameRender(getMemDC(), rcRuin.left, rcRuin.top);
		}
		if (isUnique)
		{
			uniqueRuin->frameRender(getMemDC(), rcRuin.left, rcRuin.top);
		}

		if (isRuin && ruinIndex < 8)
		{
			if (isNomal)
			{
				F_buttonImg->render(getMemDC(), rcRuin.left + 15, rcRuin.bottom + 20);
				lookImg->render(getMemDC(), rcRuin.left + 45, rcRuin.bottom + 20);
			}
			if (isUnique)
			{
				F_buttonImg->render(getMemDC(), rcRuin.left + 130, rcRuin.bottom + 20);
				lookImg->render(getMemDC(), rcRuin.left + 160, rcRuin.bottom + 20);
			}
		}

		//Rectangle(getMemDC(), rcItem);
		if (ruinIndex > 7 && DATA->getPlayerRuin() == SKUL)
		{
			if (isNomal)
			{
				soldierRuin->render(getMemDC(), rcItem.left, rcItem.top);
			}
			if (isUnique)
			{
				samuraiRuin->render(getMemDC(), rcItem.left, rcItem.top);
			}
		}

		if (isItem == true && isNomal == true)
		{
			inforSoldier->render(getMemDC(), DATA->getPlayerRc().left + 150, DATA->getPlayerRc().top - 300);
			F_buttonImg->render(getMemDC(), DATA->getPlayerRc().left + 220, DATA->getPlayerRc().top);
			putImg->render(getMemDC(), DATA->getPlayerRc().left + 250, DATA->getPlayerRc().top);
		}
		if (isItem == true && isUnique == true)//사무라이 이미지 추가하면 if로 나눠야함
		{
			inforSamurai->render(getMemDC(), DATA->getPlayerRc().left + 150, DATA->getPlayerRc().top - 300);
			F_buttonImg->render(getMemDC(), DATA->getPlayerRc().left + 220, DATA->getPlayerRc().top + 100);
			putImg->render(getMemDC(), DATA->getPlayerRc().left + 250, DATA->getPlayerRc().top + 100);
		}
	}
	char str8[100];
	char str9[100];

	sprintf(str8, "ItemX : %f", itemX);
	TextOut(getMemDC(), 10, 230, str8, strlen(str8));
	sprintf(str9, "ItemY : %f", itemY);
	TextOut(getMemDC(), 10, 250, str9, strlen(str9));
}

void map3::animation()
{
	//문 애니메이션
	doorCount++;
	DoorImg->setFrameY(0);
	if (doorCount % 5 == 0)
	{
		doorIndex++;
		if (doorIndex > 8)
		{
			doorIndex = 0;
		}
		DoorImg->setFrameX(doorIndex);
	}
	if (isLook)
	{
		if (isNomal)
		{
			ruinCount++;
			nomalRuin->setFrameY(0);
			if (ruinCount % 5 == 0)
			{
				ruinIndex++;
				if (ruinIndex > 8)
				{
					ruinIndex = 8;
				}
				nomalRuin->setFrameX(ruinIndex);
			}
		}
		if (isUnique)
		{
			ruinCount++;
			uniqueRuin->setFrameY(0);
			if (ruinCount % 5 == 0)
			{
				ruinIndex++;
				if (ruinIndex > 10)
				{
					ruinIndex = 10;
				}
				uniqueRuin->setFrameX(ruinIndex);
			}
		}
	}
}
