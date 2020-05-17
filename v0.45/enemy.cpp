#include "stdafx.h"
#include "enemy.h"
#include "player.h"

HRESULT enemy::init()
{
	setEnemy(ENEMY_TREE, 630, 260, 84, 93);
	setEnemy(ENEMY_SOLDIER, 1200, 600, 62, 106);
	setEnemy(ENEMY_SOLDIER, 1400, 600, 62, 106);
	setEnemy(ENEMY_BIGTREE, 1020, 437, 224, 220);
	setEnemy(ENEMY_BIGSOLDIER, 1700, 555, 212, 192);
	//enemyHp = new enemyHpbar;
	//enemyHp->init("enemyHp_Front", "enemyHp_Back",vEnemy.size());
	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	for (int i = 0; i < vEnemy.size(); i++)
	{
		//enemyHp->setGauge(vEnemy[i].maxHp, vEnemy[i].hp);
		//enemyHp->setPos(DATA->getPixelGround().x + vEnemy[i].enemyX, DATA->getPixelGround().y + vEnemy[i].enemyY + 100, vEnemy.size());
		vEnemy[i].rc = RectMakeCenter(DATA->getPixelGround().x + vEnemy[i].enemyX, DATA->getPixelGround().y + vEnemy[i].enemyY, vEnemy[i].Width, vEnemy[i].Height);
		vEnemy[i].attScope = RectMakeCenter(DATA->getPixelGround().x + vEnemy[i].enemyX, DATA->getPixelGround().y + vEnemy[i].enemyY, 500, 93);
		if (vEnemy[i].kind == ENEMY_SOLDIER || vEnemy[i].kind == ENEMY_TREE)
		{
			vEnemy[i].rcAtk = RectMakeCenter(DATA->getPixelGround().x + vEnemy[i].enemyX, DATA->getPixelGround().y + vEnemy[i].enemyY, 70, 93);
			vEnemy[i].rcAtt = RectMakeCenter(DATA->getPixelGround().x + vEnemy[i].enemyX, DATA->getPixelGround().y + vEnemy[i].enemyY, 90, 93);
		}
		if (vEnemy[i].kind == ENEMY_BIGSOLDIER || vEnemy[i].kind == ENEMY_BIGTREE)
		{
			vEnemy[i].rcAtk = RectMakeCenter(DATA->getPixelGround().x + vEnemy[i].enemyX, DATA->getPixelGround().y + vEnemy[i].enemyY, 260, 103);
			vEnemy[i].rcAtt = RectMakeCenter(DATA->getPixelGround().x + vEnemy[i].enemyX, DATA->getPixelGround().y + vEnemy[i].enemyY + 80, 200, 33);
		}
		//soldier.rc = RectMakeCenter(DATA->getPixelGround().x + soldier.enemyX, DATA->getPixelGround().y + soldier.enemyY, 45, 80);
		//soldier.attScope = RectMakeCenter(DATA->getPixelGround().x + soldier.enemyX, DATA->getPixelGround().y + soldier.enemyY, 200, 80);
	}
	//공격범위에 들어왔을때 플레이어 오는 로직
	this->enemyScope();
	this->enemyMove();
	this->enemyAnimation();
	this->playerEnemyATK();
}

