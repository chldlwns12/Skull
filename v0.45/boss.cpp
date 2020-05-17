#include "stdafx.h"
#include "boss.h"
#include "player.h"

HRESULT boss::init()
{
	handIDLEImg_L = IMAGEMANAGER->findImage("보스손IDLE_L");
	handIDLEImg_R = IMAGEMANAGER->findImage("보스손IDLE_R");
	head = IMAGEMANAGER->findImage("보스머리");
	body = IMAGEMANAGER->findImage("보스몸통");
	mouse = IMAGEMANAGER->findImage("보스아랫턱");
	att1HandImg_L = IMAGEMANAGER->findImage("보스공격1_L");
	att1HandImg_R = IMAGEMANAGER->findImage("보스공격1_R");
	att2HandImg_L = IMAGEMANAGER->findImage("보스공격2_L");
	att2HandImg_R = IMAGEMANAGER->findImage("보스공격2_R");
	att3HandImg_L = IMAGEMANAGER->findImage("보스공격3_L");
	att3HandImg_R = IMAGEMANAGER->findImage("보스공격3_R");
	att2HandImg_TL = IMAGEMANAGER->findImage("보스공격2손_L");
	att2HandImg_TR = IMAGEMANAGER->findImage("보스공격2손_R");
	att2Head = IMAGEMANAGER->findImage("보스공격2머리");
	att2Body = IMAGEMANAGER->findImage("보스공격2몸통");
	att2Mouse = IMAGEMANAGER->findImage("보스공격2아랫턱");
	deadBody = IMAGEMANAGER->findImage("보스죽은후몸통");
	deadHead = IMAGEMANAGER->findImage("보스죽은후머리");
	deadMouse = IMAGEMANAGER->findImage("보스죽은후아랫턱");
	deadHand_L = IMAGEMANAGER->findImage("보스죽은후손");
	deadHand_R = IMAGEMANAGER->findImage("보스죽은후손");
	chargeEndHead = IMAGEMANAGER->findImage("탄막후머리");
	charge = IMAGEMANAGER->findImage("기모으기");
	groundeEfect = IMAGEMANAGER->findImage("땅이펙트");
	smallbullet = IMAGEMANAGER->findImage("보스작은총알");
	bigBullet = IMAGEMANAGER->findImage("보스큰총알");
	boom = IMAGEMANAGER->findImage("폭발이펙트");
	bossHpBar = new progressBar;
	bossHpBar->init("보스체력바_Front", "보스체력바_Back");
	bossHpBar->setPos(390, 30);


	bossMaxHp = 5000;
	bossHp = 5000;
	bossATK = 10;

	HeadAngle = 0.f;
	BodyAngle = 0.f;

	randomPattern = 0;

	count = index = 0;
	count2 = 0;
	index2 = 2;
	count3 = index3 = 0;

	patternCoolDown = 0;

	isStartPettern = false;
	isAttack = false;

	petternCount = 0;

	randomHand = 0;
	BodyX = WINSIZEX / 2 + 200;
	BodyY = 400;
	HeadX = WINSIZEX / 2 + 200;
	HeadY = 270;
	leftHandX = WINSIZEX / 2;
	leftHandY = 450;
	rightHandX = WINSIZEX / 2 + 430;
	rightHandY = 450;
	mouseX = WINSIZEX / 2 + 230;
	mouseY = 430;

	pettern1_left = false;
	leftHand = false;
	rightHand = false;
	pettern1Count = 0;
	startPattern1 = false;

	startPattern2 = false;
	pettern2Count = 0;
	Pattern2charge = false;
	Pattern2Fire = false;
	isFire = false;
	fireCount = 0;

	ptBullet = new bullet;
	ptBullet->init("보스작은총알", 8, 1000.f);
	ptBigBullet = new bullet;
	ptBigBullet->init("보스큰총알", 1, 1000.f, true);

	efectIndex = 0;
	efectCount = 0;
	AtkAngle = 0.f;
	isAttacked = false;
	skulAttEfect = IMAGEMANAGER->findImage("일반해골공격이펙트");
	samuraiAttEfect = IMAGEMANAGER->findImage("사무라이공격이펙트");
	soldierAttEfect = IMAGEMANAGER->findImage("사무라이공격이펙트");

	start = false;

	bossState = BOSS_IDLE;
	return S_OK;
}

