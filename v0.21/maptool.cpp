#include "stdafx.h"
#include "maptool.h"

HRESULT maptool::init()
{
	//타일맵 이미지 초기화
	//이미지 선언 싹바뀜 - 이준 (헤더쪽도 확인 요망)
	terrainImg = IMAGEMANAGER->findImage("지형타일");
	terrainImgMini = IMAGEMANAGER->findImage("지형타일_미니");

	//objectImg = IMAGEMANAGER->findImage("오브젝트타일_병합");
	//objectImgMini = IMAGEMANAGER->findImage("오브젝트타일_병합미니");
	//
	//enemyImg = IMAGEMANAGER->findImage("에너미타일_병합"); //에너미 타일 이미지 추가 -동주 0409 
	//enemyImgMini = IMAGEMANAGER->findImage("에너미타일_병합미니"); //에너미 미니타일 이미지 추가 -동주 0409

	toolBoxImg = IMAGEMANAGER->findImage("툴박스");
	buttonEraserImg = IMAGEMANAGER->findImage("버튼_이레이저");
	buttonLoadImg = IMAGEMANAGER->findImage("버튼_로드");
	buttonResetImg = IMAGEMANAGER->findImage("버튼_리셋");
	buttonSaveImg = IMAGEMANAGER->findImage("버튼_세이브");
	buttonTerrainImg = IMAGEMANAGER->findImage("버튼_지형");
	buttonObjectImg = IMAGEMANAGER->findImage("버튼_오브젝트");
	buttonDragImg = IMAGEMANAGER->findImage("버튼_드래그");
	//buttonPlayerImg = IMAGEMANAGER->findImage("버튼_플레이어");
	//buttonEnemyImg = IMAGEMANAGER->findImage("버튼_에너미");
	buttonExitImg = IMAGEMANAGER->findImage("버튼_엑시트");

	buttonEraserOnImg = IMAGEMANAGER->findImage("버튼_이레이저온");
	buttonLoadOnImg = IMAGEMANAGER->findImage("버튼_로드온");
	buttonResetOnImg = IMAGEMANAGER->findImage("버튼_리셋온");
	buttonSaveOnImg = IMAGEMANAGER->findImage("버튼_세이브온");
	buttonTerrainOnImg = IMAGEMANAGER->findImage("버튼_지형온");
	buttonObjectOnImg = IMAGEMANAGER->findImage("버튼_오브젝트온");
	buttonDragOnImg = IMAGEMANAGER->findImage("버튼_드래그온");
	//buttonPlayerOnImg = IMAGEMANAGER->findImage("버튼_플레이어온");
	//buttonEnemyOnImg = IMAGEMANAGER->findImage("버튼_에너미온");
	buttonExitOnImg = IMAGEMANAGER->findImage("버튼_엑시트온");

	//buttonLeftImg = IMAGEMANAGER->findImage("버튼_왼쪽화살표");
	//buttonRightImg = IMAGEMANAGER->findImage("버튼_오른쪽화살표");
	//
	//buttonLeftOnImg = IMAGEMANAGER->findImage("버튼_왼쪽화살표온");
	//buttonRightOnImg = IMAGEMANAGER->findImage("버튼_오른쪽화살표온");

	mapToolBgImg1 = IMAGEMANAGER->findImage("백그라운드1");
	mapToolBgImg2 = IMAGEMANAGER->findImage("백그라운드2");
	mapToolBgImg3 = IMAGEMANAGER->findImage("백그라운드3");
	mapToolBgImg4 = IMAGEMANAGER->findImage("백그라운드4");

	miniMapImg1 = IMAGEMANAGER->findImage("백그라운드1_미니");
	miniMapImg2 = IMAGEMANAGER->findImage("백그라운드2_미니");
	miniMapImg3 = IMAGEMANAGER->findImage("백그라운드3_미니");
	miniMapImg4 = IMAGEMANAGER->findImage("백그라운드4_미니");

	//현재타일 초기화
	sCurrentTile.x = 0;
	sCurrentTile.y = 0;
	sToolBox.moveSpeed = 5;
	sToolBox.toggle = false;
	sToolBox.selectedPage = 1;

	//타일 셋업
	this->tileSetup();

	//초기 선택 값 = 지형
	ctrlSelect = CTRL_TERRAIN;

	//드래그 초기화
	isDrag = false;
	saveX = saveY = 0;

	//윈사이즈 렉트
	rcWins = RectMake(0, 0, WINSIZEX, WINSIZEY);
	//백그라운드 렉트
	rcBg = RectMake(0, 0, 1940, 810);
	//미니맵 렉트
	rcMini = RectMake(WINSIZEX - 194, 0, 194, 81);
	rcMcamera = RectMake(WINSIZEX - 194, 0, 128, 72);


	//버튼박스클릭 - 버튼클릭했을때 이미지변경 불변수
	isSaveClick = false;
	isLoadClick = false;
	isObjectClick = false;
	isTerrainClick = false;
	isDragClick = false;
	isEraserClick = false;
	isResetClick = false;
	isLeftPointerClick = false;
	isRightPointerClick = false;
	isEnemyClick = false;
	isPlayerClick = false;
	isExitClick = false;

	dragRc = RectMake(-10, -10, 1, 1);

	//이준
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		sTile[i].isTouch = false;
		sTile[i].enemy.isPushed = false; //0413 현구 에너미 넣었냐? 불 변수 초기화
		sTile[i].currentEnemy = 0;
	}
	selectEnemyNum = 0;


	return S_OK;
}

void maptool::release()
{
}

