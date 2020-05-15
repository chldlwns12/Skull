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

void progressBar::render(bool isArpha)
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
			0, 0, _width, _progressBarFront->getHeight(), 150);
	}
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
