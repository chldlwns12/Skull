#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init(const char * frontImg, const char * backImg)
{
	//체력바 이미지 초기화
	_progressBarFront = IMAGEMANAGER->findImage(frontImg);
	_progressBarBack = IMAGEMANAGER->findImage(backImg);
	//체력바 위치 초기화
	_x = _progressBarBack->getX();
	_y = _progressBarBack->getY();
	//체력바 가로, 세로길이 초기화
	_width = _progressBarBack->getWidth();
	_height = _progressBarBack->getHeight();
	//체력바 렉트 초기화
	_rcProgress = RectMake(_x, _y, _width, _height);
	return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{
	//프로그레스바 렉트 업데이트
	_rcProgress = RectMake(_x, _y, _width, _height);
}

void progressBar::render()
{
	//렌더링 되는 순서의 의해서 렌더가 되니까 피통부터 렌더 시킨다
	_progressBarBack->render(getMemDC(), _x, _y);
	//앞에 보여지는 체력바 이미지

	_progressBarFront->render(getMemDC(), _x, _y,
		0, 0, _width, _progressBarFront->getHeight());

}

void progressBar::setGauge(float maxHp, float currentHp)
{
	_width = (currentHp / maxHp) * _progressBarBack->getWidth();
}

//=============================================================
//	## skillCooltime ## (프로그래스바 = 체력바 = 로딩바 등등)
//=============================================================
HRESULT skillCooltime::init(const char * frontImg, const char * backImg)
{
	//체력바 이미지 초기화
	_progressBarFront = IMAGEMANAGER->findImage(frontImg);
	_progressBarBack = IMAGEMANAGER->findImage(backImg);
	//체력바 위치 초기화
	_x = _progressBarBack->getX();
	_y = _progressBarBack->getY();
	//체력바 가로, 세로길이 초기화
	_width = _progressBarBack->getWidth();
	_height = _progressBarBack->getHeight();
	//체력바 렉트 초기화
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
	//렌더링 되는 순서의 의해서 렌더가 되니까 피통부터 렌더 시킨다
	_progressBarBack->render(getMemDC(), _x, _y);
	//앞에 보여지는 체력바 이미지
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
////	## enemy ## (다수의 적 Hp바)
////=============================================================
//
//HRESULT enemyHpbar::init(const char* frontImg, const char* backImg, int z)
//{
//	count = z;
//	for (int i = 0; i < count; i++)
//	{
//		//체력바 이미지 초기화
//		_vHpBar[i]._progressBarFront = IMAGEMANAGER->findImage(frontImg);
//		_vHpBar[i]._progressBarBack = IMAGEMANAGER->findImage(backImg);
//		//체력바 위치 초기화
//		_vHpBar[i]._x = _vHpBar[i]._progressBarBack->getX();
//		_vHpBar[i]._y = _vHpBar[i]._progressBarBack->getY();
//		//체력바 가로, 세로길이 초기화
//		_vHpBar[i]._width = _vHpBar[i]._progressBarBack->getWidth();
//		_vHpBar[i]._height = _vHpBar[i]._progressBarBack->getHeight();
//		//체력바 렉트 초기화
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
//		//프로그레스바 렉트 업데이트
//		_vHpBar[i]._rcProgress = RectMake(_vHpBar[i]._x, _vHpBar[i]._y, _vHpBar[i]._width, _vHpBar[i]._height);
//	}
//}
//
//void enemyHpbar::render()
//{
//	for (int i = 0; i < count; i++)
//	{
//		//렌더링 되는 순서의 의해서 렌더가 되니까 피통부터 렌더 시킨다
//		_vHpBar[i]._progressBarBack->render(getMemDC(), _vHpBar[i]._x, _vHpBar[i]._y);
//		//앞에 보여지는 체력바 이미지
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
