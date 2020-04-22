#include "stdafx.h"
#include "menuScene.h"

HRESULT menuScene::init()
{
	menuBgImg = IMAGEMANAGER->findImage("���ø޴�");
	menuBaseImg = IMAGEMANAGER->findImage("�޴�_�⺻");
	menuStartImg = IMAGEMANAGER->findImage("�޴�_��ŸƮ");
	menuMaptoolImg = IMAGEMANAGER->findImage("�޴�_����");
	menuExitImg = IMAGEMANAGER->findImage("�޴�_������");

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
	//�޴� �̹��� ��ȭ
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
	//�޴� Ŭ��
	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&rcStart, _ptMouse))
		{
			//�ΰ��Ӿ� �����.
		}
		if (PtInRect(&rcMaptool, _ptMouse))
		{
			//SCENEMANAGER->loadScene("����");
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
