#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init()
{
	//로딩클래스 초기화
	_loading = new loading;
	_loading->init();

	//로딩 이미지 및 사운드 초기화
	this->loadingImage();
	this->loadingSound();

	//로딩 해골 이미지
	IMAGEMANAGER->addFrameImage("로딩해골", "Images/일반해골달리기.bmp", 320, 64, 8, 2);

	_count = _index = 0;
	return S_OK;
}

void loadingScene::release()
{
	//로딩클래스 해제
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	//로딩클래스 업데이트
	_loading->update();

	//로딩완료후 화면 변경
	if (_loading->loadingDone())
	{
		SCENEMANAGER->loadScene("메뉴화면");
	}
	_count++;
	IMAGEMANAGER->findImage("로딩해골")->setFrameY(0);

	//애니메이션
	if (_count % 4 == 0)
	{
		_index++;
		if (_index > 8)
		{
			_index = 0;
		}
		IMAGEMANAGER->findImage("로딩해골")->setFrameX(_index);
	}

}

void loadingScene::render()
{
	//로딩클래스 렌더
	_loading->render();

	for (int i = 0; i < _loading->getLoadItem().size(); i++)
	{
		if (_loading->getLoadItem()[i]->getLoadKind() == LOAD_KIND_IMAGE_0) continue;
		sprintf(_LoadFileName, _loading->getLoadItem()[i]->getImageResource().fileName);
	}

	SetBkMode(getMemDC(), TRANSPARENT);
	TextOut(getMemDC(), 370, 602, _LoadFileName, strlen(_LoadFileName));

	IMAGEMANAGER->findImage("로딩해골")->frameRender(getMemDC(), _loading->getProgressBar()->getWidth() + 300, 570);
}


//로딩이미지 함수(이곳에 이미지를 전부 넣어라)
void loadingScene::loadingImage()
{
	//_loading->loadImage();
	//_loading->loadFrameImage();

	_loading->loadImage("백그라운드1", "Images/Background1.bmp", 961, 810);
	_loading->loadImage("백그라운드2", "Images/Background2.bmp", 961, 801);
	_loading->loadImage("백그라운드3", "Images/Background3.bmp", 970, 801);
	_loading->loadImage("백그라운드4", "Images/Background4.bmp", 970, 810);
	_loading->loadImage("맵타일", "Images/맵타일.bmp", 512, 340);
	_loading->loadImage("스컬메뉴", "Images/스컬메뉴.bmp", 1280, 720);
	_loading->loadImage("메뉴_기본", "Images/메뉴_기본.bmp", 378, 560);
	_loading->loadImage("메뉴_스타트", "Images/메뉴_스타트.bmp", 378, 560);
	_loading->loadImage("메뉴_맵툴", "Images/메뉴_맵툴.bmp", 378, 560);
	_loading->loadImage("메뉴_나가기", "Images/메뉴_나가기.bmp", 378, 560);

	_loading->loadFrameImage("달리기", "Images/일반해골달리기.bmp", 320, 64, 8, 2);
	_loading->loadFrameImage("점프", "Images/점프.bmp", 252, 72, 7, 2);
	_loading->loadFrameImage("공격", "Images/공격.bmp", 531, 106, 9, 2);

	//로딩이 너무 빠르게 진행되서 천천히 돌아가도록 테스트용으로 만들기
	//for (int i = 0; i < 180; i++)
	//{
	//	_loading->loadImage("테스트", WINSIZEX, WINSIZEY);
	//}
}

//로딩사운드 함수(이곳에 사운드를 전부 넣어라)
void loadingScene::loadingSound()
{
}
