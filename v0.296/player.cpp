#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	playerRunImg = IMAGEMANAGER->findImage("달리기");
	playerIdleImg = IMAGEMANAGER->findImage("IDLE");
	playerJumpImg = IMAGEMANAGER->findImage("점프");
	playerAttImg1 = IMAGEMANAGER->findImage("공격1");
	playerAttImg2 = IMAGEMANAGER->findImage("공격2");
	playerDashImg = IMAGEMANAGER->findImage("대쉬");
	playerDashEfectImg1 = IMAGEMANAGER->findImage("대쉬효과");

	playerX = 100.f;
	playerY = 555.f;
	jumpSpeed = 0.f;
	playerSpeed = 10.f;
	gravity = 0.f;
	jumpCount = 0;
	attCount = 0;
	attIndex = 0;
	isJump = false;
	_playerState = PLAYER_IDLE;
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

	for (int i = 0; i < 5; i++)
	{
		saveX[i] = 0;
		saveY[i] = 0;
	}
	return S_OK;
}

void player::release()
{
}

void player::update()
{
	rcPlayer = RectMakeCenter(playerX, playerY, 80, 64);
	rcPlayerCamera = RectMakeCenter(playerX, playerY, WINSIZEX, 500);

	ptRight.x = rcPlayer.right;
	ptRight.y = playerY;
	rcRight = RectMakeCenter(ptRight.x, ptRight.y, 5, 5);
	ptLeft.x = rcPlayer.left;
	ptLeft.y = playerY;
	rcLeft = RectMakeCenter(ptLeft.x, ptLeft.y, 5, 5);
	ptBottom.x = playerX;
	ptBottom.y = rcPlayer.bottom - 15;
	rcBottom = RectMakeCenter(ptBottom.x, ptBottom.y, 10, 10);
	ptTop.x = playerX;
	ptTop.y = rcPlayer.top + 5;
	rcTop = RectMakeCenter(ptTop.x, ptTop.y, 10, 10);
	
	if (INPUT->GetKey(VK_RIGHT))
	{
		if (rcPlayer.right < WINSIZEX)
		{
			playerX += playerSpeed;
		}

		isLeft = false;
		if (isJump == false)
		{
			_playerState = PLAYER_RUN;
		}
	}
	if(INPUT->GetKeyUp(VK_RIGHT))
	{
		if (isJump == false)
		{
			_playerState = PLAYER_IDLE;
		}
	}
	if (INPUT->GetKey(VK_LEFT))
	{
		if (rcPlayer.left > 0)
		{
			playerX -= playerSpeed;
		}

		isLeft = true;
		if (isJump == false)
		{
			_playerState = PLAYER_RUN;
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
	if (INPUT->GetKeyDown('C')) //&& jumpCount < 2) 나중에 주석풀어서 두번만 뛰도록 해야함
	{
		animationCount = 0;
		animationIndex = 0;
		if (_playerState == PLAYER_RUN || _playerState == PLAYER_IDLE)
		{
			_playerState = PLAYER_JUMP;
		}
		else if (_playerState == PLAYER_JUMP)
		{
			gravity = 0.f;
			jumpSpeed = 2.f;
			_playerState = PLAYER_DOUBLEJUMP;
		}
		jumpSpeed += 12.f;
		//jumpCount++;
		isJump = true;
	}

	//공격
	if (INPUT->GetKeyDown('X'))
	{
		Att1CoolDown = 0;
		Att2CoolDown = 0;
		if (_playerState == PLAYER_ATT && isEndAtt1 == true)
		{
			_playerState = PLAYER_ATT2;
		}
		else if(_playerState == PLAYER_RUN || _playerState == PLAYER_JUMP || _playerState == PLAYER_DOUBLEJUMP || _playerState == PLAYER_IDLE || _playerState == PLAYER_ATT2)
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
			animationIndex = 6;
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
			animationIndex = 2;
			isAtt2 = true;
			isAtt1 = false;
		}
	}
	if (INPUT->GetKeyUp('X'))
	{
		isAttCool = true;
	}

	//대쉬
	if (INPUT->GetKeyDown('Z'))// && INPUT->GetKey(VK_RIGHT) || INPUT->GetKeyDown('Z') && INPUT->GetKey(VK_LEFT))
	{
		_playerState = PLAYER_DASH;
		Efect1 = 0;
		Efect2 = 0;
		Efect3 = 0;
		Efect4 = 0;
		Efect5 = 0;
		isDash = true;
	}

	if (_playerState == PLAYER_DASH)
	{
		if (Efect1 < 65)
		{
			if (isLeft)
			{
				if (rcPlayer.left > 0)
				{
					playerX -= 15.f;
				}
			}
			else
			{
				if (rcPlayer.right < WINSIZEX)
				{
					playerX += 15.f;
				}
			}
		}
		else
		{
			isDash = false;
		}

		Efect1 += 6;
		saveX[0] = playerX - 40;
		saveY[0] = playerY - 22;

		if (Efect1 >= 255)
		{
			Efect1 = 255;
		}
		if (Efect1 >= 20)
		{
			Efect2 += 7;
		}
		if (Efect1 == 6)
		{
			saveX[1] = playerX - 40;
			saveY[1] = playerY - 22;
		}

		if (Efect2 >= 255)
		{
			Efect2 = 255;
		}
		if (Efect2 >= 20)
		{
			Efect3 += 8;
		}
		if (Efect2 == 7)
		{
			saveX[2] = playerX - 40;
			saveY[2] = playerY - 22;
		}

		if (Efect3 >= 255)
		{
			Efect3 = 255;
		}
		if (Efect3 >= 20)
		{
			Efect4 += 9;
		}
		if (Efect3 == 8)
		{
			saveX[3] = playerX - 40;
			saveY[3] = playerY - 22;
		}

		if (Efect4 >= 255)
		{
			Efect4 = 255;
		}
		if (Efect4 >= 20)
		{
			Efect5 += 10;
		}
		if (Efect4 == 9)
		{
			saveX[4] = playerX - 40;
			saveY[4] = playerY - 22;
		}


		if (Efect5 >= 255)
		{
			Efect5 = 255;
			_playerState = PLAYER_IDLE;
		}
	}
	
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

	if (_playerState == PLAYER_JUMP || _playerState == PLAYER_DOUBLEJUMP || isJump)
	{
		gravity += 0.7f;
		playerX += cosf(PI / 2) * jumpSpeed;
		playerY += -sinf(PI / 2) * jumpSpeed + gravity;
	}

	this->PlayerAnimation();
}

void player::render()
{
	//Rectangle(getMemDC(), rcPlayerCamera);
	//Rectangle(getMemDC(), rcRight);
	//Rectangle(getMemDC(), rcLeft);
	//Rectangle(getMemDC(), rcBottom);
	//Rectangle(getMemDC(), rcTop);

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
	if (_playerState == PLAYER_DASH)
	{
		if (isLeft)
		{
			playerDashEfectImg1->alphaFrameRender(getMemDC(), saveX[0], saveY[0], Efect1);
			if (Efect1 >= 20)
			{
				playerDashEfectImg1->alphaFrameRender(getMemDC(), saveX[1], saveY[1], Efect2);
			}
			if (Efect2 >= 20)
			{
				playerDashEfectImg1->alphaFrameRender(getMemDC(), saveX[2], saveY[2], Efect2);
			}
			if (Efect3 >= 20)
			{
				playerDashEfectImg1->alphaFrameRender(getMemDC(), saveX[3], saveY[3], Efect2);
			}
			if (Efect4 >= 20)
			{
				playerDashEfectImg1->alphaFrameRender(getMemDC(), saveX[4], saveY[4], Efect2);
			}
		}
		else
		{
			playerDashEfectImg1->alphaFrameRender(getMemDC(), saveX[0], saveY[0], Efect1);
			if (Efect1 >= 20)
			{
				playerDashEfectImg1->alphaFrameRender(getMemDC(), saveX[1], saveY[1], Efect2);
			}
			if (Efect2 >= 20)
			{
				playerDashEfectImg1->alphaFrameRender(getMemDC(), saveX[2], saveY[2], Efect2);
			}
			if (Efect3 >= 20)
			{
				playerDashEfectImg1->alphaFrameRender(getMemDC(), saveX[3], saveY[3], Efect2);
			}
			if (Efect4 >= 20)
			{
				playerDashEfectImg1->alphaFrameRender(getMemDC(), saveX[4], saveY[4], Efect2);
			}
		}
		playerDashImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top + 10);
	}

	char str[100];

	sprintf(str, "%d", attIndex);
	TextOut(getMemDC(), 100, 100, str, strlen(str));
}

