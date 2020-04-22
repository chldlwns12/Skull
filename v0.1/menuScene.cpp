#include "stdafx.h"
#include "menuScene.h"

HRESULT menuScene::init()
{
	menuBgImg = IMAGEMANAGER->findImage("스컬메뉴");
	menuBaseImg = IMAGEMANAGER->findImage("메뉴_기본");
	menuStartImg = IMAGEMANAGER->findImage("메뉴_스타트");
	menuMaptoolImg = IMAGEMANAGER->findImage("메뉴_맵툴");
	menuExitImg = IMAGEMANAGER->findImage("메뉴_나가기");

	rcStart = RectMake(880, 133, 378, 110);
	rcMaptool = RectMake(880, 292, 378, 110);
	rcExit = RectMake(880, 449, 378, 110);

	isStart = false;
	isMaptool = false;
	isExit = false;
	return S_OK;
}

void menuScene::release()
{
}

void menuScene::update()
{
	//메뉴 이미지 변화
	if (PtInRect(&rcStart, _ptMouse))
	{
		isStart = true;
	}
	else
	{
		isStart = false;
	}

	if (PtInRect(&rcMaptool, _ptMouse))
	{
		isMaptool = true;
	}
	else
	{
		isMaptool = false;
	}

	if (PtInRect(&rcExit, _ptMouse))
	{
		isExit = true;
	}
	else
	{
		isExit = false;
	}
	//메뉴 클릭
	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&rcStart, _ptMouse))
		{
			//인게임씬 오면됨.
		}
		if (PtInRect(&rcMaptool, _ptMouse))
		{
			//SCENEMANAGER->loadScene("맵툴");
		}
		if (PtInRect(&rcExit, _ptMouse))
		{
			PostQuitMessage(0);
		}
	}
}

void menuScene::render()
{
	menuBgImg->render(getMemDC());

	if (isStart)
	{
		menuStartImg->render(getMemDC(), 880, 0);
	}
	else if (isMaptool)
	{
		menuMaptoolImg->render(getMemDC(), 880, 0);
	}
	else if (isExit)
	{
		menuExitImg->render(getMemDC(), 880, 0);
	}
	else
	{
		menuBaseImg->render(getMemDC(), 880, 0);
	}
	//Rectangle(getMemDC(), rcStart);
	//Rectangle(getMemDC(), rcMaptool);
	//Rectangle(getMemDC(), rcExit);
}
