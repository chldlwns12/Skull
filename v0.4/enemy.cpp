#include "stdafx.h"
#include "enemy.h"

HRESULT enemy::init()
{
	tree.enemyX = 630;
	tree.enemyY = 260;
	tree.att = 0;
	tree.count = 0;
	tree.index = 0;
	tree.state = ENEMY_IDLE;
	tree.idleImg = IMAGEMANAGER->findImage("나무IDLE");
	tree.runImg = IMAGEMANAGER->findImage("나무달리기");
	tree.attImg = IMAGEMANAGER->findImage("나무공격");
	tree.hitImg = IMAGEMANAGER->findImage("나무히트");
	tree.deadImg = IMAGEMANAGER->findImage("나무죽음");
	tree.hp = 10;
	tree.isLeft = false;
	tree.isAtt = false;

	soldier.enemyX = 1200;
	soldier.enemyY = 610;
	soldier.att = 0;
	soldier.count = 0;
	soldier.index = 0;
	soldier.state = ENEMY_IDLE;
	soldier.idleImg = IMAGEMANAGER->findImage("병사IDLE");
	soldier.runImg = IMAGEMANAGER->findImage("병사달리기");
	soldier.attImg = IMAGEMANAGER->findImage("병사공격");
	soldier.hitImg = IMAGEMANAGER->findImage("병사히트");
	soldier.deadImg = IMAGEMANAGER->findImage("병사죽음");
	soldier.hp = 10;
	soldier.isLeft = false;
	soldier.isAtt = false;
	
	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	tree.rc = RectMakeCenter(DATA->getPixelGround().x + tree.enemyX, DATA->getPixelGround().y + tree.enemyY, 84, 93);
	tree.attScope = RectMakeCenter(DATA->getPixelGround().x + tree.enemyX, DATA->getPixelGround().y + tree.enemyY, 500, 93);
	soldier.rc = RectMakeCenter(DATA->getPixelGround().x + soldier.enemyX, DATA->getPixelGround().y + soldier.enemyY, 45, 80);
	soldier.attScope = RectMakeCenter(DATA->getPixelGround().x + soldier.enemyX, DATA->getPixelGround().y + soldier.enemyY, 200, 80);
	
	//공격범위에 들어왔을때 플레이어 오는 로직
	this->enemyScope();
	this->enemyMove();
	this->enemyAnimation();
}

void enemy::render()
{
	//Rectangle(getMemDC(), tree.attScope);

	if (tree.state == ENEMY_IDLE)
	{
		tree.idleImg->frameRender(getMemDC(), tree.rc.left, tree.rc.top);
	}
	if (tree.state == ENEMY_RUN)
	{
		tree.runImg->frameRender(getMemDC(), tree.rc.left, tree.rc.top);
	}
	if (tree.state == ENEMY_ATT)
	{
		tree.attImg->frameRender(getMemDC(), tree.rc.left, tree.rc.top);
	}

	if (soldier.state == ENEMY_IDLE)
	{
		soldier.idleImg->frameRender(getMemDC(), soldier.rc.left, soldier.rc.top);
	}
}

void enemy::enemyAnimation()
{
	switch (tree.state)
	{
	case ENEMY_IDLE:
		tree.count++;
		if (tree.isLeft == false)
		{
			tree.idleImg->setFrameY(0);
			if (tree.count % 5 == 0)
			{
				tree.index++;
				if (tree.index > 5)
				{
					tree.index = 0;
				}
				tree.idleImg->setFrameX(tree.index);
			}
		}
		else
		{
			tree.idleImg->setFrameY(1);
			if (tree.count % 5 == 0)
			{
				tree.index--;
				if (tree.index < 0)
				{
					tree.index = 5;
				}
				tree.idleImg->setFrameX(tree.index);
			}
		}
		break;
	case ENEMY_RUN:
		tree.count++;
		if (tree.isLeft == false)
		{
			tree.runImg->setFrameY(0);
			if (tree.count % 6 == 0)
			{
				tree.index++;
				if (tree.index > 6)
				{
					tree.index = 0;
				}
				tree.runImg->setFrameX(tree.index);
			}
		}
		else
		{
			tree.runImg->setFrameY(1);
			if (tree.count % 6 == 0)
			{
				tree.index--;
				if (tree.index < 0)
				{
					tree.index = 6;
				}
				tree.runImg->setFrameX(tree.index);
			}
		}
		break;
	case ENEMY_ATT:
		tree.count++;
		if (tree.isLeft == false)
		{
			tree.attImg->setFrameY(0);
			if (tree.count % 6 == 0)
			{
				tree.index++;
				if (tree.index > 4)
				{
					tree.index = 0;
				}
				tree.attImg->setFrameX(tree.index);
			}
		}
		else
		{
			tree.attImg->setFrameY(1);
			if (tree.count % 6 == 0)
			{
				tree.index--;
				if (tree.index < 0)
				{
					tree.index = 4;
				}
				tree.attImg->setFrameX(tree.index);
			}
		}
		break;
	case ENEMY_HIT:
		break;
	case ENEMY_DEAD:
		break;
	}

	switch (soldier.state)
	{
	case ENEMY_IDLE:
		soldier.count++;
		if (soldier.isLeft == false)
		{
			soldier.idleImg->setFrameY(0);
			if (soldier.count % 5 == 0)
			{
				soldier.index++;
				if (soldier.index > 5)
				{
					soldier.index = 0;
				}
				soldier.idleImg->setFrameX(soldier.index);
			}
		}
		else
		{
			soldier.idleImg->setFrameY(1);
			if (soldier.count % 5 == 0)
			{
				soldier.index--;
				if (soldier.index < 0)
				{
					soldier.index = 5;
				}
				soldier.idleImg->setFrameX(soldier.index);
			}
		}
		break;
	case ENEMY_RUN:
		break;
	case ENEMY_ATT:
		break;
	case ENEMY_HIT:
		break;
	case ENEMY_DEAD:
		break;
	}
}

void enemy::enemyScope()
{
	RECT rcTemp;
	if (IntersectRect(&rcTemp, &DATA->getPlayerRc(), &tree.attScope))
	{
		tree.isAtt = true;
	}
	else
	{
		tree.isAtt = false;
	}

	if (IntersectRect(&rcTemp, &DATA->getPlayerRc(), &soldier.attScope))
	{
		soldier.isAtt = true;
	}
	else
	{
		soldier.isAtt = false;
	}
}

void enemy::enemyMove()
{
	if (tree.isAtt)
	{
		if (DATA->getPlayerRc().right < tree.enemyX - 30)
		{
			tree.isLeft = true;
			tree.enemyX -= 4;
			if (DATA->getPlayerRc().right >= tree.enemyX - 30)
			{
				tree.state = ENEMY_ATT;
			}
			else
			{
				tree.state = ENEMY_RUN;
			}

		}
		
		if (DATA->getPlayerRc().left > tree.enemyX + 30)
		{
			tree.isLeft = false;
			tree.enemyX += 4;
			if (DATA->getPlayerRc().left <= tree.enemyX + 30)
			{
				tree.state = ENEMY_ATT;
			}
			else
			{
				tree.state = ENEMY_RUN;
			}

		}
	}
	else
	{
		tree.state = ENEMY_IDLE;
	}

}
