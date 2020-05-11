#include "stdafx.h"
#include "loading.h"
//=============================================================
//	## loadItem ## (�ε������)
//=============================================================
HRESULT loadItem::init(string strKey, int width, int height)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_0;
	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = strKey;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::init(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_1;

	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string strKey, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_2;

	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_FRAMEIMAGE_1;

	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

//=============================================================
//	## loading ## (�ε�Ŭ����)
//=============================================================

HRESULT loading::init()
{
	//�ε�ȭ�� ��׶��� �̹��� �ʱ�ȭ
	_background = IMAGEMANAGER->addImage("bgLoadingScene", "Images/���÷ε�.bmp", WINSIZEX, WINSIZEY);

	//�ε��� �̹��� �ʱ�ȭ
	IMAGEMANAGER->addImage("loadingBarFront", "Images/loadingBarFront.bmp", 600, 31);
	IMAGEMANAGER->addImage("loadingBarBack_1", "Images/loadingBarBack_1.bmp", 13, 31);
	IMAGEMANAGER->addImage("loadingBarBack_2", "Images/loadingBarBack_2.bmp", 600, 31);
	IMAGEMANAGER->addImage("loadingBarBack_3", "Images/loadingBarBack_3.bmp", 13, 31);

	//�ε� ���� �̹��� �ʱ�ȭ
	_loadingNumber[0] = IMAGEMANAGER->addImage("����0", "Images/����_00.bmp", 15, 17);
	_loadingNumber[1] = IMAGEMANAGER->addImage("����1", "Images/����_01.bmp", 10, 17);
	_loadingNumber[2] = IMAGEMANAGER->addImage("����2", "Images/����_02.bmp", 15, 17);
	_loadingNumber[3] = IMAGEMANAGER->addImage("����3", "Images/����_03.bmp", 15, 17);
	_loadingNumber[4] = IMAGEMANAGER->addImage("����4", "Images/����_04.bmp", 15, 17);
	_loadingNumber[5] = IMAGEMANAGER->addImage("����5", "Images/����_05.bmp", 15, 17);
	_loadingNumber[6] = IMAGEMANAGER->addImage("����6", "Images/����_06.bmp", 14, 17);
	_loadingNumber[7] = IMAGEMANAGER->addImage("����7", "Images/����_07.bmp", 14, 17);
	_loadingNumber[8] = IMAGEMANAGER->addImage("����8", "Images/����_08.bmp", 14, 17);
	_loadingNumber[9] = IMAGEMANAGER->addImage("����9", "Images/����_09.bmp", 15, 17);
	IMAGEMANAGER->addImage("�ۼ�Ʈ", "Images/�ۼ�Ʈ.bmp", 16, 13);
	//�ε��� Ŭ���� �ʱ�ȭ
	_loadingBar = new progressBar;
	_loadingBar->init("loadingBarFront", "loadingBarBack_2");
	//_loadingBar->setGauge(0, 0);
	//�ε��� ��ġ
	//_loadingBar->setPos(294, 600);
	_loadingBar->setPos(307, 600);

	//���� ������
	_currentGauge = 0;
	_Gauge = 0;
	return S_OK;
}

void loading::release()
{
	_loadingBar->release();
	SAFE_DELETE(_loadingBar);
}

void loading::update()
{
	_loadingBar->update();
	setGauge(_vLoadItem.size(), _currentGauge);
}

void loading::render()
{
	//��׶��� ����
	_background->render(getMemDC());
	//�ε��� ����
	IMAGEMANAGER->findImage("loadingBarBack_1")->render(getMemDC(), 294, 600);
	IMAGEMANAGER->findImage("loadingBarBack_3")->render(getMemDC(), 907, 600);
	_loadingBar->render();
	IMAGEMANAGER->findImage("�ۼ�Ʈ")->render(getMemDC(), 972, 605);
	LoadingNumber();
}

void loading::loadImage(string strKey, int width, int height)
{
	loadItem* item = new loadItem;
	item->init(strKey, width, height);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string strKey, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, x, y, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, width, height, frameX, frameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, x, y, width, height, frameX, frameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

bool loading::loadingDone()
{
	//�ε��Ϸ��
	if (_currentGauge >= _vLoadItem.size())
	{
		return true;
	}

	loadItem* item = _vLoadItem[_currentGauge];
	switch (item->getLoadKind())
	{
	case LOAD_KIND_IMAGE_0:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.width, img.height);
	}
	break;

	case LOAD_KIND_IMAGE_1:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height, img.isTrans, img.transColor);
	}
	break;

	case LOAD_KIND_IMAGE_2:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.isTrans, img.transColor);
	}
	break;

	case LOAD_KIND_FRAMEIMAGE_0:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.isTrans, img.transColor);
	}
	break;

	case LOAD_KIND_FRAMEIMAGE_1:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.frameX, img.frameY, img.isTrans, img.transColor);
	}
	break;

	//�� ���� ���� ���� ���� �غ���!!
	case LOAD_KIND_SOUND:
	{
	}
	break;
	}

	//���� ������ ����
	_currentGauge++;

	//�ε��� �̹��� ����
	_loadingBar->setGauge(_vLoadItem.size(), _currentGauge);


	return false;
}

int loading::setGauge(float maxLoad, float currentLoad)
{
	_Gauge = (currentLoad / maxLoad) * 100.f;

	return _Gauge;
}

void loading::LoadingNumber()
{
	for (int i = 0; i < 10; i++)
	{
		if (_Gauge == i && _Gauge < 10)
		{
			_loadingNumber[i]->render(getMemDC(), 955, 602);
		}
		if (_Gauge >= 10 && _Gauge < 100)
		{
			int temp1 = _Gauge / 10;	//10���ڸ�
			int temp2 = _Gauge % 10;	//1���ڸ�

			_loadingNumber[temp1]->render(getMemDC(), 940, 602);
			_loadingNumber[temp2]->render(getMemDC(), 955, 602);
		}
	}
}
