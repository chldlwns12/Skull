#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	playerRunImg = IMAGEMANAGER->findImage("일반해골달리기");
	playerIdleImg = IMAGEMANAGER->findImage("일반해골IDLE");
	playerJumpImg = IMAGEMANAGER->findImage("일반해골점프");
	playerAttImg1 = IMAGEMANAGER->findImage("일반해골공격1");
	playerAttImg2 = IMAGEMANAGER->findImage("일반해골공격2");
	playerDashImg = IMAGEMANAGER->findImage("일반해골대쉬");
	playerDashEfectImg1 = IMAGEMANAGER->findImage("일반해골대쉬효과");
	playerStartImg = IMAGEMANAGER->findImage("시작");
	playerchangeImg = IMAGEMANAGER->findImage("일반해골교대");
	playerJumpAttImg = IMAGEMANAGER->findImage("일반해골점프공격");
	playerSkillImg = IMAGEMANAGER->findImage("일반해골스킬");
	playerSkill_RImg = IMAGEMANAGER->findImage("일반해골스킬_오른쪽");
	playerSkill_LImg = IMAGEMANAGER->findImage("일반해골스킬_왼쪽");

	nonRunImg = IMAGEMANAGER->findImage("머리없는달리기");
	nonIdleImg = IMAGEMANAGER->findImage("머리없는IDLE");
	nonJumpImg = IMAGEMANAGER->findImage("머리없는점프");
	nonAttImg1 = IMAGEMANAGER->findImage("머리없는공격1");
	nonAttImg2 = IMAGEMANAGER->findImage("머리없는공격2");
	nonDashImg = IMAGEMANAGER->findImage("머리없는대쉬");
	nonDashEfectImg = IMAGEMANAGER->findImage("머리없는대쉬효과");
	nonJumpAttImg = IMAGEMANAGER->findImage("머리없는점프공격");

	soldierRunImg = IMAGEMANAGER->findImage("해골병사달리기");
	soldierIdleImg = IMAGEMANAGER->findImage("해골병사IDLE");
	soldierJumpImg = IMAGEMANAGER->findImage("해골병사점프");
	soldierAttImg = IMAGEMANAGER->findImage("해골병사공격");
	soldierDashImg = IMAGEMANAGER->findImage("해골병사대쉬");
	soldierDashEfectImg = IMAGEMANAGER->findImage("해골병사대쉬효과");
	soldierChangeImg = IMAGEMANAGER->findImage("해골병사교대");
	soldierJumpAttImg = IMAGEMANAGER->findImage("해골병사점프공격");
	soldierSkillImg = IMAGEMANAGER->findImage("해골병사스킬");

	samuraiRunImg = IMAGEMANAGER->findImage("사무라이달리기");
	samuraiIdleImg = IMAGEMANAGER->findImage("사무라이IDLE");
	samuraiJumpImg = IMAGEMANAGER->findImage("사무라이점프");
	samuraiAttImg1 = IMAGEMANAGER->findImage("사무라이공격1");
	samuraiAttImg2 = IMAGEMANAGER->findImage("사무라이공격2");
	samuraiAttImg3 = IMAGEMANAGER->findImage("사무라이공격3");
	samuraiDashImg = IMAGEMANAGER->findImage("사무라이대쉬");
	samuraiDashEfectImg = IMAGEMANAGER->findImage("사무라이대쉬효과");
	samuraiChangeImg = IMAGEMANAGER->findImage("사무라이교대");
	samuraiJumpAttImg = IMAGEMANAGER->findImage("사무라이점프공격");
	samuraiSkillImg_1 = IMAGEMANAGER->findImage("사무라이스킬1");
	samuraiSkillImg_2 = IMAGEMANAGER->findImage("사무라이스킬2");
	samuraiNapdoImg = IMAGEMANAGER->findImage("사무라이납도");
	samuraiSignImg = IMAGEMANAGER->findImage("사무라이표식이펙트");
	samuraiSkill1_E = IMAGEMANAGER->findImage("사무라이스킬1이펙트");
	samuraiNap_E = IMAGEMANAGER->findImage("사무라이납도이펙트");

	
	castleWall1 = IMAGEMANAGER->findImage("맵1_성벽1");

	playerX = WINSIZEX / 2;
	playerY = 563.f;

	playerMexHp = 150;
	playerCurrentHp = 150;
	jumpSpeed = 0.f;
	playerSpeed = 10.f;
	gravity = 0.f;
	jumpCount = 0;
	attCount = 0;
	attIndex = 0;
	isJump = false;
	_playerState = PLAYER_START;
	animationCount = 0;
	animationIndex = 0;
	isLeft = false;
	//공격
	isEndAtt1 = true;
	isEndAtt2 = true;
	isEndAtt3 = true;
	//isAtt1 = false;
	//isAtt2 = false;
	//isAtt3 = false;
	Att1CoolDown = 0;
	Att2CoolDown = 0;
	Att3CoolDown = 0;
	isAttCool = false;
	//대쉬
	Efect1 = 0;
	Efect2 = 0;
	Efect3 = 0;
	Efect4 = 0;
	Efect5 = 0;
	isDash = false;
	dashCooldown = 0;
	dashCount = 0;
	//스킬
	saveX = 0;
	skulCooldown_1 = 0;
	skulCooldown_2 = 0;
	soldierCooldown_1 = 0;
	samuraiCooldown_1 = 0;
	samuraiCooldown_2 = 0;
	CooldownMax = 500;
	changeCooldown = 0;
	Head = new Skul;
	Head->init(1, 500, ROTATERENDER);
	headAngle = 0.f;
	isSkulSkill1 = false;
	isSkulSkill2 = false;
	isSoldierSkillCool = false;
	isSamuraiSkillCool1 = false;
	isSamuraiSkillCool2 = false;
	isSoldierSkill = false;
	DATA->setIsSoldierSkill(false);
	isSamuraiSkill1 = false;
	DATA->setIsSamuraiSkill1(false);
	isSamuraiSkill2 = false;
	DATA->setIsSamuraiSkill2(false);
	skillEfect1 = 0;
	skillEfect2 = 0;
	skillEfect3 = 0;
	skillEfect4 = 0;
	skillEfect5 = 0;
	napdoCount = napdoIndex = 0;
	isCounter = false;
	isAttecked = false;
	//교대
	isChange = false;
	DATA->setIsChange(false);
	ChangeCount = 0;

	isColl = true;
	isMove = false;

	rcFront = RectMake(0, 0, 1588, 720);

	isRightPixel = false;
	isLeftPixel = false;

	moveX = moveY = 0;

	DATA->setHaveRuin(SKUL, 0);
	DATA->setHaveRuin(NON, 1);
	
	return S_OK;
}

void player::release()
{
	Head->release();
}

void player::update()
{
	this->setPlayer();
	this->playerMove();
	this->playerCooldown();
	this->PixelCollision();
	if (DATA->getPlayerRuin() == SKUL)
	{
		this->skulAnimation();
	}
	if (DATA->getPlayerRuin() == SOLDIER)
	{
		this->soldierAnimation();
	}
	if (DATA->getPlayerRuin() == SAMURAI)
	{
		this->samuraiAnimation();
	}
}

