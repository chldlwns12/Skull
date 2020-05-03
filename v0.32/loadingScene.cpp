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
	TextOut(getMemDC(), 370, 562, _LoadFileName, strlen(_LoadFileName));

	IMAGEMANAGER->findImage("�ε��ذ�")->frameRender(getMemDC(), _loading->getProgressBar()->getWidth() + 280, 575);
}


//�ε��̹��� �Լ�(�̰��� �̹����� ���� �־��)
void loadingScene::loadingImage()
{
	//_loading->loadImage();
	//_loading->loadFrameImage();

	_loading->loadImage("��׶���1", "Images/Background1_����.bmp", 3880, 810);
	_loading->loadImage("��׶���1_�̴�", "Images/Background1_�̴�.bmp", 388, 81);
	_loading->loadImage("��׶���2", "Images/Background2_����.bmp", 3880, 810);
	_loading->loadImage("��׶���2_�̴�", "Images/Background2_�̴�.bmp", 388, 81);
	_loading->loadImage("��׶���3", "Images/Background3_����.bmp", 3880, 810);
	_loading->loadImage("��׶���3_�̴�", "Images/Background3_�̴�.bmp", 388, 81);
	_loading->loadImage("��׶���4", "Images/Background4_����.bmp", 3880, 810);
	_loading->loadImage("��׶���4_�̴�", "Images/Background4_�̴�.bmp", 388, 81);

	_loading->loadImage("���ø޴�", "Images/���ø޴�.bmp", 1280, 720);
	_loading->loadImage("�޴�_�⺻", "Images/�޴�_�⺻.bmp", 378, 560);
	_loading->loadImage("�޴�_��ŸƮ", "Images/�޴�_��ŸƮ.bmp", 378, 560);
	_loading->loadImage("�޴�_����", "Images/�޴�_����.bmp", 378, 560);
	_loading->loadImage("�޴�_������", "Images/�޴�_������.bmp", 378, 560);
	_loading->loadImage("��ư_�巡��", "Images/��ư_�巡��.bmp", 173, 57);
	_loading->loadImage("��ư_�巡�׿�", "Images/��ư_�巡�׿�.bmp", 173, 57);
	_loading->loadImage("��ư_�ε�", "Images/��ư_�ε�.bmp", 173, 57);
	_loading->loadImage("��ư_�ε��", "Images/��ư_�ε��.bmp", 173, 57);
	_loading->loadImage("��ư_����", "Images/��ư_����.bmp", 173, 57);
	_loading->loadImage("��ư_���¿�", "Images/��ư_���¿�.bmp", 173, 57);
	_loading->loadImage("��ư_���̺�", "Images/��ư_���̺�.bmp", 173, 57);
	_loading->loadImage("��ư_���̺��", "Images/��ư_���̺��.bmp", 173, 57);
	_loading->loadImage("��ư_����Ʈ", "Images/��ư_����Ʈ.bmp", 173, 57);
	_loading->loadImage("��ư_����Ʈ��", "Images/��ư_����Ʈ��.bmp", 173, 57);
	_loading->loadImage("��ư_������Ʈ", "Images/��ư_������Ʈ.bmp", 173, 57);
	_loading->loadImage("��ư_������Ʈ��", "Images/��ư_������Ʈ��.bmp", 173, 57);
	_loading->loadImage("��ư_�̷�����", "Images/��ư_�̷�����.bmp", 173, 57);
	_loading->loadImage("��ư_�̷�������", "Images/��ư_�̷�������.bmp", 173, 57);
	_loading->loadImage("��ư_����", "Images/��ư_����.bmp", 173, 57);
	_loading->loadImage("��ư_������", "Images/��ư_������.bmp", 173, 57);
	_loading->loadImage("���ڽ�", "Images/���ڽ�.bmp", 1000, 450);
	//�ΰ��� �޴�
	_loading->loadImage("�ΰ��Ӹ޴�ȭ��", "Images/�ΰ��Ӹ޴�ȭ��.bmp", 372, 696);
	_loading->loadImage("�ΰ���_��ӹ�ư", "Images/�ΰ���_��ӹ�ư.bmp", 173, 57);
	_loading->loadImage("�ΰ���_��ӹ�ưOn", "Images/�ΰ���_��ӹ�ưOn.bmp", 173, 57);
	_loading->loadImage("�ΰ���_�ɼǹ�ư", "Images/�ΰ���_�ɼǹ�ư.bmp", 173, 57);
	_loading->loadImage("�ΰ���_�ɼǹ�ưOn", "Images/�ΰ���_�ɼǹ�ưOn.bmp", 173, 57);
	_loading->loadImage("�ΰ���_�������ư", "Images/�ΰ���_�������ư.bmp", 173, 57);
	_loading->loadImage("�ΰ���_�������ưOn", "Images/�ΰ���_�������ưOn.bmp", 173, 57);
	//��1
	_loading->loadImage("��1_���1", "Images/���۸�/���۹��_1.bmp", 1940, 720);
	_loading->loadImage("��1_�ϴ�1", "Images/���۸�/�����ϴ�_1.bmp", 1040, 2047);
	_loading->loadImage("��1_�ϴ�2", "Images/���۸�/�����ϴ�_2.bmp", 1880, 720);
	_loading->loadImage("��1_����1", "Images/���۸�/���۱���_1_����.bmp", 1896, 690);
	_loading->loadImage("��1_����2", "Images/���۸�/���۱���_2.bmp", 405, 105);
	_loading->loadImage("��1_����3", "Images/���۸�/���۱���_3.bmp", 313, 82);
	_loading->loadImage("��1_�ٴ�", "Images/���۸�/�ٴ�_����.bmp", 1940, 720);
	_loading->loadImage("��1_���鸮��1", "Images/���۸�/���ۼ��鸮��_1.bmp", 228, 190);
	_loading->loadImage("��1_���鸮��2", "Images/���۸�/���ۼ��鸮��_2.bmp", 223, 245);
	_loading->loadImage("��1_���鸮��3", "Images/���۸�/���ۼ��鸮��_3.bmp", 213, 240);
	_loading->loadImage("��1_������Ʈ", "Images/���۸�/������Ʈ_����.bmp", 3284, 720);

	_loading->loadFrameImage("����Ÿ��", "Images/����Ÿ��.bmp", 510, 340, 15, 10);
	_loading->loadFrameImage("����Ÿ��_�̴�", "Images/����Ÿ��_�̴�.bmp", 51, 34, 15, 10);
	_loading->loadFrameImage("�޸���", "Images/�޸���.bmp", 640, 128, 8, 2);
	_loading->loadFrameImage("����", "Images/����.bmp", 527, 151, 7, 2);
	_loading->loadFrameImage("����1", "Images/����1.bmp", 666, 198, 6, 2);
	_loading->loadFrameImage("����2", "Images/����2.bmp", 330, 198, 3, 2);
	//_loading->loadFrameImage("IDLE", "Images/IDLE.bmp", 407, 128, 5, 2);
	_loading->loadFrameImage("IDLE", "Images/IDLE_����.bmp", 411, 128, 5, 2);
	_loading->loadFrameImage("�뽬", "Images/�뽬.bmp", 81, 103, 1, 2);
	_loading->loadFrameImage("�뽬ȿ��", "Images/�뽬ȿ��.bmp", 81, 103, 1, 2);

	//�ε��� �ʹ� ������ ����Ǽ� õõ�� ���ư����� �׽�Ʈ������ �����
	//for (int i = 0; i < 380; i++)
	//{
	//	_loading->loadImage("�׽�Ʈ", WINSIZEX, WINSIZEY);
	//}
}

//�ε����� �Լ�(�̰��� ���带 ���� �־��)         
void loadingScene::loadingSound()
{
}
