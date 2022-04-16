#include "ItemUI.h"

ItemUI::ItemUI() 
	: MoneyRenderer_(nullptr)
	, BombRenderer_(nullptr)
	, KeyRenderer_(nullptr)
	, Money_(0)
	, Bomb_(0)
	, Key_(0)
{
}

ItemUI::~ItemUI() 
{
}

void ItemUI::UpdateUI()
{
	int test = Money_;
	int test2 = Bomb_;
	int test3 = Key_;
	MoneyCount_[0]->SetIndex(Money_ / 10);
	MoneyCount_[1]->SetIndex(Money_ % 10);

	BombCount_[0]->SetIndex(Bomb_ / 10);
	BombCount_[1]->SetIndex(Bomb_ % 10);

	KeyCount_[0]->SetIndex(Key_ / 10);
	KeyCount_[1]->SetIndex(Key_ % 10);
}

void ItemUI::SetMoney(int _Value)
{
	Money_ = _Value;
	UpdateUI();
}

void ItemUI::SetBomb(int _Value)
{
	Bomb_ = _Value;
	UpdateUI();
}

void ItemUI::SetKey(int _Value, bool _IsMaster)
{
	Key_ = _Value;

	if (IsMasterKey_ != _IsMaster)
	{
		IsMasterKey_ = _IsMaster;
		if (true == IsMasterKey_)
		{
			KeyRenderer_->SetIndex(4);
		}
		else
		{
			KeyRenderer_->SetIndex(1);
		}
	}
	UpdateUI();
}

void ItemUI::Reset()
{
	Money_ = 0;
	Bomb_ = 0;
	Key_ = 0;
}

void ItemUI::Start()
{
	SetPosition({ 30, 120 });

	MoneyRenderer_ = CreateRenderer("hudpickups.bmp", RenderPivot::CENTER, { 0, 0 });
	MoneyRenderer_->SetIndex(0);

	BombRenderer_ = CreateRenderer("hudpickups.bmp", RenderPivot::CENTER, { 0, 35 });
	BombRenderer_->SetIndex(3);
	
	KeyRenderer_ = CreateRenderer("hudpickups.bmp", RenderPivot::CENTER, { 0, 70 });
	KeyRenderer_->SetIndex(1);


	for (int i = 0; i < 2; i++)
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("whitecounter.bmp", RenderPivot::CENTER, { 15 + 18.0f * (i+1), 0 });
		TmpRenderer->SetIndex(0);
		MoneyCount_.push_back(TmpRenderer);
	}

	for (int i = 0; i < 2; i++)
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("whitecounter.bmp", RenderPivot::CENTER, { 15 + 18.0f * (i + 1), 35 });
		TmpRenderer->SetIndex(0);
		BombCount_.push_back(TmpRenderer);
	}

	for (int i = 0; i < 2; i++)
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("whitecounter.bmp", RenderPivot::CENTER, { 15 + 18.0f * (i + 1), 70 });
		TmpRenderer->SetIndex(0);
		KeyCount_.push_back(TmpRenderer);
	}
}

