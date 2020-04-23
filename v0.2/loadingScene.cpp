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

	_loading->loadImage("백그라운드1", "Images/Background1_수정.bmp", 1940, 810);
	_loading->loadImage("백그라운드1_미니", "Images/Background1_미니.bmp", 194, 81);
	_loading->loadImage("백그라운드2", "Images/Background2_수정.bmp", 1940, 810);
	_loading->loadImage("백그라운드2_미니", "Images/Background2_미니.bmp", 194, 81);
	_loading->loadImage("백그라운드3", "Images/Background3_수정.bmp", 1940, 810);
	_loading->loadImage("백그라운드3_미니", "Images/Background3_미니.bmp", 194, 81);
	_loading->loadImage("백그라운드4", "Images/Background4_수정.bmp", 1940, 810);
	_loading->loadImage("백그라운드4_미니", "Images/Background4_미니.bmp", 194, 81);

	_loading->loadImage("스컬메뉴", "Images/스컬메뉴.bmp", 1280, 720);
	_loading->loadImage("메뉴_기본", "Images/메뉴_기본.bmp", 378, 560);
	_loading->loadImage("메뉴_스타트", "Images/메뉴_스타트.bmp", 378, 560);
	_loading->loadImage("메뉴_맵툴", "Images/메뉴_맵툴.bmp", 378, 560);
	_loading->loadImage("메뉴_나가기", "Images/메뉴_나가기.bmp", 378, 560);
	_loading->loadImage("버튼_드래그", "Images/버튼_드래그.bmp", 173, 57);
	_loading->loadImage("버튼_드래그온", "Images/버튼_드래그온.bmp", 173, 57);
	_loading->loadImage("버튼_로드", "Images/버튼_로드.bmp", 173, 57);
	_loading->loadImage("버튼_로드온", "Images/버튼_로드온.bmp", 173, 57);
	_loading->loadImage("버튼_리셋", "Images/버튼_리셋.bmp", 173, 57);
	_loading->loadImage("버튼_리셋온", "Images/버튼_리셋온.bmp", 173, 57);
	_loading->loadImage("버튼_세이브", "Images/버튼_세이브.bmp", 173, 57);
	_loading->loadImage("버튼_세이브온", "Images/버튼_세이브온.bmp", 173, 57);
	_loading->loadImage("버튼_엑시트", "Images/버튼_엑시트.bmp", 173, 57);
	_loading->loadImage("버튼_엑시트온", "Images/버튼_엑시트온.bmp", 173, 57);
	_loading->loadImage("버튼_오브젝트", "Images/버튼_오브젝트.bmp", 173, 57);
	_loading->loadImage("버튼_오브젝트온", "Images/버튼_오브젝트온.bmp", 173, 57);
	_loading->loadImage("버튼_이레이저", "Images/버튼_이레이저.bmp", 173, 57);
	_loading->loadImage("버튼_이레이저온", "Images/버튼_이레이저온.bmp", 173, 57);
	_loading->loadImage("버튼_지형", "Images/버튼_지형.bmp", 173, 57);
	_loading->loadImage("버튼_지형온", "Images/버튼_지형온.bmp", 173, 57);
	_loading->loadImage("툴박스", "Images/툴박스.bmp", 1000, 450);
	//인게임 메뉴
	_loading->loadImage("인게임메뉴화면", "Images/인게임메뉴화면.bmp", 372, 696);
	_loading->loadImage("인게임_계속버튼", "Images/인게임_계속버튼.bmp", 173, 57);
	_loading->loadImage("인게임_계속버튼On", "Images/인게임_계속버튼On.bmp", 173, 57);
	_loading->loadImage("인게임_옵션버튼", "Images/인게임_옵션버튼.bmp", 173, 57);
	_loading->loadImage("인게임_옵션버튼On", "Images/인게임_옵션버튼On.bmp", 173, 57);
	_loading->loadImage("인게임_나가기버튼", "Images/인게임_나가기버튼.bmp", 173, 57);
	_loading->loadImage("인게임_나가기버튼On", "Images/인게임_나가기버튼On.bmp", 173, 57);


	_loading->loadFrameImage("지형타일", "Images/지형타일.bmp", 510, 340, 15, 10);
	_loading->loadFrameImage("지형타일_미니", "Images/지형타일_미니.bmp", 51, 34, 15, 10);
	_loading->loadFrameImage("달리기", "Images/일반해골달리기.bmp", 320, 64, 8, 2);
	_loading->loadFrameImage("점프", "Images/점프.bmp", 252, 72, 7, 2);
	_loading->loadFrameImage("공격", "Images/공격.bmp", 531, 106, 9, 2);

	//로딩이 너무 빠르게 진행되서 천천히 돌아가도록 테스트용으로 만들기
	//for (int i = 0; i < 280; i++)
	//{
	//	_loading->loadImage("테스트", WINSIZEX, WINSIZEY);
	//}
}

//로딩사운드 함수(이곳에 사운드를 전부 넣어라)
void loadingScene::loadingSound()
{
}
