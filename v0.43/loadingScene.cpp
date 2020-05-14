#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init()
{
	//로딩클래스 초기화
	_loading = new loading;
	_loading->init();

	//로딩 이미지 및 사운드 초기화
	this->loadingImage();
	this->loadingSound();

	//로딩 해골 이미지
	IMAGEMANAGER->addFrameImage("로딩해골", "Images/일반해골달리기.bmp", 320, 64, 8, 2);

	_count = _index = 0;
	return S_OK;
}

void loadingScene::release()
{
	//로딩클래스 해제
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	//로딩클래스 업데이트
	_loading->update();

	//로딩완료후 화면 변경
	if (_loading->loadingDone())
	{
		SCENEMANAGER->loadScene("메뉴화면");
	}
	_count++;
	IMAGEMANAGER->findImage("로딩해골")->setFrameY(0);

	//애니메이션
	if (_count % 4 == 0)
	{
		_index++;
		if (_index > 8)
		{
			_index = 0;
		}
		IMAGEMANAGER->findImage("로딩해골")->setFrameX(_index);
	}

}

void loadingScene::render()
{
	//로딩클래스 렌더
	_loading->render();

	for (int i = 0; i < _loading->getLoadItem().size(); i++)
	{
		if (_loading->getLoadItem()[i]->getLoadKind() == LOAD_KIND_IMAGE_0) continue;
		sprintf(_LoadFileName, _loading->getLoadItem()[i]->getImageResource().fileName);
	}

	SetBkMode(getMemDC(), TRANSPARENT);
	TextOut(getMemDC(), 370, 562, _LoadFileName, strlen(_LoadFileName));

	IMAGEMANAGER->findImage("로딩해골")->frameRender(getMemDC(), _loading->getProgressBar()->getWidth() + 280, 575);
}


