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
	_loading->loadImage("��׶���1", "Images/Background1_����.bmp", 2600, 810);
	_loading->loadImage("��׶���1_�̴�", "Images/Background1_�̴�.bmp", 260, 81);
	_loading->loadImage("��׶���2", "Images/Background2_����.bmp", 2600, 810);
	_loading->loadImage("��׶���2_�̴�", "Images/Background2_�̴�.bmp", 260, 81);
	_loading->loadImage("��׶���3", "Images/Background3_����.bmp", 2600, 810);
	_loading->loadImage("��׶���3_�̴�", "Images/Background3_�̴�.bmp", 260, 81);
	_loading->loadImage("��׶���4", "Images/Background4_����.bmp", 2600, 810);
	_loading->loadImage("��׶���4_�̴�", "Images/Background4_�̴�.bmp", 260, 81);

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
	_loading->loadImage("��1_�ϴ�1", "Images/���۸�/�����ϴ�_1_����.bmp", 1280, 4961);
	_loading->loadImage("��1_�ϴ�2", "Images/���۸�/�����ϴ�_2.bmp", 1880, 720);
	_loading->loadImage("��1_����1", "Images/���۸�/���۱���_1_����.bmp", 1896, 690);
	_loading->loadImage("��1_����2", "Images/���۸�/���۱���_2.bmp", 405, 105);
	_loading->loadImage("��1_����3", "Images/���۸�/���۱���_3.bmp", 313, 82);
	_loading->loadImage("��1_����4", "Images/���۸�/���۱���_4.bmp", 1175, 1190);
	_loading->loadImage("��1_����5", "Images/���۸�/���۱���_5.bmp", 1120, 1616);
	_loading->loadImage("��1_�ٴ�", "Images/���۸�/�ٴ�_����.bmp", 3284, 720);
	_loading->loadImage("��1_���鸮��1", "Images/���۸�/���ۼ��鸮��_1.bmp", 228, 190);
	_loading->loadImage("��1_���鸮��2", "Images/���۸�/���ۼ��鸮��_2.bmp", 223, 245);
	_loading->loadImage("��1_���鸮��3", "Images/���۸�/���ۼ��鸮��_3.bmp", 213, 240);
	_loading->loadImage("��1_������Ʈ", "Images/���۸�/������Ʈ.bmp", 3284, 720);
	_loading->loadImage("��1_����1", "Images/���۸�/ž��.bmp", 311, 700);
	_loading->loadImage("��1_����2", "Images/���۸�/ž��2.bmp", 253, 700);
	_loading->loadImage("��1_����3", "Images/���۸�/����1.bmp", 311, 4661);
	_loading->loadImage("��1_��", "Images/���۸�/�����.bmp", 1280, 1525);
	_loading->loadImage("��1_��1" "Images/���۸�/����_1.bmp", 1051, 629);
	_loading->loadImage("��1_��2", "Images/���۸�/����_2.bmp", 1052, 381);
	_loading->loadImage("�Ʒ���_�ٴ�", "Images/���۸�/�Ʒ��ʹٴ�.bmp", 1588, 720);
	_loading->loadImage("�Ʒ���_�ٴ�_show", "Images/���۸�/�Ʒ��ʹٴ�_show.bmp", 1588, 170);
	_loading->loadImage("�Ʒ���_������Ʈ", "Images/���۸�/�Ʒ��ʿ�����Ʈ.bmp", 1588, 720);
	_loading->loadImage("�Ʒ���_�չ��", "Images/���۸�/�Ʒ��ʾչ��.bmp", 1588, 720);
	_loading->loadImage("F��ȣ�ۿ�", "Images/���۸�/F_Button.bmp", 26, 24);
	_loading->loadImage("����", "Images/���۸�/����.bmp", 72, 20);
	//��2
	_loading->loadImage("��2_�ٴ�", "Images/��2/map2_pixel.bmp", 2600, 810);
	_loading->loadImage("��2_������Ʈ", "Images/��2/map2_object.bmp", 2600, 810);
	_loading->loadImage("��2_����Ʈ", "Images/��2/map2_front.bmp", 2600, 810);

	//�÷��̾� �������̹���
	_loading->loadFrameImage("�޸���", "Images/�޸���.bmp", 640, 128, 8, 2);
	_loading->loadFrameImage("����", "Images/����.bmp", 527, 151, 7, 2);
	_loading->loadFrameImage("����1", "Images/����1.bmp", 666, 198, 6, 2);
	_loading->loadFrameImage("����2", "Images/����2.bmp", 330, 198, 3, 2);
	_loading->loadFrameImage("IDLE", "Images/IDLE_����.bmp", 411, 128, 5, 2);
	_loading->loadFrameImage("�뽬", "Images/�뽬.bmp", 81, 103, 1, 2);
	_loading->loadFrameImage("�뽬ȿ��", "Images/�뽬ȿ��.bmp", 81, 103, 1, 2);
	//���ʹ� �������̹���
	//����
	_loading->loadFrameImage("����IDLE", "Images/enemy/Tree_Idle.bmp", 420, 186, 5, 2);
	_loading->loadFrameImage("�����޸���", "Images/enemy/Tree_Run.bmp", 477, 183, 6, 2);
	_loading->loadFrameImage("��������", "Images/enemy/Tree_Att.bmp", 450, 180, 4, 2);
	_loading->loadFrameImage("������Ʈ", "Images/enemy/Tree_Hit.bmp", 156, 192, 2, 2);
	_loading->loadFrameImage("��������", "Images/enemy/Tree_Dead.bmp", 108, 87, 1, 2);
	//����
	_loading->loadFrameImage("����IDLE", "Images/enemy/Soldier_Idle.bmp", 270, 159, 6, 2);
	_loading->loadFrameImage("����޸���", "Images/enemy/Soldier_Run.bmp", 672, 138, 8, 2);
	_loading->loadFrameImage("�������", "Images/enemy/Soldier_Att.bmp", 488, 180, 5, 2);
	_loading->loadFrameImage("������Ʈ", "Images/enemy/Soldier_Hit.bmp", 138, 141, 2, 2);
	_loading->loadImage("��������", "Images/enemy/Soldier_Dead.bmp", 21, 35);
	//�� �������̹���
	_loading->loadFrameImage("���۹�", "Images/���۸�/���۹�_����.bmp", 2960, 248, 8, 1);


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