void enemy::render()
{
	char str10[100];
	char str11[100];
	for (int i = 0; i < vEnemy.size(); i++)
	{
		Rectangle(getMemDC(), vEnemy[i].rcAtt);
		if (vEnemy.empty()) continue;

		if (vEnemy[i].state == ENEMY_IDLE)
		{
			if (vEnemy[i].isLeft)
			{
				vEnemy[i].idleImg->frameRender(getMemDC(), vEnemy[i].rc.left, vEnemy[i].rc.top, vEnemy[i].index, 1);
			}
			else
			{
				vEnemy[i].idleImg->frameRender(getMemDC(), vEnemy[i].rc.left, vEnemy[i].rc.top, vEnemy[i].index, 0);
			}
		}
		if (vEnemy[i].state == ENEMY_RUN)
		{
			if (vEnemy[i].kind == ENEMY_BIGTREE) continue;
			if (vEnemy[i].isLeft)
			{
				vEnemy[i].runImg->frameRender(getMemDC(), vEnemy[i].rc.left, vEnemy[i].rc.top + vEnemy[i].runY, vEnemy[i].index, 1);
			}
			else
			{
				vEnemy[i].runImg->frameRender(getMemDC(), vEnemy[i].rc.left, vEnemy[i].rc.top + vEnemy[i].runY, vEnemy[i].index, 0);
			}
		}
		if (vEnemy[i].state == ENEMY_ATT)
		{
			if (vEnemy[i].isLeft)
			{
				vEnemy[i].attImg->frameRender(getMemDC(), vEnemy[i].rc.left + vEnemy[i].attX, vEnemy[i].rc.top + vEnemy[i].attY, vEnemy[i].index, 1);
			}
			else
			{
				vEnemy[i].attImg->frameRender(getMemDC(), vEnemy[i].rc.left + vEnemy[i].attX, vEnemy[i].rc.top + vEnemy[i].attY, vEnemy[i].index, 0);
			}
		}
		if (vEnemy[i].state == ENEMY_HIT)
		{
			if (vEnemy[i].isLeft)
			{
				vEnemy[i].hitImg->frameRender(getMemDC(), vEnemy[i].rc.left, vEnemy[i].rc.top + vEnemy[i].hitY, vEnemy[i].index, 1);
			}
			else
			{
				vEnemy[i].hitImg->frameRender(getMemDC(), vEnemy[i].rc.left, vEnemy[i].rc.top + vEnemy[i].hitY, vEnemy[i].index, 0);
			}
		}
		if (vEnemy[i].state == ENEMY_DEAD)
		{
			if (vEnemy[i].isLeft)
			{
				vEnemy[i].deadImg->frameRender(getMemDC(), vEnemy[i].rc.left + vEnemy[i].deadX, vEnemy[i].rc.top + vEnemy[i].deadY, vEnemy[i].index, 1);
			}
			else
			{
				vEnemy[i].deadImg->frameRender(getMemDC(), vEnemy[i].rc.left + vEnemy[i].deadX, vEnemy[i].rc.top + vEnemy[i].deadY, vEnemy[i].index, 0);
			}
			vEnemy[i].deadEfectImg->frameRender(getMemDC(), vEnemy[i].rc.left - 40, vEnemy[i].rc.top - 50, vEnemy[i].efectIndex, vEnemy[i].efectIndex);
		}
		if (vEnemy[i].isAtacked)
		{
			if (vEnemy[i].isSkill)
			{
				if (DATA->getPlayerRuin() == SOLDIER)
				{
					vEnemy[i].soldierAttEfect->rotateFrameRender(getMemDC(), rcEfect.left, rcEfect.top, vEnemy[i].efectIndex, 0, vEnemy[i].AtkAngle);
				}
				else if (DATA->getPlayerRuin() == SAMURAI)
				{
					vEnemy[i].samuraiSkill1_E->rotateFrameRender(getMemDC(), rcEfect.left, rcEfect.top, vEnemy[i].efectIndex, 0, vEnemy[i].AtkAngle);
				}
			}
			else
			{
				if (DATA->getPlayerRuin() == SKUL)
				{
					vEnemy[i].skulAttEfect->frameRender(getMemDC(), rcEfect.left, rcEfect.top, vEnemy[i].efectIndex, 0);
				}
				else if (DATA->getPlayerRuin() == SOLDIER)
				{
					vEnemy[i].soldierAttEfect->rotateFrameRender(getMemDC(), rcEfect.left, rcEfect.top, vEnemy[i].efectIndex, 0, vEnemy[i].AtkAngle);
				}
				else if (DATA->getPlayerRuin() == SAMURAI)
				{
					vEnemy[i].samuraiAttEfect->rotateFrameRender(getMemDC(), rcEfect.left, rcEfect.top, vEnemy[i].efectIndex, 0, vEnemy[i].AtkAngle);
				}
			}
		sprintf(str10, "maxCool : %d", vEnemy[i].efectCount);
		TextOut(getMemDC(), 10, 270, str10, strlen(str10));
		sprintf(str11, "STATE : %d", vEnemy[i].efectIndex);
		TextOut(getMemDC(), 10, 290, str11, strlen(str11));
		}
		//enemyHp->render();
	}
	
	
}

