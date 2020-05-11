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

	castleWall1 = IMAGEMANAGER->findImage("맵1_성벽1");

	playerX = WINSIZEX / 2;
	playerY = 563.f;

	playerMexHp = 150;
	playerCurrentHp = 100;
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
	isEndAtt1 = false;
	isAtt1 = false;
	isAtt2 = false;
	isAttCool = false;
	Att1CoolDown = 0;
	Att2CoolDown = 0;
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
	skillCooldown_1 = 0;
	skillCooldown_2 = 0;
	changeCooldown = 0;
	Head = new Skul;
	Head->init(1, 500, ROTATERENDER);
	headAngle = 0.f;
	skill1 = false;
	skill2 = false;

	isColl = true;
	isMove = false;

	rcFront = RectMake(0, 0, 1588, 720);

	isRightPixel = false;
	isLeftPixel = false;
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
	this->PlayerAnimation();
}

void player::render()
{
	//Rectangle(getMemDC(), DATA->getPlayerCamera().rcCamera);
	//Rectangle(getMemDC(), DATA->getPlayerRc());
	if (skill1 == true && Head->getIsCooldown() == true)
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
		if (_playerState == PLAYER_SKILL1)
		{
			playerSkillImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top);
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
	if (skill2 == false)
	{
		Head->render();
	}

	if (DATA->getStage() == STAGE_1)
	{
		castleWall1->render(getMemDC(), DATA->getPixelGround().x, DATA->getPixelGround().y - 700);
	}
	if (DATA->getStage() == STAGE_1_2)
	{
		DATA->getBackGround().img->render(getMemDC(), rcFront.left, rcFront.top);
	}

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

	sprintf(str, "playerX : %f", playerX);
	TextOut(getMemDC(), 10, 90, str, strlen(str));
	sprintf(str2, "playerY : %f", playerY);
	TextOut(getMemDC(), 10, 110, str2, strlen(str2));
	sprintf(str3, "backX : %f", DATA->getPixelGround().x);
	TextOut(getMemDC(), 10, 130, str3, strlen(str3));
	sprintf(str6, "backY : %f", DATA->getPixelGround().y);
	TextOut(getMemDC(), 10, 150, str6, strlen(str6));
	sprintf(str4, "left : %f", ptRight);
	TextOut(getMemDC(), 10, 170, str4, strlen(str4));
	sprintf(str5, "right : %f", ptLeft);
	TextOut(getMemDC(), 10, 190, str5, strlen(str5));
	sprintf(str7, "bottom : %f", ptBottom);
	TextOut(getMemDC(), 10, 210, str7, strlen(str7));
}

