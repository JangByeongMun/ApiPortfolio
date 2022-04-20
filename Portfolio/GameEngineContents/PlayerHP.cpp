#include "PlayerHP.h"
#include <GameEngineBase/GameEngineWindow.h>

PlayerHP::PlayerHP()
	: RendererVector_()
	, MaxRedHP_(0)
	, CurrentRedHP_(0)
	, CurrentAddHP_(0)
	, IsHalfRed_(false)
	, IsHalfAdd_(false)
{
}

PlayerHP::~PlayerHP() 
{
}

void PlayerHP::Start()
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
		TmpRenderer->CameraEffectOff();
		RendererVector_.push_back(TmpRenderer);
	}
}

void PlayerHP::UpdateUI()
{
	for (int i = 0; i < MaxCount; i++)
	{
		if (i < CurrentRedHP_ - 1)
		{
			RendererVector_[i]->SetIndex(0);
		}
		else if (i < CurrentRedHP_)
		{
			if (true == IsHalfRed_)
			{
				RendererVector_[i]->SetIndex(1);
			}
			else
			{
				RendererVector_[i]->SetIndex(0);
			}
		}
		else if (i < MaxRedHP_)
		{
			RendererVector_[i]->SetIndex(2);
		}
		else if (i - MaxRedHP_ < CurrentAddHP_ - 1)
		{
			int TmpValue = i - MaxRedHP_;
			if (AddHeartVector_[TmpValue] == HeartType::SoulHeart)
			{
				RendererVector_[i]->SetIndex(5);
			}
			if (AddHeartVector_[TmpValue] == HeartType::BlackHeart)
			{
				RendererVector_[i]->SetIndex(7);
			}
		}
		else if (i - MaxRedHP_ < CurrentAddHP_)
		{
			int TmpValue = i - MaxRedHP_;
			if (AddHeartVector_[TmpValue] == HeartType::SoulHeart)
			{
				if (true == IsHalfAdd_)
				{
					RendererVector_[i]->SetIndex(6);
				}
				else
				{
					RendererVector_[i]->SetIndex(5);
				}
			}
			else if (AddHeartVector_[TmpValue] == HeartType::BlackHeart)
			{
				if (true == IsHalfAdd_)
				{
					RendererVector_[i]->SetIndex(8);
				}
				else
				{
					RendererVector_[i]->SetIndex(7);
				}
			}
		}
	}
	int a = 0;
}

void PlayerHP::SetMaxHp(int _Value)
{
	MaxRedHP_ = _Value;
	CurrentRedHP_ = _Value;
	UpdateUI();
}

void PlayerHP::AddMaxHp(int _Value, int _Heal)
{
	if (_Heal == -1)
	{
		_Heal = _Value;
	}

	MaxRedHP_ += _Value;
	CurrentRedHP_ += _Heal;
	UpdateUI();
}

void PlayerHP::AddRedHp(int _Value, bool _IsHalf)
{
	if (_Value > 0) // ��Ʈ �߰��ϋ�
	{
		if (true == _IsHalf) // �߰��� ����¥���϶�
		{
			if (false == IsHalfRed_) // ������°� ������ �ƴϿ�����
			{
				CurrentRedHP_ += _Value;
			}

			IsHalfRed_ = !IsHalfRed_;
		}
		else if (false == _IsHalf) // �߰��� �����϶�
		{
			CurrentRedHP_ += _Value;
		}
	}


	else if (_Value < 0) // ��Ʈ �����϶�
	{
		if (true == _IsHalf) // ���Ұ� ����¥���϶�
		{
			if (true == IsHalfRed_)// ������°� ������ ������
			{
				CurrentRedHP_ += _Value;
			}

			IsHalfRed_ = !IsHalfRed_;
		}
		else if (false == _IsHalf) // ���Ұ� �����϶�
		{
			CurrentRedHP_ += _Value;
		}
	}

	if (CurrentRedHP_ >= MaxRedHP_)
	{
		CurrentRedHP_ = MaxRedHP_;
		IsHalfRed_ = false;
	}
	UpdateUI();
}

void PlayerHP::AddHearts(int _Value, HeartType _Type, bool _IsHalf)
{
	if (_Value > 0) // ��Ʈ �߰��ϋ�
	{
		if (true == _IsHalf) // �߰��� ����¥���϶�
		{
			if (false == IsHalfAdd_) // ������°� ������ �ƴϿ�����
			{
				CurrentAddHP_ += _Value;
				AddHeartVector_.push_back(_Type);
			}
			
			IsHalfAdd_ = !IsHalfAdd_;
		}
		else if(false == _IsHalf) // �߰��� �����϶�
		{
			CurrentAddHP_ += _Value;
			AddHeartVector_.push_back(_Type);
		}
	}


	else if (_Value < 0) // ��Ʈ �����϶�
	{
		if (true == _IsHalf) // ���Ұ� ����¥���϶�
		{
			if (true == IsHalfAdd_)// ������°� ������ ������
			{
				CurrentAddHP_ += _Value;
				AddHeartVector_.pop_back();
			}

			IsHalfAdd_ = !IsHalfAdd_;
		}
		else if (false == _IsHalf) // ���Ұ� �����϶�
		{
			CurrentAddHP_ += _Value;
			AddHeartVector_.pop_back();
		}
	}

	UpdateUI();
}
