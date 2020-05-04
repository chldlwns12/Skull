#include "stdafx.h"
#include "map1.h"

HRESULT map1::init()
{
	DATA->setPixelGroundImg(IMAGEMANAGER->findImage("¸Ê1_¹Ù´Ú"));
	DATA->setPixelGroundX(0);
	DATA->setPixelGroundY(0);
	

	bgImg = IMAGEMANAGER->findImage("¸Ê1_¹è°æ1");
	cloudImg1 = IMAGEMANAGER->findImage("¸Ê1_±¸¸§1");
	cloudImg2 = IMAGEMANAGER->findImage("¸Ê1_±¸¸§2");
	cloudImg3 = IMAGEMANAGER->findImage("¸Ê1_±¸¸§3");
	cloudImg4 = IMAGEMANAGER->findImage("¸Ê1_±¸¸§4");
	cloudImg5 = IMAGEMANAGER->findImage("¸Ê1_±¸¸§5");

	skyImg1 = IMAGEMANAGER->findImage("¸Ê1_ÇÏ´Ã1");
	skyImg2 = IMAGEMANAGER->findImage("¸Ê1_ÇÏ´Ã2");
	chanImg1 = IMAGEMANAGER->findImage("¸Ê1_¼§µé¸®¿¡1");
	chanImg2 = IMAGEMANAGER->findImage("¸Ê1_¼§µé¸®¿¡2");
	chanImg3 = IMAGEMANAGER->findImage("¸Ê1_¼§µé¸®¿¡3");
	objectImg = IMAGEMANAGER->findImage("¸Ê1_¿ÀºêÁ§Æ®");
	castle = IMAGEMANAGER->findImage("¸Ê1_¼º");
	//castleWall1 = IMAGEMANAGER->findImage("¸Ê1_¼ºº®1");
	castleWall2 = IMAGEMANAGER->findImage("¸Ê1_¼ºº®2");
	//castleWall3 = IMAGEMANAGER->findImage("¸Ê1_¼ºº®3");
	mountain1 = IMAGEMANAGER->findImage("¸Ê1_»ê1");
	mountain2 = IMAGEMANAGER->findImage("¸Ê1_»ê2");

	rcBackGround1 = RectMake(0, 0, 1860, 720);
	rcBackGround2 = RectMake(0, 0, 1940, 720);
	rcBackGround3 = RectMake(0, 0, 3284, 720);
	rcBackGround4 = RectMake(0, 0, 1280, 4961);

	tileX = tileY = 0.f;

	isMove = false;
	isChange = false;
	loopX = 0;
	return S_OK;
}

void map1::release()
{
}

void map1::update()
{
	loopX--;

	if (DATA->getStage() == START && isChange == true)
	{
		DATA->setPixelGroundImg(IMAGEMANAGER->findImage("¸Ê1_¹Ù´Ú"));
		DATA->setPixelGroundX(0);
		DATA->setPixelGroundY(0);
		//DATA->setPixelGroundRc(RectMake(DATA->getPixelGround().x, DATA->getPixelGround().y, 1280, 2519));
		isChange = false;
	}

	if (DATA->getStage() == STAGE_1 && isChange == false)
	{
		DATA->setPixelGroundImg(IMAGEMANAGER->findImage("¸Ê1_¼ºº®3"));
		DATA->setPixelGroundX(0);
		DATA->setPixelGroundY(590);
		DATA->setPixelGroundRc(RectMake(DATA->getPixelGround().x, DATA->getPixelGround().y, 311, 1661));
		isChange = true;
	}

	if (DATA->getStage() == START)
	{
		if (INPUT->GetKey(VK_RIGHT))
		{
			if (DATA->getPlayerCamera().rcCamera.right >= WINSIZEX)
			{
				if (DATA->getPlayerCamera().rcCamera.right < rcBackGround3.right)
				{
					rcBackGround1.left--;
					rcBackGround1.right--;
					rcBackGround2.left -= 2;
					rcBackGround2.right -= 2;
					rcBackGround3.left -= 8;
					rcBackGround3.right -= 8;
					tileX -= 8.f;
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
				if (DATA->getPlayerCamera().rcCamera.left > rcBackGround3.left)
				{
					rcBackGround1.left++;
					rcBackGround1.right++;
					rcBackGround2.left += 2;
					rcBackGround2.right += 2;
					rcBackGround3.left += 8;
					rcBackGround3.right += 8;
					tileX += 8.f;
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

	if (DATA->getStage() == STAGE_1)
	{
		if (DATA->getPlayerCamera().rcCamera.bottom >= WINSIZEY)
		{
			if (DATA->getPlayerCamera().rcCamera.bottom < rcBackGround4.bottom)
			{
				if (DATA->getPixelGroundRc().right < DATA->getPlayerRc().left)
				{
					rcBackGround4.top -= 24;
					rcBackGround4.bottom -= 24;

					tileY -= 24;
					DATA->setPixelGroundY(tileY);

					DATA->setPlayerCameraIsBottom(true);
				}	
			}
			else
			{
				DATA->setPlayerCameraIsBottom(false);
			}
		}
		else
		{
			DATA->setPlayerCameraIsBottom(false);
		}
		
		if (DATA->getPlayerCamera().rcCamera.top <= 0)
		{
			if (DATA->getPlayerCamera().rcCamera.top > rcBackGround4.top)
			{
				//tileY += 8;
				//DATA->setRcBackGroundBottom(tileY);
				//DATA->setRcBackGroundTop(tileY);

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

void map1::render()
{
	if (DATA->getStage() == START)
	{
		skyImg2->render(getMemDC());
		cloudImg1->render(getMemDC(), rcBackGround1.left, rcBackGround1.top);
		bgImg->render(getMemDC(), rcBackGround2.left, rcBackGround2.top);
		DATA->getPixelGround().img->render(getMemDC(), DATA->getPixelGround().x, DATA->getPixelGround().y);
		objectImg->render(getMemDC(), rcBackGround3.left, rcBackGround3.top);
	}
	else if (DATA->getStage() == STAGE_1)
	{
		RECT rc = RectMake(rcBackGround4.left + 180, rcBackGround4.top + 560, 1120, 1616);
		cloudImg5->loopRender(getMemDC(), &rc, loopX, 0);
		skyImg1->render(getMemDC(),rcBackGround4.left, rcBackGround4.top);
		castleWall2->render(getMemDC(), DATA->getPixelGround().x, DATA->getPixelGround().y - 700);
		DATA->getPixelGround().img->render(getMemDC(), DATA->getPixelGround().x, DATA->getPixelGround().y);
		//Rectangle(getMemDC(), DATA->getPixelGround().rc);
	}

}