void player::render()
{
	//Rectangle(getMemDC(), DATA->getPlayerCamera().rcCamera);
	//Rectangle(getMemDC(), DATA->getPlayerRc());
	if (DATA->getPlayerRuin() == SKUL)
	{
		if (isSkulSkill1 == true)
		{
			if (_playerState == PLAYER_RUN)
			{
				nonRunImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top);
			}
			if (_playerState == PLAYER_IDLE)
			{
				nonIdleImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top + 15);
			}
			if (_playerState == PLAYER_JUMP)
			{
				nonJumpImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top);
			}
			if (_playerState == PLAYER_DOUBLEJUMP)
			{
				nonJumpImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top);
			}
			if (_playerState == PLAYER_ATT)
			{
				nonAttImg1->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top - 30);
			}
			if (_playerState == PLAYER_ATT2)
			{
				nonAttImg2->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top - 30);
			}
			if (_playerState == PLAYER_JUMPATT)
			{
				nonJumpAttImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top - 30);
			}
			if (_playerState == PLAYER_DASH)
			{
				if (isLeft)
				{
					nonDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left + 20, rcPlayer.top + 10, Efect1);
					if (Efect1 >= 20)
					{
						nonDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left + 40, rcPlayer.top + 10, Efect2);
					}
					if (Efect2 >= 20)
					{
						nonDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left + 60, rcPlayer.top + 10, Efect2);
					}
					if (Efect3 >= 20)
					{
						nonDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left + 80, rcPlayer.top + 10, Efect2);
					}
					if (Efect4 >= 20)
					{
						nonDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left + 100, rcPlayer.top + 10, Efect2);
					}
				}
				else
				{
					nonDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left - 20, rcPlayer.top + 10, Efect1);
					if (Efect1 >= 20)
					{
						nonDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left - 40, rcPlayer.top + 10, Efect2);
					}
					if (Efect2 >= 20)
					{
						nonDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left - 60, rcPlayer.top + 10, Efect2);
					}
					if (Efect3 >= 20)
					{
						nonDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left - 80, rcPlayer.top + 10, Efect2);
					}
					if (Efect4 >= 20)
					{
						nonDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left - 100, rcPlayer.top + 10, Efect2);
					}
				}
				nonDashImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top + 10);
			}
		}
		else
		{
			if (_playerState == PLAYER_START)
			{
				playerStartImg->frameRender(getMemDC(), rcPlayer.left - 158, rcPlayer.top - 62);
			}
			if (_playerState == PLAYER_RUN)
			{
				playerRunImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top);
			}
			if (_playerState == PLAYER_IDLE)
			{
				playerIdleImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top);
			}
			if (_playerState == PLAYER_JUMP)
			{
				playerJumpImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top);
			}
			if (_playerState == PLAYER_DOUBLEJUMP)
			{
				playerJumpImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top);
			}
			if (_playerState == PLAYER_ATT)
			{
				playerAttImg1->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top - 30);
			}
			if (_playerState == PLAYER_ATT2)
			{
				playerAttImg2->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top - 30);
			}
			if (_playerState == PLAYER_JUMPATT)
			{
				playerJumpAttImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top - 30);
			}
			if (_playerState == PLAYER_DASH)
			{
				if (isLeft)
				{
					playerDashEfectImg1->alphaFrameRender(getMemDC(), rcPlayer.left + 20, rcPlayer.top + 10, Efect1);
					if (Efect1 >= 20)
					{
						playerDashEfectImg1->alphaFrameRender(getMemDC(), rcPlayer.left + 40, rcPlayer.top + 10, Efect2);
					}
					if (Efect2 >= 20)
					{
						playerDashEfectImg1->alphaFrameRender(getMemDC(), rcPlayer.left + 60, rcPlayer.top + 10, Efect2);
					}
					if (Efect3 >= 20)
					{
						playerDashEfectImg1->alphaFrameRender(getMemDC(), rcPlayer.left + 80, rcPlayer.top + 10, Efect2);
					}
					if (Efect4 >= 20)
					{
						playerDashEfectImg1->alphaFrameRender(getMemDC(), rcPlayer.left + 100, rcPlayer.top + 10, Efect2);
					}
				}
				else
				{
					playerDashEfectImg1->alphaFrameRender(getMemDC(), rcPlayer.left - 20, rcPlayer.top + 10, Efect1);
					if (Efect1 >= 20)
					{
						playerDashEfectImg1->alphaFrameRender(getMemDC(), rcPlayer.left - 40, rcPlayer.top + 10, Efect2);
					}
					if (Efect2 >= 20)
					{
						playerDashEfectImg1->alphaFrameRender(getMemDC(), rcPlayer.left - 60, rcPlayer.top + 10, Efect2);
					}
					if (Efect3 >= 20)
					{
						playerDashEfectImg1->alphaFrameRender(getMemDC(), rcPlayer.left - 80, rcPlayer.top + 10, Efect2);
					}
					if (Efect4 >= 20)
					{
						playerDashEfectImg1->alphaFrameRender(getMemDC(), rcPlayer.left - 100, rcPlayer.top + 10, Efect2);
					}
				}
				playerDashImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top + 10);
			}

		}
		if (_playerState == PLAYER_SKILL1)
		{
			playerSkillImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top);
		}
		if (_playerState == PLAYER_CHANGE)
		{
			playerchangeImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top - 23);
		}
		Head->render();
	}
	if (DATA->getPlayerRuin() == SOLDIER)
	{
		if (_playerState == PLAYER_RUN)
		{
			soldierRunImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top - 10);
		}
		if (_playerState == PLAYER_IDLE)
		{
			soldierIdleImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top - 10);
		}
		if (_playerState == PLAYER_JUMP)
		{
			soldierJumpImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top);
		}
		if (_playerState == PLAYER_DOUBLEJUMP)
		{
			soldierJumpImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top);
		}
		if (_playerState == PLAYER_ATT)
		{
			soldierAttImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top - 30);
		}
		if (_playerState == PLAYER_JUMPATT)
		{
			soldierJumpAttImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top - 30);
		}
		if (_playerState == PLAYER_SKILL1)
		{ 
			if (isLeft)
			{
				soldierSkillImg->alphaFrameRender(getMemDC(), rcPlayer.left + 20, rcPlayer.top - 30, skillEfect1);
				if (skillEfect1 >= 20)
				{
					soldierSkillImg->alphaFrameRender(getMemDC(), rcPlayer.left + 40, rcPlayer.top - 30, skillEfect2);
				}
				if (skillEfect2 >= 20)
				{
					soldierSkillImg->alphaFrameRender(getMemDC(), rcPlayer.left + 60, rcPlayer.top - 30, skillEfect2);
				}
				if (skillEfect3 >= 20)
				{
					soldierSkillImg->alphaFrameRender(getMemDC(), rcPlayer.left + 80, rcPlayer.top - 30, skillEfect2);
				}
				if (skillEfect4 >= 20)
				{
					soldierSkillImg->alphaFrameRender(getMemDC(), rcPlayer.left + 100, rcPlayer.top - 30, skillEfect2);
				}
			}
			else
			{
				soldierSkillImg->alphaFrameRender(getMemDC(), rcPlayer.left - 20, rcPlayer.top - 30, skillEfect1);
				if (skillEfect1 >= 20)
				{
					soldierSkillImg->alphaFrameRender(getMemDC(), rcPlayer.left - 40, rcPlayer.top - 30, skillEfect2);
				}
				if (skillEfect2 >= 20)
				{
					soldierSkillImg->alphaFrameRender(getMemDC(), rcPlayer.left - 60, rcPlayer.top - 30, skillEfect2);
				}
				if (skillEfect3 >= 20)
				{
					soldierSkillImg->alphaFrameRender(getMemDC(), rcPlayer.left - 80, rcPlayer.top - 30, skillEfect2);
				}
				if (skillEfect4 >= 20)
				{
					soldierSkillImg->alphaFrameRender(getMemDC(), rcPlayer.left - 100, rcPlayer.top - 30, skillEfect2);
				}
			}
			soldierSkillImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top - 30);
		}
		if (_playerState == PLAYER_DASH)
		{
			if (isLeft)
			{
				soldierDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left + 20, rcPlayer.top + 10, Efect1);
				if (Efect1 >= 20)
				{
					soldierDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left + 40, rcPlayer.top + 10, Efect2);
				}
				if (Efect2 >= 20)
				{
					soldierDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left + 60, rcPlayer.top + 10, Efect2);
				}
				if (Efect3 >= 20)
				{
					soldierDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left + 80, rcPlayer.top + 10, Efect2);
				}
				if (Efect4 >= 20)
				{
					soldierDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left + 100, rcPlayer.top + 10, Efect2);
				}
			}
			else
			{
				soldierDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left - 20, rcPlayer.top + 10, Efect1);
				if (Efect1 >= 20)
				{
					soldierDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left - 40, rcPlayer.top + 10, Efect2);
				}
				if (Efect2 >= 20)
				{
					soldierDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left - 60, rcPlayer.top + 10, Efect2);
				}
				if (Efect3 >= 20)
				{
					soldierDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left - 80, rcPlayer.top + 10, Efect2);
				}
				if (Efect4 >= 20)
				{
					soldierDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left - 100, rcPlayer.top + 10, Efect2);
				}
			}
			soldierDashImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top + 10);
		}
	}
	if (DATA->getPlayerRuin() == SAMURAI)
	{
		if (_playerState == PLAYER_RUN)
		{
			samuraiRunImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top - 10);
		}
		if (_playerState == PLAYER_IDLE)
		{
			samuraiIdleImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top - 10);
		}
		if (_playerState == PLAYER_JUMP)
		{
			samuraiJumpImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top);
		}
		if (_playerState == PLAYER_DOUBLEJUMP)
		{
			samuraiJumpImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top);
		}
		if (_playerState == PLAYER_ATT)
		{
			samuraiAttImg1->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top - 15);
		}
		if (_playerState == PLAYER_ATT2)
		{
			samuraiAttImg2->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top - 25);
		}
		if (_playerState == PLAYER_ATT3)
		{
			samuraiAttImg3->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top - 20);
		}
		if (_playerState == PLAYER_JUMPATT)
		{
			if (isLeft)
			{
				samuraiJumpAttImg->frameRender(getMemDC(), rcPlayer.left - 30, rcPlayer.top - 30);
			}
			else
			{
				samuraiJumpAttImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top - 30);
			}
		}
		if (_playerState == PLAYER_SKILL1)
		{
			if (isSamuraiSkill1)
			{
				if (isLeft)
				{
					samuraiSkillImg_1->alphaFrameRender(getMemDC(), rcPlayer.left + 20, rcPlayer.top - 15, skillEfect1);
					if (skillEfect1 >= 20)
					{
						samuraiSkillImg_1->alphaFrameRender(getMemDC(), rcPlayer.left + 40, rcPlayer.top - 15, skillEfect2);
					}
					if (skillEfect2 >= 20)
					{
						samuraiSkillImg_1->alphaFrameRender(getMemDC(), rcPlayer.left + 60, rcPlayer.top - 15, skillEfect2);
					}
					if (skillEfect3 >= 20)
					{
						samuraiSkillImg_1->alphaFrameRender(getMemDC(), rcPlayer.left + 80, rcPlayer.top - 15, skillEfect2);
					}
					if (skillEfect4 >= 20)
					{
						samuraiSkillImg_1->alphaFrameRender(getMemDC(), rcPlayer.left + 100, rcPlayer.top - 15, skillEfect2);
					}
				}
				else
				{
					samuraiSkillImg_1->alphaFrameRender(getMemDC(), rcPlayer.left - 20, rcPlayer.top - 15, skillEfect1);
					if (skillEfect1 >= 20)
					{
						samuraiSkillImg_1->alphaFrameRender(getMemDC(), rcPlayer.left - 40, rcPlayer.top - 15, skillEfect2);
					}
					if (skillEfect2 >= 20)
					{
						samuraiSkillImg_1->alphaFrameRender(getMemDC(), rcPlayer.left - 60, rcPlayer.top - 15, skillEfect2);
					}
					if (skillEfect3 >= 20)
					{
						samuraiSkillImg_1->alphaFrameRender(getMemDC(), rcPlayer.left - 80, rcPlayer.top - 15, skillEfect2);
					}
					if (skillEfect4 >= 20)
					{
						samuraiSkillImg_1->alphaFrameRender(getMemDC(), rcPlayer.left - 100, rcPlayer.top - 15, skillEfect2);
					}
				}
			}
			samuraiSkillImg_1->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top - 15 );
		}
		if (_playerState == PLAYER_SKILL2)
		{
			samuraiSkillImg_2->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top - 15);
		}
		if (_playerState == PLAYER_DASH)
		{
			if (isLeft)
			{
				samuraiDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left + 20, rcPlayer.top + 10, Efect1);
				if (Efect1 >= 20)
				{
					samuraiDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left + 40, rcPlayer.top + 10, Efect2);
				}
				if (Efect2 >= 20)
				{
					samuraiDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left + 60, rcPlayer.top + 10, Efect2);
				}
				if (Efect3 >= 20)
				{
					samuraiDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left + 80, rcPlayer.top + 10, Efect2);
				}
				if (Efect4 >= 20)
				{
					samuraiDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left + 100, rcPlayer.top + 10, Efect2);
				}
			}
			else
			{
				samuraiDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left - 20, rcPlayer.top + 10, Efect1);
				if (Efect1 >= 20)
				{
					samuraiDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left - 40, rcPlayer.top + 10, Efect2);
				}
				if (Efect2 >= 20)
				{
					samuraiDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left - 60, rcPlayer.top + 10, Efect2);
				}
				if (Efect3 >= 20)
				{
					samuraiDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left - 80, rcPlayer.top + 10, Efect2);
				}
				if (Efect4 >= 20)
				{
					samuraiDashEfectImg->alphaFrameRender(getMemDC(), rcPlayer.left - 100, rcPlayer.top + 10, Efect2);
				}
			}
			samuraiDashImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top + 10);
		}
		if (_playerState == PLAYER_NAPDO)
		{
			samuraiNapdoImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top - 10);
		}
		if (_playerState == PLAYER_CHANGE)
		{
			samuraiChangeImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top - 10);
		}
	}

	if (DATA->getStage() == STAGE_1)
	{
		castleWall1->render(getMemDC(), DATA->getPixelGround().x, DATA->getPixelGround().y - 700);
	}
	if (DATA->getStage() == STAGE_1_2)
	{
		DATA->getBackGround().img->render(getMemDC(), rcFront.left, rcFront.top);
	}

	
	//samuraiSkillImg_1->frameRender(getMemDC(), 0, 0,0,0);
	//Rectangle(getMemDC(), rcRight);
	//Rectangle(getMemDC(), rcLeft);
	//Rectangle(getMemDC(), rcBottom);
	//Rectangle(getMemDC(), rcTop);

	char str[100];
	char str2[100];
	char str3[100];
	char str4[100];
	char str5[100];
	char str6[100];
	char str7[100];

	sprintf(str, "Skul1 : %d", skulCooldown_1);
	TextOut(getMemDC(), 10, 90, str, strlen(str));
	sprintf(str2, "Skul2 : %d", skulCooldown_2);
	TextOut(getMemDC(), 10, 110, str2, strlen(str2));
	sprintf(str3, "Soldier : %d", soldierCooldown_1);
	TextOut(getMemDC(), 10, 130, str3, strlen(str3));
	sprintf(str6, "Samurai1 : %d", samuraiCooldown_1);
	TextOut(getMemDC(), 10, 150, str6, strlen(str6));
	sprintf(str4, "Samurai2 : %d", samuraiCooldown_2);
	TextOut(getMemDC(), 10, 170, str4, strlen(str4));
	sprintf(str5, "maxCool : %d", CooldownMax);
	TextOut(getMemDC(), 10, 190, str5, strlen(str5));
	sprintf(str7, "bottom : %d", isDash);
	TextOut(getMemDC(), 10, 210, str7, strlen(str7));
}

