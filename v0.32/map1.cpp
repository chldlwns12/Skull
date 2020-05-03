#include "stdafx.h"
#include "map1.h"

HRESULT map1::init()
{
	DATA->setPixelGroundImg(IMAGEMANAGER->findImage("��1_�ٴ�"));
	DATA->setPixelGroundX(0);
	DATA->setPixelGroundY(0);
	bgImg = IMAGEMANAGER->findImage("��1_���1");
	cloudImg1 = IMAGEMANAGER->findImage("��1_����1");
	cloudImg2 = IMAGEMANAGER->findImage("��1_����2");
	cloudImg3 = IMAGEMANAGER->findImage("��1_����3");
	skyImg1 = IMAGEMANAGER->findImage("��1_�ϴ�1");
	skyImg2 = IMAGEMANAGER->findImage("��1_�ϴ�2");
	chanImg1 = IMAGEMANAGER->findImage("��1_���鸮��1");
	chanImg2 = IMAGEMANAGER->findImage("��1_���鸮��2");
	chanImg3 = IMAGEMANAGER->findImage("��1_���鸮��3");
	objectImg = IMAGEMANAGER->findImage("��1_������Ʈ");

	rcBackGround1 = RectMake(0, 0, 1860, 720);
	rcBackGround2 = RectMake(0, 0, 1940, 720);
	rcBackGround3 = RectMake(0, 0, 3284, 720);
	return S_OK;
}

void map1::release()
{
}

void map1::update()
{

}

void map1::render()
{
	skyImg2->render(getMemDC());
	cloudImg1->render(getMemDC(), rcBackGround1.left, rcBackGround1.top);
	bgImg->render(getMemDC(), rcBackGround2.left, rcBackGround2.top);
	DATA->getPixelGround().img->render(getMemDC(), DATA->getPixelGround().x, DATA->getPixelGround().y);
	objectImg->render(getMemDC(), rcBackGround3.left, rcBackGround3.top);
}