//로딩이미지 함수(이곳에 이미지를 전부 넣어라)
void loadingScene::loadingImage()
{
	_loading->loadImage("백그라운드1", "Images/Background1_수정.bmp", 2600, 810);
	_loading->loadImage("백그라운드1_미니", "Images/Background1_미니.bmp", 260, 81);
	_loading->loadImage("백그라운드2", "Images/Background2_수정.bmp", 2600, 810);
	_loading->loadImage("백그라운드2_미니", "Images/Background2_미니.bmp", 260, 81);
	_loading->loadImage("백그라운드3", "Images/Background3_수정.bmp", 2600, 810);
	_loading->loadImage("백그라운드3_미니", "Images/Background3_미니.bmp", 260, 81);
	_loading->loadImage("백그라운드4", "Images/Background4_수정.bmp", 2600, 810);
	_loading->loadImage("백그라운드4_미니", "Images/Background4_미니.bmp", 260, 81);

	_loading->loadImage("스컬메뉴", "Images/스컬메뉴.bmp", 1280, 720);
	_loading->loadImage("메뉴_기본", "Images/메뉴_기본.bmp", 378, 560);
	_loading->loadImage("메뉴_스타트", "Images/메뉴_스타트.bmp", 378, 560);
	_loading->loadImage("메뉴_맵툴", "Images/메뉴_맵툴.bmp", 378, 560);
	_loading->loadImage("메뉴_나가기", "Images/메뉴_나가기.bmp", 378, 560);
	_loading->loadImage("버튼_드래그", "Images/버튼_드래그.bmp", 173, 57);
	_loading->loadImage("버튼_드래그온", "Images/버튼_드래그온.bmp", 173, 57);
	_loading->loadImage("버튼_로드", "Images/버튼_로드.bmp", 173, 57);
	_loading->loadImage("버튼_로드온", "Images/버튼_로드온.bmp", 173, 57);
	_loading->loadImage("버튼_리셋", "Images/버튼_리셋.bmp", 173, 57);
	_loading->loadImage("버튼_리셋온", "Images/버튼_리셋온.bmp", 173, 57);
	_loading->loadImage("버튼_세이브", "Images/버튼_세이브.bmp", 173, 57);
	_loading->loadImage("버튼_세이브온", "Images/버튼_세이브온.bmp", 173, 57);
	_loading->loadImage("버튼_엑시트", "Images/버튼_엑시트.bmp", 173, 57);
	_loading->loadImage("버튼_엑시트온", "Images/버튼_엑시트온.bmp", 173, 57);
	_loading->loadImage("버튼_오브젝트", "Images/버튼_오브젝트.bmp", 173, 57);
	_loading->loadImage("버튼_오브젝트온", "Images/버튼_오브젝트온.bmp", 173, 57);
	_loading->loadImage("버튼_이레이저", "Images/버튼_이레이저.bmp", 173, 57);
	_loading->loadImage("버튼_이레이저온", "Images/버튼_이레이저온.bmp", 173, 57);
	_loading->loadImage("버튼_지형", "Images/버튼_지형.bmp", 173, 57);
	_loading->loadImage("버튼_지형온", "Images/버튼_지형온.bmp", 173, 57);
	_loading->loadImage("툴박스", "Images/툴박스.bmp", 1000, 450);
	//인게임 메뉴
	_loading->loadImage("인게임메뉴화면", "Images/인게임메뉴화면.bmp", 372, 696);
	_loading->loadImage("인게임_계속버튼", "Images/인게임_계속버튼.bmp", 173, 57);
	_loading->loadImage("인게임_계속버튼On", "Images/인게임_계속버튼On.bmp", 173, 57);
	_loading->loadImage("인게임_옵션버튼", "Images/인게임_옵션버튼.bmp", 173, 57);
	_loading->loadImage("인게임_옵션버튼On", "Images/인게임_옵션버튼On.bmp", 173, 57);
	_loading->loadImage("인게임_나가기버튼", "Images/인게임_나가기버튼.bmp", 173, 57);
	_loading->loadImage("인게임_나가기버튼On", "Images/인게임_나가기버튼On.bmp", 173, 57);
	//맵1
	_loading->loadImage("맵1_배경1", "Images/시작맵/시작배경_1.bmp", 1940, 720);
	_loading->loadImage("맵1_하늘1", "Images/시작맵/시작하늘_1_수정.bmp", 1280, 4961);
	_loading->loadImage("맵1_하늘2", "Images/시작맵/시작하늘_2.bmp", 1880, 720);
	_loading->loadImage("맵1_구름1", "Images/시작맵/시작구름_1_수정.bmp", 1896, 690);
	_loading->loadImage("맵1_구름2", "Images/시작맵/시작구름_2.bmp", 405, 105);
	_loading->loadImage("맵1_구름3", "Images/시작맵/시작구름_3.bmp", 313, 82);
	_loading->loadImage("맵1_구름4", "Images/시작맵/시작구름_4.bmp", 1175, 1190);
	_loading->loadImage("맵1_구름5", "Images/시작맵/시작구름_5.bmp", 1120, 1616);
	_loading->loadImage("맵1_바닥", "Images/시작맵/바닥_수정.bmp", 3284, 720);
	_loading->loadImage("맵1_샹들리에1", "Images/시작맵/시작샹들리에_1.bmp", 228, 190);
	_loading->loadImage("맵1_샹들리에2", "Images/시작맵/시작샹들리에_2.bmp", 223, 245);
	_loading->loadImage("맵1_샹들리에3", "Images/시작맵/시작샹들리에_3.bmp", 213, 240);
	_loading->loadImage("맵1_오브젝트", "Images/시작맵/오브젝트.bmp", 3284, 720);
	_loading->loadImage("맵1_성벽1", "Images/시작맵/탑벽.bmp", 311, 700);
	_loading->loadImage("맵1_성벽2", "Images/시작맵/탑벽2.bmp", 253, 700);
	_loading->loadImage("맵1_성벽3", "Images/시작맵/성벽1.bmp", 311, 4661);
	_loading->loadImage("맵1_성", "Images/시작맵/성배경.bmp", 1280, 1525);
	_loading->loadImage("맵1_산1" "Images/시작맵/산배경_1.bmp", 1051, 629);
	_loading->loadImage("맵1_산2", "Images/시작맵/산배경_2.bmp", 1052, 381);
	_loading->loadImage("아래맵_바닥", "Images/시작맵/아래맵바닥.bmp", 1588, 720);
	_loading->loadImage("아래맵_바닥_show", "Images/시작맵/아래맵바닥_show.bmp", 1588, 170);
	_loading->loadImage("아래맵_오브젝트", "Images/시작맵/아래맵오브젝트.bmp", 1588, 720);
	_loading->loadImage("아래맵_앞배경", "Images/시작맵/아래맵앞배경.bmp", 1588, 720);
	_loading->loadImage("F상호작용", "Images/시작맵/F_Button.bmp", 26, 24);
	_loading->loadImage("들어가기", "Images/시작맵/들어가기.bmp", 72, 20);
	//맵2
	_loading->loadImage("맵2_바닥", "Images/맵2/map2_pixel.bmp", 2600, 810);
	_loading->loadImage("맵2_오브젝트", "Images/맵2/map2_object.bmp", 2600, 810);
	_loading->loadImage("맵2_프론트", "Images/맵2/map2_front.bmp", 2600, 810);
	//맵3
	_loading->loadImage("맵3_바닥", "Images/맵3/map3_pixel.bmp", 1666, 720);
	_loading->loadImage("맵3_오브젝트", "Images/맵3/map3_object.bmp", 1666, 720);
	_loading->loadImage("살펴보기", "Images/맵3/살펴보기.bmp", 72, 20);
	//UI관련
	//_loading->loadImage("플레이어UI창", "Images/캐릭터UI.bmp", 342, 135);
	//_loading->loadImage("UI창_space", "Images/Space.bmp", 342, 135);
	//_loading->loadImage("작은원", "Images/작은원.bmp", 342, 135);
	_loading->loadImage("플레이어UI창", "Images/캐릭터UI_수정.bmp", 334, 134);
	_loading->loadImage("UI창_space", "Images/Space_수정.bmp", 334, 134);
	_loading->loadImage("작은원", "Images/작은원_수정.bmp", 334, 134);
	_loading->loadImage("스컬큰프로필", "Images/큰프로필.bmp", 90, 90);
	_loading->loadImage("스컬작은프로필", "Images/작은프로필.bmp", 42, 42);
	_loading->loadImage("스컬스킬1", "Images/스컬스킬_1.bmp", 52, 52);
	_loading->loadImage("스컬스킬2", "Images/스컬스킬_2.bmp", 52, 52);
	_loading->loadImage("스킬칸", "Images/스킬칸_수정.bmp", 56, 56);
	_loading->loadImage("A_button", "Images/A_button.bmp", 26, 24);
	_loading->loadImage("S_button", "Images/S_button.bmp", 26, 24);
	_loading->loadImage("playerHpBar_front", "Images/체력바_Front.bmp", 236, 25);
	_loading->loadImage("playerHpBar_back", "Images/체력바_Back.bmp", 236, 25);
	_loading->loadFrameImage("skillCoolDown", "Images/cooldown/skillcool_수정.bmp", 1958, 180, 14, 1);
	_loading->loadImage("showCoolDown", "Images/cooldown/showCoolDown.bmp", 51, 51);
	_loading->loadImage("병사큰프로필", "Images/soldier_큰프로필.bmp", 90, 90);
	_loading->loadImage("병사작은프로필", "Images/soldier_작은프로필.bmp", 42, 42);
	_loading->loadImage("병사스킬1", "Images/soldier_Skill1.bmp", 52, 52);
	_loading->loadImage("사무라이큰프로필", "Images/samurai_큰프로필.bmp", 90, 90);
	_loading->loadImage("사무라이작은프로필", "Images/samurai_작은프로필.bmp", 42, 42);
	_loading->loadImage("사무라이스킬1_icon", "Images/samurai_Skill1.bmp", 52, 52);
	_loading->loadImage("사무라이스킬2_icon", "Images/samurai_Skill2.bmp", 52, 52);
	_loading->loadImage("일반해골설명", "Images/일반해골설명.bmp", 222, 298);
	_loading->loadImage("병사해골설명", "Images/병사해골설명.bmp", 222, 298);
	_loading->loadImage("사무라이해골설명", "Images/사무라이해골설명.bmp", 222, 400);
	_loading->loadImage("줍기", "Images/줍기.bmp", 36, 20);
	//플레이어 프레임이미지
	//일반해골
	_loading->loadFrameImage("시작", "Images/skul/START.bmp", 6480, 128, 27, 1);
	_loading->loadFrameImage("일반해골달리기", "Images/skul/RUN.bmp", 672, 130, 8, 2);
	_loading->loadFrameImage("일반해골점프", "Images/skul/JUMP.bmp", 518, 156, 7, 2);
	_loading->loadFrameImage("일반해골공격1", "Images/skul/ATT1.bmp", 600, 212, 5, 2);
	_loading->loadFrameImage("일반해골공격2", "Images/skul/ATT2.bmp", 472, 224, 4, 2);
	_loading->loadFrameImage("일반해골IDLE", "Images/skul/IDLE.bmp", 328, 132, 4, 2);
	_loading->loadFrameImage("일반해골대쉬", "Images/skul/DASH.bmp", 76, 96, 1, 2);
	_loading->loadFrameImage("일반해골대쉬효과", "Images/skul/DASH_EFECT.bmp", 76, 96, 1, 2);
	_loading->loadFrameImage("일반해골점프공격", "Images/skul/JUMPATT.bmp", 464, 216, 4, 2);
	_loading->loadFrameImage("일반해골교대", "Images/skul/CHANGE.bmp", 882, 210, 7, 2);
	_loading->loadFrameImage("일반해골스킬", "Images/skul/SKILL.bmp", 496, 144, 4, 2);
	_loading->loadImage("일반해골스킬_오른쪽", "Images/skul/HEAD_R.bmp", 28, 22);
	_loading->loadImage("일반해골스킬_왼쪽", "Images/skul/HEAD_L.bmp", 28, 22);
	//머리없는 해골
	_loading->loadFrameImage("머리없는달리기", "Images/skul/RUN_non.bmp", 768, 128, 8, 2);
	_loading->loadFrameImage("머리없는점프", "Images/skul/jump_non.bmp", 532, 152, 7, 2);
	_loading->loadFrameImage("머리없는공격1", "Images/skul/ATT_non.bmp", 600, 212, 5, 2);
	_loading->loadFrameImage("머리없는공격2", "Images/skul/ATT2_non.bmp", 472, 224, 4, 2);
	_loading->loadFrameImage("머리없는IDLE", "Images/skul/IDLE_non.bmp", 336, 100, 4, 2);
	_loading->loadFrameImage("머리없는대쉬", "Images/skul/DASH_non.bmp", 62, 80, 1, 2);
	_loading->loadFrameImage("머리없는대쉬효과", "Images/skul/DASH_EFECT_non.bmp", 62, 80, 1, 2);
	_loading->loadFrameImage("머리없는점프공격", "Images/skul/jumpAtt_non.bmp", 464, 220, 4, 2);
	//병사해골
	_loading->loadFrameImage("해골병사달리기", "Images/soldier/RUN.bmp", 640, 148, 8, 2);
	_loading->loadFrameImage("해골병사점프", "Images/soldier/JUMP.bmp", 574, 160, 7, 2);
	_loading->loadFrameImage("해골병사공격", "Images/soldier/ATT.bmp", 672, 192, 7, 2);
	_loading->loadFrameImage("해골병사IDLE", "Images/soldier/IDLE.bmp", 256, 156, 4, 2);
	_loading->loadFrameImage("해골병사대쉬", "Images/soldier/DASH.bmp", 88, 112, 1, 2);
	_loading->loadFrameImage("해골병사대쉬효과", "Images/soldier/DASH_EFECT.bmp", 88, 112, 1, 2);
	_loading->loadFrameImage("해골병사점프공격", "Images/soldier/JUMPATT.bmp", 368, 178, 4, 2);
	_loading->loadFrameImage("해골병사교대", "Images/soldier/CHAN.bmp", 276, 192, 3, 2);
	_loading->loadFrameImage("해골병사스킬", "Images/soldier/SKILL.bmp", 376, 192, 4, 2);
	//사무라이 해골
	_loading->loadFrameImage("사무라이달리기", "Images/samurai/RUN.bmp", 528, 148, 6, 2);
	_loading->loadFrameImage("사무라이점프", "Images/samurai/JUMP.bmp", 640, 152, 8, 2);
	_loading->loadFrameImage("사무라이공격1", "Images/samurai/ATT1.bmp", 696, 164, 6, 2);
	_loading->loadFrameImage("사무라이공격2", "Images/samurai/ATT2.bmp", 624, 232, 4, 2);
	_loading->loadFrameImage("사무라이공격3", "Images/samurai/ATT3.bmp", 830, 192, 5, 2);
	_loading->loadFrameImage("사무라이IDLE", "Images/samurai/IDLE.bmp", 456, 156, 6, 2);
	_loading->loadFrameImage("사무라이대쉬", "Images/samurai/DASH.bmp", 90, 116, 1, 2);
	_loading->loadFrameImage("사무라이대쉬효과", "Images/samurai/DASH_EFECT.bmp", 90, 116, 1, 2);
	_loading->loadFrameImage("사무라이점프공격", "Images/samurai/JUMPATT.bmp", 930, 152, 5, 2);
	_loading->loadFrameImage("사무라이교대", "Images/samurai/CHAN.bmp", 440, 164, 4, 2);
	_loading->loadFrameImage("사무라이스킬1", "Images/samurai/SKILL1.bmp", 1344, 164, 12, 2);
	_loading->loadFrameImage("사무라이스킬2", "Images/samurai/SKILL2.bmp", 1140, 164, 10, 2);
	_loading->loadFrameImage("사무라이납도", "Images/samurai/NAP.bmp", 702, 164, 9, 2);
	_loading->loadFrameImage("사무라이표식이펙트", "Images/samurai/SIGN_EFECT.bmp", 200, 19, 5, 1);
	_loading->loadFrameImage("사무라이스킬1이펙트", "Images/samurai/SKILL1_EFECT.bmp", 1728, 156, 9, 1);
	_loading->loadFrameImage("사무라이납도이펙트", "Images/samurai/NAP_EFECT.bmp", 740, 51, 10, 1);
	//뼈무덤
	_loading->loadFrameImage("노멀뼈무덤", "Images/ruin/NOMAL.bmp", 1458, 106, 9, 1);
	_loading->loadFrameImage("유니크뼈무덤", "Images/ruin/UNIQUE.bmp", 4048, 222, 11, 1);
	_loading->loadImage("병사해골", "Images/ruin/병사아이템.bmp", 38, 40);
	_loading->loadImage("사무라이해골", "Images/ruin/사무라이아이템.bmp", 66, 34);
	//에너미 프레임이미지
	//나무
	_loading->loadFrameImage("나무IDLE", "Images/enemy/Tree_Idle.bmp", 420, 186, 5, 2);
	_loading->loadFrameImage("나무달리기", "Images/enemy/Tree_Run.bmp", 477, 183, 6, 2);
	_loading->loadFrameImage("나무공격", "Images/enemy/Tree_Att.bmp", 450, 180, 4, 2);
	_loading->loadFrameImage("나무히트", "Images/enemy/Tree_Hit.bmp", 156, 192, 2, 2);
	_loading->loadFrameImage("나무죽음", "Images/enemy/Tree_Dead.bmp", 108, 87, 1, 2);
	//병사
	_loading->loadFrameImage("병사IDLE", "Images/enemy/Soldier_Idle.bmp", 270, 159, 6, 2);
	_loading->loadFrameImage("병사달리기", "Images/enemy/Soldier_Run.bmp", 672, 138, 8, 2);
	_loading->loadFrameImage("병사공격", "Images/enemy/Soldier_Att.bmp", 488, 180, 5, 2);
	_loading->loadFrameImage("병사히트", "Images/enemy/Soldier_Hit.bmp", 138, 141, 2, 2);
	_loading->loadImage("병사죽음", "Images/enemy/Soldier_Dead.bmp", 21, 35);
	//맵 프레임이미지
	_loading->loadFrameImage("시작문", "Images/시작맵/시작문_수정.bmp", 2960, 248, 8, 1);


	//로딩이 너무 빠르게 진행되서 천천히 돌아가도록 테스트용으로 만들기
	//for (int i = 0; i < 380; i++)
	//{
	//	_loading->loadImage("테스트", WINSIZEX, WINSIZEY);
	//}
}

//로딩사운드 함수(이곳에 사운드를 전부 넣어라)         
void loadingScene::loadingSound()
{
}