void player::skulAnimation()
{
	if (isSkulSkill1 == false)
	{
		switch (_playerState)
		{
		case PLAYER_IDLE:
			animationCount++;
			if (isLeft == false)
			{
				playerIdleImg->setFrameY(0);
				if (animationCount % 7 == 0)
				{
					animationIndex++;
					if (animationIndex > 4)
					{
						animationIndex = 0;
					}
					playerIdleImg->setFrameX(animationIndex);
				}
			}
			else
			{
				playerIdleImg->setFrameY(1);
				if (animationCount % 7 == 0)
				{
					animationIndex--;
					if (animationIndex < 0)
					{
						animationIndex = 4;
					}
					playerIdleImg->setFrameX(animationIndex);
				}
			}
			break;
		case PLAYER_RUN:
			animationCount++;
			if (isLeft == false)
			{
				playerRunImg->setFrameY(0);
				if (animationCount % 4 == 0)
				{
					animationIndex++;
					if (animationIndex > 8)
					{
						animationIndex = 0;
					}
					playerRunImg->setFrameX(animationIndex);
				}
			}
			else
			{
				playerRunImg->setFrameY(1);
				if (animationCount % 4 == 0)
				{
					animationIndex--;
					if (animationIndex < 0)
					{
						animationIndex = 8;
					}
					playerRunImg->setFrameX(animationIndex);
				}
			}
			break;
		case PLAYER_JUMP:
			animationCount++;
			if (isLeft == false)
			{
				playerJumpImg->setFrameY(0);
				if (animationCount % 6 == 0)
				{
					animationIndex++;
					if (animationIndex > 7)
					{
						animationIndex = 4;
					}
					playerJumpImg->setFrameX(animationIndex);
				}
			}
			else
			{
				playerJumpImg->setFrameY(1);
				if (animationCount % 6 == 0)
				{
					animationIndex--;
					if (animationIndex < 0)
					{
						animationIndex = 2;
					}
					playerJumpImg->setFrameX(animationIndex);
				}
			}
			break;
		case PLAYER_DOUBLEJUMP:
			animationCount++;
			if (isLeft == false)
			{
				playerJumpImg->setFrameY(0);
				if (animationCount % 6 == 0)
				{
					animationIndex++;
					if (animationIndex > 7)
					{
						animationIndex = 5;
					}
					playerJumpImg->setFrameX(animationIndex);
				}
			}
			else
			{
				playerJumpImg->setFrameY(1);
				if (animationCount % 6 == 0)
				{
					animationIndex--;
					if (animationIndex < 0)
					{
						animationIndex = 7;
					}
					playerJumpImg->setFrameX(animationIndex);
				}
			}
			break;
		case PLAYER_ATT:
			animationCount++;
			if (isLeft == false)
			{
				playerAttImg1->setFrameY(0);
				if (animationCount % 5 == 0)
				{
					animationIndex++;
					if (animationIndex > 5)
					{
						animationIndex = 5;
						isEndAtt1 = true;
					}
					playerAttImg1->setFrameX(animationIndex);
				}
			}
			else
			{
				playerAttImg1->setFrameY(1);
				if (animationCount % 5 == 0)
				{
					animationIndex--;
					if (animationIndex < 0)
					{
						animationIndex = 0;
						isEndAtt1 = true;
					}
					playerAttImg1->setFrameX(animationIndex);
				}
			}
			break;
		case PLAYER_ATT2:
			animationCount++;
			if (isLeft == false)
			{
				playerAttImg2->setFrameY(0);
				if (animationCount % 5 == 0)
				{
					animationIndex++;
					if (animationIndex > 3)
					{
						animationIndex = 3;
						isEndAtt2 = false;
					}
					playerAttImg2->setFrameX(animationIndex);
				}
			}
			else
			{
				playerAttImg2->setFrameY(1);
				if (animationCount % 5 == 0)
				{
					animationIndex--;
					if (animationIndex < 0)
					{
						animationIndex = 0;
						isEndAtt2 = false;
					}
					playerAttImg2->setFrameX(animationIndex);
				}
			}
			break;
		case PLAYER_DASH:
			if (isLeft == false)
			{
				playerDashImg->setFrameY(0);
				playerDashImg->setFrameX(1);
				playerDashEfectImg1->setFrameY(0);
				playerDashEfectImg1->setFrameX(1);
			}
			else
			{
				playerDashImg->setFrameY(1);
				playerDashImg->setFrameX(1);
				playerDashEfectImg1->setFrameY(1);
				playerDashEfectImg1->setFrameX(1);
			}
			break;
		case PLAYER_START:
			animationCount++;
			playerStartImg->setFrameY(0);
			if (animationCount % 5 == 0)
			{
				animationIndex++;
				if (animationIndex > 27)
				{
					_playerState = PLAYER_IDLE;
				}
				playerStartImg->setFrameX(animationIndex);
			}
			break;
		case PLAYER_JUMPATT:
			animationCount++;
			if (isLeft == false)
			{
				playerJumpAttImg->setFrameY(0);
				if (animationCount % 5 == 0)
				{
					animationIndex++;
					if (animationIndex > 4)
					{
						animationIndex = 4;
					}
					playerJumpAttImg->setFrameX(animationIndex);
				}
			}
			else
			{
				playerJumpAttImg->setFrameY(1);
				if (animationCount % 5 == 0)
				{
					animationIndex--;
					if (animationIndex < 0)
					{
						animationIndex = 0;
					}
					playerJumpAttImg->setFrameX(animationIndex);
				}
			}
			break;
		case PLAYER_CHANGE:
			animationCount++;
			if (isLeft == false)
			{
				playerchangeImg->setFrameY(0);
				if (animationCount % 5 == 0)
				{
					animationIndex++;
					if (animationIndex > 6)
					{
						ChangeCount++;
						animationIndex = 0;
						if (ChangeCount > 2)
						{
							_playerState = PLAYER_IDLE;
							isChange = false;
							DATA->setIsChange(false);
							ChangeCount = 0;
						}
					}
					playerchangeImg->setFrameX(animationIndex);
				}
			}
			else
			{
				playerchangeImg->setFrameY(1);
				if (animationCount % 5 == 0)
				{
					animationIndex--;
					if (animationIndex < 0)
					{
						ChangeCount++;
						animationIndex = 6;
						if (ChangeCount > 2)
						{
							_playerState = PLAYER_IDLE;
							isChange = false;
							DATA->setIsChange(false);
							ChangeCount = 0;
						}
					}
					playerchangeImg->setFrameX(animationIndex);
				}
			}
			break;
		}
	}
	else
	{
		switch (_playerState)
		{
		case PLAYER_IDLE:
			animationCount++;
			if (isLeft == false)
			{
				nonIdleImg->setFrameY(0);
				if (animationCount % 7 == 0)
				{
					animationIndex++;
					if (animationIndex > 4)
					{
						animationIndex = 0;
					}
					nonIdleImg->setFrameX(animationIndex);
				}
			}
			else
			{
				nonIdleImg->setFrameY(1);
				if (animationCount % 7 == 0)
				{
					animationIndex--;
					if (animationIndex < 0)
					{
						animationIndex = 4;
					}
					nonIdleImg->setFrameX(animationIndex);
				}
			}
			break;
		case PLAYER_RUN:
			animationCount++;
			if (isLeft == false)
			{
				nonRunImg->setFrameY(0);
				if (animationCount % 4 == 0)
				{
					animationIndex++;
					if (animationIndex > 8)
					{
						animationIndex = 0;
					}
					nonRunImg->setFrameX(animationIndex);
				}
			}
			else
			{
				nonRunImg->setFrameY(1);
				if (animationCount % 4 == 0)
				{
					animationIndex--;
					if (animationIndex < 0)
					{
						animationIndex = 8;
					}
					nonRunImg->setFrameX(animationIndex);
				}
			}
			break;
		case PLAYER_JUMP:
			animationCount++;
			if (isLeft == false)
			{
				nonJumpImg->setFrameY(0);
				if (animationCount % 6 == 0)
				{
					animationIndex++;
					if (animationIndex > 7)
					{
						animationIndex = 4;
					}
					nonJumpImg->setFrameX(animationIndex);
				}
			}
			else
			{
				nonJumpImg->setFrameY(1);
				if (animationCount % 6 == 0)
				{
					animationIndex--;
					if (animationIndex < 0)
					{
						animationIndex = 2;
					}
					nonJumpImg->setFrameX(animationIndex);
				}
			}
			break;
		case PLAYER_DOUBLEJUMP:
			animationCount++;
			if (isLeft == false)
			{
				nonJumpImg->setFrameY(0);
				if (animationCount % 6 == 0)
				{
					animationIndex++;
					if (animationIndex > 7)
					{
						animationIndex = 5;
					}
					nonJumpImg->setFrameX(animationIndex);
				}
			}
			else
			{
				nonJumpImg->setFrameY(1);
				if (animationCount % 6 == 0)
				{
					animationIndex--;
					if (animationIndex < 0)
					{
						animationIndex = 7;
					}
					nonJumpImg->setFrameX(animationIndex);
				}
			}
			break;
		case PLAYER_ATT:
			animationCount++;
			if (isLeft == false)
			{
				nonAttImg1->setFrameY(0);
				if (animationCount % 5 == 0)
				{
					animationIndex++;
					if (animationIndex > 5)
					{
						animationIndex = 5;
						isEndAtt1 = true;
					}
					nonAttImg1->setFrameX(animationIndex);
				}
			}
			else
			{
				nonAttImg1->setFrameY(1);
				if (animationCount % 5 == 0)
				{
					animationIndex--;
					if (animationIndex < 0)
					{
						animationIndex = 0;
						isEndAtt1 = true;
					}
					nonAttImg1->setFrameX(animationIndex);
				}
			}
			break;
		case PLAYER_ATT2:
			animationCount++;
			if (isLeft == false)
			{
				nonAttImg2->setFrameY(0);
				if (animationCount % 5 == 0)
				{
					animationIndex++;
					if (animationIndex > 3)
					{
						animationIndex = 3;
						isEndAtt1 = false;
					}
					nonAttImg2->setFrameX(animationIndex);
				}
			}
			else
			{
				nonAttImg2->setFrameY(1);
				if (animationCount % 5 == 0)
				{
					animationIndex--;
					if (animationIndex < 0)
					{
						animationIndex = 0;
						isEndAtt1 = false;
					}
					nonAttImg2->setFrameX(animationIndex);
				}
			}
			break;
		case PLAYER_DASH:
			if (isLeft == false)
			{
				nonDashImg->setFrameY(0);
				nonDashImg->setFrameX(1);
				nonDashEfectImg->setFrameY(0);
				nonDashEfectImg->setFrameX(1);
			}
			else
			{
				nonDashImg->setFrameY(1);
				nonDashImg->setFrameX(1);
				nonDashEfectImg->setFrameY(1);
				nonDashEfectImg->setFrameX(1);
			}
			break;
		case PLAYER_JUMPATT:
			animationCount++;
			if (isLeft == false)
			{
				nonJumpAttImg->setFrameY(0);
				if (animationCount % 5 == 0)
				{
					animationIndex++;
					if (animationIndex > 4)
					{
						animationIndex = 4;
					}
					nonJumpAttImg->setFrameX(animationIndex);
				}
			}
			else
			{
				nonJumpAttImg->setFrameY(1);
				if (animationCount % 5 == 0)
				{
					animationIndex--;
					if (animationIndex < 0)
					{
						animationIndex = 0;
					}
					nonJumpAttImg->setFrameX(animationIndex);
				}
			}
			break;
		}
	}

	switch (_playerState)
	{
	case PLAYER_SKILL1:
		animationCount++;
		if (isLeft == false)
		{
			playerSkillImg->setFrameY(0);
			if (animationCount % 5 == 0)
			{
				animationIndex++;
				if (animationIndex > 3)
				{
					animationIndex = 3;
					_playerState = PLAYER_IDLE;
				}
				playerSkillImg->setFrameX(animationIndex);
			}
		}
		else
		{
			playerSkillImg->setFrameY(1);
			if (animationCount % 5 == 0)
			{
				animationIndex--;
				if (animationIndex < 0)
				{
					animationIndex = 0;
					_playerState = PLAYER_IDLE;
				}
				playerSkillImg->setFrameX(animationIndex);
			}
		}
		break;
	}
}