void boss::release()
{
	ptBullet->release();
	ptBigBullet->release();
	bossHpBar->release();
}

void boss::update()
{
	bossHpBar->setGauge(bossMaxHp, bossHp);

	rcBody = RectMakeCenter(DATA->getPixelGround().x + BodyX, BodyY, 836, 682);
	rcHead = RectMakeCenter(DATA->getPixelGround().x + HeadX, HeadY, 482, 336);
	rcMouse = RectMakeCenter(DATA->getPixelGround().x + mouseX, mouseY, 220, 194);
	rcLeftHand = RectMakeCenter(DATA->getPixelGround().x + leftHandX, leftHandY, 350, 302);
	rcRightHand = RectMakeCenter(DATA->getPixelGround().x + rightHandX, rightHandY, 350, 302);
	bossHpBar->update();
	ptBullet->update();
	ptBigBullet->update();
	this->bossAnimation();
	this->bossAnimation2();
	patternCoolDown++;
	if (patternCoolDown % 100 == 0)
	{
		start = true;
	}
	if (start)
	{
		this->randomPettern();
	}
	playerBossATK();
	//pettern_2();
}

void boss::render()
{
	if (Pattern2Fire == false)
	{
		body->render(getMemDC(), rcBody.left, rcBody.top);
		head->render(getMemDC(), rcHead.left, rcHead.top);
		mouse->render(getMemDC(), rcMouse.left, rcMouse.top);
	}
	else
	{
		if (isFire)
		{
			att2Body->frameRender(getMemDC(), rcHead.left - 180, rcHead.top, 1, 0);
			att2Head->frameRender(getMemDC(), rcBody.left + 170, rcBody.top, 1, 0);
			att2Mouse->frameRender(getMemDC(), rcMouse.left - 10, rcMouse.top + 20, 1, 0);
		}
		else
		{
			att2Body->frameRender(getMemDC(), rcHead.left - 180, rcHead.top, 0, 0);
			att2Head->frameRender(getMemDC(), rcBody.left + 170, rcBody.top, 0, 0);
			att2Mouse->frameRender(getMemDC(), rcMouse.left - 10, rcMouse.top + 20, 0, 0);
		}
	}
	if (bossState == BOSS_IDLE)
	{
		handIDLEImg_L->frameRender(getMemDC(), rcLeftHand.left, rcLeftHand.top);
		handIDLEImg_R->frameRender(getMemDC(), rcRightHand.left, rcRightHand.top);
	}
	else if (bossState == BOSS_ATT1)
	{
		att1HandImg_L->frameRender(getMemDC(), rcLeftHand.left, rcLeftHand.top);
		att1HandImg_R->frameRender(getMemDC(), rcRightHand.left, rcRightHand.top);
	}
	else if (bossState == BOSS_ATT2)
	{
		if (Pattern2Fire == false)
		{
			att2HandImg_L->frameRender(getMemDC(), rcLeftHand.left - 50, rcLeftHand.top + 60);
			att2HandImg_R->frameRender(getMemDC(), rcRightHand.left + 50, rcRightHand.top + 60);
		}
		else
		{
			if (isFire)
			{
				att2HandImg_TL->frameRender(getMemDC(), rcLeftHand.left - 50, rcLeftHand.top + 110, 1, 0);
				att2HandImg_TR->frameRender(getMemDC(), rcRightHand.left + 50, rcRightHand.top + 110, 0, 0);
			}
			else if (isFire == false)
			{
				att2HandImg_TL->frameRender(getMemDC(), rcLeftHand.left - 50, rcLeftHand.top + 110, 0, 0);
				att2HandImg_TR->frameRender(getMemDC(), rcRightHand.left + 50, rcRightHand.top + 110, 1, 0);
			}
		}
		if (startPattern2 == true && Pattern2Fire == false)
		{
			charge->frameRender(getMemDC(), rcHead.left + 60, rcHead.top);
		}
	}

	if (isAttacked)
	{
		if (DATA->getPlayerRuin() == SKUL)
		{
			skulAttEfect->frameRender(getMemDC(), rcEfect.left, rcEfect.top, efectIndex, 0);
		}
		else if (DATA->getPlayerRuin() == SOLDIER)
		{
			soldierAttEfect->rotateFrameRender(getMemDC(), rcEfect.left, rcEfect.top, efectIndex, 0, AtkAngle);
		}
		else if (DATA->getPlayerRuin() == SAMURAI)
		{
			samuraiAttEfect->rotateFrameRender(getMemDC(), rcEfect.left, rcEfect.top, efectIndex, 0, AtkAngle);
		}
	}

	bossHpBar->render();
	IMAGEMANAGER->render("보스체력바_Back2", getMemDC(), 362, 30);
	IMAGEMANAGER->render("보스체력바_Back3", getMemDC(), 942, 30);
	ptBullet->render();
	ptBigBullet->render();
}

