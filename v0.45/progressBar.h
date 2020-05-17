#pragma once
#include "gameNode.h"
//=============================================================
//	## progressBar ## (프로그래스바 = 체력바 = 로딩바 등등)
//=============================================================
class progressBar : public gameNode
{
private:
	image* _progressBarFront;	//체력바 앞 이미지
	image* _progressBarBack;	//체력바 뒤 이미지
	RECT _rcProgress;			//체력바 렉트
	float _x, _y;				//체력바 위치좌표
	float _width;				//체력바 가로길이
	float _height;				//체력바 세로길이

public:
	HRESULT init(const char* frontImg, const char* backImg);
	void release();
	void update();
	void render();

	//체력바 위치 세팅하기
	void setPos(float x, float y) { _x = x; _y = y; }
	//체력바 게이지 세팅하기
	void setGauge(float maxHp, float currentHp);

	float getWidth() { return _width; }

	image* getProgressBarBack() { return _progressBarBack; }

	progressBar() {}
	~progressBar() {}
};

//=============================================================
//	## skillCooltime ## (프로그래스바 = 체력바 = 로딩바 등등)
//=============================================================
class skillCooltime : public gameNode
{
private:
	image* _progressBarFront;	//체력바 앞 이미지
	image* _progressBarBack;	//체력바 뒤 이미지
	RECT _rcProgress;			//체력바 렉트
	float _x, _y;				//체력바 위치좌표
	float _width;				//체력바 가로길이
	float _height;				//체력바 세로길이

public:
	HRESULT init(const char* frontImg, const char* backImg);
	void release();
	void update();
	void render(bool isArpha = false);

	//체력바 위치 세팅하기
	void setPos(float x, float y) { _x = x; _y = y; }
	//체력바 게이지 세팅하기
	void setGauge(float maxHp, float currentHp);

	float getWidth() { return _width; }

	image* getProgressBarBack() { return _progressBarBack; }

	skillCooltime() {}
	~skillCooltime() {}
};

//=============================================================
//	## enemy ## (다수의 적 Hp바)
//=============================================================

struct tagHpBar
{
	image* _progressBarFront;	//체력바 앞 이미지
	image* _progressBarBack;	//체력바 뒤 이미지
	RECT _rcProgress;			//체력바 렉트
	float _x, _y;				//체력바 위치좌표
	float _width;				//체력바 가로길이
	float _height;				//체력바 세로길이
};

class enemyHpbar : public gameNode
{
private:
	vector<tagHpBar> _vHpBar;

	int count;
public:
	HRESULT init(const char* frontImg, const char* backImg, int z);
	void release();
	void update();
	void render();

	//체력바 위치 세팅하기
	void setPos(float x, float y, int z) 
	{ 
		for (int i = 0; i < z; i++)
		{
			_vHpBar[i]._x = x; _vHpBar[i]._y = y; 
		}
	}
	//체력바 게이지 세팅하기
	void setGauge(float maxHp, float currentHp);

	//image* getProgressBarBack(int z) 
	//{
	//	for (int i = 0; i < _vHpBar.size(); i++)
	//	{
	//		return _vHpBar[i]._progressBarBack;
	//	}
	//}

	enemyHpbar() {}
	~enemyHpbar() {}
};