void player::soldierAnimation()
{
	switch (_playerState)
	{
	case PLAYER_IDLE:
		animationCount++;
		if (isLeft == false)
		{
			soldierIdleImg->setFrameY(0);
			if (animationCount % 6 == 0)
			{
				animationIndex++;
				if (animationIndex > 3)
				{
					animationIndex = 0;
				}
				soldierIdleImg->setFrameX(animationIndex);
			}
		}
		else
		{
			soldierIdleImg->setFrameY(1);
			if (animationCount % 6 == 0)
			{
				animationIndex--;
				if (animationIndex < 0)
				{
					animationIndex = 3;
				}
				soldierIdleImg->setFrameX(animationIndex);
			}
		}
		break;
	case PLAYER_RUN:
		animationCount++;
		if (isLeft == false)
		{
			soldierRunImg->setFrameY(0);
			if (animationCount % 6 == 0)
			{
				animationIndex++;
				if (animationIndex > 7)
				{
					animationIndex = 0;
				}
				soldierRunImg->setFrameX(animationIndex);
			}
		}
		else
		{
			soldierRunImg->setFrameY(1);
			if (animationCount % 6 == 0)
			{
				animationIndex--;
				if (animationIndex < 0)
				{
					animationIndex = 7;
				}
				soldierRunImg->setFrameX(animationIndex);
			}
		}
		break;
	case PLAYER_JUMP:
		animationCount++;
		if (isLeft == false)
		{
			soldierJumpImg->setFrameY(0);
			if (animationCount % 6 == 0)
			{
				animationIndex++;
				if (animationIndex > 7)
				{
					animationIndex = 7;
				}
				soldierJumpImg->setFrameX(animationIndex);
			}
		}
		else
		{
			soldierJumpImg->setFrameY(1);
			if (animationCount % 6 == 0)
			{
				animationIndex--;
				if (animationIndex < 0)
				{
					animationIndex = 0;
				}
				soldierJumpImg->setFrameX(animationIndex);
			}
		}
		break;
	case PLAYER_DOUBLEJUMP:
		animationCount++;
		if (isLeft == false)
		{
			soldierJumpImg->setFrameY(0);
			if (animationCount % 6 == 0)
			{
				animationIndex++;
				if (animationIndex > 7)
				{
					animationIndex = 7;
				}
				soldierJumpImg->setFrameX(animationIndex);
			}
		}
		else
		{
			soldierJumpImg->setFrameY(1);
			if (animationCount % 6 == 0)
			{
				animationIndex--;
				if (animationIndex < 0)
				{
					animationIndex = 0;
				}
				soldierJumpImg->setFrameX(animationIndex);
			}
		}
		break;
	case PLAYER_ATT:
		animationCount++;
		if (isLeft == false)
		{
			soldierAttImg->setFrameY(0);
			if (animationCount % 5 == 0)
			{
				animationIndex++;
				if (animationIndex > 6)
				{
					animationIndex = 6;
					isEndAtt1 = true;
				}
				soldierAttImg->setFrameX(animationIndex);
			}
		}
		else
		{
			soldierAttImg->setFrameY(1);
			if (animationCount % 5 == 0)
			{
				animationIndex--;
				if (animationIndex < 0)
				{
					animationIndex = 0;
					isEndAtt1 = true;
				}
				soldierAttImg->setFrameX(animationIndex);
			}
		}
		break;
	case PLAYER_DASH:
		if (isLeft == false)
		{
			soldierDashImg->setFrameY(0);
			soldierDashImg->setFrameX(1);
			soldierDashEfectImg->setFrameY(0);
			soldierDashEfectImg->setFrameX(1);
		}
		else
		{
			soldierDashImg->setFrameY(1);
			soldierDashImg->setFrameX(1);
			soldierDashEfectImg->setFrameY(1);
			soldierDashEfectImg->setFrameX(1);
		}
		break;
	case PLAYER_JUMPATT:
		animationCount++;
		if (isLeft == false)
		{
			soldierJumpAttImg->setFrameY(0);
			if (animationCount % 5 == 0)
			{
				animationIndex++;
				if (animationIndex > 4)
				{
					animationIndex = 4;
				}
				soldierJumpAttImg->setFrameX(animationIndex);
			}
		}
		else
		{
			soldierJumpAttImg->setFrameY(1);
			if (animationCount % 5 == 0)
			{
				animationIndex--;
				if (animationIndex < 0)
				{
					animationIndex = 0;
				}
				soldierJumpAttImg->setFrameX(animationIndex);
			}
		}
		break;
	case PLAYER_SKILL1:
		animationCount++;
		if (isLeft == false)
		{
			soldierSkillImg->setFrameY(0);
			if (animationCount % 5 == 0)
			{
				animationIndex++;
				if (animationIndex > 4)
				{
					animationIndex = 4;
				}
				soldierSkillImg->setFrameX(animationIndex);
			}
		}
		else
		{
			soldierSkillImg->setFrameY(1);
			if (animationCount % 5 == 0)
			{
				animationIndex--;
				if (animationIndex < 0)
				{
					animationIndex = 0;
				}
				soldierSkillImg->setFrameX(animationIndex);
			}
		}
		break;
	case PLAYER_CHANGE:
		animationCount++;
		if (isLeft == false)
		{
			playerchangeImg->setFrameY(0);
			if (animationCount % 5 == 0)
			{
				animationIndex++;
				if (animationIndex > 2)
				{
					_playerState = PLAYER_IDLE;
				}
				playerchangeImg->setFrameX(animationIndex);
			}
		}
		else
		{
			playerchangeImg->setFrameY(1);
			if (animationCount % 5 == 0)
			{
				animationIndex--;
				if (animationIndex < 0)
				{
					_playerState = PLAYER_IDLE;
				}
				playerchangeImg->setFrameX(animationIndex);
			}
		}
		break;
	}
}

