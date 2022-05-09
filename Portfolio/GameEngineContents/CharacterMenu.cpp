#include "CharacterMenu.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngine.h>
#include "ContentsGlobal.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "BindingOfIsaac.h"
#include <GameEngineBase/GameEngineSound.h>

CharacterMenu::CharacterMenu() 
	: CurrentIndex_(0)
	, CurrentDifficulty_(0)
	, DifficultyArrow_(nullptr)
	, HardRenderer_(nullptr)
{
}

CharacterMenu::~CharacterMenu() 
{
}

void CharacterMenu::ChangeIndex(int _Index)
{
	CurrentIndex_ = _Index;

	UpdateUI();
}

void CharacterMenu::AddIndex(int _Index)
{
	if (_Index > 0)
	{
		GameEngineSound::SoundPlayOneShotWithVolume("character select right.wav", 0, 0.1f * Option_SFX);
	}
	else
	{
		GameEngineSound::SoundPlayOneShotWithVolume("character select left.wav", 0, 0.1f * Option_SFX);
	}

	CurrentIndex_ += _Index;
	if (CurrentIndex_ < 0)
	{
		CurrentIndex_ = 4;
	}
	if (CurrentIndex_ > 4)
	{
		CurrentIndex_ = 0;
	}

	UpdateUI();
}

void CharacterMenu::ChangeDifficult(int _Difficult)
{
	CurrentDifficulty_ = _Difficult;

	UpdateUI();
}

void CharacterMenu::AddDifficult(int _Difficult)
{
	CurrentDifficulty_ += _Difficult;
	if (CurrentDifficulty_ < 0)
	{
		CurrentDifficulty_ = 1;
	}
	if (CurrentDifficulty_ > 1)
	{
		CurrentDifficulty_ = 0;
	}

	UpdateUI();
}

void CharacterMenu::UpdateUI()
{
	for (int i = 0; i < AllCharacters_.size(); i++)
	{
		int TmpIndex = (CurrentIndex_ + i) % 5;
		AllCharacters_[TmpIndex]->SetPivot(AllPose_[i]);

		if (i == 0)
		{
			AllCharacters_[TmpIndex]->SetAlpha(255);
			AllCharacters_[TmpIndex]->SetOrder(3);
		}
		else if (i == 1 || i == 4)
		{
			AllCharacters_[TmpIndex]->SetAlpha(230);
			AllCharacters_[TmpIndex]->SetOrder(2);
		}
		else if (i == 2 || i == 3)
		{
			AllCharacters_[TmpIndex]->SetAlpha(150);
			AllCharacters_[TmpIndex]->SetOrder(1);
		}
	}

	for (int i = 0; i < AllCharactersName_.size(); i++)
	{
		if (i == CurrentIndex_)
		{
			AllCharactersName_[i]->On();
		}
		else
		{
			AllCharactersName_[i]->Off();
		}
	}

	for (int i = 0; i < StateHp_.size(); i++)
	{
		if (i == AllState_[CurrentIndex_].Hp - 1)
		{
			StateHp_[i]->On();
		}
		else
		{
			StateHp_[i]->Off();
		}
	}

	for (int i = 0; i < StateSpeed_.size(); i++)
	{
		if (i == AllState_[CurrentIndex_].Speed - 1)
		{
			StateSpeed_[i]->On();
		}
		else
		{
			StateSpeed_[i]->Off();
		}
	}

	for (int i = 0; i < StateAttack_.size(); i++)
	{
		if (i == AllState_[CurrentIndex_].Attack - 1)
		{
			StateAttack_[i]->On();
		}
		else
		{
			StateAttack_[i]->Off();
		}
	}

	for (int i = 0; i < StateItem_.size(); i++)
	{
		if (i == AllState_[CurrentIndex_].Item)
		{
			StateItem_[i]->On();
		}
		else
		{
			StateItem_[i]->Off();
		}
	}

	DifficultyArrow_->SetPivot(DifficultyArrowPos_[CurrentDifficulty_]);

	if (1 == CurrentDifficulty_)
	{
		HardRenderer_->On();
	}
	else
	{
		HardRenderer_->Off();
	}
}

void CharacterMenu::SelectIndex()
{
	if (6 == CurrentIndex_)
	{
		GameEngineRandom Random;
		CurrentIndex_ = Random.RandomInt(0, 5);
	}

	//BindingOfIsaac* TmpEngine = dynamic_cast<BindingOfIsaac*>(&GameEngine::GetInst());
	//if (nullptr != TmpEngine)
	//{
	//	TmpEngine->ResetPlayLevel("Play");
	//}
	SelectedCharacterType = static_cast<CharacterType>(CurrentIndex_);
	GameEngine::GetInst().ChangeLevel("MenuLoading");
}

