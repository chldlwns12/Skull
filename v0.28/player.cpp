#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	playerRunImg = IMAGEMANAGER->findImage("달리기");
	playerIdleImg = IMAGEMANAGER->findImage("IDLE");
	playerJumpImg = IMAGEMANAGER->findImage("점프");
	playerAttImg = IMAGEMANAGER->findImage("공격");

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
		_playerState = PLAYER_IDLE;
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
		_playerState = PLAYER_IDLE;
	}
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
	attCount++;
	if (INPUT->GetKeyDown('X'))
	{
		_playerState = PLAYER_ATT;
		//attIndex++;
		if (isLeft == false)// && attIndex == 1)
		{
			animationIndex = 0;
		}
		else if (isLeft == true)// && attIndex == 1)
		{
			animationIndex = 6;
		}

		//if (isLeft == false && attIndex == 2)
		//{
		//	animationIndex = 5;
		//}
		//else if (isLeft == true && attIndex == 2)
		//{
		//	animationIndex = 3;
		//}
	}

	//if (attCount % 90 == 0 || attIndex > 2)
	//{
	//	//_playerState = PLAYER_IDLE;
	//	attIndex = 0;
	//	attCount = 0;
	//}

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
		playerAttImg->frameRender(getMemDC(), rcPlayer.left, rcPlayer.top - 30);
	}
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
		//if (attIndex == 1)
		//{
			if (isLeft == false)
			{
				playerAttImg->setFrameY(0);
				if (animationCount % 5 == 0)
				{
					animationIndex++;
					if (animationIndex > 6)
					{
						animationIndex = 6;
					}
					playerAttImg->setFrameX(animationIndex);
				}
			}
			else
			{
				playerAttImg->setFrameY(1);
				if (animationCount % 5 == 0)
				{
					animationIndex--;
					if (animationIndex < 0)
					{
						animationIndex = 0;
					}
					playerAttImg->setFrameX(animationIndex);
				}
			}
		//}
		//if (attIndex == 2)
		//{
		//	if (isLeft == false)
		//	{
		//		playerAttImg->setFrameY(0);
		//		if (animationCount % 7 == 0)
		//		{
		//			animationIndex++;
		//			if (animationIndex > 9)
		//			{
		//				animationIndex = 9;
		//			}
		//			playerAttImg->setFrameX(animationIndex);
		//		}
		//	}
		//	else
		//	{
		//		playerAttImg->setFrameY(1);
		//		if (animationCount % 7 == 0)
		//		{
		//			animationIndex--;
		//			if (animationIndex < 0)
		//			{
		//				animationIndex = 0;
		//			}
		//			playerAttImg->setFrameX(animationIndex);
		//		}
		//	}
		//}
		break;
	case PLAYER_DASH:
		break;
	}
}