void boss::bossAnimation()
{
	switch (bossState)
	{
	case BOSS_IDLE:
		count++;
		handIDLEImg_L->setFrameY(0);
		if (count % 10 == 0)
		{
			index++;
			if (index > 4)
			{
				index = 0;
			}
			handIDLEImg_L->setFrameX(index);
		}
		count2++;
		handIDLEImg_R->setFrameY(0);
		if (count2 % 10 == 0)
		{
			index2--;
			if (index2 < 0)
			{
				index2 = 4;
			}
			handIDLEImg_R->setFrameX(index2);
		}
		break;
	case BOSS_ATT1:
		count++;
		att1HandImg_L->setFrameY(0);
		if (count % 8 == 0)
		{
			index++;
			if (index > 4)
			{
				index = 4;
			}
			att1HandImg_L->setFrameX(index);
		}
		count2++;
		att1HandImg_R->setFrameY(0);
		if (count2 % 8 == 0)
		{
			index2--;
			if (index2 < 0)
			{
				index2 = 0;
			}
			att1HandImg_R->setFrameX(index2);
		}
		break;
	case BOSS_ATT2:
		count++;
		att2HandImg_L->setFrameY(0);
		if (count % 8 == 0)
		{
			index++;
			if (index > 4)
			{
				index = 4;
			}
			att2HandImg_L->setFrameX(index);
		}
		count2++;
		att2HandImg_R->setFrameY(0);
		if (count2 % 8 == 0)
		{
			index2--;
			if (index2 < 0)
			{
				index2 = 0;
			}
			att2HandImg_R->setFrameX(index2);
		}
		break;
	case BOSS_ATT3:
		break;
	case BOSS_DEAD:
		break;
	}

	if (isAttacked)
	{
		efectCount++;

		if (DATA->getPlayerRuin() == SKUL)
		{
			skulAttEfect->setFrameY(0);
			if (efectCount % 4 == 0)
			{
				efectIndex++;
				if (efectIndex > 8)
				{
					efectIndex = 8;
				}
				skulAttEfect->setFrameX(efectIndex);
			}
		}
		if (DATA->getPlayerRuin() == SOLDIER)
		{
			soldierAttEfect->setFrameY(0);
			if (efectCount % 4 == 0)
			{
				efectIndex++;
				if (efectIndex > 11)
				{
					efectIndex = 11;
				}
				soldierAttEfect->setFrameX(efectIndex);
			}
		}
		if (DATA->getPlayerRuin() == SAMURAI)
		{
			samuraiAttEfect->setFrameY(0);
			if (efectCount % 4 == 0)
			{
				efectIndex++;
				if (efectIndex > 11)
				{
					efectIndex = 11;
				}
				samuraiAttEfect->setFrameX(efectIndex);
			}
		}
	}
}

void boss::bossAnimation2()
{
	switch (bossState)
	{
	case BOSS_IDLE:
		break;
	case BOSS_ATT1:
		break;
	case BOSS_ATT2:
		count3++;
		charge->setFrameY(0);
		if (count3 % 3 == 0)
		{
			index3++;
			if (index3 > 28)
			{
				pettern2Count++;
				index3 = 0;
				if (pettern2Count > 2)
				{
					Pattern2charge = true;
				}
			}
			charge->setFrameX(index3);
		}
		break;
	case BOSS_ATT3:
		break;
	case BOSS_DEAD:
		break;
	}
}

void boss::randomPettern()
{
	if (isStartPettern == false)
	{
		randomPattern = RANDOM->Range(1,2);
		isStartPettern = true;
	}
	switch (randomPattern)
	{
	case 1:
		this->pettern_1();
		break;
	case 2:
		this->pettern_2();
		break;
	}
}