void player::PlayerAnimation()
{
	if (skill1 == false)
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
						isEndAtt1 = false;
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
						isEndAtt1 = false;
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
					skill1 = true;
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
					skill1 = true;
					_playerState = PLAYER_IDLE;
				}
				playerSkillImg->setFrameX(animationIndex);
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
	else if (DATA->getStage() == STAGE_2)
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
				playerY = (i - (rcPlayer.bottom - rcPlayer.top) / 2) + 5;
				gravity = 0.f;
				jumpSpeed = 0.f;
				if (_playerState == PLAYER_JUMP || _playerState == PLAYER_DOUBLEJUMP || _playerState == PLAYER_JUMPATT)
				{
					_playerState = PLAYER_IDLE;
				}
				isJump = false;
				jumpCount = 0;
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
		}

		if (rcPlayer.right >= WINSIZEX)
		{
			if (DATA->getStage() == START)
			{
				DATA->setStage(STAGE_1);
			}
		}
		isLeft = false;
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

		if (_playerState == PLAYER_ATT && isEndAtt1 == true)
		{
			_playerState = PLAYER_ATT2;
		}
		else if (_playerState == PLAYER_RUN || _playerState == PLAYER_JUMP || _playerState == PLAYER_DOUBLEJUMP || _playerState == PLAYER_IDLE || _playerState == PLAYER_ATT2)
		{
			_playerState = PLAYER_ATT;
		}

		if (isLeft == false && _playerState == PLAYER_ATT && isAtt1 == false)
		{
			animationIndex = 0;
			isAtt1 = true;
			isAtt2 = false;
		}
		else if (isLeft == true && _playerState == PLAYER_ATT && isAtt1 == false)
		{
			animationIndex = 5;
			isAtt1 = true;
			isAtt2 = false;
		}

		if (isLeft == false && _playerState == PLAYER_ATT2 && isAtt2 == false)
		{
			animationIndex = 0;
			isAtt2 = true;
			isAtt1 = false;
		}
		else if (isLeft == true && _playerState == PLAYER_ATT2 && isAtt2 == false)
		{
			animationIndex = 3;
			isAtt2 = true;
			isAtt1 = false;
		}
	}
	if (INPUT->GetKeyUp('X'))
	{
		isAttCool = true;
	}

	//대쉬
	if (INPUT->GetKeyDown('Z') && dashCount < 2)// && INPUT->GetKey(VK_RIGHT) || INPUT->GetKeyDown('Z') && INPUT->GetKey(VK_LEFT))
	{
		_playerState = PLAYER_DASH;
		Efect1 = 0;
		Efect2 = 0;
		Efect3 = 0;
		Efect4 = 0;
		Efect5 = 0;
		isDash = true;
		dashCount++;
	}

	//스킬
	if (INPUT->GetKeyDown('A'))
	{
		if (isLeft)
		{
			Head->fire(rcPlayer.right, rcPlayer.top, 0.f, 10.f, "일반해골스킬_왼쪽");
		}
		else
		{
			Head->fire(rcPlayer.right, rcPlayer.top, 0.f, 10.f, "일반해골스킬_오른쪽");
		}
		headAngle = 0.f;
		_playerState = PLAYER_SKILL1;
	}
	Head->update();
	headAngle -= 0.2f;
	Head->rotateAngle(headAngle);

	if (INPUT->GetKeyDown('S'))
	{
		skill2 = true;
		playerX = Head->getSaveX();
		skill1 = false;
	}

	if (_playerState == PLAYER_DASH)
	{
		if (Efect1 < 65)
		{
			if (isLeft)
			{
				if (rcPlayer.left > 0)
				{
					playerX += cosf(PI) * 20.f;
					playerY += -sinf(PI) * 20.f;
				}
			}
			else
			{
				if (rcPlayer.right < WINSIZEX)
				{
					playerX += cosf(0.f) * 20.f;
					playerY += -sinf(0.f) * 20.f;
				}
			}
		}
		else
		{
			isDash = false;
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

		//if (Efect1 == 6)
		//{
		//	if (isLeft)
		//	{
		//		saveX[0] = playerX + 10;
		//	}
		//	else
		//	{
		//		saveX[0] = playerX - 50;
		//	}
		//	saveY[0] = playerY - 22;
		//}
		//if (Efect2 == 7)
		//{
		//	if (isLeft)
		//	{
		//		saveX[1] = playerX + 20;
		//	}
		//	else
		//	{
		//		saveX[1] = playerX - 60;
		//	}
		//	saveY[1] = playerY - 22;
		//}
		//if (Efect3 == 8)
		//{
		//	if (isLeft)
		//	{
		//
		//		saveX[2] = playerX + 30;
		//	}
		//	else
		//	{
		//		saveX[2] = playerX - 70;
		//	}
		//	saveY[2] = playerY - 22;
		//}
		//if (Efect4 == 9)
		//{
		//	if (isLeft)
		//	{
		//		saveX[3] = playerX + 40;
		//	}
		//	else
		//	{
		//		saveX[3] = playerX - 80;
		//	}
		//	saveY[3] = playerY - 22;
		//}
		//if (Efect5 == 10)
		//{
		//	if (isLeft)
		//	{
		//		saveX[4] = playerX + 50;
		//	}
		//	else
		//	{
		//		saveX[4] = playerX - 90;
		//	}
		//	saveY[4] = playerY - 22;
		//}

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
	}

	if (Att1CoolDown % 60 == 50 || Att2CoolDown % 60 == 50)
	{
		_playerState = PLAYER_IDLE;
		Att1CoolDown = 0;
		Att2CoolDown = 0;
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

	if (skill2)
	{
		skillCooldown_2++;
		if (skillCooldown_2 % 350 == 340)
		{
			skill2 = false;
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
	headGravity = Head->getBulletGravity();

	if (Head->getIsCooldown() == false)
	{
		skill1 = false;
	}
}
