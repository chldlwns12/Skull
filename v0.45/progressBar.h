#pragma once
#include "gameNode.h"
//=============================================================
//	## progressBar ## (���α׷����� = ü�¹� = �ε��� ���)
//=============================================================
class progressBar : public gameNode
{
private:
	image* _progressBarFront;	//ü�¹� �� �̹���
	image* _progressBarBack;	//ü�¹� �� �̹���
	RECT _rcProgress;			//ü�¹� ��Ʈ
	float _x, _y;				//ü�¹� ��ġ��ǥ
	float _width;				//ü�¹� ���α���
	float _height;				//ü�¹� ���α���

public:
	HRESULT init(const char* frontImg, const char* backImg);
	void release();
	void update();
	void render();

	//ü�¹� ��ġ �����ϱ�
	void setPos(float x, float y) { _x = x; _y = y; }
	//ü�¹� ������ �����ϱ�
	void setGauge(float maxHp, float currentHp);

	float getWidth() { return _width; }

	image* getProgressBarBack() { return _progressBarBack; }

	progressBar() {}
	~progressBar() {}
};

//=============================================================
//	## skillCooltime ## (���α׷����� = ü�¹� = �ε��� ���)
//=============================================================
class skillCooltime : public gameNode
{
private:
	image* _progressBarFront;	//ü�¹� �� �̹���
	image* _progressBarBack;	//ü�¹� �� �̹���
	RECT _rcProgress;			//ü�¹� ��Ʈ
	float _x, _y;				//ü�¹� ��ġ��ǥ
	float _width;				//ü�¹� ���α���
	float _height;				//ü�¹� ���α���

public:
	HRESULT init(const char* frontImg, const char* backImg);
	void release();
	void update();
	void render(bool isArpha = false);

	//ü�¹� ��ġ �����ϱ�
	void setPos(float x, float y) { _x = x; _y = y; }
	//ü�¹� ������ �����ϱ�
	void setGauge(float maxHp, float currentHp);

	float getWidth() { return _width; }

	image* getProgressBarBack() { return _progressBarBack; }

	skillCooltime() {}
	~skillCooltime() {}
};

//=============================================================
//	## enemy ## (�ټ��� �� Hp��)
//=============================================================

struct tagHpBar
{
	image* _progressBarFront;	//ü�¹� �� �̹���
	image* _progressBarBack;	//ü�¹� �� �̹���
	RECT _rcProgress;			//ü�¹� ��Ʈ
	float _x, _y;				//ü�¹� ��ġ��ǥ
	float _width;				//ü�¹� ���α���
	float _height;				//ü�¹� ���α���
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

	//ü�¹� ��ġ �����ϱ�
	void setPos(float x, float y, int z) 
	{ 
		for (int i = 0; i < z; i++)
		{
			_vHpBar[i]._x = x; _vHpBar[i]._y = y; 
		}
	}
	//ü�¹� ������ �����ϱ�
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