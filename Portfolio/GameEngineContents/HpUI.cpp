#include "HpUI.h"
#include <GameEngineBase/GameEngineWindow.h>

HpUI::HpUI()
	: RendererVector_()
	, AddHeart_()
	, MaxHP_(3)
	, CurrentHP_(3)
{
}

HpUI::~HpUI() 
{
}

void HpUI::Start()
{
	int MaxCount = 12;
	SetPosition({130, 35});
	RendererVector_.reserve(MaxCount);

	for (int i = 0; i < MaxCount; i++)
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("ui_hearts_1.bmp");

		if (i < MaxHP_)
		{
			TmpRenderer->SetIndex(0);
		}
		else
		{
			TmpRenderer->SetIndex(9);
		}

		float x = static_cast<float>((i % (MaxCount / 2)) * 36);
		float y = static_cast<float>((i / (MaxCount / 2)) * 36);
		TmpRenderer->SetPivot({ x, y });
	}
}

void HpUI::AddMaxHP(int _value, int _heal)
{
	MaxHP_ += _value;
	CurrentHP_ += _heal;
}

void HpUI::SetCurrentHP(int _value)
{
	CurrentHP_ = _value;
}

void HpUI::ChangeCurrentHP(int _value)
{
	CurrentHP_ += _value;
}

void HpUI::AddColorHeart(HeartType _Type)
{
	//AddHeart_.push(_Type);
}