void player::samuraiAnimation()
{
	switch (_playerState)
	{
	case PLAYER_IDLE:
		animationCount++;
		if (isLeft == false)
		{
			samuraiIdleImg->setFrameY(0);
			if (animationCount % 7 == 0)
			{
				animationIndex++;
				if (animationIndex > 5)
				{
					animationIndex = 0;
				}
				samuraiIdleImg->setFrameX(animationIndex);
			}
		}
		else
		{
			samuraiIdleImg->setFrameY(1);
			if (animationCount % 7 == 0)
			{
				animationIndex--;
				if (animationIndex < 0)
				{
					animationIndex = 5;
				}
				samuraiIdleImg->setFrameX(animationIndex);
			}
		}
		break;
	case PLAYER_RUN:
		animationCount++;
		if (isLeft == false)
		{
			samuraiRunImg->setFrameY(0);
			if (animationCount % 5 == 0)
			{
				animationIndex++;
				if (animationIndex > 5)
				{
					animationIndex = 0;
				}
				samuraiRunImg->setFrameX(animationIndex);
			}
		}
		else
		{
			samuraiRunImg->setFrameY(1);
			if (animationCount % 5 == 0)
			{
				animationIndex--;
				if (animationIndex < 0)
				{
					animationIndex = 5;
				}
				samuraiRunImg->setFrameX(animationIndex);
			}
		}
		break;
	case PLAYER_JUMP:
		animationCount++;
		if (isLeft == false)
		{
			samuraiJumpImg->setFrameY(0);
			if (animationCount % 6 == 0)
			{
				animationIndex++;
				if (animationIndex > 7)
				{
					animationIndex = 7;
				}
				samuraiJumpImg->setFrameX(animationIndex);
			}
		}
		else
		{
			samuraiJumpImg->setFrameY(1);
			if (animationCount % 6 == 0)
			{
				animationIndex--;
				if (animationIndex < 0)
				{
					animationIndex = 0;
				}
				samuraiJumpImg->setFrameX(animationIndex);
			}
		}
		break;
	case PLAYER_DOUBLEJUMP:
		animationCount++;
		if (isLeft == false)
		{
			samuraiJumpImg->setFrameY(0);
			if (animationCount % 6 == 0)
			{
				animationIndex++;
				if (animationIndex > 7)
				{
					animationIndex = 7;
				}
				samuraiJumpImg->setFrameX(animationIndex);
			}
		}
		else
		{
			samuraiJumpImg->setFrameY(1);
			if (animationCount % 6 == 0)
			{
				animationIndex--;
				if (animationIndex < 0)
				{
					animationIndex = 0;
				}
				samuraiJumpImg->setFrameX(animationIndex);
			}
		}
		break;
	case PLAYER_ATT:
		animationCount++;
		if (isLeft == false)
		{
			samuraiAttImg1->setFrameY(0);
			if (animationCount % 5 == 0)
			{
				animationIndex++;
				if (animationIndex > 6)
				{
					animationIndex = 5;
					isEndAtt1 = true;
				}
				samuraiAttImg1->setFrameX(animationIndex);
			}
		}
		else
		{
			samuraiAttImg1->setFrameY(1);
			if (animationCount % 5 == 0)
			{
				animationIndex--;
				if (animationIndex < 0)
				{
					animationIndex = 0;
					isEndAtt1 = true;
				}
				samuraiAttImg1->setFrameX(animationIndex);
			}
		}
		break;
	case PLAYER_ATT2:
		animationCount++;
		if (isLeft == false)
		{
			samuraiAttImg2->setFrameY(0);
			if (animationCount % 5 == 0)
			{
				animationIndex++;
				if (animationIndex > 3)
				{
					animationIndex = 3;
					isEndAtt2 = true;
				}
				samuraiAttImg2->setFrameX(animationIndex);
			}
		}
		else
		{
			samuraiAttImg2->setFrameY(1);
			if (animationCount % 5 == 0)
			{
				animationIndex--;
				if (animationIndex < 0)
				{
					animationIndex = 0;
					isEndAtt2 = true;
				}
				samuraiAttImg2->setFrameX(animationIndex);
			}
		}
		break;
	case PLAYER_ATT3:
		animationCount++;
		if (isLeft == false)
		{
			samuraiAttImg3->setFrameY(0);
			if (animationCount % 5 == 0)
			{
				animationIndex++;
				if (animationIndex > 4)
				{
					animationIndex = 4;
					isEndAtt3 = true;
				}
				samuraiAttImg3->setFrameX(animationIndex);
			}
		}
		else
		{
			samuraiAttImg3->setFrameY(1);
			if (animationCount % 5 == 0)
			{
				animationIndex--;
				if (animationIndex < 0)
				{
					animationIndex = 0;
					isEndAtt3 = true;
				}
				samuraiAttImg3->setFrameX(animationIndex);
			}
		}
		break;
	case PLAYER_DASH:
		if (isLeft == false)
		{
			samuraiDashImg->setFrameY(0);
			samuraiDashImg->setFrameX(1);
			samuraiDashEfectImg->setFrameY(0);
			samuraiDashEfectImg->setFrameX(1);
		}
		else
		{
			samuraiDashImg->setFrameY(1);
			samuraiDashImg->setFrameX(1);
			samuraiDashEfectImg->setFrameY(1);
			samuraiDashEfectImg->setFrameX(1);
		}
		break;
	case PLAYER_JUMPATT:
		animationCount++;
		if (isLeft == false)
		{
			samuraiJumpAttImg->setFrameY(0);
			if (animationCount % 5 == 0)
			{
				animationIndex++;
				if (animationIndex > 4)
				{
					animationIndex = 4;
				}
				samuraiJumpAttImg->setFrameX(animationIndex);
			}
		}
		else
		{
			samuraiJumpAttImg->setFrameY(1);
			if (animationCount % 5 == 0)
			{
				animationIndex--;
				if (animationIndex < 0)
				{
					animationIndex = 0;
				}
				samuraiJumpAttImg->setFrameX(animationIndex);
			}
		}
		break;
	case PLAYER_SKILL1:
		animationCount++;
		if (isLeft == false)
		{
			samuraiSkillImg_1->setFrameY(0);
			if (animationCount % 5 == 0)
			{
				animationIndex++;
				if (animationIndex > 11)
				{
					//animationIndex = 11;
					_playerState = PLAYER_NAPDO;
				}
				samuraiSkillImg_1->setFrameX(animationIndex);
			}
		}
		else
		{
			samuraiSkillImg_1->setFrameY(1);
			if (animationCount % 5 == 0)
			{
				animationIndex--;
				if (animationIndex < 0)
				{
					//animationIndex = 0;
					_playerState = PLAYER_NAPDO;
				}
				samuraiSkillImg_1->setFrameX(animationIndex);
			}
		}
		break;
	case PLAYER_SKILL2:
		animationCount++;
		if (isLeft == false)
		{
			samuraiSkillImg_2->setFrameY(0);
			if (animationCount % 5 == 0)
			{
				if(isCounter == false)
				{
					animationIndex++;
				}
				if (animationIndex > 9)
				{
					//animationIndex = 9;
					_playerState = PLAYER_NAPDO;
				}
				samuraiSkillImg_2->setFrameX(animationIndex);
			}
		}
		else
		{
			samuraiSkillImg_2->setFrameY(1);
			if (animationCount % 5 == 0)
			{
				if (isCounter == false)
				{
					animationIndex--;
				}
				if (animationIndex < 0)
				{
					//animationIndex = 0;
					_playerState = PLAYER_NAPDO;
				}
				samuraiSkillImg_2->setFrameX(animationIndex);
			}
		}
		break;
	case PLAYER_NAPDO:
		napdoCount++;
		if (isLeft == false)
		{
			samuraiNapdoImg->setFrameY(0);
			if (napdoCount % 6 == 0)
			{
				napdoIndex++;
				if (napdoIndex > 9)
				{
					//napdoIndex = 9;
					_playerState = PLAYER_IDLE;
				}
				samuraiNapdoImg->setFrameX(napdoIndex);
			}
		}
		else
		{
			samuraiNapdoImg->setFrameY(1);
			if (napdoCount % 6 == 0)
			{
				napdoIndex--;
				if (napdoIndex < 0)
				{
					//napdoIndex = 0;
					_playerState = PLAYER_IDLE;
				}
				samuraiNapdoImg->setFrameX(napdoIndex);
			}
		}
		break;
	case PLAYER_CHANGE:
		animationCount++;
		if (isLeft == false)
		{
			samuraiChangeImg->setFrameY(0);
			if (animationCount % 7 == 0)
			{
				animationIndex++;
				if (animationIndex > 3)
				{
					animationIndex = 0;

					_playerState = PLAYER_IDLE;
					isChange = false;
					DATA->setIsChange(false);
				}
				samuraiChangeImg->setFrameX(animationIndex);
			}
		}
		else
		{
			samuraiChangeImg->setFrameY(1);
			if (animationCount % 7 == 0)
			{
				animationIndex--;
				if (animationIndex < 0)
				{
					animationIndex = 3;
					
					_playerState = PLAYER_IDLE;
					isChange = false;
					DATA->setIsChange(false);		
				}
				samuraiChangeImg->setFrameX(animationIndex);
			}
		}
		break;
	}
}

