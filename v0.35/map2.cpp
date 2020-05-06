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
	object = IMAGEMANAGER->findImage("맵2_오브젝트");
	front = IMAGEMANAGER->findImage("맵2_프론트");

	rcBg1 = RectMake(0, 0, 2600, 810);
	rcBg2 = RectMake(0, 0, 2600, 810);
	rcBg3 = RectMake(0, 0, 2600, 810);
	rcBg4 = RectMake(0, 0, 2600, 810);

	tileX = tileY = 0;

	return S_OK;
}

void map2::release()
{
}

void map2::update()
{
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
		DATA->getPixelGround().img->render(getMemDC(), DATA->getPixelGround().x, DATA->getPixelGround().y);
		front->render(getMemDC(), DATA->getPixelGround().x, DATA->getPixelGround().y);
	}
}