void maptool::update()
{
	this->toolBoxUpdate();
	//this->setEnemySelectRect(); //0413 현구 에너미 선택용 렉트 함수로 바꿈.

	if (isDragClick == true)
	{
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			//타일 선택 구문 드래그 상태일때 안되서 드래그에 추가함 - 이준
			for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
			{
				if (sToolBox.toggle == false) continue; //토글키 안누르면 충돌처리를 하지 않는다.
				if (PtInRect(&sSampleTile[i].rc, _ptMouse))
				{
					RECT rcTemp3;
					if (IntersectRect(&rcTemp3, &rcToolCamera, &sSampleTile[i].rc))
					{
						if (ctrlSelect == CTRL_TERRAIN)
						{
							sCurrentTile.x = sSampleTile[i].terrainFrameX;
							sCurrentTile.y = sSampleTile[i].terrainFrameY;
						}
						if (ctrlSelect == CTRL_OBJECT)
						{
							sCurrentTile.x = sSampleTile[i].objFrameX;
							sCurrentTile.y = sSampleTile[i].objFrameY;
						}
						if (ctrlSelect == CTRL_ENEMY)
						{
							sCurrentTile.x = sSampleTile[i].enemyFrameX;
							sCurrentTile.y = sSampleTile[i].enemyFrameY;
						}

						break;
					}
				}
			}

			isDrag = true;
			saveX = _ptMouse.x;
			saveY = _ptMouse.y;

			if (PtInRect(&sToolBtn.rcSave, _ptMouse))
			{
				isSaveClick = true;		//추가 세이브눌렀을때 이미지 변경해줌
				this->save();
				this->miniSave();
			}
			if (PtInRect(&sToolBtn.rcLoad, _ptMouse))
			{
				isLoadClick = true;		//추가 로드눌렀을때 이미지 변경해줌
				this->load();
				this->miniLoad();
			}

			if (PtInRect(&sToolBtn.rcEraser, _ptMouse))
			{
				if (isEraserClick == false)		//추가 이레이저 눌렀을때 이미지 변경해줌
				{
					isEraserClick = true;
					ctrlSelect = CTRL_ERASER;
				}
				else
				{
					isEraserClick = false;		//이레이저는 다시 눌러주면 풀림
					if (isTerrainClick)			//현구짱 이레이저 예외처리 드래그
					{
						ctrlSelect = CTRL_TERRAIN;
					}
					else if (isObjectClick)
					{
						ctrlSelect = CTRL_OBJECT;
					}
				}
			}
			//아래 5개 구문 추가 안되어있어서 드래그 상태였을때 버튼이 눌리지 않아서 추가해뒀음 - 이준
			if (PtInRect(&sToolBtn.rcLeftPointer, _ptMouse) && sToolBox.selectedPage >= 2)
			{
				isLeftPointerClick = true;
				sToolBox.selectedPage--;
			}
			if (PtInRect(&sToolBtn.rcRightPointer, _ptMouse) && sToolBox.selectedPage < 4)
			{
				isRightPointerClick = true;
				sToolBox.selectedPage++;
			}
			if (PtInRect(&sToolBtn.rcTerrain, _ptMouse))
			{
				isTerrainClick = true;
				isObjectClick = false; //오브젝트 상태 변환 -동주 
				isEnemyClick = false;//연우 0409
				ctrlSelect = CTRL_TERRAIN;
			}
			if (PtInRect(&sToolBtn.rcObject, _ptMouse))
			{
				isObjectClick = true;
				isTerrainClick = false; //터레인 상태 변환 -동주
				isEnemyClick = false;
				ctrlSelect = CTRL_OBJECT;
			}
			if (PtInRect(&sToolBtn.rcReset, _ptMouse))
			{
				isResetClick = true;
				isEraserClick = false;
				ctrlSelect = CTRL_RESET;
			}
			if (PtInRect(&sToolBtn.rcPlayer, _ptMouse))
			{
				isPlayerClick = true;
			}
			if (PtInRect(&sToolBtn.rcEnemy, _ptMouse))
			{
				isEnemyClick = true; //연우 0409
				isObjectClick = false; //연우 0409
				isTerrainClick = false; //연우 0409
				ctrlSelect = CTRL_ENEMY; //연우 0409
			}
			if (PtInRect(&sToolBtn.rcDrag, _ptMouse))
			{
				if (isDragClick == false)
				{
					isDragClick = true;
				}
				else if (isDragClick == true)
				{
					isDragClick = false;
				}
			}
			if (PtInRect(&sToolBtn.rcExit, _ptMouse))
			{
				isExitClick = true;
				SCENEMANAGER->loadScene("메뉴화면");
			}
		}
		if (INPUT->GetKey(VK_LBUTTON))
		{
			dragRc = RectMake(saveX, saveY, (_ptMouse.x - saveX), (_ptMouse.y - saveY));
		}

		if (INPUT->GetKeyUp(VK_LBUTTON))		//겟키업으로 눌렀을때 true 값 fasle처리해주기
		{
			isDrag = false;
			isSaveClick = false;
			isLoadClick = false;
			isResetClick = false;
			isPlayerClick = false;
			//isEnemyClick = false;
			isExitClick = false;
			isLeftPointerClick = false;  //연우 0409 
			isRightPointerClick = false;
		}
	}
	else
	{
		//좌클릭시 해당 위치에 선택된 타일 그리기
		if (INPUT->GetKey(VK_LBUTTON)) this->setMap();

		//버튼 클릭 충돌 처리
		if (INPUT->GetKeyDown(VK_LBUTTON) && (sToolBox.toggle == true))
		{
			//if (ctrlSelect == CTRL_ENEMY)
			//{
			//	if (sToolBox.toggle == true)//0413 현구 툴박스 안켰는데 선택된 에너미 타일 골라지는 것 예외처리.
			//	{
			//		if (PtInRect(&sEnemyTile.rcGreyBean, _ptMouse))
			//		{
			//			selectEnemyNum = 1;
			//		}
			//		if (PtInRect(&sEnemyTile.rcBlackBean, _ptMouse))
			//		{
			//			selectEnemyNum = 2;
			//		}
			//		if (PtInRect(&sEnemyTile.rcBlueBean, _ptMouse))
			//		{
			//			selectEnemyNum = 3;
			//		}
			//		if (PtInRect(&sEnemyTile.rcBlueFlower, _ptMouse))
			//		{
			//			selectEnemyNum = 4;
			//		}
			//		if (PtInRect(&sEnemyTile.rcGreenFlower, _ptMouse))
			//		{
			//			selectEnemyNum = 5;
			//		}
			//		if (PtInRect(&sEnemyTile.rcWingTurtle, _ptMouse))
			//		{
			//			selectEnemyNum = 6;
			//		}
			//		if (PtInRect(&sEnemyTile.rcGreyBird, _ptMouse))
			//		{
			//			selectEnemyNum = 7;
			//		}
			//		if (PtInRect(&sEnemyTile.rcGreenBird, _ptMouse))
			//		{
			//			selectEnemyNum = 8;
			//		}
			//		if (PtInRect(&sEnemyTile.rcRedBird, _ptMouse))
			//		{
			//			selectEnemyNum = 9;
			//		}
			//		if (PtInRect(&sEnemyTile.rcDoChi, _ptMouse))
			//		{
			//			selectEnemyNum = 10;
			//		}
			//		if (PtInRect(&sEnemyTile.rcMushroom, _ptMouse))
			//		{
			//			selectEnemyNum = 11;
			//		}
			//		if (PtInRect(&sEnemyTile.rcBlueTurtle, _ptMouse))
			//		{
			//			selectEnemyNum = 12;
			//		}
			//		if (PtInRect(&sEnemyTile.rcGreenTurtle, _ptMouse))
			//		{
			//			selectEnemyNum = 13;
			//		}
			//		if (PtInRect(&sEnemyTile.rcBoss, _ptMouse))
			//		{
			//			selectEnemyNum = 14;
			//		}
			//		if (PtInRect(&sEnemyTile.rcRightBullet, _ptMouse))
			//		{
			//			selectEnemyNum = 15;
			//		}
			//		if (PtInRect(&sEnemyTile.rcLeftBullet, _ptMouse))
			//		{
			//			selectEnemyNum = 16;
			//		}
			//		if (PtInRect(&sEnemyTile.rcCannon, _ptMouse))
			//		{
			//			selectEnemyNum = 17;
			//		}
			//	}
			//	for (int i = 0; i < TILEX * TILEY; i++)
			//	{
			//		if (PtInRect(&sTile[i].rc, _ptMouse))
			//		{
			//			if (sToolBox.toggle == true && (PtInRect(&sToolBox.rcBack, _ptMouse)))continue; //0413 현구 툴박스 뒤에 렌더 안되게 예외처리
			//			sTile[i].currentEnemy = selectEnemyNum;
			//			sTile[i].isTouch = true;
			//		}
			//	}
			//}

			if (PtInRect(&sToolBtn.rcSave, _ptMouse))
			{
				isSaveClick = true;		//추가 세이브 눌렀을때 이미지 변경해줌
				this->save();
				this->miniSave();
			}
			if (PtInRect(&sToolBtn.rcLoad, _ptMouse))
			{
				isLoadClick = true;		//추가 로드 눌렀을때 이미지 변경해줌
				this->load();
				this->miniLoad();
			}

			if (PtInRect(&sToolBtn.rcEraser, _ptMouse))
			{
				if (isEraserClick == false)		//추가 이레이저 눌렀을때 이미지 변경해줌
				{
					isEraserClick = true;
					ctrlSelect = CTRL_ERASER;
				}
				else
				{
					isEraserClick = false;		//이레이저는 다시 눌러주면 풀림
					if (isTerrainClick)			//현구짱 이레이저 예외처리
					{
						ctrlSelect = CTRL_TERRAIN;
					}
					else if (isObjectClick)
					{
						ctrlSelect = CTRL_OBJECT;
					}
				}

			}

			if (PtInRect(&sToolBtn.rcLeftPointer, _ptMouse) && sToolBox.selectedPage >= 2)
			{
				isLeftPointerClick = true;
				sToolBox.selectedPage--;
			}
			if (PtInRect(&sToolBtn.rcRightPointer, _ptMouse) && sToolBox.selectedPage < 4)
			{
				isRightPointerClick = true;
				sToolBox.selectedPage++;

				//에너미 이넘 상태일떄 다음페이지 못넘어가게 예외처리 -동주 
				if (ctrlSelect == CTRL_ENEMY)
				{
					sToolBox.selectedPage = 1;
				}
			}
			if (PtInRect(&sToolBtn.rcTerrain, _ptMouse))
			{
				isTerrainClick = true;
				isObjectClick = false;
				isEnemyClick = false;
				ctrlSelect = CTRL_TERRAIN;
			}
			if (PtInRect(&sToolBtn.rcObject, _ptMouse))
			{
				isObjectClick = true;
				isTerrainClick = false;//임시추가
				isEnemyClick = false;
				ctrlSelect = CTRL_OBJECT;
			}
			if (PtInRect(&sToolBtn.rcReset, _ptMouse))		//리셋버튼만들어서 피티인렉해줌
			{
				isResetClick = true;
				isEraserClick = false;
				ctrlSelect = CTRL_RESET;
			}
			//if (PtInRect(&sToolBtn.rcPlayer, _ptMouse))
			//{
			//	isPlayerClick = true;
			//}
			//if (PtInRect(&sToolBtn.rcEnemy, _ptMouse))
			//{
			//	isEnemyClick = true; //연우 0409
			//	isObjectClick = false; //연우 0409
			//	isTerrainClick = false; //연우 0409
			//	ctrlSelect = CTRL_ENEMY; //연우 0409
			//}
			if (PtInRect(&sToolBtn.rcDrag, _ptMouse))
			{
				if (isDragClick == false)
				{
					isDragClick = true;
				}
				else if (isDragClick == true)
				{
					isDragClick = false;
				}
			}
			if (PtInRect(&sToolBtn.rcExit, _ptMouse))
			{
				isExitClick = true;
				SCENEMANAGER->loadScene("메뉴화면");
			}
		}
		if (INPUT->GetKeyUp(VK_LBUTTON))					//세이브,로드,리셋버튼 false 겟키업 추가
		{
			isSaveClick = false;
			isLoadClick = false;
			isResetClick = false;
			//isTerrain = false;
			//isObject = false;
			isLeftPointerClick = false;
			isRightPointerClick = false;
			isPlayerClick = false;
			//isEnemyClick = false;
			isExitClick = false;
		}
	}

	//타일 렉트 초기화
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			sTile[i * TILEX + j].rc = RectMake(rcBg.left + j * TILESIZE, rcBg.top + i * TILESIZE, TILESIZE, TILESIZE);
		}
	}

	//미니맵 타일 렉트 초기화
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			sMiniTile[i * TILEX + j].rc = RectMake(rcMini.left + j * (TILESIZE / 10 + 0.4f), rcMini.top + i * (TILESIZE / 10 + 0.5f), TILESIZE / 10, TILESIZE / 10);
		}
	}

	if (INPUT->GetKey('D'))
	{
		dragRc = RectMake(-10, -10, 1, 1);
		if (WINSIZEX >= rcBg.right)
		{
			rcBg.right = WINSIZEX;
		}
		else
		{
			rcBg.left -= 10;
			rcBg.right -= 10;
			rcMcamera.left += 1;
			rcMcamera.right += 1;
		}
	}
	if (INPUT->GetKey('A'))
	{
		dragRc = RectMake(-10, -10, 1, 1);
		if (0 <= rcBg.left)
		{
			rcBg.left = 0;
		}
		else
		{
			rcBg.left += 10;
			rcBg.right += 10;
			rcMcamera.left -= 1;
			rcMcamera.right -= 1;
		}
	}
	if (INPUT->GetKey('W'))
	{
		dragRc = RectMake(-10, -10, 1, 1);
		if (0 <= rcBg.top)
		{
			rcBg.top = 0;
		}
		else
		{
			rcBg.top += 10;
			rcBg.bottom += 10;
			rcMcamera.top -= 1;
			rcMcamera.bottom -= 1;
		}
	}
	if (INPUT->GetKey('S'))
	{
		dragRc = RectMake(-10, -10, 1, 1);
		if (WINSIZEY >= rcBg.bottom)
		{
			rcBg.bottom = WINSIZEY;
		}
		else
		{
			rcBg.top -= 10;
			rcBg.bottom -= 10;
			rcMcamera.top += 1;
			rcMcamera.bottom += 1;
		}
	}

	if (ctrlSelect == CTRL_RESET)					//리셋 로직 추가
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			//리셋 상태 추가 -동주

			//타일 리셋 트레인 리셋
			sTile[i].terrainFrameX = 0;
			sTile[i].terrainFrameY = 0;
			sTile[i].terrain = terrainSelect(sCurrentTile.x, sCurrentTile.y);
			ctrlSelect = CTRL_TERRAIN;

			////타일 리셋 오브젝트 리셋
			//sTile[i].objFrameX = 10;
			//sTile[i].objFrameY = 9;
			//sTile[i].obj = objectSelect(sCurrentTile.x, sCurrentTile.y);
			//ctrlSelect = CTRL_OBJECT;

			//미니맵 트레인 리셋
			sMiniTile[i].terrainFrameX = 0;
			sMiniTile[i].terrainFrameY = 0;
			sMiniTile[i].terrain = terrainSelect(sCurrentTile.x, sCurrentTile.y);
			ctrlSelect = CTRL_TERRAIN;

			////미니맵 오브젝트 리셋
			//sMiniTile[i].objFrameX = 12;
			//sMiniTile[i].objFrameY = 10;
			//sMiniTile[i].obj = objectSelect(sCurrentTile.x, sCurrentTile.y);
			//ctrlSelect = CTRL_OBJECT;
			//미니맵 에너미 리셋
			//for (int i = 0; i < TILEX * TILEY; i++)
			//{
			//	sTile[i].currentEnemy = 0;
			//
			//}
		}
	}
	//툴박스 카메라 렉트추가 - 이준
	rcToolCamera = RectMake(sToolBox.rcBack.left + 15, sToolBox.rcBack.top + 15, 510, 340);

	RECT tempRc;
	//렉트충돌을 위한 코드
	if (isDrag)
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			if ((sToolBox.toggle)) break;

			if (IntersectRect(&tempRc, &sTile[i].rc, &dragRc))
			{
				if (ctrlSelect == CTRL_ERASER)
				{
					sTile[i].isTouch = false;
				}
				else
				{
					sTile[i].isTouch = true;
				}
			}
		}
	}
	else
	{
		if (INPUT->GetKey(VK_LBUTTON))
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				if ((sToolBox.toggle)) break;

				if (PtInRect(&sTile[i].rc, _ptMouse))
				{
					if (ctrlSelect == CTRL_ERASER)
					{
						sTile[i].isTouch = false;
					}
					else
					{
						sTile[i].isTouch = true;
					}
				}
			}
		}
	}	
}

