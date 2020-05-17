#include "stdafx.h"
#include "bossMap.h"

HRESULT bossMap::init()
{
	ptBoss = new boss;
	ptBoss->init();
	BackGroundImg1 = IMAGEMANAGER->findImage("보스배경1");
	BackGroundImg2 = IMAGEMANAGER->findImage("보스배경2");
	tileImg = IMAGEMANAGER->findImage("보스맵타일");
	LeftTree = IMAGEMANAGER->findImage("왼쪽발판");
	RightTree = IMAGEMANAGER->findImage("오른쪽발판");

	rcBg1 = RectMake(0, 0, 1875, 720);
	rcBg2 = RectMake(0, 0, 1865, 720);
	
	count = index = 0;
	count2 = 0;
	index2 = 10;

	tileX = tileY = 0.f;
	return S_OK;
}

void bossMap::release()
{
	ptBoss->release();
}

void bossMap::update()
{
	ptBoss->update();
	if (DATA->getPlayer().isDash == true || DATA->getPlayer().isSoldierSkill || DATA->getPlayer().isSamuraiSkill1)// || DATA->getPlayer().isSamuraiSkill2)
	{
		if (DATA->getPlayer().isLeft == false)
		{
			if (DATA->getPlayerCamera().rcCamera.right >= WINSIZEX)
			{
				if (DATA->getPlayerCamera().rcCamera.right <= rcBg2.right)
				{
					rcBg1.left -= 16;
					rcBg1.right -= 16;
					rcBg2.left -= 16;
					rcBg2.right -= 16;

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
				if (DATA->getPlayerCamera().rcCamera.left >= rcBg2.left)
				{
					rcBg1.left += 16;
					rcBg1.right += 16;
					rcBg2.left += 16;
					rcBg2.right += 16;

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
				if (DATA->getPlayerCamera().rcCamera.right <= rcBg2.right)
				{
					rcBg1.left -= 4;
					rcBg1.right -= 4;
					rcBg2.left -= 4;
					rcBg2.right -= 4;

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
				if (DATA->getPlayerCamera().rcCamera.left >= rcBg2.left)
				{
					rcBg1.left += 4;
					rcBg1.right += 4;
					rcBg2.left += 4;
					rcBg2.right += 4;

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
			if (DATA->getPlayerCamera().rcCamera.right <= rcBg2.right)
			{
				rcBg1.left -= 8;
				rcBg1.right -= 8;
				rcBg2.left -= 8;
				rcBg2.right -= 8;
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
			if (DATA->getPlayerCamera().rcCamera.left >= rcBg2.left)
			{
				rcBg1.left+=8;
				rcBg1.right+=8;
				rcBg2.left += 8;
				rcBg2.right += 8;
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

	count++;
	LeftTree->setFrameY(0);
	if (count % 5 == 0)
	{
		index++;
		if (index > 10)
		{
			index = 10;
		}
		LeftTree->setFrameX(index);
	}

	count2++;
	RightTree->setFrameY(0);
	if (count2 % 5 == 0)
	{
		index2--;
		if (index2 < 0)
		{
			index2 = 0;
		}
		RightTree->setFrameX(index2);
	}
}

void bossMap::render()
{
	if (DATA->getStage() == BOSS_STAGE)
	{
		BackGroundImg2->render(getMemDC(), rcBg2.left, rcBg2.top);
		BackGroundImg1->render(getMemDC(), rcBg1.left, rcBg1.top);
		LeftTree->frameRender(getMemDC(), DATA->getPixelGround().x + 10, DATA->getPixelGround().y + 410);
		RightTree->frameRender(getMemDC(), DATA->getPixelGround().x + 1010, DATA->getPixelGround().y + 410);
		ptBoss->render();
		tileImg->render(getMemDC(), DATA->getPixelGround().x, DATA->getPixelGround().y);
		if (INPUT->GetToggleKey('P'))
		{
			DATA->getPixelGround().img->render(getMemDC(), DATA->getPixelGround().x, DATA->getPixelGround().y);
		}

	}
}
