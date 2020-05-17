#include "stdafx.h"
#include "map2.h"

HRESULT map2::init()
{
	//DATA->setPixelGroundImg(IMAGEMANAGER->findImage("맵2_바닥"));
	//DATA->setPixelGroundX(0);
	//DATA->setPixelGroundY(0);
	backGroundImg1 = IMAGEMANAGER->findImage("백그라운드1");
	backGroundImg2 = IMAGEMANAGER->findImage("백그라운드2");
	backGroundImg3 = IMAGEMANAGER->findImage("백그라운드3");
	backGroundImg4 = IMAGEMANAGER->findImage("백그라운드4");
	tile = IMAGEMANAGER->findImage("맵2_show");
	object = IMAGEMANAGER->findImage("맵2_오브젝트");
	front = IMAGEMANAGER->findImage("맵2_프론트");
	DoorImg = IMAGEMANAGER->findImage("시작문");
	F_buttonImg = IMAGEMANAGER->findImage("F상호작용");
	InputImg = IMAGEMANAGER->findImage("들어가기");

	rcBg1 = RectMake(0, 0, 2600, 810);
	rcBg2 = RectMake(0, 0, 2600, 810);
	rcBg3 = RectMake(0, 0, 2600, 810);
	rcBg4 = RectMake(0, 0, 2600, 810);


	tileX = tileY = 0;
	isDoor = false;
	doorCount = doorIndex = 0;
	return S_OK;
}

void map2::release()
{
}

void map2::update()
{
	rcColl1 = RectMake(rcBg4.left, rcBg4.top + 310, 745, 190);
	rcDoor = RectMake(rcBg4.left + 2200, rcBg4.top + 100, 370, 248);

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
		else if (DATA->getPlayer().isLeft == true)
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

	//체인지
	if (DATA->getPlayer().isChange && DATA->getPlayerRuin() == SKUL)
	{
		if (DATA->getPlayer().isLeft == false)
		{
			if (DATA->getPlayerCamera().rcCamera.right >= WINSIZEX)
			{
				if (DATA->getPlayerCamera().rcCamera.right <= rcBg4.right)
				{
					rcBg1.left -= 1;
					rcBg1.right -= 1;
					rcBg2.left -= 2;
					rcBg2.right -= 2;
					rcBg3.left -= 3;
					rcBg3.right -= 3;
					rcBg4.left -= 4;
					rcBg4.right -= 4;

					tileX -= 4;
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
					rcBg1.left += 1;
					rcBg1.right += 1;
					rcBg2.left += 2;
					rcBg2.right += 2;
					rcBg3.left += 3;
					rcBg3.right += 3;
					rcBg4.left += 4;
					rcBg4.right += 4;

					tileX += 4;
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

	RECT rcTemp;
	if (IntersectRect(&rcTemp, &rcDoor, &DATA->getPlayerRc()))
	{
		isDoor = true;
		if (INPUT->GetKeyDown('F'))
		{
			DATA->setStage(BOSS_STAGE);
		}
	}
	else
	{
		isDoor = false;
	}
}

void map2::render()
{
	if (DATA->getStage() == STAGE_2)
	{
		backGroundImg1->render(getMemDC(), rcBg1.left, rcBg1.top);
		backGroundImg2->render(getMemDC(), rcBg2.left, rcBg2.top);
		backGroundImg3->render(getMemDC(), rcBg3.left, rcBg3.top);
		backGroundImg4->render(getMemDC(), rcBg4.left, rcBg4.top);
		object->render(getMemDC(), DATA->getPixelGround().x, DATA->getPixelGround().y);
		tile->render(getMemDC(), DATA->getPixelGround().x, DATA->getPixelGround().y);
		if (INPUT->GetToggleKey('P'))
		{
			DATA->getPixelGround().img->render(getMemDC(), DATA->getPixelGround().x, DATA->getPixelGround().y);
		}
		front->render(getMemDC(), DATA->getPixelGround().x, DATA->getPixelGround().y);
		DoorImg->frameRender(getMemDC(), rcDoor.left, rcDoor.top);
		if (isDoor)
		{
			F_buttonImg->render(getMemDC(), rcDoor.left + 140, rcDoor.bottom + 20);
			InputImg->render(getMemDC(), rcDoor.left + 170, rcDoor.bottom + 20);
		}
		if (INPUT->GetToggleKey('T'))
		{
			Rectangle(getMemDC(), rcColl1);
			Rectangle(getMemDC(), rcDoor);
		}
	}
}