void player::PixelCollision()
{
	ptBottom = (playerY + (rcPlayer.bottom - rcPlayer.top) / 2) - 20;
	ptTop = (playerY - (rcPlayer.bottom - rcPlayer.top) / 2) - 20;
	ptRight = (playerX + (rcPlayer.right - rcPlayer.left) / 2) - DATA->getPixelGround().x;
	ptLeft = (playerX - (rcPlayer.right - rcPlayer.left) / 2) - DATA->getPixelGround().x;
	
	rcBottom = RectMakeCenter(playerX, ptBottom, 10, 10);
	rcRight = RectMakeCenter(ptRight, playerY, 10, 10);
	rcLeft = RectMakeCenter(ptLeft, playerY, 10, 10);
	/*이부분이 픽셀충돌의 핵심*/
	if (DATA->getStage() == START)
	{
		for (int i = ptBottom - 10; i < ptBottom + 10; i++)
		{
			COLORREF color = GetPixel(DATA->getPixelGround().img->getMemDC(), playerX, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				playerY = (i - (rcPlayer.bottom - rcPlayer.top) / 2) + 20;
				gravity = 0.f;
				jumpSpeed = 0.f;
				isJump = false;
				jumpCount = 0;
				if (_playerState == PLAYER_JUMP || _playerState == PLAYER_DOUBLEJUMP || _playerState == PLAYER_JUMPATT)
				{
					_playerState = PLAYER_IDLE;
				}
				break;
			}
			else if ((r == 255 && g == 0 && b == 255))
			{
				isJump = true;
			}
		}
	}
	else if (DATA->getStage() == STAGE_1)
	{
		RECT rcTemp1;

		if (IntersectRect(&rcTemp1, &DATA->getPixelGroundRc(), &DATA->getPlayerRc()))
		{
			//DATA->setIsTouch(true);
			playerY = DATA->getPixelGroundRc().top - 32.f;
			gravity = 0.f;
			jumpSpeed = 0.f;
			_playerState = PLAYER_IDLE;
			isJump = false;
			jumpCount = 0;
		}
		else if(DATA->getPixelGroundRc().right < rcPlayer.left && isJump == false)
		{
			gravity += 0.7f;
			playerY += -sinf(PI / 2) * jumpSpeed + gravity;
		}
	}
	else if (DATA->getStage() == STAGE_1_2)
	{
		for (int i = ptBottom - 10; i < ptBottom + 10; i++)
		{
			COLORREF color = GetPixel(DATA->getPixelGround().img->getMemDC(), playerX, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				playerY = (i - (rcPlayer.bottom - rcPlayer.top) / 2) + 10;
				gravity = 0.f;
				jumpSpeed = 0.f;
				isJump = false;
				jumpCount = 0;
				if (_playerState == PLAYER_JUMP || _playerState == PLAYER_DOUBLEJUMP || _playerState == PLAYER_JUMPATT)
				{
					_playerState = PLAYER_IDLE;
				}
				break;
			}
		}
	}
	else if (DATA->getStage() == STAGE_2 || DATA->getStage() == STAGE_3)
	{
		ptBottom = (playerY + (rcPlayer.bottom - rcPlayer.top) / 2) - 5;
		int i;
		for (i = ptBottom - 10; i < ptBottom + 10; i++)
		{
			COLORREF color = GetPixel(DATA->getPixelGround().img->getMemDC(), playerX - DATA->getPixelGround().x, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				if (gravity > jumpSpeed)
				{
					playerY = (i - (rcPlayer.bottom - rcPlayer.top) / 2) + 5;
					gravity = 0.f;
					jumpSpeed = 0.f;
					if (_playerState == PLAYER_JUMP || _playerState == PLAYER_DOUBLEJUMP || _playerState == PLAYER_JUMPATT)
					{
						_playerState = PLAYER_IDLE;
					}
					isJump = false;
					jumpCount = 0;
				}
				break;
			}
			else if ((r == 255 && g == 0 && b == 255))
			{
				isJump = true;
			}
		}

		for (i = ptTop - 5; i < ptTop + 5; i++)
		{
			COLORREF color = GetPixel(DATA->getPixelGround().img->getMemDC(), playerX - DATA->getPixelGround().x, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				if (r == 0 && g == 0 && b == 0) continue;
				jumpSpeed = 0.f;
				break;
			}
		}

		for (i = ptRight - 10; i < ptRight + 10; i++)
		{
			COLORREF color = GetPixel(DATA->getPixelGround().img->getMemDC(), i, playerY + DATA->getPixelGround().y);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);
		
			if (!(r == 255 && g == 0 && b == 255))
			{
				isRightPixel = true;
				break;
			}
		}
		if (i == ptRight + 10)
			isRightPixel = false;

		for (i = ptLeft - 10; i < ptLeft + 10; i++)
		{
			COLORREF color = GetPixel(DATA->getPixelGround().img->getMemDC(), i, playerY + DATA->getPixelGround().y);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);
		
			if (!(r == 255 && g == 0 && b == 255))
			{
				isLeftPixel = true;
				break;
			}
		}
		if(i == ptLeft + 10)
			isLeftPixel = false;
	}

	for (int i = Head->getVBulletBottom() - 3; i < Head->getVBulletBottom() + 3; i++)
	{
		COLORREF color = GetPixel(DATA->getPixelGround().img->getMemDC(), Head->getVBulletX(), i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
	
		if (!(r == 255 && g == 0 && b == 255))
		{
			Head->setBulletGravity(0);
			Head->setRotateAngle(0);
			break;
		}
	}

}