void player::PlayerAnimation()
{
	switch (_playerState)
	{
	case PLAYER_IDLE:
		animationCount++;
		if (isLeft == false)
		{
			playerIdleImg->setFrameY(0);
			if (animationCount % 5 == 0)
			{
				animationIndex++;
				if (animationIndex > 5)
				{
					animationIndex = 0;
				}
				playerIdleImg->setFrameX(animationIndex);
			}
		}
		else
		{
			playerIdleImg->setFrameY(1);
			if (animationCount % 5 == 0)
			{
				animationIndex--;
				if (animationIndex < 0)
				{
					animationIndex = 5;
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
			if (animationCount % 7 == 0)
			{
				animationIndex++;
				if (animationIndex > 7)
				{
					animationIndex = 0;
				}
				playerJumpImg->setFrameX(animationIndex);
			}
		}
		else
		{
			playerJumpImg->setFrameY(1);
			if (animationCount % 7 == 0)
			{
				animationIndex--;
				if (animationIndex < 0)
				{
					animationIndex = 3;
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
			if (animationCount % 7 == 0)
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
			if (animationCount % 7 == 0)
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
					if (animationIndex > 6)
					{
						animationIndex = 6;
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
				if (animationIndex > 2)
				{
					animationIndex = 2;
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
	}
}
