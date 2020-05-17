#include "stdafx.h"
#include "loading.h"
//=============================================================
//	## loadItem ## (로드아이템)
//=============================================================
HRESULT loadItem::init(string strKey, int width, int height)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_0;
	//이미지 구조체 초기화
	_imageResource.keyName = strKey;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::init(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_1;

	//이미지 구조체 초기화
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
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_2;

	//이미지 구조체 초기화
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
	//로딩종류 초기화
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	//이미지 구조체 초기화
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
	//로딩종류 초기화
	_kind = LOAD_KIND_FRAMEIMAGE_1;

	//이미지 구조체 초기화
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
//	## loading ## (로딩클래스)
//=============================================================

HRESULT loading::init()
{
	//로딩화면 백그라운드 이미지 초기화
	_background = IMAGEMANAGER->addImage("bgLoadingScene", "Images/스컬로딩.bmp", WINSIZEX, WINSIZEY);

	//로딩바 이미지 초기화
	IMAGEMANAGER->addImage("loadingBarFront", "Images/loadingBarFront.bmp", 600, 31);
	IMAGEMANAGER->addImage("loadingBarBack_1", "Images/loadingBarBack_1.bmp", 13, 31);
	IMAGEMANAGER->addImage("loadingBarBack_2", "Images/loadingBarBack_2.bmp", 600, 31);
	IMAGEMANAGER->addImage("loadingBarBack_3", "Images/loadingBarBack_3.bmp", 13, 31);

	//로딩 숫자 이미지 초기화
	_loadingNumber[0] = IMAGEMANAGER->addImage("숫자0", "Images/숫자_00.bmp", 15, 17);
	_loadingNumber[1] = IMAGEMANAGER->addImage("숫자1", "Images/숫자_01.bmp", 10, 17);
	_loadingNumber[2] = IMAGEMANAGER->addImage("숫자2", "Images/숫자_02.bmp", 15, 17);
	_loadingNumber[3] = IMAGEMANAGER->addImage("숫자3", "Images/숫자_03.bmp", 15, 17);
	_loadingNumber[4] = IMAGEMANAGER->addImage("숫자4", "Images/숫자_04.bmp", 15, 17);
	_loadingNumber[5] = IMAGEMANAGER->addImage("숫자5", "Images/숫자_05.bmp", 15, 17);
	_loadingNumber[6] = IMAGEMANAGER->addImage("숫자6", "Images/숫자_06.bmp", 14, 17);
	_loadingNumber[7] = IMAGEMANAGER->addImage("숫자7", "Images/숫자_07.bmp", 14, 17);
	_loadingNumber[8] = IMAGEMANAGER->addImage("숫자8", "Images/숫자_08.bmp", 14, 17);
	_loadingNumber[9] = IMAGEMANAGER->addImage("숫자9", "Images/숫자_09.bmp", 15, 17);
	IMAGEMANAGER->addImage("퍼센트", "Images/퍼센트.bmp", 16, 13);
	//로딩바 클래스 초기화
	_loadingBar = new progressBar;
	_loadingBar->init("loadingBarFront", "loadingBarBack_2");
	//_loadingBar->setGauge(0, 0);
	//로딩바 위치
	//_loadingBar->setPos(294, 600);
	_loadingBar->setPos(307, 600);

	//현재 게이지
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
	//백그라운드 렌더
	_background->render(getMemDC());
	//로딩바 렌더
	IMAGEMANAGER->findImage("loadingBarBack_1")->render(getMemDC(), 294, 600);
	IMAGEMANAGER->findImage("loadingBarBack_3")->render(getMemDC(), 907, 600);
	_loadingBar->render();
	IMAGEMANAGER->findImage("퍼센트")->render(getMemDC(), 972, 605);
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
	//로딩완료됨
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

	//곧 사운드 배우고 난후 직접 해보자!!
	case LOAD_KIND_SOUND:
	{
	}
	break;
	}

	//현재 게이지 증가
	_currentGauge++;

	//로딩바 이미지 변경
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
			int temp1 = _Gauge / 10;	//10의자리
			int temp2 = _Gauge % 10;	//1의자리

			_loadingNumber[temp1]->render(getMemDC(), 940, 602);
			_loadingNumber[temp2]->render(getMemDC(), 955, 602);
		}
	}
}