void player::playerMove()
{
	//이동
	if (INPUT->GetKey(VK_RIGHT))
	{
		//isLeftPixel = false;
		if (rcPlayer.right < WINSIZEX && isRightPixel == false)
		{
			playerX += playerSpeed;
			//moveX
		}

		if (rcPlayer.right >= WINSIZEX)
		{
			if (DATA->getStage() == START)
			{
				DATA->setStage(STAGE_1);
			}
		}
		isLeft = false;
		DATA->setPlayerIsLeft(false);
		if (isJump == false)
		{
			_playerState = PLAYER_RUN;
		}

		if (DATA->getPlayerCamera().isRight == true && DATA->getStage() == START)
		{
			playerX = WINSIZEX / 2;
		}
		if (DATA->getPlayerCamera().isRight == true && DATA->getStage() == STAGE_1_2)
		{
			playerX = WINSIZEX / 2;

			rcFront.left -= 8;
			rcFront.right -= 8;
		}
		if (DATA->getPlayerCamera().isRight == true && DATA->getStage() == STAGE_2)
		{
			playerX = WINSIZEX / 2;
		}
		if (DATA->getPlayerCamera().isRight == true && DATA->getStage() == STAGE_3)
		{
			playerX = WINSIZEX / 2;
		}
	}
	if (INPUT->GetKeyUp(VK_RIGHT))
	{
		if (isJump == false)
		{
			_playerState = PLAYER_IDLE;
		}
	}
	if (INPUT->GetKey(VK_LEFT))
	{
		//isRightPixel = false;
		if (rcPlayer.left > 0 && isLeftPixel == false)
		{
			playerX -= playerSpeed;
		}

		if (rcPlayer.left <= 0)
		{
			if (DATA->getStage() == STAGE_1)
			{
				DATA->setStage(START);
			}
		}
		isLeft = true;
		DATA->setPlayerIsLeft(true);
		if (isJump == false)
		{
			_playerState = PLAYER_RUN;
		}

		if (DATA->getPlayerCamera().isLeft == true && DATA->getStage() == START)
		{
			playerX = WINSIZEX / 2;
		}
		if (DATA->getPlayerCamera().isLeft == true && DATA->getStage() == STAGE_1_2)
		{
			playerX = WINSIZEX / 2;
			rcFront.left += 8;
			rcFront.right += 8;
		}
		if (DATA->getPlayerCamera().isLeft == true && DATA->getStage() == STAGE_2)
		{
			playerX = WINSIZEX / 2;
		}
		if (DATA->getPlayerCamera().isLeft == true && DATA->getStage() == STAGE_3)
		{
			playerX = WINSIZEX / 2;
		}
	}
	if (INPUT->GetKeyUp(VK_LEFT))
	{
		if (isJump == false)
		{
			_playerState = PLAYER_IDLE;
		}
	}

	//점프
	if (INPUT->GetKeyDown('C') && jumpCount < 2 && _playerState != PLAYER_START) //나중에 주석풀어서 두번만 뛰도록 해야함
	{
		animationCount = 0;
		animationIndex = 0;
		if (_playerState == PLAYER_RUN || _playerState == PLAYER_IDLE)
		{
			gravity = 0.f;
			_playerState = PLAYER_JUMP;
		}
		else if (_playerState == PLAYER_JUMP)
		{
			gravity = 0.f;
			jumpSpeed = 2.f;
			_playerState = PLAYER_DOUBLEJUMP;
		}
		jumpSpeed += 12.f;
		jumpCount++;
		isJump = true;
	}

	//공격
	if (INPUT->GetKeyDown('X'))
	{
		Att1CoolDown = 0;
		Att2CoolDown = 0;
		Att3CoolDown = 0;

		if (isJump)
		{
			_playerState = PLAYER_JUMPATT;

			if (isLeft)
			{
				animationIndex = 4;
			}
			else
			{
				animationIndex = 0;
			}
		}
		if (DATA->getPlayerRuin() == SKUL)
		{
			if (_playerState == PLAYER_RUN || _playerState == PLAYER_JUMP || 
				_playerState == PLAYER_DOUBLEJUMP || _playerState == PLAYER_IDLE || 
				_playerState == PLAYER_ATT2)// && isEndAtt2 == true && isEndAtt1 == true)
			{
				_playerState = PLAYER_ATT;
				isEndAtt1 = false;
			}
			else if (_playerState == PLAYER_ATT)// && isEndAtt1 == true && isEndAtt2 == true)
			{
				_playerState = PLAYER_ATT2;
				isEndAtt2 = false;
			}

			if (isLeft == false && _playerState == PLAYER_ATT)// && isEndAtt1 == true)
			{
				animationIndex = 0;
			}
			else if (isLeft == true && _playerState == PLAYER_ATT)// && isEndAtt1 == true)
			{
				animationIndex = 5;
			}

			if (isLeft == false && _playerState == PLAYER_ATT2)// && isEndAtt2 == true)
			{
				animationIndex = 0;
			}
			else if (isLeft == true && _playerState == PLAYER_ATT2)// && isEndAtt2 == true)
			{
				animationIndex = 3;
			}
		}
		else if (DATA->getPlayerRuin() == SOLDIER)
		{
			if (_playerState == PLAYER_RUN || _playerState == PLAYER_JUMP || _playerState == PLAYER_DOUBLEJUMP || _playerState == PLAYER_IDLE)
			{
				_playerState = PLAYER_ATT;
			}

			if (isLeft == false && _playerState == PLAYER_ATT && isEndAtt1 == true)
			{
				animationIndex = 0;
				isEndAtt1 = false;
			}
			else if (isLeft == true && _playerState == PLAYER_ATT && isEndAtt1 == true)
			{
				animationIndex = 5;
				isEndAtt1 = false;
			}
		}
		else if (DATA->getPlayerRuin() == SAMURAI)
		{
			if (_playerState == PLAYER_RUN || _playerState == PLAYER_JUMP || _playerState == PLAYER_DOUBLEJUMP || _playerState == PLAYER_IDLE || _playerState == PLAYER_ATT3)
			{
				_playerState = PLAYER_ATT;
			}
			else if (_playerState == PLAYER_ATT)// && isEndAtt1 == true)
			{
				_playerState = PLAYER_ATT2;
			}
			else if (_playerState == PLAYER_ATT2)// && isEndAtt2 == true)
			{
				_playerState = PLAYER_ATT3;
			}

			if (isLeft == false && _playerState == PLAYER_ATT)// && isEndAtt1 == true)
			{
				animationIndex = 0;
			}
			else if (isLeft == true && _playerState == PLAYER_ATT)// && isEndAtt1 == true)
			{
				animationIndex = 5;
			}

			if (isLeft == false && _playerState == PLAYER_ATT2)// && isEndAtt2 == true)
			{
				animationIndex = 0;
			}
			else if (isLeft == true && _playerState == PLAYER_ATT2)// && isEndAtt2 == true)
			{
				animationIndex = 3;
			}

			if (isLeft == false && _playerState == PLAYER_ATT3)// && isEndAtt3 == true)
			{
				animationIndex = 0;
			}
			else if (isLeft == true && _playerState == PLAYER_ATT3)// && isEndAtt3 == true)
			{
				animationIndex = 3;
			}
		}
	}
	if (INPUT->GetKeyUp('X'))
	{
		isAttCool = true;
	}

	//대쉬
	if (INPUT->GetKeyDown('Z') && dashCount < 2 && isRightPixel == false && isLeftPixel == false)// && INPUT->GetKey(VK_RIGHT) || INPUT->GetKeyDown('Z') && INPUT->GetKey(VK_LEFT))
	{
		_playerState = PLAYER_DASH;
		Efect1 = 0;
		Efect2 = 0;
		Efect3 = 0;
		Efect4 = 0;
		Efect5 = 0;
		isDash = true;
		DATA->setPlayerIsDash(isDash);
		dashCount++;
	}

	//스킬
	if (INPUT->GetKeyDown('A') && isChange == false)
	{
		if (DATA->getPlayerRuin() == SKUL && isSkulSkill1 == false)
		{
			animationCount = 0;
			if (isLeft)
			{
				animationIndex = 4;
				Head->fire(playerX - DATA->getPixelGround().x, playerY, 0.f, -10.f, "일반해골스킬_왼쪽");
			}
			else
			{
				animationIndex = 0;
				Head->fire(playerX - DATA->getPixelGround().x, playerY, 0.f, 10.f, "일반해골스킬_오른쪽");
			}
			headAngle = 0.f;
			isSkulSkill1 = true;
			skulCooldown_1 = 500;
			CooldownMax = 500;
			_playerState = PLAYER_SKILL1;
		}
		else if (DATA->getPlayerRuin() == SOLDIER && isSoldierSkillCool == false)
		{
			skillEfect1 = 0;
			skillEfect2 = 0;
			skillEfect3 = 0;
			skillEfect4 = 0;
			skillEfect5 = 0;

			if (isLeft)
			{
				animationIndex = 5;
			}
			else
			{
				animationIndex = 0;
			}
			isSoldierSkill = true;
			DATA->setIsSoldierSkill(isSoldierSkill);
			isSoldierSkillCool = true;
			soldierCooldown_1 = 600;
			CooldownMax = 600;
			_playerState = PLAYER_SKILL1;
		}
		else if (DATA->getPlayerRuin() == SAMURAI && isSamuraiSkillCool1 == false)
		{
			skillEfect1 = 0;
			skillEfect2 = 0;
			skillEfect3 = 0;
			skillEfect4 = 0;
			skillEfect5 = 0;

			if (isLeft)
			{
				animationIndex = 12;
				napdoIndex = 9;
			}
			else
			{
				animationIndex = 0;
				napdoIndex = 0;
			}
			isSamuraiSkillCool1 = true;
			samuraiCooldown_1 = 400;
			CooldownMax = 400;
			_playerState = PLAYER_SKILL1;
		}
	}

	if (DATA->getPlayerRuin() == SAMURAI && _playerState == PLAYER_SKILL1)
	{
		if (isLeft)
		{
			if (animationIndex < 5)
			{
				isSamuraiSkill1 = true;
				DATA->setIsSamuraiSkill1(isSamuraiSkill1);
			}
		}
		else
		{
			if (animationIndex > 7)
			{
				isSamuraiSkill1 = true;
				DATA->setIsSamuraiSkill1(isSamuraiSkill1);
			}
		}
	}
	Head->update();
	headAngle -= 0.2f;
	Head->rotateAngle(headAngle);

	if (DATA->getPlayerRuin() == SKUL)
	{
		if (INPUT->GetKeyDown('S') && isSkulSkill2 == false && isSkulSkill1 == true && isChange == false)
		{
			isSkulSkill2 = true;
			isSkulSkill1 = false;
			playerX = Head->getSaveX();
			Head->removeBullet(0);
			CooldownMax = 500;
			skulCooldown_2 = 500;
		}
	}
	if (DATA->getPlayerRuin() == SAMURAI)
	{
		if (INPUT->GetKeyDown('S') && isSamuraiSkillCool2 == false)
		{
			skillEfect1 = 0;
			skillEfect2 = 0;
			skillEfect3 = 0;
			skillEfect4 = 0;
			skillEfect5 = 0;

			_playerState = PLAYER_SKILL2;
			isSamuraiSkillCool2 = true;
			CooldownMax = 800;
			samuraiCooldown_2 = 800;
			if (isLeft)
			{
				animationIndex = 9;
			}
			else
			{
				animationIndex = 0;
			}
		}
	}

	if (DATA->getPlayerRuin() == SAMURAI && _playerState == PLAYER_SKILL2)
	{
		if (isLeft)
		{
			if (animationIndex <= 8)
			{
				isCounter = true;
			}
		}
		else
		{
			if (animationIndex >= 1)
			{
				isCounter = true;
			}
		}

		if (isCounter)
		{
			if (PtInRect(&rcPlayer, _ptMouse))
			{
				isAttecked = true;
			}
		}
		if (isAttecked)
		{
			isCounter = false;
			isSamuraiSkill2 = true;
			DATA->setIsSamuraiSkill2(isSamuraiSkill1);
		}
	}

	if (INPUT->GetKeyDown(VK_SPACE))
	{
		isChange = true;
		DATA->setIsChange(true);

		if (DATA->getPlayerRuin() == SKUL)
		{
			if (DATA->getHaveRuin()[0] == SOLDIER)
			{
				DATA->setPlayerRuin(SOLDIER);
				_playerState = PLAYER_CHANGE;
				return;
			}
			if (DATA->getHaveRuin()[0] == SAMURAI)
			{
				if (isLeft)
				{
					animationIndex = 3;
				}
				else
				{
					animationIndex = 0;
				}
				DATA->setPlayerRuin(SAMURAI);
				_playerState = PLAYER_CHANGE;
				return;
			}

			if (DATA->getHaveRuin()[1] == SOLDIER)
			{
				DATA->setPlayerRuin(SOLDIER);
				_playerState = PLAYER_CHANGE;
				return;
			}
			if (DATA->getHaveRuin()[1] == SAMURAI)
			{
				if (isLeft)
				{
					animationIndex = 3;
				}
				else
				{
					animationIndex = 0;
				}
				DATA->setPlayerRuin(SAMURAI);
				_playerState = PLAYER_CHANGE;
				return;
			}
		}

		if (DATA->getPlayerRuin() == SOLDIER)
		{
			if (DATA->getHaveRuin()[0] == SKUL)
			{
				if (isLeft)
				{
					animationIndex = 6;
				}
				else
				{
					animationIndex = 0;
				}
				DATA->setPlayerRuin(SKUL);
				_playerState = PLAYER_CHANGE;
				return;
			}
			if (DATA->getHaveRuin()[0] == SAMURAI)
			{
				if (isLeft)
				{
					animationIndex = 3;
				}
				else
				{
					animationIndex = 0;
				}
				DATA->setPlayerRuin(SAMURAI);
				_playerState = PLAYER_CHANGE;
				return;
			}

			if (DATA->getHaveRuin()[1] == SKUL)
			{
				if (isLeft)
				{
					animationIndex = 6;
				}
				else
				{
					animationIndex = 0;
				}
				DATA->setPlayerRuin(SKUL);
				_playerState = PLAYER_CHANGE;
				return;
			}
			if (DATA->getHaveRuin()[1] == SAMURAI)
			{
				if (isLeft)
				{
					animationIndex = 3;
				}
				else
				{
					animationIndex = 0;
				}
				DATA->setPlayerRuin(SAMURAI);
				_playerState = PLAYER_CHANGE;
				return;
			}
		}

		if (DATA->getPlayerRuin() == SAMURAI)
		{
			if (DATA->getHaveRuin()[0] == SOLDIER)
			{
				DATA->setPlayerRuin(SOLDIER);
				_playerState = PLAYER_CHANGE;
				return;
			}
			if (DATA->getHaveRuin()[0] == SKUL)
			{
				if (isLeft)
				{
					animationIndex = 6;
				}
				else
				{
					animationIndex = 0;
				}
				DATA->setPlayerRuin(SKUL);
				_playerState = PLAYER_CHANGE;
				return;
			}

			if (DATA->getHaveRuin()[1] == SOLDIER)
			{
				DATA->setPlayerRuin(SOLDIER);
				_playerState = PLAYER_CHANGE;
				return;
			}
			if (DATA->getHaveRuin()[1] == SKUL)
			{
				if (isLeft)
				{
					animationIndex = 6;
				}
				else
				{
					animationIndex = 0;
				}
				DATA->setPlayerRuin(SKUL);
				_playerState = PLAYER_CHANGE;
				return;
			}
		}
	}

	if (DATA->getPlayerRuin() == SKUL && _playerState == PLAYER_CHANGE)
	{
		if (isLeft)
		{
			playerX -= 5;
		}
		else
		{
			playerX += 5;
		}

		if (DATA->getPlayerCamera().isRight == true && DATA->getStage() == START)
		{
			playerX = WINSIZEX / 2;
		}
		if (DATA->getPlayerCamera().isRight == true && DATA->getStage() == STAGE_1_2)
		{
			playerX = WINSIZEX / 2;

			rcFront.left -= 8;
			rcFront.right -= 8;
		}
		if (DATA->getPlayerCamera().isRight == true && DATA->getStage() == STAGE_2)
		{
			playerX = WINSIZEX / 2;
		}
		if (DATA->getPlayerCamera().isRight == true && DATA->getStage() == STAGE_3)
		{
			playerX = WINSIZEX / 2;
		}
	}

	if (DATA->getPlayerRuin() == SAMURAI && _playerState == PLAYER_CHANGE)
	{
		if (isLeft)
		{
			playerX -= 8.f;
		}
		else
		{
			playerX += 8.f;
		}

		if (DATA->getPlayerCamera().isRight == true && DATA->getStage() == START)
		{
			playerX = WINSIZEX / 2;
		}
		if (DATA->getPlayerCamera().isRight == true && DATA->getStage() == STAGE_1_2)
		{
			playerX = WINSIZEX / 2;

			rcFront.left -= 8;
			rcFront.right -= 8;
		}
		if (DATA->getPlayerCamera().isRight == true && DATA->getStage() == STAGE_2)
		{
			playerX = WINSIZEX / 2;
		}
		if (DATA->getPlayerCamera().isRight == true && DATA->getStage() == STAGE_3)
		{
			playerX = WINSIZEX / 2;
		}
	}

	if (isSoldierSkill == true || isSamuraiSkill1 == true || isSamuraiSkill2 == true)
	{
		if (skillEfect1 < 65)
		{
			if (isLeft)
			{
				if (rcPlayer.left > 0 && DATA->getPlayerCamera().isLeft == false)
				{
					playerX += cosf(PI) * 20.f;
					playerY += -sinf(PI) * 20.f;
				}
			}
			else
			{
				if (rcPlayer.right < WINSIZEX && DATA->getPlayerCamera().isRight == false)
				{
					playerX += cosf(0.f) * 20.f;
					playerY += -sinf(0.f) * 20.f;
				}
			}
		}

		skillEfect1 += 6;

		if (skillEfect1 >= 255)
		{
			skillEfect1 = 255;
		}
		if (skillEfect1 >= 20)
		{
			skillEfect2 += 7;
		}

		if (skillEfect2 >= 255)
		{
			skillEfect2 = 255;
		}
		if (skillEfect2 >= 20)
		{
			skillEfect3 += 8;
		}

		if (skillEfect3 >= 255)
		{
			skillEfect3 = 255;
		}
		if (skillEfect3 >= 20)
		{
			skillEfect4 += 9;
		}

		if (skillEfect4 >= 255)
		{
			skillEfect4 = 255;
		}
		if (skillEfect4 >= 20)
		{
			skillEfect5 += 10;
		}
		if (skillEfect5 >= 255)
		{
			skillEfect5 = 255;
			if (DATA->getPlayerRuin() == SOLDIER)
			{
				_playerState = PLAYER_IDLE;
			}
			if (isSamuraiSkill1)
			{
				isSamuraiSkill1 = false;
				
				DATA->setIsSamuraiSkill1(isSamuraiSkill1);
			}
			if (isSamuraiSkill2)
			{
				isSamuraiSkill2 = false;
				DATA->setIsSamuraiSkill2(isSamuraiSkill2);
			}
			if (isSoldierSkill)
			{
				isSoldierSkill = false;
				DATA->setIsSoldierSkill(isSoldierSkill);
			}
		}
	}

	if (_playerState == PLAYER_DASH || isDash == true)
	{
		if (Efect1 < 65)
		{
			if (isLeft)
			{
				if (rcPlayer.left > 0 && DATA->getPlayerCamera().isLeft == false)
				{
					playerX += cosf(PI) * 20.f;
					playerY += -sinf(PI) * 20.f;
				}
			}
			else
			{
				if (rcPlayer.right < WINSIZEX && DATA->getPlayerCamera().isRight == false)
				{
					playerX += cosf(0.f) * 20.f;
					playerY += -sinf(0.f) * 20.f;
				}
			}
		}
		else
		{
			isDash = false;
			DATA->setPlayerIsDash(isDash);
		}

		Efect1 += 6;

		if (Efect1 >= 255)
		{
			Efect1 = 255;
		}
		if (Efect1 >= 20)
		{
			Efect2 += 7;
		}

		if (Efect2 >= 255)
		{
			Efect2 = 255;
		}
		if (Efect2 >= 20)
		{
			Efect3 += 8;
		}

		if (Efect3 >= 255)
		{
			Efect3 = 255;
		}
		if (Efect3 >= 20)
		{
			Efect4 += 9;
		}

		if (Efect4 >= 255)
		{
			Efect4 = 255;
		}
		if (Efect4 >= 20)
		{
			Efect5 += 10;
		}
		if (Efect5 >= 255)
		{
			Efect5 = 255;
			_playerState = PLAYER_IDLE;
		}
	}

	RECT rcTemp2;
	if (DATA->getStage() == STAGE_1)
	{
		if (IntersectRect(&rcTemp2, &DATA->getNextRc(), &rcPlayer))
		{
			DATA->setStage(STAGE_1_2);
		}
	}
	if (DATA->getPlayerCamera().isBottom == true && DATA->getStage() == STAGE_1)
	{

		if (DATA->getPixelGroundRc().right < rcPlayer.left)
		{
			playerY = 600;
			gravity = 0.f;
			jumpSpeed = 0.f;
			_playerState = PLAYER_JUMP;

		}
	}
}

