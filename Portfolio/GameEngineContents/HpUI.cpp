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

int MaxCount = 12;
void HpUI::Start()
{
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

void HpUI::Setting()
{
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

void HpUI::SetMaxHP(int _Value)
{
	MaxHP_ = _Value;
	Setting();
}

void HpUI::AddMaxHP(int _Value, int _Heal)
{
	MaxHP_ += _Value;
	CurrentHP_ += _Heal;
	Setting();
}

void HpUI::SetCurrentHP(int _Value)
{
	CurrentHP_ = _Value;
	Setting();
}

void HpUI::AddCurrentHP(int _Value)
{
	CurrentHP_ += _Value;
	Setting();
}

void HpUI::AddColorHeart(HeartType _Type)
{
	//AddHeart_.push(_Type);
	Setting();
}