#include "MenuFileSelect.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>

MenuFileSelect::MenuFileSelect()
	: AllFiles_()
	, CurrentIndex_()
	, NextIndex_()
	, IsChange(false)
	, CurrentTime_()
	, ChangeTime_()
{
}

MenuFileSelect::~MenuFileSelect() 
{
}

void MenuFileSelect::ChangeFile(int _Index)
{
	if (_Index > 2)
	{
		_Index = 2;
	}
	if (_Index < 0)
	{
		_Index = 0;
	}

	IsChange = true;
	NextIndex_ = _Index;
	ChangeTime_ = CurrentTime_;
}

void MenuFileSelect::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half() + float4(0, 675));

	CreateRenderer("saveselectmenu_Name.bmp", RenderPivot::CENTER, { 0, -300 });

	GameEngineRenderer* Renderer = nullptr;
	float4 Pos = {0, 0};

	Pos = { -360, -30 };
	Renderer = CreateRenderer("saveselectmenu_File1.bmp", RenderPivot::CENTER, Pos + float4(0, -30));
	AllFiles_.push_back(Renderer);
	AllPos_.push_back(Pos);

	Pos = { 0, -30 };
	Renderer = CreateRenderer("saveselectmenu_File2.bmp", RenderPivot::CENTER, Pos);
	AllFiles_.push_back(Renderer);
	AllPos_.push_back(Pos);

	Pos = { 360, -30 };
	Renderer = CreateRenderer("saveselectmenu_File3.bmp", RenderPivot::CENTER, Pos);
	AllFiles_.push_back(Renderer);
	AllPos_.push_back(Pos);

	CreateRenderer("saveselectmenu_Delete.bmp", RenderPivot::CENTER, { 0, 300 });
}

void MenuFileSelect::Update()
{
	CurrentTime_ += GameEngineTime::GetDeltaTime();

	if (true == IsChange)
	{
		AllFiles_[CurrentIndex_]->SetPivot(
			float4::Lerp(AllPos_[CurrentIndex_] - float4(0, 30), AllPos_[CurrentIndex_], (CurrentTime_ - ChangeTime_) * 10)
		);

		AllFiles_[NextIndex_]->SetPivot(
			float4::Lerp(AllPos_[NextIndex_], AllPos_[NextIndex_] - float4(0, 30), (CurrentTime_ - ChangeTime_ - 0.1f) * 10)
		);

		if (CurrentTime_ - ChangeTime_ >= 0.2f)
		{
			IsChange = false;
			CurrentIndex_ = NextIndex_;
			NextIndex_ = -1;
		}
	}
}