void maptool::render()
{
	mapToolBgImg1->render(getMemDC(), rcBg.left, rcBg.top);
	mapToolBgImg2->render(getMemDC(), rcBg.left, rcBg.top);
	mapToolBgImg3->render(getMemDC(), rcBg.left, rcBg.top);
	mapToolBgImg4->render(getMemDC(), rcBg.left, rcBg.top);

	miniMapImg1->render(getMemDC(), rcMini.left, rcMini.top);
	miniMapImg2->render(getMemDC(), rcMini.left, rcMini.top);
	miniMapImg3->render(getMemDC(), rcMini.left, rcMini.top);
	miniMapImg4->render(getMemDC(), rcMini.left, rcMini.top);

	FrameRect(getMemDC(), rcMini, RGB(0, 0, 0));
	FrameRect(getMemDC(), rcMcamera, RGB(255, 0, 0));

	//인게임화면 지형을 그린다
	RECT rcTemp;
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (IntersectRect(&rcTemp, &rcWins, &sTile[i].rc))
		{
			terrainImg->frameRender(getMemDC(), sTile[i].rc.left, sTile[i].rc.top,
				sTile[i].terrainFrameX, sTile[i].terrainFrameY);
			//프레임 렌더 이미지 변경 -동주 
			terrainImgMini->frameRender(getMemDC(), sMiniTile[i].rc.left, sMiniTile[i].rc.top,
				sMiniTile[i].terrainFrameX, sMiniTile[i].terrainFrameY);

			//objectImg->frameRender(getMemDC(), sTile[i].rc.left, sTile[i].rc.top,
			//	sTile[i].objFrameX, sTile[i].objFrameY);
			//
			//objectImgMini->frameRender(getMemDC(), sMiniTile[i].rc.left, sMiniTile[i].rc.top,
			//	sMiniTile[i].objFrameX, sMiniTile[i].objFrameY);

			//if (!sTile[i].isTouch) continue;
			//switch (sTile[i].currentEnemy)
			//{
			//case 1:
			//	IMAGEMANAGER->findImage("회색콩벌레_수정")->render(getMemDC(), sTile[i].rc.left, sTile[i].rc.top);
			//	this->setEnemyData(GREY_BEAN, sTile[i].rc.left, sTile[i].rc.top); //0413 현구 해당 에너미의 종류, x,y좌표를 넣는다.
			//	break;
			//case 2:
			//	IMAGEMANAGER->findImage("검은콩벌레_수정")->render(getMemDC(), sTile[i].rc.left, sTile[i].rc.top);
			//	this->setEnemyData(BLACK_BEAN, sTile[i].rc.left, sTile[i].rc.top);
			//	break;
			//case 3:
			//	IMAGEMANAGER->findImage("파란콩벌레_수정")->render(getMemDC(), sTile[i].rc.left, sTile[i].rc.top);
			//	this->setEnemyData(BLUE_BEAN, sTile[i].rc.left, sTile[i].rc.top);
			//	break;
			//case 4:
			//	IMAGEMANAGER->findImage("파란꽃_수정")->render(getMemDC(), sTile[i].rc.left, sTile[i].rc.top);
			//	this->setEnemyData(BLUE_FLOWER, sTile[i].rc.left, sTile[i].rc.top);
			//	break;
			//case 5:
			//	IMAGEMANAGER->findImage("초록꽃_수정")->render(getMemDC(), sTile[i].rc.left, sTile[i].rc.top);
			//	this->setEnemyData(GREEN_FLOWER, sTile[i].rc.left, sTile[i].rc.top);
			//	break;
			//case 6:
			//	IMAGEMANAGER->findImage("날개거북_수정")->render(getMemDC(), sTile[i].rc.left, sTile[i].rc.top);
			//	this->setEnemyData(WING_TURTLE, sTile[i].rc.left, sTile[i].rc.top);
			//	break;
			//case 7:
			//	IMAGEMANAGER->findImage("회색새_수정")->render(getMemDC(), sTile[i].rc.left, sTile[i].rc.top);
			//	this->setEnemyData(GREY_BIRD, sTile[i].rc.left, sTile[i].rc.top);
			//	break;
			//case 8:
			//	IMAGEMANAGER->findImage("초록새_수정")->render(getMemDC(), sTile[i].rc.left, sTile[i].rc.top);
			//	this->setEnemyData(GREEN_BIRD, sTile[i].rc.left, sTile[i].rc.top);
			//	break;
			//case 9:
			//	IMAGEMANAGER->findImage("빨간새_수정")->render(getMemDC(), sTile[i].rc.left, sTile[i].rc.top);
			//	this->setEnemyData(RED_BIRD, sTile[i].rc.left, sTile[i].rc.top);
			//	break;
			//case 10:
			//	IMAGEMANAGER->findImage("도치_수정")->render(getMemDC(), sTile[i].rc.left, sTile[i].rc.top);
			//	this->setEnemyData(DOCHI, sTile[i].rc.left, sTile[i].rc.top);
			//	break;
			//case 11:
			//	IMAGEMANAGER->findImage("버섯_수정")->render(getMemDC(), sTile[i].rc.left, sTile[i].rc.top);
			//	this->setEnemyData(MUSHROOM, sTile[i].rc.left, sTile[i].rc.top);
			//	break;
			//case 12:
			//	IMAGEMANAGER->findImage("파란거북_수정")->render(getMemDC(), sTile[i].rc.left, sTile[i].rc.top);
			//	this->setEnemyData(BLUE_TURTLE, sTile[i].rc.left, sTile[i].rc.top);
			//	break;
			//case 13:
			//	IMAGEMANAGER->findImage("초록거북_수정")->render(getMemDC(), sTile[i].rc.left, sTile[i].rc.top);
			//	this->setEnemyData(GREEN_TURTLE, sTile[i].rc.left, sTile[i].rc.top);
			//	break;
			//case 14:
			//	IMAGEMANAGER->findImage("보스_수정")->render(getMemDC(), sTile[i].rc.left, sTile[i].rc.top);
			//	this->setEnemyData(BOSS, sTile[i].rc.left, sTile[i].rc.top);
			//	break;
			//case 15:
			//	IMAGEMANAGER->findImage("오른쪽폭탄_수정")->render(getMemDC(), sTile[i].rc.left, sTile[i].rc.top);
			//	break;
			//case 16:
			//	IMAGEMANAGER->findImage("왼쪽폭탄_수정")->render(getMemDC(), sTile[i].rc.left, sTile[i].rc.top);
			//	break;
			//case 17:
			//	IMAGEMANAGER->findImage("포탑_수정")->render(getMemDC(), sTile[i].rc.left, sTile[i].rc.top);
			//	break;
			//}
		}
	}


	if (isDrag)
	{
		//아래 버그 드래그 버그 잡아둔것 - 이준 (엘스 사라지고 인풋으로 바꿧음)
		if (INPUT->GetKey(VK_LBUTTON))
		{
			FrameRect(getMemDC(), dragRc, RGB(255, 0, 0));
		}

		if (INPUT->GetKeyUp(VK_LBUTTON))
		{
			//인게임화면 렉트틀과 충돌했냐?
			RECT _tempRc;
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				if (IntersectRect(&_tempRc, &sTile[i].rc, &dragRc))
				{
					//현재버튼이 지형이냐?
					if (ctrlSelect == CTRL_TERRAIN)
					{
						sTile[i].terrainFrameX = sCurrentTile.x;
						sTile[i].terrainFrameY = sCurrentTile.y;
						sTile[i].terrain = terrainSelect(sCurrentTile.x, sCurrentTile.y);

						sMiniTile[i].terrainFrameX = sCurrentTile.x;
						sMiniTile[i].terrainFrameY = sCurrentTile.y;
						sMiniTile[i].terrain = terrainSelect(sCurrentTile.x, sCurrentTile.y);
					}
					//현재버튼이 오브젝트냐?
					//if (ctrlSelect == CTRL_OBJECT)
					//{
					//	sTile[i].objFrameX = sCurrentTile.x;
					//	sTile[i].objFrameY = sCurrentTile.y;
					//	sTile[i].obj = objectSelect(sCurrentTile.x, sCurrentTile.y);
					//
					//	sMiniTile[i].objFrameX = sCurrentTile.x;
					//	sMiniTile[i].objFrameY = sCurrentTile.y;
					//	sMiniTile[i].obj = objectSelect(sCurrentTile.x, sCurrentTile.y);
					//}
					////이준
					//if (ctrlSelect == CTRL_ENEMY)
					//{
					//	sTile[i].enemyFrameX = sCurrentTile.x;
					//	sTile[i].enemyFrameY = sCurrentTile.y;
					//}
					//현재버튼이 지우개냐?
					if (ctrlSelect == CTRL_ERASER)							//이레이저 로직추가
					{
						if (isEraserClick)
						{//임시 주석해제
							if (isTerrainClick)
							{
								sTile[i].terrainFrameX = 0;
								sTile[i].terrainFrameY = 0;
								//sTile[i].isTouch = false;
								sMiniTile[i].terrainFrameX = 0;
								sMiniTile[i].terrainFrameY = 0;
							}
							//if (isObjectClick)
							//{
							//	sTile[i].objFrameX = 10;
							//	sTile[i].objFrameY = 9;
							//	sMiniTile[i].objFrameX = 12;
							//	sMiniTile[i].objFrameY = 10;
							//}
							//if (isEnemyClick)
							//{
							//	sTile[i].objFrameX = 10;
							//	sTile[i].objFrameY = 9;
							//}
						}
					}
				}
			}
		}
	}

	//F1 입력시 인게임화면 렉트 보여주기
	if (INPUT->GetToggleKey(VK_F1))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			FrameRect(getMemDC(), sTile[i].rc, RGB(0, 0, 0));
			if (sTile[i].isTouch)
			{
				Rectangle(getMemDC(), sTile[i].rc);
			}
		}
	}

	if (INPUT->GetToggleKey(VK_F3))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			FrameRect(getMemDC(), sMiniTile[i].rc, RGB(0, 255, 0));
		}
	}

	//F2 입력시 툴박스 + 페이지 + 버튼 렉트 보여주기
	if (INPUT->GetToggleKey(VK_F2))
	{
		toolBoxImg->render(getMemDC(), sToolBox.rcBack.left - 15, sToolBox.rcBack.top - 15);
		buttonLoadImg->render(getMemDC(), sToolBtn.rcLoad.left, sToolBtn.rcLoad.top);
		buttonSaveImg->render(getMemDC(), sToolBtn.rcSave.left, sToolBtn.rcSave.top);
		buttonResetImg->render(getMemDC(), sToolBtn.rcReset.left, sToolBtn.rcReset.top);
		buttonEraserImg->render(getMemDC(), sToolBtn.rcEraser.left, sToolBtn.rcEraser.top);
		buttonTerrainImg->render(getMemDC(), sToolBtn.rcTerrain.left, sToolBtn.rcTerrain.top);
		buttonObjectImg->render(getMemDC(), sToolBtn.rcObject.left, sToolBtn.rcObject.top);
		buttonDragImg->render(getMemDC(), sToolBtn.rcDrag.left, sToolBtn.rcDrag.top);
		buttonExitImg->render(getMemDC(), sToolBtn.rcExit.left, sToolBtn.rcExit.top);
		//Rectangle(getMemDC(), sToolBox.rcBack);
		//Rectangle(getMemDC(), sToolBox.rcPage);
		//Rectangle(getMemDC(), sToolBtn.rcLoad);
		//Rectangle(getMemDC(), sToolBtn.rcSave);
		//Rectangle(getMemDC(), sToolBtn.rcReset);
		//Rectangle(getMemDC(), sToolBtn.rcDelete);
		//Rectangle(getMemDC(), sToolBtn.rcTerrain);
		//Rectangle(getMemDC(), sToolBtn.rcObject);
		//Rectangle(getMemDC(), sToolBtn.rcDrag);
		//Rectangle(getMemDC(), sToolBtn.rcPlayer);
		//buttonPlayerImg->render(getMemDC(), sToolBtn.rcPlayer.left, sToolBtn.rcPlayer.top);
		////Rectangle(getMemDC(), sToolBtn.rcMonster);
		//buttonEnemyImg->render(getMemDC(), sToolBtn.rcEnemy.left, sToolBtn.rcEnemy.top);
		////Rectangle(getMemDC(), sToolBtn.rcExit);

		//에너미 타일 렉트 렌더 -동주,연우 0410
		//if (INPUT->GetToggleKey('M'))
		//{
		//	Rectangle(getMemDC(), sEnemyTile.rcGreyBean);
		//	Rectangle(getMemDC(), sEnemyTile.rcBlackBean);
		//	Rectangle(getMemDC(), sEnemyTile.rcBlueBean);
		//	Rectangle(getMemDC(), sEnemyTile.rcGreyBird);
		//	Rectangle(getMemDC(), sEnemyTile.rcGreenBird);
		//	Rectangle(getMemDC(), sEnemyTile.rcRedBird);
		//	Rectangle(getMemDC(), sEnemyTile.rcDoChi);
		//	Rectangle(getMemDC(), sEnemyTile.rcMushroom);
		//	Rectangle(getMemDC(), sEnemyTile.rcBlueFlower);
		//	Rectangle(getMemDC(), sEnemyTile.rcGreenFlower);
		//	Rectangle(getMemDC(), sEnemyTile.rcWingTurtle);
		//	Rectangle(getMemDC(), sEnemyTile.rcBlueTurtle);
		//	Rectangle(getMemDC(), sEnemyTile.rcGreenTurtle);
		//	Rectangle(getMemDC(), sEnemyTile.rcBoss);
		//	Rectangle(getMemDC(), sEnemyTile.rcRightBullet);
		//	Rectangle(getMemDC(), sEnemyTile.rcLeftBullet);
		//	Rectangle(getMemDC(), sEnemyTile.rcCannon);
		//}

		//Rectangle(getMemDC(), rcToolCamera);
		RECT _rcTemp;
		switch (sToolBox.selectedPage)
		{
		case 1:
			//if (ctrlSelect == CTRL_OBJECT)
			//{
			//	objectImg->render(getMemDC(), sToolBox.rcBack.left + 15, sToolBox.rcBack.top + 15, 0, 0, 448, 320);
			//}
			if (ctrlSelect == CTRL_TERRAIN) // if 조건 추가 - 동주 0409
			{
				terrainImg->render(getMemDC(), sToolBox.rcBack.left + 15, sToolBox.rcBack.top + 35, 0, 0, 510, 340);
			}
			//else if (ctrlSelect == CTRL_ENEMY) //에너미타일_병합 렌더 -동주 0409
			//{
			//	enemyImg->render(getMemDC(), sToolBox.rcBack.left + 15, sToolBox.rcBack.top + 15);
			//}
			//케이스 1~4까지 포문 추가 - 타일 테두리 렉트 인터섹트렉트 - 이준
			for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
			{
				if (IntersectRect(&_rcTemp, &rcToolCamera, &sSampleTile[i].rc))
				{
					FrameRect(getMemDC(), sSampleTile[i].rc, RGB(255, 255, 0));
				}
			}
			break;
		//case 2:
		//	if (ctrlSelect == CTRL_OBJECT)
		//	{
		//		objectImg->render(getMemDC(), sToolBox.rcBack.left + 15, sToolBox.rcBack.top + 15, 448, 0, 448, 320);
		//	}
		//	else
		//	{
		//		//병합 사진파일로 바꾸면서 이미지 소스좌표 및 소스가로세로 크기 변화 추가 - 이준
		//		terrainImg->render(getMemDC(), sToolBox.rcBack.left + 15, sToolBox.rcBack.top + 15, 448, 0, 448, 320);
		//	}
		//	//케이스 1~4까지 포문 추가 - 타일 테두리 렉트 인터섹트렉트 - 이준
		//	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
		//	{
		//		if (IntersectRect(&_rcTemp, &rcToolCamera, &sSampleTile[i].rc))
		//		{
		//			FrameRect(getMemDC(), sSampleTile[i].rc, RGB(255, 255, 0));
		//		}
		//	}
		//	break;
		//case 3:
		//	if (ctrlSelect == CTRL_OBJECT)
		//	{
		//		objectImg->render(getMemDC(), sToolBox.rcBack.left + 15, sToolBox.rcBack.top + 15, 896, 0, 448, 320);
		//	}
		//	else
		//	{
		//		//병합 사진파일로 바꾸면서 이미지 소스좌표 및 소스가로세로 크기 변화 추가 - 이준
		//		terrainImg->render(getMemDC(), sToolBox.rcBack.left + 15, sToolBox.rcBack.top + 15, 896, 0, 448, 320);
		//	}
		//	//케이스 1~4까지 포문 추가 - 타일 테두리 렉트 인터섹트렉트 - 이준
		//	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
		//	{
		//		if (IntersectRect(&_rcTemp, &rcToolCamera, &sSampleTile[i].rc))
		//		{
		//			FrameRect(getMemDC(), sSampleTile[i].rc, RGB(255, 255, 0));
		//		}
		//	}
		//	break;
		//case 4:
		//	if (ctrlSelect == CTRL_OBJECT)
		//	{
		//		objectImg->render(getMemDC(), sToolBox.rcBack.left + 15, sToolBox.rcBack.top + 15, 1344, 0, 448, 320);
		//	}
		//	else
		//	{
		//		//병합 사진파일로 바꾸면서 이미지 소스좌표 및 소스가로세로 크기 변화 추가 - 이준
		//		terrainImg->render(getMemDC(), sToolBox.rcBack.left + 15, sToolBox.rcBack.top + 15, 1344, 0, 448, 320);
		//	}
		//	//케이스 1~4까지 포문 추가 - 타일 테두리 렉트 인터섹트렉트 - 이준
		//	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
		//	{
		//		if (IntersectRect(&_rcTemp, &rcToolCamera, &sSampleTile[i].rc))
		//		{
		//			FrameRect(getMemDC(), sSampleTile[i].rc, RGB(255, 255, 0));
		//		}
		//	}
		//	break;
		}

		//눌렀을때 버튼 변환 로직 추가
		if (isLoadClick)
		{
			buttonLoadOnImg->render(getMemDC(), sToolBtn.rcLoad.left, sToolBtn.rcLoad.top);
		}
		if (isSaveClick)
		{
			buttonSaveOnImg->render(getMemDC(), sToolBtn.rcSave.left, sToolBtn.rcSave.top);
		}
		if (isResetClick)
		{
			buttonResetOnImg->render(getMemDC(), sToolBtn.rcReset.left, sToolBtn.rcReset.top);
		}
		if (isEraserClick)
		{
			buttonEraserOnImg->render(getMemDC(), sToolBtn.rcEraser.left, sToolBtn.rcEraser.top);
		}
		if (isObjectClick)
		{
			buttonObjectOnImg->render(getMemDC(), sToolBtn.rcObject.left, sToolBtn.rcObject.top);
		}
		if (isTerrainClick)
		{
			buttonTerrainOnImg->render(getMemDC(), sToolBtn.rcTerrain.left, sToolBtn.rcTerrain.top);
		}
		if (isDragClick)
		{
			buttonDragOnImg->render(getMemDC(), sToolBtn.rcDrag.left, sToolBtn.rcDrag.top);
		}
		if (isExitClick)
		{
			buttonExitOnImg->render(getMemDC(), sToolBtn.rcExit.left, sToolBtn.rcExit.top);
		}
		//if (isPlayerClick)
		//{
		//	buttonPlayerOnImg->render(getMemDC(), sToolBtn.rcPlayer.left, sToolBtn.rcPlayer.top);
		//}
		//if (isEnemyClick)
		//{
		//	buttonEnemyOnImg->render(getMemDC(), sToolBtn.rcEnemy.left, sToolBtn.rcEnemy.top);
		//}

		//화살표 이미지 클릭감 ㅎㅎ
		//if (isLeftPointerClick)
		//{
		//	buttonLeftOnImg->render(getMemDC(), sToolBtn.rcLeftPointer.left, sToolBtn.rcLeftPointer.top);
		//}
		//else
		//{
		//	//Rectangle(getMemDC(), sToolBtn.rcLeftPointer);
		//	buttonLeftImg->render(getMemDC(), sToolBtn.rcLeftPointer.left, sToolBtn.rcLeftPointer.top);
		//}
		//if (isRightPointerClick)
		//{
		//	buttonRightOnImg->render(getMemDC(), sToolBtn.rcRightPointer.left, sToolBtn.rcRightPointer.top);
		//}
		//else
		//{
		//	//Rectangle(getMemDC(), sToolBtn.rcRightPointer);
		//	buttonRightImg->render(getMemDC(), sToolBtn.rcRightPointer.left, sToolBtn.rcRightPointer.top);
		//}

		//툴박스 표시되어 있을 때 화살표 입력시 툴박스 상하좌우 이동
		//if (INPUT->GetKey(VK_LEFT))
		//{
		//	sToolBox.x -= sToolBox.moveSpeed;
		//}
		//if (INPUT->GetKey(VK_RIGHT))
		//{
		//	sToolBox.x += sToolBox.moveSpeed;
		//}
		//if (INPUT->GetKey(VK_UP))
		//{
		//	sToolBox.y -= sToolBox.moveSpeed;
		//}
		//if (INPUT->GetKey(VK_DOWN))
		//{
		//	sToolBox.y += sToolBox.moveSpeed;
		//}
		if (INPUT->GetKey(VK_RBUTTON))
		{
			if (PtInRect(&sToolBox.rcBack, _ptMouse))
			{
				sToolBox.x = _ptMouse.x;
				sToolBox.y = _ptMouse.y + 150;
			}
		}

		sToolBox.toggle = true;
	}
	else
	{
		sToolBox.toggle = false;
	}

}

