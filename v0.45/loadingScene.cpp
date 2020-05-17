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
	_loading->loadImage("��2_show", "Images/��2/map2_show.bmp", 2600, 810);
	_loading->loadImage("��2_������Ʈ", "Images/��2/map2_object.bmp", 2600, 810);
	_loading->loadImage("��2_����Ʈ", "Images/��2/map2_front.bmp", 2600, 810);
	//��3
	_loading->loadImage("��3_�ٴ�", "Images/��3/map3_pixel.bmp", 1666, 720);
	_loading->loadImage("��3_������Ʈ", "Images/��3/map3_object.bmp", 1666, 720);
	_loading->loadImage("���캸��", "Images/��3/���캸��.bmp", 72, 20);
	//������
	_loading->loadImage("�������1", "Images/������/boss_BackGround1.bmp", 1875, 720);
	_loading->loadImage("�������2", "Images/������/boss_BackGround2.bmp", 1865, 720);
	_loading->loadImage("�������ȼ�", "Images/������/bossMap_Pixel.bmp", 1875, 720);
	_loading->loadFrameImage("���ʹ���", "Images/������/���ʹ���.bmp", 7620, 180, 10, 1);
	_loading->loadFrameImage("�����ʹ���", "Images/������/�����ʹ���.bmp", 7620, 180, 10, 1);
	_loading->loadImage("������Ÿ��", "Images/������/������_Ÿ��.bmp", 1875, 720);
	//UI����
	//_loading->loadImage("�÷��̾�UIâ", "Images/ĳ����UI.bmp", 342, 135);
	//_loading->loadImage("UIâ_space", "Images/Space.bmp", 342, 135);
	//_loading->loadImage("������", "Images/������.bmp", 342, 135);
	_loading->loadImage("�÷��̾�UIâ", "Images/ĳ����UI_����.bmp", 334, 134);
	_loading->loadImage("UIâ_space", "Images/Space_����.bmp", 334, 134);
	_loading->loadImage("������", "Images/������_����.bmp", 334, 134);
	_loading->loadImage("����ū������", "Images/ū������.bmp", 90, 90);
	_loading->loadImage("��������������", "Images/����������.bmp", 42, 42);
	_loading->loadImage("���ý�ų1", "Images/���ý�ų_1.bmp", 52, 52);
	_loading->loadImage("���ý�ų2", "Images/���ý�ų_2.bmp", 52, 52);
	_loading->loadImage("��ųĭ", "Images/��ųĭ_����.bmp", 56, 56);
	_loading->loadImage("A_button", "Images/A_button.bmp", 26, 24);
	_loading->loadImage("S_button", "Images/S_button.bmp", 26, 24);
	_loading->loadImage("playerHpBar_front", "Images/ü�¹�_Front.bmp", 236, 25);
	_loading->loadImage("playerHpBar_back", "Images/ü�¹�_Back.bmp", 236, 25);
	_loading->loadFrameImage("skillCoolDown", "Images/cooldown/skillcool_����.bmp", 1958, 180, 14, 1);
	_loading->loadFrameImage("skillCoolDown2", "Images/cooldown/skillcool_����2.bmp", 1958, 180, 14, 1);
	_loading->loadImage("showCoolDown", "Images/cooldown/showCoolDown.bmp", 51, 51);
	_loading->loadImage("����ū������", "Images/soldier_ū������.bmp", 90, 90);
	_loading->loadImage("��������������", "Images/soldier_����������.bmp", 42, 42);
	_loading->loadImage("���罺ų1", "Images/soldier_Skill1.bmp", 51, 51);
	_loading->loadImage("�繫����ū������", "Images/samurai_ū������.bmp", 90, 90);
	_loading->loadImage("�繫��������������", "Images/samurai_����������.bmp", 42, 42);
	_loading->loadImage("�繫���̽�ų1_icon", "Images/samurai_Skill1.bmp", 51, 51);
	_loading->loadImage("�繫���̽�ų2_icon", "Images/samurai_Skill2.bmp", 51, 51);
	_loading->loadImage("�Ϲ��ذ񼳸�", "Images/�Ϲ��ذ񼳸�.bmp", 222, 298);
	_loading->loadImage("�����ذ񼳸�", "Images/�����ذ񼳸�.bmp", 222, 298);
	_loading->loadImage("�繫�����ذ񼳸�", "Images/�繫�����ذ񼳸�.bmp", 222, 400);
	_loading->loadImage("�ݱ�", "Images/�ݱ�.bmp", 36, 20);
	_loading->loadImage("�̴ϸ�Ʋ", "Images/miniMap_UI.bmp", 224, 130);
	//�÷��̾� �������̹���
	//�Ϲ��ذ�
	_loading->loadFrameImage("����", "Images/skul/START.bmp", 6480, 128, 27, 1);
	_loading->loadFrameImage("�Ϲ��ذ�޸���", "Images/skul/RUN.bmp", 672, 130, 8, 2);
	_loading->loadFrameImage("�Ϲ��ذ�����", "Images/skul/JUMP.bmp", 518, 156, 7, 2);
	_loading->loadFrameImage("�Ϲ��ذ����1", "Images/skul/ATT1.bmp", 600, 212, 5, 2);
	_loading->loadFrameImage("�Ϲ��ذ����2", "Images/skul/ATT2.bmp", 472, 224, 4, 2);
	_loading->loadFrameImage("�Ϲ��ذ�IDLE", "Images/skul/IDLE.bmp", 328, 132, 4, 2);
	_loading->loadFrameImage("�Ϲ��ذ�뽬", "Images/skul/DASH.bmp", 76, 96, 1, 2);
	_loading->loadFrameImage("�Ϲ��ذ�뽬ȿ��", "Images/skul/DASH_EFECT.bmp", 76, 96, 1, 2);
	_loading->loadFrameImage("�Ϲ��ذ���������", "Images/skul/JUMPATT.bmp", 464, 216, 4, 2);
	_loading->loadFrameImage("�Ϲ��ذ񱳴�", "Images/skul/CHANGE.bmp", 882, 210, 7, 2);
	_loading->loadFrameImage("�Ϲ��ذ�ų", "Images/skul/SKILL.bmp", 496, 144, 4, 2);
	_loading->loadImage("�Ϲ��ذ�ų_������", "Images/skul/HEAD_R.bmp", 28, 22);
	_loading->loadImage("�Ϲ��ذ�ų_����", "Images/skul/HEAD_L.bmp", 28, 22);
	_loading->loadFrameImage("��������Ʈ", "Images/jumpEfect.bmp", 720, 24, 8, 1);
	_loading->loadFrameImage("�뽬����Ʈ", "Images/dashEfect.bmp", 324, 62, 9, 2);
	_loading->loadFrameImage("�Ϲ��ذ��������Ʈ", "Images/skulAttEfect.bmp", 992, 148, 8, 2);
	//�Ӹ����� �ذ�
	_loading->loadFrameImage("�Ӹ����´޸���", "Images/skul/RUN_non.bmp", 768, 128, 8, 2);
	_loading->loadFrameImage("�Ӹ���������", "Images/skul/jump_non.bmp", 532, 152, 7, 2);
	_loading->loadFrameImage("�Ӹ����°���1", "Images/skul/ATT_non.bmp", 600, 212, 5, 2);
	_loading->loadFrameImage("�Ӹ����°���2", "Images/skul/ATT2_non.bmp", 472, 224, 4, 2);
	_loading->loadFrameImage("�Ӹ�����IDLE", "Images/skul/IDLE_non.bmp", 336, 100, 4, 2);
	_loading->loadFrameImage("�Ӹ����´뽬", "Images/skul/DASH_non.bmp", 62, 80, 1, 2);
	_loading->loadFrameImage("�Ӹ����´뽬ȿ��", "Images/skul/DASH_EFECT_non.bmp", 62, 80, 1, 2);
	_loading->loadFrameImage("�Ӹ�������������", "Images/skul/jumpAtt_non.bmp", 464, 220, 4, 2);
	//�����ذ�
	_loading->loadFrameImage("�ذ񺴻�޸���", "Images/soldier/RUN.bmp", 640, 148, 8, 2);
	_loading->loadFrameImage("�ذ񺴻�����", "Images/soldier/JUMP.bmp", 574, 160, 7, 2);
	_loading->loadFrameImage("�ذ񺴻����", "Images/soldier/ATT.bmp", 672, 192, 7, 2);
	_loading->loadFrameImage("�ذ񺴻�IDLE", "Images/soldier/IDLE.bmp", 256, 156, 4, 2);
	_loading->loadFrameImage("�ذ񺴻�뽬", "Images/soldier/DASH.bmp", 88, 112, 1, 2);
	_loading->loadFrameImage("�ذ񺴻�뽬ȿ��", "Images/soldier/DASH_EFECT.bmp", 88, 112, 1, 2);
	_loading->loadFrameImage("�ذ񺴻���������", "Images/soldier/JUMPATT.bmp", 368, 178, 4, 2);
	_loading->loadFrameImage("�ذ񺴻米��", "Images/soldier/CHAN.bmp", 276, 192, 3, 2);
	_loading->loadFrameImage("�ذ񺴻罺ų", "Images/soldier/SKILL.bmp", 376, 192, 4, 2);
	//�繫���� �ذ�
	_loading->loadFrameImage("�繫���̴޸���", "Images/samurai/RUN.bmp", 528, 148, 6, 2);
	_loading->loadFrameImage("�繫��������", "Images/samurai/JUMP.bmp", 640, 152, 8, 2);
	_loading->loadFrameImage("�繫���̰���1", "Images/samurai/ATT1.bmp", 696, 164, 6, 2);
	_loading->loadFrameImage("�繫���̰���2", "Images/samurai/ATT2.bmp", 624, 232, 4, 2);
	_loading->loadFrameImage("�繫���̰���3", "Images/samurai/ATT3.bmp", 830, 192, 5, 2);
	_loading->loadFrameImage("�繫����IDLE", "Images/samurai/IDLE.bmp", 456, 156, 6, 2);
	_loading->loadFrameImage("�繫���̴뽬", "Images/samurai/DASH.bmp", 90, 116, 1, 2);
	_loading->loadFrameImage("�繫���̴뽬ȿ��", "Images/samurai/DASH_EFECT.bmp", 90, 116, 1, 2);
	_loading->loadFrameImage("�繫������������", "Images/samurai/JUMPATT.bmp", 930, 152, 5, 2);
	_loading->loadFrameImage("�繫���̱���", "Images/samurai/CHAN.bmp", 440, 164, 4, 2);
	_loading->loadFrameImage("�繫���̽�ų1", "Images/samurai/SKILL1.bmp", 1344, 164, 12, 2);
	_loading->loadFrameImage("�繫���̽�ų2", "Images/samurai/SKILL2.bmp", 1140, 164, 10, 2);
	_loading->loadFrameImage("�繫���̳���", "Images/samurai/NAP.bmp", 702, 164, 9, 2);
	_loading->loadFrameImage("�繫����ǥ������Ʈ", "Images/samurai/SIGN_EFECT.bmp", 200, 19, 5, 1);
	_loading->loadFrameImage("�繫���̽�ų1����Ʈ", "Images/samurai/SKILL1_EFECT.bmp", 1728, 156, 9, 1);
	_loading->loadFrameImage("�繫���̳�������Ʈ", "Images/samurai/NAP_EFECT.bmp", 740, 51, 10, 1);
	_loading->loadFrameImage("�繫���̽�ų�������Ʈ", "Images/skillDashEfect.bmp", 1098, 152, 9, 2);
	//_loading->loadFrameImage("�繫���̰�������Ʈ", "Images/samuraiAttEfect.bmp", 792, 94, 11, 1);
	_loading->loadFrameImage("�繫���̰�������Ʈ", "Images/samuraiAttEfect_����.bmp", 1584, 188, 11, 1);
	//������
	_loading->loadFrameImage("��ֻ�����", "Images/ruin/NOMAL.bmp", 1458, 106, 9, 1);
	_loading->loadFrameImage("����ũ������", "Images/ruin/UNIQUE.bmp", 4048, 222, 11, 1);
	_loading->loadImage("�����ذ�", "Images/ruin/���������.bmp", 38, 40);
	_loading->loadImage("�繫�����ذ�", "Images/ruin/�繫���̾�����.bmp", 66, 34);
	//���ʹ� �������̹���
	//����
	_loading->loadFrameImage("����IDLE", "Images/enemy/Tree_Idle.bmp", 420, 186, 5, 2);
	_loading->loadFrameImage("�����޸���", "Images/enemy/Tree_Run.bmp", 477, 183, 6, 2);
	_loading->loadFrameImage("��������", "Images/enemy/Tree_Att.bmp", 450, 180, 4, 2);
	_loading->loadFrameImage("������Ʈ", "Images/enemy/Tree_Hit.bmp", 156, 192, 2, 2);
	_loading->loadFrameImage("��������", "Images/enemy/Tree_Dead.bmp", 108, 87, 1, 2);
	//����
	_loading->loadFrameImage("����IDLE", "Images/enemy/Soldier_Idle.bmp", 372, 212, 6, 2);
	_loading->loadFrameImage("����޸���", "Images/enemy/Soldier_Run.bmp", 784, 184, 8, 2);
	_loading->loadFrameImage("�������", "Images/enemy/Soldier_Att.bmp", 630, 240, 5, 2);
	_loading->loadFrameImage("������Ʈ", "Images/enemy/Soldier_Hit.bmp", 172, 188, 2, 2);
	_loading->loadFrameImage("��������", "Images/enemy/Soldier_Dead.bmp", 136, 26, 1, 1);
	//ū����
	_loading->loadFrameImage("ū����IDLE", "Images/enemy/bigTree_IDLE.bmp", 1344, 220, 6, 1);
	_loading->loadFrameImage("ū��������1", "Images/enemy/bigTree_ATT.bmp", 2224, 216, 8, 1);
	_loading->loadFrameImage("ū��������2", "Images/enemy/bigTree_ATT2.bmp", 786, 222, 3, 1);
	_loading->loadFrameImage("ū�����Ѿ�", "Images/enemy/bigTree_Bullet.bmp", 128, 28, 4, 1);
	_loading->loadFrameImage("ū��������", "Images/enemy/bigTree_DEAD.bmp", 192, 146, 1, 1);
	//ū����
	_loading->loadFrameImage("ū����IDLE", "Images/enemy/bigSoldier_IDLE.bmp", 1060, 384, 5, 2);
	_loading->loadFrameImage("ū����޸���", "Images/enemy/bigSoldier_RUN.bmp", 1680, 372, 8, 2);
	_loading->loadFrameImage("ū�������1", "Images/enemy/bigSoldier_ATT1.bmp", 1848, 420, 7, 2);
	_loading->loadFrameImage("ū�������2", "Images/enemy/bigSoldier_ATT2.bmp", 444, 436, 2, 2);
	_loading->loadFrameImage("ū��������", "Images/enemy/bigSoldier_DEAD.bmp", 588, 412, 2, 2);

	_loading->loadFrameImage("����ȯ����Ʈ", "Images/enemy/enemySommon_Efect.bmp", 312, 43, 6, 1);
	_loading->loadFrameImage("����������Ʈ", "Images/enemy/enemyDead_Efect_����.bmp", 2244, 206, 11, 1);
	_loading->loadImage("enemyHp_Back", "Images/enemy/enemyHp_Back.bmp", 120, 8);
	_loading->loadImage("enemyHp_Front", "Images/enemy/enemyHp_Front.bmp", 120, 8);

	//����
	//_loading->loadFrameImage("������IDLE", "Images/boss/IDLE.bmp", 1320, 588, 4, 2);
	_loading->loadFrameImage("������IDLE_R", "Images/boss/�޼�_IDLE.bmp", 1320, 294, 4, 1);
	_loading->loadFrameImage("������IDLE_L", "Images/boss/������_IDLE.bmp", 1320, 294, 4, 1);
	_loading->loadImage("�����Ӹ�", "Images/boss/�Ӹ�.bmp", 482, 336);
	_loading->loadImage("��������", "Images/boss/����.bmp", 836, 682);
	_loading->loadImage("�����Ʒ���", "Images/boss/�Ʒ���.bmp", 220, 194);
	//_loading->loadFrameImage("��������1", "Images/boss/Att1.bmp", 1400, 604, 4, 2);
	_loading->loadFrameImage("��������1_R", "Images/boss/�޼�_Att1.bmp", 1400, 302, 4, 1);
	_loading->loadFrameImage("��������1_L", "Images/boss/������_Att1.bmp", 1400, 302, 4, 1);
	//_loading->loadFrameImage("��������2", "Images/boss/Att2.bmp", 1152, 548, 3, 2);
	_loading->loadFrameImage("��������2_R", "Images/boss/�޼�_Att2.bmp", 1152, 274, 3, 1);
	_loading->loadFrameImage("��������2_L", "Images/boss/������_Att2.bmp", 1152, 274, 3, 1);
	_loading->loadImage("��������3_R", "Images/boss/�޼�_Att3.bmp", 302, 334);
	_loading->loadImage("��������3_L", "Images/boss/������_Att3.bmp", 302, 334);
	_loading->loadFrameImage("��������2�Ӹ�", "Images/boss/att2�Ӹ�.bmp", 964, 336, 2, 1);
	_loading->loadFrameImage("��������2����", "Images/boss/att2����.bmp", 1692, 682, 2, 1);
	//_loading->loadFrameImage("��������2��", "Images/boss/att2��.bmp", 768, 448, 2, 2);
	_loading->loadFrameImage("��������2��_R", "Images/boss/�޼�_Att2T.bmp", 768, 224, 2, 1);
	_loading->loadFrameImage("��������2��_L", "Images/boss/������_Att2T.bmp", 768, 224, 2, 1);
	_loading->loadFrameImage("��������2�Ʒ���", "Images/boss/att2�Ʒ���.bmp", 444, 194, 2, 1);
	_loading->loadFrameImage("���������ĸӸ�", "Images/boss/�����ĸӸ�.bmp", 1452, 336, 3, 1);
	_loading->loadFrameImage("���������ĸ���", "Images/boss/�����ĸ���.bmp", 1676, 682, 2, 1);
	_loading->loadFrameImage("���������ļ�", "Images/boss/�����ļ�.bmp", 772, 448, 2, 2);
	_loading->loadImage("���������ľƷ���", "Images/boss/�����ľƷ���.bmp", 220, 186);
	_loading->loadImage("ź���ĸӸ�", "Images/boss/ź��������Ӹ�.bmp", 482, 336);
	_loading->loadFrameImage("�������", "Images/boss/�������.bmp", 11312, 354, 28, 1);
	_loading->loadFrameImage("������Ʈ", "Images/boss/������Ʈ.bmp", 10736, 414, 11, 1);
	_loading->loadImage("���������Ѿ�", "Images/boss/boss_Bullet.bmp", 30, 30);
	_loading->loadFrameImage("����ū�Ѿ�", "Images/boss/boss_BigBullet.bmp", 2600, 197, 13, 1);
	_loading->loadFrameImage("��������Ʈ", "Images/boss/��������Ʈ.bmp", 4080, 314, 8, 1);

	_loading->loadImage("����ü�¹�_Back", "Images/boss/bossHpBar_Back1.bmp", 552, 46);
	_loading->loadImage("����ü�¹�_Back2", "Images/boss/bossHpBar_Back2.bmp", 28, 40);
	_loading->loadImage("����ü�¹�_Back3", "Images/boss/bossHpBar_Back3.bmp", 28, 40);
	_loading->loadImage("����ü�¹�_Front", "Images/boss/bossHpBar_Front.bmp", 552, 46);
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
