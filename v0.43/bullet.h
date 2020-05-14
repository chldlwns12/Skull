#pragma once
#include "gameNode.h"

//총알 구조체
struct tagBullet
{
	image* bulletImage;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float speed;
	float angle;
	float gravity;
	float radius;
	bool fire;
	int count;
};

//=============================================================
//	## bullet ## (공용총알 - 너희들이 만들어야 함)
//=============================================================
class bullet : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

private:
	const char* _imageName;	//총알 이미지 이름
	float _range;			//총알 사거리
	int _bulletMax;			//총알 최대갯수
	bool _isFrameImg;		//프레임 이미지냐?

public:
	HRESULT init(const char* imageName, int bulletMax, float range, bool isFrameImg = false);
	void release();
	void update();
	void render();

	//총알발사
	void fire(float x, float y, float angle, float speed);
	//총알무브
	void move();

	//총알벡터 가져오기
	vector<tagBullet> getBullet() { return _vBullet; }
	//폭탄 삭제
	void removeBullet(int index);

	bullet() {}
	~bullet() {}
};


//=============================================================
//	## missile ## (missile[0] -> 배열처럼 미리 장전해두고 총알발사)
//=============================================================
class missile : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

private:
	float _range;		//총알 사거리
	int _bulletMax;		//총알 최대갯수

public:
	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();

	//총알발사
	void fire(float x, float y);
	//총알무브
	void move();

	missile() {}
	~missile() {}
};


//=============================================================
//	## bomb ## (폭탄처럼 한발씩 발사하고 생성하고 자동삭제)
//=============================================================
class bomb : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

private:
	float _range;		//총알 사거리
	int _bulletMax;		//총알 최대갯수

public:
	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();

	//총알발사
	void fire(float x, float y);
	//총알무브
	void move();

	//총알벡터 가져오기
	vector<tagBullet> getBullet() { return _vBullet; }
	//폭탄 삭제
	void removeBomb(int index);

	bomb() {}
	~bomb() {}
};

enum BULLETIMG
{
	RENDER = 0,
	FRAMERENDER,
	ROTATERENDER
};

//=============================================================
//	## Skul ## 스컬총알
//=============================================================
class Skul : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

private:
	//const char* _imageName;	//총알 이미지 이름
	float _range;			//총알 사거리
	int _bulletMax;			//총알 최대갯수
	//bool _isFrameImg;		//프레임 이미지냐?
	BULLETIMG bulletImgState;
	float _rotateAngle;
	float gravity;

	//int headCoolDown;
	//bool isCoolDown;
	bool isRange;

	float bulletPtTop;
	float bulletPtBottom;
	float bulletPtRight;
	float bulletPtLeft;

	float saveX;
public:
	HRESULT init(int bulletMax, float range, BULLETIMG Img = RENDER);
	void release();
	void update();
	void render();

	//총알발사
	void fire(float x, float y, float angle, float speed, const char* imageName);
	//총알무브
	void move();

	//총알벡터 가져오기
	vector<tagBullet> getBullet() { return _vBullet; }
	//폭탄 삭제
	void removeBullet(int index);

	//로테이트앵글
	void rotateAngle(float angle);

	float getVBulletX() 
	{ 
		for (int i = 0 ; i < _vBullet.size(); i++)
		{
			if (_vBullet.empty()) break;
			return _vBullet[i].x;
		}
	}
	float getVBulletY() 
	{ 
		for (int i = 0; i < _vBullet.size(); i++)
		{
			if (_vBullet.empty()) break;
			return _vBullet[i].y;
		}
	}
	float getVBulletBottom() { return bulletPtBottom; }
	float getVBulletRight() { return bulletPtRight; }
	float getBulletLeft() { return bulletPtLeft; }
	float getBulletGravity() { return gravity; }
	float getSaveX() { return saveX; }
	//int getHeadCoolDown() { return headCoolDown; }
	//bool getIsCooldown() { return isCoolDown; }

	void setBulletGravity(float gv) { gravity = gv; }
	void setRotateAngle(float angle) { _rotateAngle = angle; }
	Skul() {}
	~Skul() {}
};