void maptool::tileSetup()
{
	//툴박스 초기화
	sToolBox.toggle = false;
	sToolBox.x = WINSIZEX / 2;
	sToolBox.y = 410;
	sToolBox.width = 1000;
	sToolBox.height = 400;

	//페이지 초기화
	sToolBox.pageWidth = 480;
	sToolBox.pageHeight = 400;

	//툴버튼 초기화
	sToolBtn.width = 173;
	sToolBtn.height = 53;

	//샘플타일 렉트 초기화
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			sSampleTile[i * SAMPLETILEX + j].terrainFrameX = j;
			sSampleTile[i * SAMPLETILEX + j].terrainFrameY = i;
			//sSampleTile[i * SAMPLETILEX + j].objFrameX = j;
			//sSampleTile[i * SAMPLETILEX + j].objFrameY = i;
			////이준
			//sSampleTile[i * SAMPLETILEX + j].enemyFrameX = j;
			//sSampleTile[i * SAMPLETILEX + j].enemyFrameY = i;
		}
	}

	//타일의 초기화면 
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		sTile[i].terrainFrameX = 0; //지형 타일 X좌표
		sTile[i].terrainFrameY = 0; //지형 타일 Y좌표
		sTile[i].terrain = terrainSelect(sTile[i].terrainFrameX, sTile[i].terrainFrameY); //해당 X,Y 좌표 값 가진 타일 선택
		//sTile[i].objFrameX = 0; //오브젝트 타일 X좌표
		//sTile[i].objFrameY = 0; //오브젝트 타일 Y좌표
		//sTile[i].obj = OBJ_NONE; //오브젝트 선택안한 상태
	}
}

