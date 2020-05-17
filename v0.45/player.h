#pragma once
#include "gameNode.h"
#include "progressBar.h"
#include "bullet.h"

enum PLAYERSTATE
{
	PLAYER_IDLE = 0,
	PLAYER_RUN,
	PLAYER_JUMP,
	PLAYER_DOUBLEJUMP,
	PLAYER_ATT,
	PLAYER_ATT2,
	PLAYER_ATT3,
	PLAYER_DASH,
	PLAYER_START,
	PLAYER_JUMPATT,
	PLAYER_SKILL1,
	PLAYER_SKILL2,
	PLAYER_CHANGE,
	PLAYER_NAPDO
};

class enemy;
class boss;

class player : public gameNode
{
private:
	Skul* Head;
	enemy* ptPlayerEnemy;
	boss* ptPlayerBoss;
private:
	PLAYERSTATE _playerState;


	//플레이어 기본사항 - 공격력 체력 등등 추가해야함
	float playerX, playerY;
	float playerSpeed;
	int attCount;
	int attIndex;
	RECT rcPlayer;
	int playerCurrentHp;
	int playerMexHp;
	float moveX, moveY;
	//bool isMoving;
	//점프
	float jumpSpeed;
	float gravity;
	bool isJump;
	bool isSky;
	int jumpCount;
	image* jumpEfect;
	int jumpSaveX;
	int jumpSaveY;
	bool jumpDown;
	//공격
	bool isEndAtt1;
	bool isEndAtt2;
	bool isEndAtt3;
	//bool isAtt1;
	//bool isAtt2;
	//bool isAtt3;
	int Att1CoolDown;
	int Att2CoolDown;
	int Att3CoolDown;
	bool isAttCool;
	RECT rcATK;
	bool isATK;
	int playerATK;
	//대쉬
	int Efect1;
	int Efect2;
	int Efect3;
	int Efect4;
	int Efect5;
	bool isDash;
	int dashCount;
	int dashCooldown;
	image* dashGroundEfect;
	//스킬
	int skulCooldown_1;
	int skulCooldown_2;
	int soldierCooldown_1;
	int samuraiCooldown_1;
	int samuraiCooldown_2;
	int CooldownMax;
	int changeCooldown;
	int napdoCount;
	int napdoIndex;
	//int headAngle;
	RECT rcHead;
	int saveX;
	bool change;
	float headAngle;
	float headGravity;
	bool isSkulSkill1;
	bool isSkulSkill2;
	RECT rcSkill;
	//bool skill2;
	bool isSoldierSkill;
	bool isSamuraiSkill1;
	bool isSamuraiSkill2;
	bool isSoldierSkillCool;
	bool isSamuraiSkillCool1;
	bool isSamuraiSkillCool2;
	int skillEfect1;
	int skillEfect2;
	int skillEfect3;
	int skillEfect4;
	int skillEfect5;
	bool isCounter;
	bool isAttecked;
	//교대
	bool isChange;
	int ChangeCount;

	//충돌
	float ptRight;
	float ptLeft;
	float ptTop;
	float ptBottom;
	RECT rcRight;
	RECT rcLeft;
	RECT rcTop;
	RECT rcBottom;
	bool isColl;
	bool isTouch;

	bool isRightPixel;
	bool isLeftPixel;
	
	//플레이어 카메라
	//RECT rcPlayerCamera;

	bool isLeft;
	int animationCount;
	int animationIndex;

	//머리있는 이미지
	image* playerStartImg;
	image* playerRunImg;
	image* playerIdleImg;
	image* playerJumpImg;
	image* playerDashImg;
	image* playerDashEfectImg1;
	image* playerAttImg1;
	image* playerAttImg2;
	image* playerJumpAttImg;
	image* playerchangeImg;
	image* playerSkillImg;
	image* playerSkill_RImg;
	image* playerSkill_LImg;
	
	//머리없는 이미지
	image* nonRunImg;
	image* nonIdleImg;
	image* nonJumpImg;
	image* nonDashImg;
	image* nonDashEfectImg;
	image* nonAttImg1;
	image* nonAttImg2;
	image* nonJumpAttImg;
	//병사해골 이미지
	image* soldierRunImg;
	image* soldierIdleImg;
	image* soldierJumpImg;
	image* soldierDashImg;
	image* soldierDashEfectImg;
	image* soldierAttImg;
	image* soldierJumpAttImg;
	image* soldierChangeImg;
	image* soldierSkillImg;
	
	//사무라이해골 이미지
	image* samuraiRunImg;
	image* samuraiIdleImg;
	image* samuraiJumpImg;
	image* samuraiDashImg;
	image* samuraiDashEfectImg;
	image* samuraiAttImg1;
	image* samuraiAttImg2;
	image* samuraiAttImg3;
	image* samuraiJumpAttImg;
	image* samuraiChangeImg;
	image* samuraiSkillImg_1;
	image* samuraiSkillImg_2;
	image* samuraiNapdoImg;
	image* samuraiSignImg;
	
	image* samuraiNap_E;
	

	image* castleWall1;

	bool isMove;

	RECT rcFront;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void skulAnimation();
	void soldierAnimation();
	void samuraiAnimation();
	void PixelCollision();
	void playerMove();
	void playerCooldown();
	void setPlayer();
	void EnemyPlayerATK();
	void BossPlayerATK();

	bool getIsJump() { return isJump; }
	bool getIsLeft() { return isLeft; }
	bool getIsDash() { return isDash; }
	RECT getRcPlayer() { return rcPlayer; }
	RECT getRcRight() { return rcRight; }
	RECT getRcLeft() { return rcLeft; }
	RECT getRcBottom() { return rcBottom; }
	RECT getRcTop() { return rcTop; }
	int getPlayerMexHp() { return playerMexHp; }
	int getPlayerCurrentHp() { return playerCurrentHp; }
	int getSkulCooldown1() { return skulCooldown_1; }
	int getSkulCooldown2() { return skulCooldown_2; }
	int getSoldierCooldown1() { return soldierCooldown_1; }
	int getSamuraiCooldown1() { return samuraiCooldown_1; }
	int getSamuraiCooldown2() { return samuraiCooldown_2; }
	int getSkillCooldowsMax() { return CooldownMax; }
	bool getSkulSkill1() { return isSkulSkill1; }
	bool getSkulSkill2() { return isSkulSkill2; }
	bool getSoldierSkill1() { return isSoldierSkillCool; }
	bool getSamuraiSkill1() { return isSamuraiSkillCool1; }
	bool getSamuraiSkill2() { return isSamuraiSkillCool2; }
	RECT getRcATK() { return rcATK; }
	bool getIsATK() { return isATK; }
	int getPlayerATK() { return playerATK; }
	float getPlayerX() { return playerX; }
	float getPlayerY() { return playerY; }
	RECT getRcSkill() { return rcSkill; }

	void setPlayerY(float Y) { playerY = Y; }
	void setPlayerX(float X) { playerX = X; }
	void setJumpSpeed(float speed) { jumpSpeed = speed; }
	void setPlayerSpeed(float speed) { playerSpeed = speed; }
	void setGravity(float gv) { gravity = gv; }
	void setIsJump(bool jump) { isJump = jump; }
	void setState(PLAYERSTATE state) { _playerState = state; }
	void setJumpCount(int count) { jumpCount = count; }
	void setIsColl(bool coll) { isColl = coll; }
	void setPtEnemy(enemy* pt) { ptPlayerEnemy = pt; }
	void setPtBoss(boss* pt) { ptPlayerBoss = pt; }
};

