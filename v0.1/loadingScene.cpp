#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init()
{
	//�ε�Ŭ���� �ʱ�ȭ
	_loading = new loading;
	_loading->init();

	//�ε� �̹��� �� ���� �ʱ�ȭ
	this->loadingImage();
	this->loadingSound();

	//�ε� �ذ� �̹���
	IMAGEMANAGER->addFrameImage("�ε��ذ�", "Images/�Ϲ��ذ�޸���.bmp", 320, 64, 8, 2);

	_count = _index = 0;
	return S_OK;
}

void loadingScene::release()
{
	//�ε�Ŭ���� ����
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	//�ε�Ŭ���� ������Ʈ
	_loading->update();

	//�ε��Ϸ��� ȭ�� ����
	if (_loading->loadingDone())
	{
		SCENEMANAGER->loadScene("�޴�ȭ��");
	}
	_count++;
	IMAGEMANAGER->findImage("�ε��ذ�")->setFrameY(0);

	//�ִϸ��̼�
	if (_count % 4 == 0)
	{
		_index++;
		if (_index > 8)
		{
			_index = 0;
		}
		IMAGEMANAGER->findImage("�ε��ذ�")->setFrameX(_index);
	}

}

void loadingScene::render()
{
	//�ε�Ŭ���� ����
	_loading->render();

	for (int i = 0; i < _loading->getLoadItem().size(); i++)
	{
		if (_loading->getLoadItem()[i]->getLoadKind() == LOAD_KIND_IMAGE_0) continue;
		sprintf(_LoadFileName, _loading->getLoadItem()[i]->getImageResource().fileName);
	}

	SetBkMode(getMemDC(), TRANSPARENT);
	TextOut(getMemDC(), 370, 602, _LoadFileName, strlen(_LoadFileName));

	IMAGEMANAGER->findImage("�ε��ذ�")->frameRender(getMemDC(), _loading->getProgressBar()->getWidth() + 300, 570);
}


//�ε��̹��� �Լ�(�̰��� �̹����� ���� �־��)
void loadingScene::loadingImage()
{
	//_loading->loadImage();
	//_loading->loadFrameImage();

	_loading->loadImage("��׶���1", "Images/Background1.bmp", 961, 810);
	_loading->loadImage("��׶���2", "Images/Background2.bmp", 961, 801);
	_loading->loadImage("��׶���3", "Images/Background3.bmp", 970, 801);
	_loading->loadImage("��׶���4", "Images/Background4.bmp", 970, 810);
	_loading->loadImage("��Ÿ��", "Images/��Ÿ��.bmp", 512, 340);
	_loading->loadImage("���ø޴�", "Images/���ø޴�.bmp", 1280, 720);
	_loading->loadImage("�޴�_�⺻", "Images/�޴�_�⺻.bmp", 378, 560);
	_loading->loadImage("�޴�_��ŸƮ", "Images/�޴�_��ŸƮ.bmp", 378, 560);
	_loading->loadImage("�޴�_����", "Images/�޴�_����.bmp", 378, 560);
	_loading->loadImage("�޴�_������", "Images/�޴�_������.bmp", 378, 560);

	_loading->loadFrameImage("�޸���", "Images/�Ϲ��ذ�޸���.bmp", 320, 64, 8, 2);
	_loading->loadFrameImage("����", "Images/����.bmp", 252, 72, 7, 2);
	_loading->loadFrameImage("����", "Images/����.bmp", 531, 106, 9, 2);

	//�ε��� �ʹ� ������ ����Ǽ� õõ�� ���ư����� �׽�Ʈ������ �����
	//for (int i = 0; i < 180; i++)
	//{
	//	_loading->loadImage("�׽�Ʈ", WINSIZEX, WINSIZEY);
	//}
}

//�ε����� �Լ�(�̰��� ���带 ���� �־��)
void loadingScene::loadingSound()
{
}
