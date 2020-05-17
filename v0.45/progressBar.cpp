#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init(const char * frontImg, const char * backImg)
{
	//ü�¹� �̹��� �ʱ�ȭ
	_progressBarFront = IMAGEMANAGER->findImage(frontImg);
	_progressBarBack = IMAGEMANAGER->findImage(backImg);
	//ü�¹� ��ġ �ʱ�ȭ
	_x = _progressBarBack->getX();
	_y = _progressBarBack->getY();
	//ü�¹� ����, ���α��� �ʱ�ȭ
	_width = _progressBarBack->getWidth();
	_height = _progressBarBack->getHeight();
	//ü�¹� ��Ʈ �ʱ�ȭ
	_rcProgress = RectMake(_x, _y, _width, _height);
	return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{
	//���α׷����� ��Ʈ ������Ʈ
	_rcProgress = RectMake(_x, _y, _width, _height);
}

void progressBar::render()
{
	//������ �Ǵ� ������ ���ؼ� ������ �Ǵϱ� ������� ���� ��Ų��
	_progressBarBack->render(getMemDC(), _x, _y);
	//�տ� �������� ü�¹� �̹���

	_progressBarFront->render(getMemDC(), _x, _y,
		0, 0, _width, _progressBarFront->getHeight());

}

void progressBar::setGauge(float maxHp, float currentHp)
{
	_width = (currentHp / maxHp) * _progressBarBack->getWidth();
}

//=============================================================
//	## skillCooltime ## (���α׷����� = ü�¹� = �ε��� ���)
//=============================================================
HRESULT skillCooltime::init(const char * frontImg, const char * backImg)
{
	//ü�¹� �̹��� �ʱ�ȭ
	_progressBarFront = IMAGEMANAGER->findImage(frontImg);
	_progressBarBack = IMAGEMANAGER->findImage(backImg);
	//ü�¹� ��ġ �ʱ�ȭ
	_x = _progressBarBack->getX();
	_y = _progressBarBack->getY();
	//ü�¹� ����, ���α��� �ʱ�ȭ
	_width = _progressBarBack->getWidth();
	_height = _progressBarBack->getHeight();
	//ü�¹� ��Ʈ �ʱ�ȭ
	_rcProgress = RectMake(_x, _y, _width, _height);
	return S_OK;
}

void skillCooltime::release()
{
}

void skillCooltime::update()
{
	_rcProgress = RectMake(_x, _y, _width, _height);
}

void skillCooltime::render(bool isArpha)
{
	//������ �Ǵ� ������ ���ؼ� ������ �Ǵϱ� ������� ���� ��Ų��
	_progressBarBack->render(getMemDC(), _x, _y);
	//�տ� �������� ü�¹� �̹���
	if (isArpha == false)
	{
		_progressBarFront->render(getMemDC(), _x, _y,
			0, 0, _width, _progressBarFront->getHeight());
	}
	else if (isArpha == true)
	{
		_progressBarFront->alphaRender(getMemDC(), _x, _y,
			0, 0, _progressBarFront->getWidth(), _height, 160);
	}
}

void skillCooltime::setGauge(float maxHp, float currentHp)
{
	_height = (currentHp / maxHp) * _progressBarBack->getHeight();
}

////=============================================================
////	## enemy ## (�ټ��� �� Hp��)
////=============================================================
//
//HRESULT enemyHpbar::init(const char* frontImg, const char* backImg, int z)
//{
//	count = z;
//	for (int i = 0; i < count; i++)
//	{
//		//ü�¹� �̹��� �ʱ�ȭ
//		_vHpBar[i]._progressBarFront = IMAGEMANAGER->findImage(frontImg);
//		_vHpBar[i]._progressBarBack = IMAGEMANAGER->findImage(backImg);
//		//ü�¹� ��ġ �ʱ�ȭ
//		_vHpBar[i]._x = _vHpBar[i]._progressBarBack->getX();
//		_vHpBar[i]._y = _vHpBar[i]._progressBarBack->getY();
//		//ü�¹� ����, ���α��� �ʱ�ȭ
//		_vHpBar[i]._width = _vHpBar[i]._progressBarBack->getWidth();
//		_vHpBar[i]._height = _vHpBar[i]._progressBarBack->getHeight();
//		//ü�¹� ��Ʈ �ʱ�ȭ
//		_vHpBar[i]._rcProgress = RectMake(_vHpBar[i]._x, _vHpBar[i]._y, _vHpBar[i]._width, _vHpBar[i]._height);
//	}
//	return S_OK;
//}
//
//void enemyHpbar::release()
//{
//}
//
//void enemyHpbar::update()
//{
//	for (int i = 0; i < count; i++)
//	{
//		//���α׷����� ��Ʈ ������Ʈ
//		_vHpBar[i]._rcProgress = RectMake(_vHpBar[i]._x, _vHpBar[i]._y, _vHpBar[i]._width, _vHpBar[i]._height);
//	}
//}
//
//void enemyHpbar::render()
//{
//	for (int i = 0; i < count; i++)
//	{
//		//������ �Ǵ� ������ ���ؼ� ������ �Ǵϱ� ������� ���� ��Ų��
//		_vHpBar[i]._progressBarBack->render(getMemDC(), _vHpBar[i]._x, _vHpBar[i]._y);
//		//�տ� �������� ü�¹� �̹���
//
//		_vHpBar[i]._progressBarFront->render(getMemDC(), _vHpBar[i]._x, _vHpBar[i]._y,
//			0, 0, _vHpBar[i]._width, _vHpBar[i]._progressBarFront->getHeight());
//	}
//}
//
//void enemyHpbar::setGauge(float maxHp, float currentHp)
//{
//	for (int i = 0; i < count; i++)
//	{
//		_vHpBar[i]._width = (currentHp / maxHp) * _vHpBar[i]._progressBarBack->getWidth();
//	}
//}
