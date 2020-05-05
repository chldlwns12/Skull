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

	castleWall1 = IMAGEMANAGER->findImage("맵1_성벽1");

	playerX = WINSIZEX / 2;
	playerY = 563.f;

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
	dashCooldown = 0;
	dashCount = 0;

	for (int i = 0; i < 5; i++)
	{
		saveX[i] = 0;
		saveY[i] = 0;
	}
	isColl = true;
	isMove = false;

	rcFront = RectMake(0, 0, 1588, 720);
	return S_OK;
}

void player::release()
{
}

void player::update()
{
	rcPlayer = RectMakeCenter(playerX, playerY, 80, 64);
	DATA->setPlayerRc(RectMakeCenter(playerX, playerY, 80, 64));

	//rcPlayerCamera = RectMakeCenter(playerX, playerY, WINSIZEX, 500);
	DATA->setPlayerCameraX(playerX);
	DATA->setPlayerCameraY(playerY);
	DATA->setPlayerCameraRc(RectMakeCenter(DATA->getPlayerCamera().x, DATA->getPlayerCamera().y, WINSIZEX, 200));

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
	if (INPUT->GetKey(VK_RIGHT))
	{
		if (rcPlayer.right < WINSIZEX)
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
	}
	if (INPUT->GetKeyUp(VK_LEFT))
	{
		if (isJump == false)
		{
			_playerState = PLAYER_IDLE;
		}
	}

	//if (DATA->getStage() == STAGE_1)
	//{
	//	if (rcPlayer.bottom >= DATA->getPixelGround().rc.bottom)
	//	{
	//		playerY = DATA->getPixelGroundRc().bottom - 32;
	//		gravity = 0.f;
	//		jumpSpeed = 0.f;
	//		jumpCount = 0;
	//	}
	//}
	RECT rcTemp2;
	if (DATA->getStage() == STAGE_1)
	{
		if (IntersectRect(&rcTemp2,&DATA->getNextRc(),&rcPlayer))
		{
			DATA->setStage(STAGE_1_2);
		}
	}
	if (DATA->getPlayerCamera().isBottom == true && DATA->getStage() == STAGE_1)
	{

		if (DATA->getPixelGroundRc().right < rcPlayer.left)
		{
			playerY = 620;
			gravity = 0.f;
			jumpSpeed = 0.f;
			_playerState = PLAYER_JUMP;

		}
	}

	//점프
	if (INPUT->GetKeyDown('C') && jumpCount < 2) //나중에 주석풀어서 두번만 뛰도록 해야함
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

	this->PixelCollision();
	this->PlayerAnimation();
}

void player::render()
{
	//Rectangle(getMemDC(), DATA->getPlayerCamera().rcCamera);

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

	sprintf(str, "%f", DATA->getPixelGround().y);
	TextOut(getMemDC(), 10, 90, str, strlen(str));
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
					animationIndex = 4;
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

void player::PixelCollision()
{
	ptBottom = (playerY + (rcPlayer.bottom - rcPlayer.top) / 2) - 20;
	rcBottom = RectMakeCenter(playerX, ptBottom, 10, 10);
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
				if (_playerState == PLAYER_JUMP || _playerState == PLAYER_DOUBLEJUMP)
				{
					_playerState = PLAYER_IDLE;
				}
				break;
			}

			if ((r == 255 && g == 0 && b == 255) && isJump == false)
			{
				gravity += 0.7f;
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

	if (DATA->getStage() == STAGE_1_2)
	{
		for (int i = ptBottom - 10; i < ptBottom + 10; i++)
		{
			COLORREF color = GetPixel(DATA->getPixelGround().img->getMemDC(), playerX, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				playerY = (i - (rcPlayer.bottom - rcPlayer.top) / 2) + 5;
				gravity = 0.f;
				jumpSpeed = 0.f;
				isJump = false;
				jumpCount = 0;
				if (_playerState == PLAYER_JUMP || _playerState == PLAYER_DOUBLEJUMP)
				{
					_playerState = PLAYER_IDLE;
				}
				break;
			}

			if ((r == 255 && g == 0 && b == 255) && isJump == false)
			{
				gravity += 0.7f;
			}
		}
	}
}