void enemy::enemyAnimation()
{
	for (int i = 0; i < vEnemy.size(); i++)
	{
		if (vEnemy.empty()) continue;

		switch (vEnemy[i].state)
		{
		case ENEMY_IDLE:
			vEnemy[i].count++;
			if (vEnemy[i].isLeft == false)
			{
				vEnemy[i].idleImg->setFrameY(0);
				if (vEnemy[i].count % 5 == 0)
				{
					vEnemy[i].index++;
					if (vEnemy[i].index > 5)
					{
						vEnemy[i].index = 0;
					}
					vEnemy[i].idleImg->setFrameX(vEnemy[i].index);
				}
			}
			else
			{
				vEnemy[i].idleImg->setFrameY(1);
				if (vEnemy[i].count % 5 == 0)
				{
					vEnemy[i].index--;
					if (vEnemy[i].index < 0)
					{
						vEnemy[i].index = 5;
					}
					vEnemy[i].idleImg->setFrameX(vEnemy[i].index);
				}
			}
			break;
		case ENEMY_RUN:
			if (vEnemy[i].kind == ENEMY_BIGTREE) continue;
			vEnemy[i].count++;
			if (vEnemy[i].isLeft == false)
			{
				vEnemy[i].runImg->setFrameY(0);
				if (vEnemy[i].count % 6 == 0)
				{
					vEnemy[i].index++;
					if (vEnemy[i].index > 6)
					{
						vEnemy[i].index = 0;
					}
					vEnemy[i].runImg->setFrameX(vEnemy[i].index);
				}
			}
			else
			{
				vEnemy[i].runImg->setFrameY(1);
				if (vEnemy[i].count % 6 == 0)
				{
					vEnemy[i].index--;
					if (vEnemy[i].index < 0)
					{
						vEnemy[i].index = 6;
					}
					vEnemy[i].runImg->setFrameX(vEnemy[i].index);
				}
			}
			break;
		case ENEMY_ATT:
			vEnemy[i].count++;
			if (vEnemy[i].isLeft == false)
			{
				vEnemy[i].attImg->setFrameY(0);
				if (vEnemy[i].count % 8 == 0)
				{
					vEnemy[i].index++;
					if (vEnemy[i].index > 7)
					{
						vEnemy[i].isAttack = true;
						vEnemy[i].index = 0;
					}
					else
					{
						vEnemy[i].isAttack = false;
					}
					vEnemy[i].attImg->setFrameX(vEnemy[i].index);
				}
			}
			else
			{
				vEnemy[i].attImg->setFrameY(1);
				if (vEnemy[i].count % 8 == 0)
				{
					vEnemy[i].index--;
					if (vEnemy[i].index < 0)
					{
						vEnemy[i].isAttack = true;
						vEnemy[i].index = 7;
					}
					else
					{
						vEnemy[i].isAttack = false;
					}
					vEnemy[i].attImg->setFrameX(vEnemy[i].index);
				}
			}
			break;
		case ENEMY_HIT:	
			vEnemy[i].count++;

			if (vEnemy[i].isLeft == false)
			{
				vEnemy[i].hitImg->setFrameY(0);
				if (vEnemy[i].count % 8 == 0)
				{
					vEnemy[i].index++;
					if (vEnemy[i].index > 2)
					{
						vEnemy[i].index = 0;
					}
					vEnemy[i].hitImg->setFrameX(vEnemy[i].index);
				}
			}
			else
			{
				vEnemy[i].hitImg->setFrameY(1);
				if (vEnemy[i].count % 8 == 0)
				{
					vEnemy[i].index--;
					if (vEnemy[i].index < 0)
					{
						vEnemy[i].index = 2;
					}
					vEnemy[i].hitImg->setFrameX(vEnemy[i].index);
				}
			}

			break;
		case ENEMY_DEAD:
			vEnemy[i].count++;

			if (vEnemy[i].isLeft == false)
			{
				vEnemy[i].deadImg->setFrameY(0);
				if (vEnemy[i].count % 5 == 0)
				{
					vEnemy[i].index++;
					if (vEnemy[i].index > 2)
					{
						vEnemy[i].index = 2;
					}
					vEnemy[i].deadImg->setFrameX(vEnemy[i].index);
				}
			}
			else
			{
				vEnemy[i].deadImg->setFrameY(1);
				if (vEnemy[i].count % 5 == 0)
				{
					vEnemy[i].index--;
					if (vEnemy[i].index < 0)
					{
						vEnemy[i].index = 0;
					}
					vEnemy[i].deadImg->setFrameX(vEnemy[i].index);
				}
			}
			break;
		}
		if (vEnemy[i].isAtacked)
		{
			vEnemy[i].efectCount++;

			if (DATA->getPlayerRuin() == SKUL)
			{
				vEnemy[i].skulAttEfect->setFrameY(0);
				if (vEnemy[i].efectCount % 4 == 0)
				{
					vEnemy[i].efectIndex++;
					if (vEnemy[i].efectIndex > 8)
					{
						vEnemy[i].efectIndex = 8;
						vEnemy[i].isAtacked = false;
					}
					vEnemy[i].skulAttEfect->setFrameX(vEnemy[i].efectIndex);
				}
			}
			if (DATA->getPlayerRuin() == SOLDIER)
			{
				vEnemy[i].soldierAttEfect->setFrameY(0);
				if (vEnemy[i].efectCount % 4 == 0)
				{
					vEnemy[i].efectIndex++;
					if (vEnemy[i].efectIndex > 11)
					{
						vEnemy[i].efectIndex = 11;
						vEnemy[i].isAtacked = false;
					}
					vEnemy[i].soldierAttEfect->setFrameX(vEnemy[i].efectIndex);
				}
			}
			if (DATA->getPlayerRuin() == SAMURAI)
			{
				vEnemy[i].samuraiAttEfect->setFrameY(0);
				if (vEnemy[i].efectCount % 4 == 0)
				{
					vEnemy[i].efectIndex++;
					if (vEnemy[i].efectIndex > 11)
					{
						vEnemy[i].efectIndex = 11;
						vEnemy[i].isAtacked = false;
					}
					vEnemy[i].samuraiAttEfect->setFrameX(vEnemy[i].efectIndex);
				}
			}
		}
		if (vEnemy[i].isDead)
		{
			vEnemy[i].efectCount++;

			vEnemy[i].deadEfectImg->setFrameY(0);
			if (vEnemy[i].efectCount % 4 == 0)
			{
				vEnemy[i].efectIndex++;
				if (vEnemy[i].efectIndex > 11)
				{
					vEnemy[i].efectIndex = 11;
					vEnemy[i].isEndEfect = true;
				}
				vEnemy[i].deadEfectImg->setFrameX(vEnemy[i].efectIndex);
			}
		}
	}

	//switch (tree.state)
	//{
	//case ENEMY_IDLE:
	//	tree.count++;
	//	if (tree.isLeft == false)
	//	{
	//		tree.idleImg->setFrameY(0);
	//		if (tree.count % 5 == 0)
	//		{
	//			tree.index++;
	//			if (tree.index > 5)
	//			{
	//				tree.index = 0;
	//			}
	//			tree.idleImg->setFrameX(tree.index);
	//		}
	//	}
	//	else
	//	{
	//		tree.idleImg->setFrameY(1);
	//		if (tree.count % 5 == 0)
	//		{
	//			tree.index--;
	//			if (tree.index < 0)
	//			{
	//				tree.index = 5;
	//			}
	//			tree.idleImg->setFrameX(tree.index);
	//		}
	//	}
	//	break;
	//case ENEMY_RUN:
	//	tree.count++;
	//	if (tree.isLeft == false)
	//	{
	//		tree.runImg->setFrameY(0);
	//		if (tree.count % 6 == 0)
	//		{
	//			tree.index++;
	//			if (tree.index > 6)
	//			{
	//				tree.index = 0;
	//			}
	//			tree.runImg->setFrameX(tree.index);
	//		}
	//	}
	//	else
	//	{
	//		tree.runImg->setFrameY(1);
	//		if (tree.count % 6 == 0)
	//		{
	//			tree.index--;
	//			if (tree.index < 0)
	//			{
	//				tree.index = 6;
	//			}
	//			tree.runImg->setFrameX(tree.index);
	//		}
	//	}
	//	break;
	//case ENEMY_ATT:
	//	tree.count++;
	//	if (tree.isLeft == false)
	//	{
	//		tree.attImg->setFrameY(0);
	//		if (tree.count % 8 == 0)
	//		{
	//			tree.index++;
	//			if (tree.index > 4)
	//			{
	//				tree.index = 0;
	//			}
	//			tree.attImg->setFrameX(tree.index);
	//		}
	//	}
	//	else
	//	{
	//		tree.attImg->setFrameY(1);
	//		if (tree.count % 8 == 0)
	//		{
	//			tree.index--;
	//			if (tree.index < 0)
	//			{
	//				tree.index = 4;
	//			}
	//			tree.attImg->setFrameX(tree.index);
	//		}
	//	}
	//	break;
	//case ENEMY_HIT:
	//	break;
	//case ENEMY_DEAD:
	//	break;
	//}
	//
	//switch (soldier.state)
	//{
	//case ENEMY_IDLE:
	//	soldier.count++;
	//	if (soldier.isLeft == false)
	//	{
	//		soldier.idleImg->setFrameY(0);
	//		if (soldier.count % 5 == 0)
	//		{
	//			soldier.index++;
	//			if (soldier.index > 5)
	//			{
	//				soldier.index = 0;
	//			}
	//			soldier.idleImg->setFrameX(soldier.index);
	//		}
	//	}
	//	else
	//	{
	//		soldier.idleImg->setFrameY(1);
	//		if (soldier.count % 5 == 0)
	//		{
	//			soldier.index--;
	//			if (soldier.index < 0)
	//			{
	//				soldier.index = 5;
	//			}
	//			soldier.idleImg->setFrameX(soldier.index);
	//		}
	//	}
	//	break;
	//case ENEMY_RUN:
	//	break;
	//case ENEMY_ATT:
	//	break;
	//case ENEMY_HIT:
	//	break;
	//case ENEMY_DEAD:
	//	break;
	//}
}