void maptool::setMap()
{
	RECT _rcTemp2;
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		if (sToolBox.toggle == false)continue; //토글키 안누르면 충돌처리를 하지 않는다.
		if (PtInRect(&sSampleTile[i].rc, _ptMouse))
		{
			//툴박스 업데이트 인터섹터렉트 예외처리 - 동주
			if (IntersectRect(&_rcTemp2, &rcToolCamera, &sSampleTile[i].rc))
			{
				if (ctrlSelect == CTRL_TERRAIN)
				{
					sCurrentTile.x = sSampleTile[i].terrainFrameX;
					sCurrentTile.y = sSampleTile[i].terrainFrameY;
				}
				if (ctrlSelect == CTRL_OBJECT)
				{
					sCurrentTile.x = sSampleTile[i].objFrameX;
					sCurrentTile.y = sSampleTile[i].objFrameY;
				}
				//if (ctrlSelect == CTRL_ENEMY)
				//{	
				//	sCurrentTile.x = sSampleTile[i].enemyFrameX;
				//	sCurrentTile.y = sSampleTile[i].enemyFrameY;
				//}
			}
			break;
		}

	}

	//인게임화면 렉트틀과 충돌했냐?
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (PtInRect(&sTile[i].rc, _ptMouse))
		{
			if (PtInRect(&sToolBox.rcBack, _ptMouse) && sToolBox.toggle == true)continue; //토글 박스 쪽을 누르면 충돌처리를 하지 않는다.
			//현재버튼이 지형이냐?
			if (ctrlSelect == CTRL_TERRAIN)
			{
				sTile[i].terrainFrameX = sCurrentTile.x;
				sTile[i].terrainFrameY = sCurrentTile.y;
				sTile[i].terrain = terrainSelect(sCurrentTile.x, sCurrentTile.y);

				sMiniTile[i].terrainFrameX = sCurrentTile.x;
				sMiniTile[i].terrainFrameY = sCurrentTile.y;
				sMiniTile[i].terrain = terrainSelect(sCurrentTile.x, sCurrentTile.y);
			}
			//현재버튼이 오브젝트냐?
			if (ctrlSelect == CTRL_OBJECT)
			{
				sTile[i].objFrameX = sCurrentTile.x;
				sTile[i].objFrameY = sCurrentTile.y;
				sTile[i].obj = objectSelect(sCurrentTile.x, sCurrentTile.y);

				sMiniTile[i].objFrameX = sCurrentTile.x;
				sMiniTile[i].objFrameY = sCurrentTile.y;
				sMiniTile[i].obj = objectSelect(sCurrentTile.x, sCurrentTile.y);
			}
			//if (ctrlSelect == CTRL_ENEMY)
			//{
			//	sTile[i].enemyFrameX = sCurrentTile.x;
			//	sTile[i].enemyFrameY = sCurrentTile.y;
			//}

			//현재버튼이 지우개냐?
			if (ctrlSelect == CTRL_ERASER)							//이레이저 로직추가
			{
				if (isEraserClick)
				{
					if (isTerrainClick)//임시주석
					{
						sTile[i].terrainFrameX = 0;
						sTile[i].terrainFrameY = 0;
						//sTile[i].isTouch = false;
						sMiniTile[i].terrainFrameX = 0;
						sMiniTile[i].terrainFrameY = 0;
					}
					//if (isObjectClick)//임시주석
					//{
					//	sTile[i].objFrameX = 14;
					//	sTile[i].objFrameY = 9;
					//	sMiniTile[i].objFrameX = 14;
					//	sMiniTile[i].objFrameY = 9;
					//}
					//if (isEnemyClick)
					//{
					//	sTile[i].currentEnemy = 0;
					//}
				}
			}
		}
	}
}

