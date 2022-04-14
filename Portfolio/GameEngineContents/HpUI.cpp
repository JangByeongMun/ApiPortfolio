#include "HPUI.h"
#include <GameEngineBase/GameEngineWindow.h>

HPUI::HPUI()
	: RendererVector_()
	, MaxRedHP_(0)
	, CurrentRedHP_(0)
	, CurrentAddHP_(0)
{
}

HPUI::~HPUI() 
{
}

void HPUI::Start()
{
	SetPosition({130, 35});

	RendererVector_.reserve(MaxCount);
	for (int i = 0; i < MaxCount; i++)
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("ui_hearts_1.bmp");

		if (i < MaxRedHP_)
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
		RendererVector_.push_back(TmpRenderer);
	}
}

void HPUI::UpdateUI()
{
	for (int i = 0; i < MaxCount * 2; i += 2)
	{
		if (i <= CurrentRedHP_)
		{
			if ((CurrentRedHP_ - i) % 2 == 0)
			{
				RendererVector_[i / 2]->SetIndex(0);
			}
			else
			{
				RendererVector_[i / 2]->SetIndex(1);
			}
		}
		else if (i <= MaxRedHP_)
		{
			RendererVector_[i / 2]->SetIndex(2);
		}
		else if (i - MaxRedHP_ <= CurrentAddHP_)
		{
			int AddInt = -1;
			if (AddHeartVector_[(i - MaxRedHP_) / 2] == HeartType::SoulHeart)
			{
				AddInt = 5;
			}
			if (AddHeartVector_[(i - MaxRedHP_) / 2] == HeartType::BlackHeart)
			{
				AddInt = 7;
			}


			if ((CurrentRedHP_ - i) % 2 == 0)
			{
				RendererVector_[i / 2]->SetIndex(AddInt + 0);
			}
			else
			{
				RendererVector_[i / 2]->SetIndex(AddInt + 1);
			}
		}
		else
		{
			RendererVector_[i / 2]->SetIndex(9);
		}
	}
}

void HPUI::AddMaxHp(int _Value, int _Heal)
{
	MaxRedHP_ = _Value;
	CurrentRedHP_ = _Heal;
	UpdateUI();
}

void HPUI::AddRedHp(int _Value)
{
	CurrentRedHP_ += _Value;
	UpdateUI();
}

void HPUI::AddHearts(int _Value, HeartType _Type)
{
	CurrentAddHP_ += _Value;

	if (CurrentAddHP_ > AddHeartVector_.size())
	{
		AddHeartVector_.push_back(_Type);
	}
	else if (AddHeartVector_.size() >= CurrentAddHP_ + 1)
	{
		AddHeartVector_.pop_back();
	}
	AddHeartVector_.push_back(_Type);
	UpdateUI();
}