void enemy::enemyScope()
{
	RECT rcTemp;
	for (int i = 0; i < vEnemy.size(); i++)
	{
		if (IntersectRect(&rcTemp, &DATA->getPlayerRc(), &vEnemy[i].attScope))
		{
			vEnemy[i].isAtt = true;
		}
		else
		{
			vEnemy[i].isAtt = false;
		}

		//if (IntersectRect(&rcTemp, &DATA->getPlayerRc(), &soldier.attScope))
		//{
		//	soldier.isAtt = true;
		//}
		//else
		//{
		//	soldier.isAtt = false;
		//}
	}
}

void enemy::enemyMove()
{
	RECT rcTemp10;
	for (int i = 0; i < vEnemy.size(); i++)
	{
		if (vEnemy[i].isDead == false)
		{
			if (vEnemy[i].kind == ENEMY_BIGTREE)
			{
				if (IntersectRect(&rcTemp10, &DATA->getPlayerRc(), &vEnemy[i].rc))
				{
					vEnemy[i].state = ENEMY_ATT;
				}
				else
				{
					vEnemy[i].state = ENEMY_IDLE;
				}
			}
			else
			{
				if (vEnemy[i].isAtt)
				{
					if (DATA->getPlayerRc().right < DATA->getPixelGround().x + vEnemy[i].enemyX - 30)
					{
						if (IntersectRect(&rcTemp10, &DATA->getPlayerRc(), &vEnemy[i].rcAtk))
						{
							vEnemy[i].state = ENEMY_ATT;
						}
						else
						{
							vEnemy[i].isLeft = true;
							vEnemy[i].enemyX -= 4;
							vEnemy[i].state = ENEMY_RUN;
						}

					}

					if (DATA->getPlayerRc().left > DATA->getPixelGround().x + vEnemy[i].enemyX + 30)
					{
						if (IntersectRect(&rcTemp10, &DATA->getPlayerRc(), &vEnemy[i].rcAtk))
						{
							vEnemy[i].state = ENEMY_ATT;
						}
						else
						{
							vEnemy[i].isLeft = false;
							vEnemy[i].enemyX += 4;
							vEnemy[i].state = ENEMY_RUN;
						}

					}
				}
				else
				{
					vEnemy[i].state = ENEMY_IDLE;
				}
			}
		}
	}
}