void CharacterMenu::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half() + float4(1400, 2000));
	CreateRenderer("charactermenu.bmp", RenderPivot::CENTER, { 0, 0 });
	CreateRenderer("charactermenu_Arrow1.bmp", RenderPivot::CENTER, { -170, 100 });
	CreateRenderer("charactermenu_Arrow2.bmp", RenderPivot::CENTER, { 170, 100 });

	// 난이도 창
	CreateRenderer("difficultywidget.bmp", RenderPivot::CENTER, { 400, 0 });
	CreateRenderer("difficultywidget_Name1.bmp", RenderPivot::CENTER, { 410, -20 });
	CreateRenderer("difficultywidget_Name2.bmp", RenderPivot::CENTER, { 370, 20 });
	CreateRenderer("difficultywidget_Name2_2.bmp", RenderPivot::CENTER, { 450, 30 });
	DifficultyArrow_ = CreateRenderer("GameMenu_Arrow.bmp", RenderPivot::CENTER, { 315, -25 });

	// 캐릭터 렌더러추가
	{
		{
			GameEngineRenderer* CharacterRenderer = CreateRenderer("charactermenu_Characters.bmp");
			CharacterRenderer->SetIndex(0);

			AllCharacters_.push_back(CharacterRenderer);
		}
		{
			GameEngineRenderer* CharacterRenderer = CreateRenderer("charactermenu_Characters.bmp");
			CharacterRenderer->SetIndex(2);

			AllCharacters_.push_back(CharacterRenderer);
		}
		{
			GameEngineRenderer* CharacterRenderer = CreateRenderer("charactermenu_Characters.bmp");
			CharacterRenderer->SetIndex(3);

			AllCharacters_.push_back(CharacterRenderer);
		}
		{
			GameEngineRenderer* CharacterRenderer = CreateRenderer("charactermenu_Characters.bmp");
			CharacterRenderer->SetIndex(5);

			AllCharacters_.push_back(CharacterRenderer);
		}
		{
			GameEngineRenderer* CharacterRenderer = CreateRenderer("charactermenu_Characters.bmp");
			CharacterRenderer->SetIndex(7);

			AllCharacters_.push_back(CharacterRenderer);
		}
	}
	
	// 캐릭터 이름 렌더러 추가
	{
		GameEngineRenderer* NameRenderer = nullptr;
		NameRenderer = CreateRenderer("charactermenu_Name1.bmp", RenderPivot::CENTER, { 30, 90 });
		AllCharactersName_.push_back(NameRenderer);

		NameRenderer = CreateRenderer("charactermenu_Name2.bmp", RenderPivot::CENTER, { 30, 90 });
		AllCharactersName_.push_back(NameRenderer);
	
		NameRenderer = CreateRenderer("charactermenu_Name3.bmp", RenderPivot::CENTER, { 10, 90 });
		AllCharactersName_.push_back(NameRenderer);
	
		NameRenderer = CreateRenderer("charactermenu_Name4.bmp", RenderPivot::CENTER, { 30, 90 });
		AllCharactersName_.push_back(NameRenderer);
	
		NameRenderer = CreateRenderer("charactermenu_Name5.bmp", RenderPivot::CENTER, { 30, 90 });
		AllCharactersName_.push_back(NameRenderer);
	}

	// 캐릭터 스텟 추가
	AllState_.push_back(CharacterValue(3, 2, 2, 0));
	AllState_.push_back(CharacterValue(2, 3, 3, 1));
	AllState_.push_back(CharacterValue(4, 1, 2, 2));
	AllState_.push_back(CharacterValue(1, 2, 4, 3));
	AllState_.push_back(CharacterValue(5, 2, 2, 4));

	// 캐릭터 위치 추가
	AllPose_.push_back({ 0, 0 });
	AllPose_.push_back({ 150, -50 });
	AllPose_.push_back({ 120, -80 });
	AllPose_.push_back({ -120, -80 });
	AllPose_.push_back({ -150, -50 });

	CreateRenderer("charactermenu_State1.bmp", RenderPivot::CENTER, { -190, 160 });
	CreateRenderer("charactermenu_State2.bmp", RenderPivot::CENTER, { -40, 160 });
	CreateRenderer("charactermenu_State3.bmp", RenderPivot::CENTER, { 110, 160 });

	// 캐릭터 스텟 수치 렌더러 저장
	{
		{
			GameEngineRenderer* StateRenderer = nullptr;

			StateRenderer = CreateRenderer("charactermenu_StateValue1.bmp", RenderPivot::CENTER, { -120, 160 });
			StateHp_.push_back(StateRenderer);
			StateRenderer = CreateRenderer("charactermenu_StateValue2.bmp", RenderPivot::CENTER, { -120, 160 });
			StateHp_.push_back(StateRenderer);
			StateRenderer = CreateRenderer("charactermenu_StateValue3.bmp", RenderPivot::CENTER, { -120, 160 });
			StateHp_.push_back(StateRenderer);
			StateRenderer = CreateRenderer("charactermenu_StateValue4.bmp", RenderPivot::CENTER, { -120, 160 });
			StateHp_.push_back(StateRenderer);
			StateRenderer = CreateRenderer("charactermenu_StateValue5.bmp", RenderPivot::CENTER, { -120, 160 });
			StateHp_.push_back(StateRenderer);
		}
		{
			GameEngineRenderer* StateRenderer = nullptr;

			StateRenderer = CreateRenderer("charactermenu_StateValue1.bmp", RenderPivot::CENTER, { 30, 160 });
			StateSpeed_.push_back(StateRenderer);
			StateRenderer = CreateRenderer("charactermenu_StateValue2.bmp", RenderPivot::CENTER, { 30, 160 });
			StateSpeed_.push_back(StateRenderer);
			StateRenderer = CreateRenderer("charactermenu_StateValue3.bmp", RenderPivot::CENTER, { 30, 160 });
			StateSpeed_.push_back(StateRenderer);
			StateRenderer = CreateRenderer("charactermenu_StateValue4.bmp", RenderPivot::CENTER, { 30, 160 });
			StateSpeed_.push_back(StateRenderer);
			StateRenderer = CreateRenderer("charactermenu_StateValue5.bmp", RenderPivot::CENTER, { 30, 160 });
			StateSpeed_.push_back(StateRenderer);
		}
		{
			GameEngineRenderer* StateRenderer = nullptr;

			StateRenderer = CreateRenderer("charactermenu_StateValue1.bmp", RenderPivot::CENTER, { 180, 160 });
			StateAttack_.push_back(StateRenderer);
			StateRenderer = CreateRenderer("charactermenu_StateValue2.bmp", RenderPivot::CENTER, { 180, 160 });
			StateAttack_.push_back(StateRenderer);
			StateRenderer = CreateRenderer("charactermenu_StateValue3.bmp", RenderPivot::CENTER, { 180, 160 });
			StateAttack_.push_back(StateRenderer);
			StateRenderer = CreateRenderer("charactermenu_StateValue4.bmp", RenderPivot::CENTER, { 180, 160 });
			StateAttack_.push_back(StateRenderer);
			StateRenderer = CreateRenderer("charactermenu_StateValue5.bmp", RenderPivot::CENTER, { 180, 160 });
			StateAttack_.push_back(StateRenderer);
		}

		{
			GameEngineRenderer* StateRenderer = nullptr;

			StateRenderer = CreateRenderer("None.bmp", RenderPivot::CENTER, { 0, 200 });
			StateItem_.push_back(StateRenderer);
			StateRenderer = CreateRenderer("charactermenu_State4_1.bmp", RenderPivot::CENTER, { 0, 230 });
			StateItem_.push_back(StateRenderer);
			StateRenderer = CreateRenderer("charactermenu_State4_2.bmp", RenderPivot::CENTER, { 0, 230 });
			StateItem_.push_back(StateRenderer);
			StateRenderer = CreateRenderer("charactermenu_State4_3.bmp", RenderPivot::CENTER, { 0, 230 });
			StateItem_.push_back(StateRenderer);
			StateRenderer = CreateRenderer("charactermenu_State4_4.bmp", RenderPivot::CENTER, { 0, 230 });
			StateItem_.push_back(StateRenderer);
		}
	}

	// 난이도 화살표 위치 저장
	DifficultyArrowPos_.push_back({ 315, -25 });
	DifficultyArrowPos_.push_back({ 310, 20 });
	HardRenderer_ = CreateRenderer("charactermenu_Hard.bmp", RenderPivot::CENTER, { 88, 210 });

	ChangeIndex(0);
}