void player::playerCooldown()
{
	if (isAttCool)
	{
		if (_playerState == PLAYER_ATT)
		{
			Att1CoolDown++;
		}
		if (_playerState == PLAYER_ATT2)
		{
			Att2CoolDown++;
		}
		if (_playerState == PLAYER_ATT3)
		{
			Att3CoolDown++;
		}
	}

	if (Att1CoolDown % 60 == 50 || Att2CoolDown % 60 == 50 || Att3CoolDown % 60 == 50)
	{
		_playerState = PLAYER_IDLE;
		Att1CoolDown = 0;
		Att2CoolDown = 0;
		Att3CoolDown = 0;
	}

	//playerY += gravity;
	//gravity += 0.35f;
	//playerX += cosf(PI / 2) * 0.f;
	//playerY += -sinf(PI / 2) * 0.f + gravity;
	if (_playerState == PLAYER_JUMP || _playerState == PLAYER_DOUBLEJUMP || isJump)
	{
		if (isDash == false)
		{
			gravity += 0.7f;
			playerX += cosf(PI / 2) * jumpSpeed;
			playerY += -sinf(PI / 2) * jumpSpeed + gravity;
		}
	}

	if (dashCount > 0)
	{
		dashCooldown++;
	}

	if (dashCooldown % 50 == 0)
	{
		dashCount = 0;
		dashCooldown = 0;
	}

	if (DATA->getPlayerRuin() == SKUL)
	{
		if (isSkulSkill1)
		{
			skulCooldown_1--;
			if (skulCooldown_1 <= 0)
			{
				skulCooldown_1 = 0;
				Head->removeBullet(0);
				isSkulSkill1 = false;
			}
		}
		if (isSkulSkill2)
		{
			skulCooldown_2--;
			if (skulCooldown_2 <= 0)
			{
				skulCooldown_2 = 0;
				isSkulSkill2 = false;
			}
		}
	}
	else if (DATA->getPlayerRuin() == SOLDIER)
	{
		if (isSoldierSkillCool)
		{
			soldierCooldown_1--;
			if (soldierCooldown_1 <= 0)
			{
				soldierCooldown_1 = 0;
				isSoldierSkill = false;
				isSoldierSkillCool = false;
			}
		}
	}
	else if (DATA->getPlayerRuin() == SAMURAI)
	{
		if (isSamuraiSkillCool1)
		{
			samuraiCooldown_1--;
			if (samuraiCooldown_1 <= 0)
			{
				samuraiCooldown_1 = 0;
				isSamuraiSkillCool1 = false;
				isSamuraiSkill1 = false;
			}
		}
		if (isSamuraiSkillCool2)
		{
			samuraiCooldown_2--;
			if (samuraiCooldown_2 <= 0)
			{
				samuraiCooldown_2 = 0;
				isSamuraiSkillCool2 = false;
				isSamuraiSkill2 = false;
				isAttecked = false;
			}
		}
	}
}

void player::setPlayer()
{
	rcPlayer = RectMakeCenter(playerX, playerY, 80, 64);

	DATA->setPlayerRc(RectMakeCenter(playerX, playerY, 80, 64));

	//rcPlayerCamera = RectMakeCenter(playerX, playerY, WINSIZEX, 500);
	DATA->setPlayerCameraX(playerX);
	DATA->setPlayerCameraY(playerY);
	DATA->setPlayerCameraRc(RectMakeCenter(DATA->getPlayerCamera().x, DATA->getPlayerCamera().y, WINSIZEX, 250));

	if (DATA->getStage() == STAGE_1 && isMove == false)
	{
		playerX = 50.f;
		playerY = 558.f;
		isMove = true;
	}
	if (DATA->getStage() == START && isMove == true)
	{
		playerX = 1200;
		isMove = false;
	}
	if (DATA->getStage() == STAGE_2 && isMove == true)
	{
		playerX = 100.f;
		playerY = 100.f;
		isMove = false;
	}
	if (DATA->getStage() == STAGE_3 && isMove == false)
	{
		playerX = 50.f;
		playerY = 150.f;
		isMove = true;
	}

	headGravity = Head->getBulletGravity();
}