void enemy::setEnemy(ENEMYKIND kind, float X, float Y, int Width, int Height)
{
	switch (kind)
	{
	case ENEMY_TREE:
		tree.enemyX = X;
		tree.enemyY = Y;
		tree.att = 6;
		tree.count = 0;
		tree.index = 0;
		tree.efectCount = 0;
		tree.efectIndex = 0;
		tree.state = ENEMY_IDLE;
		tree.idleImg = IMAGEMANAGER->findImage("나무IDLE");
		tree.runImg = IMAGEMANAGER->findImage("나무달리기");
		tree.attImg = IMAGEMANAGER->findImage("나무공격");
		tree.hitImg = IMAGEMANAGER->findImage("나무히트");
		tree.deadImg = IMAGEMANAGER->findImage("나무죽음");
		tree.maxHp = 1500;
		tree.hp = 1500;
		tree.isLeft = false;
		tree.isAtt = false;
		tree.Width = Width;
		tree.Height = Height;
		tree.attY = 0;
		tree.attX = 0;
		tree.runY = 0;
		tree.hitY = 0;
		tree.deadY = 50;
		tree.deadX = 0;
		tree.isAtacked = false;
		tree.AtkAngle = 0.f;
		tree.skulAttEfect = IMAGEMANAGER->findImage("일반해골공격이펙트");
		tree.samuraiAttEfect = IMAGEMANAGER->findImage("사무라이공격이펙트");
		tree.soldierAttEfect = IMAGEMANAGER->findImage("사무라이공격이펙트");
		tree.deadEfectImg = IMAGEMANAGER->findImage("적죽음이펙트");
		tree.summonEfectImg = IMAGEMANAGER->findImage("적소환이펙트");
		tree.samuraiSkill1_E = IMAGEMANAGER->findImage("사무라이스킬1이펙트");
		tree.isDead = false;
		tree.kind = ENEMY_TREE;
		tree.isEndEfect = false;
		tree.isAttack = false;
		tree.isSkill = false;
		tree.isAngle = false;

		vEnemy.push_back(tree);
		break;
	case SOLDIER:
		soldier.enemyX = X;
		soldier.enemyY = Y;
		soldier.att = 8;
		soldier.count = 0;
		soldier.index = 0;
		soldier.state = ENEMY_IDLE;
		soldier.idleImg = IMAGEMANAGER->findImage("병사IDLE");
		soldier.runImg = IMAGEMANAGER->findImage("병사달리기");
		soldier.attImg = IMAGEMANAGER->findImage("병사공격");
		soldier.hitImg = IMAGEMANAGER->findImage("병사히트");
		soldier.deadImg = IMAGEMANAGER->findImage("병사죽음");
		soldier.maxHp = 2000;
		soldier.hp = 2000;
		soldier.isLeft = false;
		soldier.isAtt = false;
		soldier.Width = Width;
		soldier.Height = Height;
		soldier.attY = -15;
		soldier.attX = 0;
		soldier.runY = 12;
		soldier.hitY = 0;
		soldier.deadY = 78;
		soldier.deadX = 0;
		soldier.isAtacked = false;
		soldier.AtkAngle = 0.f;
		soldier.skulAttEfect = IMAGEMANAGER->findImage("일반해골공격이펙트");
		soldier.samuraiAttEfect = IMAGEMANAGER->findImage("사무라이공격이펙트");
		soldier.soldierAttEfect = IMAGEMANAGER->findImage("사무라이공격이펙트");
		soldier.deadEfectImg = IMAGEMANAGER->findImage("적죽음이펙트");
		soldier.summonEfectImg = IMAGEMANAGER->findImage("적소환이펙트");
		soldier.samuraiSkill1_E = IMAGEMANAGER->findImage("사무라이스킬1이펙트");
		soldier.isDead = false;
		soldier.kind = ENEMY_SOLDIER;
		soldier.isEndEfect = false;
		soldier.isAttack = false;
		soldier.isSkill = false;
		soldier.isAngle = false;

		vEnemy.push_back(soldier);
		break;
	case ENEMY_BIGTREE:
		bigTree.enemyX = X;
		bigTree.enemyY = Y;
		bigTree.att = 10;
		bigTree.count = 0;
		bigTree.index = 0;
		bigTree.state = ENEMY_IDLE;
		bigTree.idleImg = IMAGEMANAGER->findImage("큰나무IDLE");
		bigTree.attImg = IMAGEMANAGER->findImage("큰나무공격1");
		bigTree.attImg2 = IMAGEMANAGER->findImage("큰나무공격2");
		bigTree.bulletImg = IMAGEMANAGER->findImage("큰나무총알");
		bigTree.deadImg = IMAGEMANAGER->findImage("큰나무죽음");
		bigTree.maxHp = 4000;
		bigTree.hp = 4000;
		bigTree.isLeft = false;
		bigTree.isAtt = false;
		bigTree.Width = Width;
		bigTree.Height = Height;
		bigTree.attY = 0;
		bigTree.attX = -10;
		bigTree.runY = 12;
		bigTree.hitY = 0;
		bigTree.deadY = 58;
		bigTree.deadX = 25;
		bigTree.isAtacked = false;
		bigTree.AtkAngle = 0.f;
		bigTree.skulAttEfect = IMAGEMANAGER->findImage("일반해골공격이펙트");
		bigTree.samuraiAttEfect = IMAGEMANAGER->findImage("사무라이공격이펙트");
		bigTree.soldierAttEfect = IMAGEMANAGER->findImage("사무라이공격이펙트");
		bigTree.deadEfectImg = IMAGEMANAGER->findImage("적죽음이펙트");
		bigTree.summonEfectImg = IMAGEMANAGER->findImage("적소환이펙트");
		bigTree.samuraiSkill1_E = IMAGEMANAGER->findImage("사무라이스킬1이펙트");
		bigTree.isDead = false;
		bigTree.kind = ENEMY_BIGTREE;
		bigTree.isEndEfect = false;
		bigTree.isAttack = false;
		bigTree.isSkill = false;
		bigTree.isAngle = false;

		vEnemy.push_back(bigTree);
		break;
	case ENEMY_BIGSOLDIER:
		bigSoldier.enemyX = X;
		bigSoldier.enemyY = Y;
		bigSoldier.att = 12;
		bigSoldier.count = 0;
		bigSoldier.index = 0;
		bigSoldier.state = ENEMY_IDLE;
		bigSoldier.idleImg = IMAGEMANAGER->findImage("큰병사IDLE");
		bigSoldier.runImg = IMAGEMANAGER->findImage("큰병사달리기");
		bigSoldier.attImg = IMAGEMANAGER->findImage("큰병사공격1");
		bigSoldier.attImg2 = IMAGEMANAGER->findImage("큰병사공격2");
		bigSoldier.deadImg = IMAGEMANAGER->findImage("큰병사죽음");
		bigSoldier.maxHp = 4000;
		bigSoldier.hp = 4000;
		bigSoldier.isLeft = false;
		bigSoldier.isAtt = false;
		bigSoldier.Width = Width;
		bigSoldier.Height = Height;
		bigSoldier.attY = -10;
		bigSoldier.attX = -10;
		bigSoldier.runY = 12;
		bigSoldier.hitY = 0;
		bigSoldier.deadY = -5;
		bigSoldier.deadX = 25;
		bigSoldier.isAtacked = false;
		bigSoldier.AtkAngle = 0.f;
		bigSoldier.skulAttEfect = IMAGEMANAGER->findImage("일반해골공격이펙트");
		bigSoldier.samuraiAttEfect = IMAGEMANAGER->findImage("사무라이공격이펙트");
		bigSoldier.soldierAttEfect = IMAGEMANAGER->findImage("사무라이공격이펙트");
		bigSoldier.deadEfectImg = IMAGEMANAGER->findImage("적죽음이펙트");
		bigSoldier.summonEfectImg = IMAGEMANAGER->findImage("적소환이펙트");
		bigSoldier.samuraiSkill1_E = IMAGEMANAGER->findImage("사무라이스킬1이펙트");
		bigSoldier.isDead = false;
		bigSoldier.kind = ENEMY_BIGSOLDIER;
		bigSoldier.isEndEfect = false;
		bigSoldier.isAttack = false;
		bigSoldier.isSkill = false;
		bigSoldier.isAngle = false;

		vEnemy.push_back(bigSoldier);
		break;
	case ENEMY_WIZARD:
		break;
	case ENEMY_ARCHER:
		break;
	}
}