void boss::pettern_1()
{
	bossState = BOSS_ATT1;

	if (leftHandX > 0 && leftHand == false)
	{
		leftHandX-= 5;
	}
	else
	{
		leftHand = true;
	}
	if (rightHandX < 1875 && rightHand == false)
	{
		rightHandX+= 5;
	}
	else
	{
		rightHand = true;
	}
	if (startPattern1 == false)
	{
		randomHand = RANDOM->Range(0, 1);
		startPattern1 = true;
		pettern1Count++;
	}
	
	if (leftHand && rightHand)
	{
		isAttack = true;
		if (randomHand == 0)
		{
			pettern1_left = true;
		}
		else
		{
			pettern1_left = false;
		}

		if (pettern1_left)
		{
			leftHandX += 10;
			if (leftHandX > 1875)
			{
				leftHandX = 0;
				startPattern1 = false;
			}
		}
		else
		{
			rightHandX -= 10;
			if (rightHandX < 0)
			{
				rightHandX = 1875.f;
				startPattern1 = false;
			}
		}
	}

	if (pettern1Count > 3)
	{
		isAttack = false;
		isStartPettern = false;
		bossState = BOSS_IDLE;
		leftHandX = WINSIZEX / 2;
		leftHandY = 450;
		rightHandX = WINSIZEX / 2 + 430;
		rightHandY = 450;
		start = false;
		patternCoolDown = 0;
		return;
	}
}

void boss::pettern_2()
{
	bossState = BOSS_ATT2;

	if (Pattern2charge == false)
	{
		if (BodyY < 480)
		{
			BodyY+=3;
		}

		if (HeadY < 400)
		{
			HeadY+=3;
		}
		if (HeadY >= 400)
		{
			startPattern2 = true;
		}

		if (mouseY < 550)
		{
			mouseY+=3;
		}
	}
	else
	{
		if (BodyY > 300)
		{
			BodyY -= 8;
		}

		if (HeadY > 120)
		{
			HeadY -= 12;
			Pattern2Fire = true;
		}

		if (mouseY > 260)
		{
			mouseY -= 12;
		}
	}

	if (Pattern2Fire)
	{
		fireCount++;
		if (fireCount % 100 == 0)
		{
			isAttack = true;
			isFire = true;
		}
	}

	if (isFire)
	{
		BigBulletAngle = getAngle(HeadX, HeadY, ptBossPlayer->getPlayerX() - DATA->getPixelGround().x, ptBossPlayer->getPlayerY() - DATA->getPixelGround().x);
		ptBigBullet->fire(HeadX, HeadY, BigBulletAngle, 6.f);

		pettern2Count++;
		isFire = false;
		if (pettern2Count > 3)
		{
			isAttack = false;
			bossState = BOSS_IDLE;
			leftHandX = WINSIZEX / 2;
			leftHandY = 450;
			rightHandX = WINSIZEX / 2 + 430;
			rightHandY = 450;
			start = false;
			patternCoolDown = 0;
			return;
		}
	}
}

void boss::playerBossATK()
{
	RECT rcTemp11;
	if (IntersectRect(&rcTemp11, &rcHead, &ptBossPlayer->getRcATK()) && ptBossPlayer->getIsATK() == true)
	{
		if (bossState == BOSS_DEAD) return;
		if (DATA->getPlayerRuin() == SKUL)
		{
			rcEfect = RectMakeCenter(DATA->getPixelGround().x + HeadX, HeadY, 124, 74);
			bossHp -= ptBossPlayer->getPlayerATK();
		}
		else if (DATA->getPlayerRuin() == SOLDIER)
		{
			rcEfect = RectMakeCenter(DATA->getPixelGround().x + HeadX, HeadY, 72, 94);
			bossHp -= ptBossPlayer->getPlayerATK();
		}
		else if (DATA->getPlayerRuin() == SAMURAI)
		{
			rcEfect = RectMakeCenter(DATA->getPixelGround().x + HeadX, HeadY, 72, 94);
			bossHp -= ptBossPlayer->getPlayerATK() * 2;
		}

		isAttacked = true;
		efectIndex = 0;
		AtkAngle = RANDOM->Range(6.28f);
	}
	else
	{
		isAttacked = false;
	}

	if (bossHp <= 0)
	{
		bossState = BOSS_DEAD;
	}
}