void maptool::save()
{
	HANDLE file;
	DWORD write;

	file = CreateFile("save.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, sTile, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
	CloseHandle(file);

}

void maptool::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("save.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, sTile, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);
}

void maptool::miniSave()
{
	HANDLE file;
	DWORD write;

	file = CreateFile("savemini.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, sMiniTile, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
	CloseHandle(file);
}

void maptool::miniLoad()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("savemini.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, sMiniTile, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);
}


void maptool::toolBoxUpdate()
{
	//툴박스 배경 렉트 생성
	sToolBox.rcBack = RectMakeCenter(sToolBox.x, sToolBox.y, sToolBox.width, sToolBox.height);

	//툴박스 페이지 렉트 생성
	sToolBox.rcPage = RectMake(sToolBox.rcBack.left, sToolBox.rcBack.top, sToolBox.pageWidth, sToolBox.pageHeight);

	//툴박스 버튼 렉트 생성
	//왼쪽 버튼들
	sToolBtn.rcTerrain = RectMake(sToolBox.x + 60, sToolBox.y - 128, sToolBtn.width, sToolBtn.height);
	//sToolBtn.rcPlayer = RectMake(sToolBox.x + 30, sToolBox.y - 88, sToolBtn.width, sToolBtn.height);
	sToolBtn.rcEraser = RectMake(sToolBox.x + 60, sToolBox.y - 58, sToolBtn.width, sToolBtn.height);
	sToolBtn.rcSave = RectMake(sToolBox.x + 60, sToolBox.y + 12, sToolBtn.width, sToolBtn.height);
	sToolBtn.rcReset = RectMake(sToolBox.x + 60, sToolBox.y + 82, sToolBtn.width, sToolBtn.height);

	//오른쪽 버튼들
	sToolBtn.rcObject = RectMake(sToolBox.x + 275, sToolBox.y - 128, sToolBtn.width, sToolBtn.height);
	//sToolBtn.rcEnemy = RectMake(sToolBox.x + 225, sToolBox.y - 88, sToolBtn.width, sToolBtn.height);
	sToolBtn.rcDrag = RectMake(sToolBox.x + 275, sToolBox.y - 58, sToolBtn.width, sToolBtn.height);
	sToolBtn.rcLoad = RectMake(sToolBox.x + 275, sToolBox.y + 12, sToolBtn.width, sToolBtn.height);
	sToolBtn.rcExit = RectMake(sToolBox.x + 275, sToolBox.y + 82, sToolBtn.width, sToolBtn.height);

	//화살표
	sToolBtn.rcLeftPointer = RectMake(sToolBox.x - 315, sToolBox.y + 140, 50, 50);
	sToolBtn.rcRightPointer = RectMake(sToolBox.x - 255, sToolBox.y + 140, 50, 50);

	//샘플타일 만들기 위치 바꿔주면서 렉트메이크해서 버튼위치 변화주기 - 이준
	switch (sToolBox.selectedPage)
	{
	case 1:
		for (int i = 0; i < SAMPLETILEY; i++)
		{
			for (int j = 0; j < SAMPLETILEX; j++)
			{
				sSampleTile[i * SAMPLETILEX + j].rc = RectMake(sToolBox.rcBack.left + 15 + j * TILESIZE, sToolBox.rcBack.top + 35 + i * TILESIZE, TILESIZE, TILESIZE);
			}
		}
		break;
	//case 2:
	//	for (int i = 0; i < SAMPLETILEY; i++)
	//	{
	//		for (int j = 0; j < SAMPLETILEX; j++)
	//		{
	//			sSampleTile[i * SAMPLETILEX + j].rc = RectMake(sToolBox.rcBack.left - 433 + j * TILESIZE, sToolBox.rcBack.top + 15 + i * TILESIZE, TILESIZE, TILESIZE);
	//		}
	//	}
	//	break;
	//case 3:
	//	for (int i = 0; i < SAMPLETILEY; i++)
	//	{
	//		for (int j = 0; j < SAMPLETILEX; j++)
	//		{
	//			sSampleTile[i * SAMPLETILEX + j].rc = RectMake(sToolBox.rcBack.left - 881 + j * TILESIZE, sToolBox.rcBack.top + 15 + i * TILESIZE, TILESIZE, TILESIZE);
	//		}
	//	}
	//	break;
	//case 4:
	//	for (int i = 0; i < SAMPLETILEY; i++)
	//	{
	//		for (int j = 0; j < SAMPLETILEX; j++)
	//		{
	//			sSampleTile[i * SAMPLETILEX + j].rc = RectMake(sToolBox.rcBack.left - 1329 + j * TILESIZE, sToolBox.rcBack.top + 15 + i * TILESIZE, TILESIZE, TILESIZE);
	//		}
	//	}
	//	break;
	}
}

void maptool::setEnemySelectRect()
{
	//에너미 타일 렉트 초기화 -동주,연우 0410
	//sEnemyTile.rcGreyBean = RectMake(sSampleTile[0].rc.left, sSampleTile[0].rc.top, 64, 64);
	//sEnemyTile.rcBlackBean = RectMake(sSampleTile[2].rc.left, sSampleTile[2].rc.top, 64, 64);
	//sEnemyTile.rcBlueBean = RectMake(sSampleTile[4].rc.left, sSampleTile[4].rc.top, 64, 64);
	//sEnemyTile.rcGreyBird = RectMake(sSampleTile[112].rc.left, sSampleTile[112].rc.top, 64, 64);
	//sEnemyTile.rcGreenBird = RectMake(sSampleTile[114].rc.left, sSampleTile[114].rc.top, 64, 64);
	//sEnemyTile.rcRedBird = RectMake(sSampleTile[116].rc.left, sSampleTile[116].rc.top, 64, 64);
	//sEnemyTile.rcDoChi = RectMake(sSampleTile[224].rc.left, sSampleTile[224].rc.top, 64, 64);
	//sEnemyTile.rcMushroom = RectMake(sSampleTile[226].rc.left, sSampleTile[226].rc.top, 64, 64);
	//sEnemyTile.rcBlueFlower = RectMake(sSampleTile[6].rc.left, sSampleTile[6].rc.top, 64, 96);
	//sEnemyTile.rcGreenFlower = RectMake(sSampleTile[8].rc.left, sSampleTile[8].rc.top, 64, 96);
	//sEnemyTile.rcWingTurtle = RectMake(sSampleTile[12].rc.left, sSampleTile[12].rc.top, 64, 96);
	//sEnemyTile.rcBlueTurtle = RectMake(sSampleTile[392].rc.left, sSampleTile[392].rc.top, 64, 96);
	//sEnemyTile.rcGreenTurtle = RectMake(sSampleTile[394].rc.left, sSampleTile[394].rc.top, 64, 96);
	//sEnemyTile.rcBoss = RectMake(sSampleTile[340].rc.left, sSampleTile[340].rc.top, 128, 128);
	//sEnemyTile.rcRightBullet = RectMake(sSampleTile[346].rc.left, sSampleTile[346].rc.top, 64, 64);
	//sEnemyTile.rcLeftBullet = RectMake(sSampleTile[458].rc.left, sSampleTile[458].rc.top, 64, 64);
	//sEnemyTile.rcCannon = RectMake(sSampleTile[348].rc.left, sSampleTile[348].rc.top, 64, 128);
}

TERRAIN maptool::terrainSelect(int frameX, int frameY)
{
	//시멘트
	if (frameX == 1 && frameY == 0)
	{
		return TR_CEMENT;
	}
	//땅
	if (frameX == 2 && frameY == 0)
	{
		return TR_GROUND;
	}
	//잔디
	if (frameX == 3 && frameY == 0)
	{
		return TR_GRASS;
	}
	//물
	if (frameX == 4 && frameY == 0)
	{
		return TR_WATER;
	}

	//기타
	return TR_GROUND;
}

OBJECT maptool::objectSelect(int frameX, int frameY)
{
	return  OBJ_BLOCKS;
}