void enemy::playerEnemyATK()
{
	RECT rcTemp9;
	for (int i = 0; i < vEnemy.size(); i++)
	{
		if (IntersectRect(&rcTemp9, &ptEnemyPlayer->getRcATK(), &vEnemy[i].rc) && ptEnemyPlayer->getIsATK() == true)
		{
			if (vEnemy[i].isEndEfect == true || vEnemy[i].state == ENEMY_DEAD) continue;
			if (DATA->getPlayerRuin() == SKUL)
			{
				rcEfect = RectMakeCenter(DATA->getPixelGround().x + vEnemy[i].enemyX, vEnemy[i].enemyY, 124, 74);
				vEnemy[i].hp -= ptEnemyPlayer->getPlayerATK();
			}
			else if (DATA->getPlayerRuin() == SOLDIER)
			{
				rcEfect = RectMakeCenter(DATA->getPixelGround().x + vEnemy[i].enemyX + 20, vEnemy[i].enemyY + 40, 72, 94);
				vEnemy[i].hp -= ptEnemyPlayer->getPlayerATK();
			}
			else if (DATA->getPlayerRuin() == SAMURAI)
			{
				rcEfect = RectMakeCenter(DATA->getPixelGround().x + vEnemy[i].enemyX + 20, vEnemy[i].enemyY + 40, 72, 94);
				vEnemy[i].hp -= ptEnemyPlayer->getPlayerATK() * 2;
			}
			vEnemy[i].efectIndex = 0;
			if (vEnemy[i].isAngle == false)
			{
				vEnemy[i].AtkAngle = RANDOM->Range(6.28f);
				vEnemy[i].isAngle = true;
			}
			if (!(vEnemy[i].kind == ENEMY_BIGTREE || vEnemy[i].kind == ENEMY_BIGSOLDIER))
			{
				vEnemy[i].state = ENEMY_HIT;
			}
			vEnemy[i].isAtacked = true;
			vEnemy[i].isSkill = false;
		}
		else
		{
			vEnemy[i].isAngle = false;
		}

		if (IntersectRect(&rcTemp9, &ptEnemyPlayer->getRcSkill(), &vEnemy[i].rc))
		{
			if (vEnemy[i].isEndEfect == true || vEnemy[i].state == ENEMY_DEAD) continue;
			if (DATA->getPlayerRuin() == SKUL)
			{
				rcEfect = RectMakeCenter(DATA->getPixelGround().x + vEnemy[i].enemyX, vEnemy[i].enemyY, 124, 74);
				vEnemy[i].hp -= ptEnemyPlayer->getPlayerATK();
			}
			else if (DATA->getPlayerRuin() == SOLDIER)
			{
				rcEfect = RectMakeCenter(DATA->getPixelGround().x + vEnemy[i].enemyX + 20, vEnemy[i].enemyY + 40, 72, 94);
				vEnemy[i].hp -= ptEnemyPlayer->getPlayerATK();
			}
			else if (DATA->getPlayerRuin() == SAMURAI)
			{
				rcEfect = RectMakeCenter(DATA->getPixelGround().x + vEnemy[i].enemyX + 20, vEnemy[i].enemyY + 40, 72, 94);
				vEnemy[i].hp -= ptEnemyPlayer->getPlayerATK() * 2;
			}
			vEnemy[i].efectIndex = 0;
			if (vEnemy[i].isAngle == false)
			{
				vEnemy[i].AtkAngle = RANDOM->Range(6.28f);
				vEnemy[i].isAngle = true;
			}
			if (!(vEnemy[i].kind == ENEMY_BIGTREE || vEnemy[i].kind == ENEMY_BIGSOLDIER))
			{
				vEnemy[i].state = ENEMY_HIT;
			}
			vEnemy[i].isSkill = true;
			vEnemy[i].isAtacked = true;
		}
		else
		{
			vEnemy[i].isAngle = false;
		}

		if (vEnemy[i].hp <= 0)
		{
			if (vEnemy[i].isEndEfect == true) continue;
			vEnemy[i].state = ENEMY_DEAD;
			vEnemy[i].isAtacked = false;
			vEnemy[i].isDead = true;
		}
	}
}
