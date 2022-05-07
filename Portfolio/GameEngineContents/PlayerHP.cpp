#include "PlayerHP.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "Player.h"
#include "RandomRoomManager.h"
#include "RoomActor.h"
#include "BlackHeartEffect.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineSound.h>
#include "ContentsGlobal.h"

PlayerHP::PlayerHP()
	: RendererVector_()
	, MaxRedHP_(0)
	, CurrentRedHP_(0)
	, CurrentAddHP_(0)
	, IsHalfRed_(false)
	, IsHalfAdd_(false)
	, IsDeath_(false)
{
}

PlayerHP::~PlayerHP()
{
}

void PlayerHP::Start()
{
	SetPosition({ 130, 35 });

	RendererVector_.reserve(MaxCount);
	for (int i = 0; i < MaxCount; i++)
	{
		GameEngineRenderer* TmpShadowRenderer = CreateRenderer("ui_hearts_1_Shadow.bmp");
		GameEngineRenderer* TmpRenderer = CreateRenderer("ui_hearts_1.bmp");

		if (i < MaxRedHP_)
		{
			TmpRenderer->SetIndex(0);
		}
		else
		{
			TmpRenderer->SetIndex(9);
			TmpShadowRenderer->Off();
		}

		float x = static_cast<float>((i % (MaxCount / 2)) * 36);
		float y = static_cast<float>((i / (MaxCount / 2)) * 36);
		TmpRenderer->SetPivot({ x, y });
		TmpRenderer->CameraEffectOff();
		RendererVector_.push_back(TmpRenderer);

		TmpShadowRenderer->SetPivot({ x, y });
		TmpShadowRenderer->CameraEffectOff();
		TmpShadowRenderer->SetAlpha(100);
		ShadowRendererVector_.push_back(TmpShadowRenderer);
	}
}

void PlayerHP::PlayerDeadCheck()
{
	if (IsDeath_ == true)
	{
		return;
	}

	if (CurrentRedHP_ <= 0 && CurrentAddHP_ <= 0)
	{
		IsDeath_ = true;

		Player::MainPlayer->ChangeBodyState(PlayerBodyState::Dead);
		Player::MainPlayer->ChangeHeadState(PlayerHeadState::Dead);
		
		{
			std::string TmpName = "IsaacDiesNew";
			TmpName += std::to_string(GameEngineRandom::MainRandom->RandomInt(0, 2)) + ".wav";
			GameEngineSound::SoundPlayOneShotWithVolume(TmpName, 0, 1.0f * Option_SFX);
		}
	}
	else
	{
		Player::MainPlayer->ChangeBodyState(PlayerBodyState::Hitted);
		Player::MainPlayer->ChangeHeadState(PlayerHeadState::Hitted);

		{
			std::string TmpName = "hurtgrunt";
			TmpName += std::to_string(GameEngineRandom::MainRandom->RandomInt(0, 2)) + ".wav";
			GameEngineSound::SoundPlayOneShotWithVolume(TmpName, 0, 1.0f * Option_SFX);
		}
	}
}

void PlayerHP::UpdateUI()
{
	for (int i = 0; i < MaxCount; i++)
	{
		if (i < CurrentRedHP_ - 1)
		{
			RendererVector_[i]->SetIndex(0);
			ShadowRendererVector_[i]->On();
		}
		else if (i < CurrentRedHP_)
		{
			if (true == IsHalfRed_)
			{
				RendererVector_[i]->SetIndex(1);
				ShadowRendererVector_[i]->On();
			}
			else
			{
				RendererVector_[i]->SetIndex(0);
				ShadowRendererVector_[i]->On();
			}
		}
		else if (i < MaxRedHP_)
		{
			RendererVector_[i]->SetIndex(2);
			ShadowRendererVector_[i]->On();
		}
		else if (i - MaxRedHP_ < CurrentAddHP_ - 1)
		{
			int TmpValue = i - MaxRedHP_;
			if (AddHeartVector_[TmpValue] == HeartData::SoulHeart)
			{
				RendererVector_[i]->SetIndex(5);
				ShadowRendererVector_[i]->On();
			}
			if (AddHeartVector_[TmpValue] == HeartData::BlackHeart)
			{
				RendererVector_[i]->SetIndex(7);
				ShadowRendererVector_[i]->On();
			}
		}
		else if (i - MaxRedHP_ < CurrentAddHP_)
		{
			int TmpValue = i - MaxRedHP_;
			if (AddHeartVector_[TmpValue] == HeartData::SoulHeart)
			{
				if (true == IsHalfAdd_)
				{
					RendererVector_[i]->SetIndex(6);
					ShadowRendererVector_[i]->On();
				}
				else
				{
					RendererVector_[i]->SetIndex(5);
					ShadowRendererVector_[i]->On();
				}
			}
			else if (AddHeartVector_[TmpValue] == HeartData::BlackHeart)
			{
				if (true == IsHalfAdd_)
				{
					RendererVector_[i]->SetIndex(8);
					ShadowRendererVector_[i]->On();
				}
				else
				{
					RendererVector_[i]->SetIndex(7);
					ShadowRendererVector_[i]->On();
				}
			}
		}
		else
		{
			RendererVector_[i]->SetIndex(9);
			ShadowRendererVector_[i]->Off();
		}
	}
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


	if (_Heal >= MaxRedHP_)
	{
		MaxRedHP_ += _Value;
		CurrentRedHP_ = MaxRedHP_;
		IsHalfRed_ = false;
	}
	else
	{
		MaxRedHP_ += _Value;
		CurrentRedHP_ += _Heal;
	}

	while (MaxRedHP_ + CurrentAddHP_ > MaxCount)
	{
		CurrentAddHP_ -= 1;
		AddHeartVector_.pop_back();
	}

	UpdateUI();
}

bool PlayerHP::AddRedHp(bool _IsHalf)
{
	if (IsHalfRed_ == false && CurrentRedHP_ == MaxRedHP_)
	{
		return false;
	}

	if (true == _IsHalf) // 추가가 절반짜리일때
	{
		if (false == IsHalfRed_) // 현재상태가 절반이 아니였을떄
		{
			CurrentRedHP_ += 1;
		}

		IsHalfRed_ = !IsHalfRed_;
	}
	else if (false == _IsHalf) // 추가가 정수일때
	{
		CurrentRedHP_ += 1;
	}

	if (CurrentRedHP_ > MaxRedHP_)
	{
		CurrentRedHP_ = MaxRedHP_;
		IsHalfRed_ = false;
	}
	UpdateUI();
	return true;
}

bool PlayerHP::AddHearts(HeartData _Type, bool _IsHalf)
{
	if (IsHalfAdd_ == false && MaxRedHP_ + CurrentAddHP_ == MaxCount)
	{
		return false;
	}

	if (true == _IsHalf) // 추가가 절반짜리일때
	{
		if (false == IsHalfAdd_) // 현재상태가 절반이 아니였을떄
		{
			CurrentAddHP_ += 1;
			AddHeartVector_.push_back(_Type);
		}

		IsHalfAdd_ = !IsHalfAdd_;
	}
	else if (false == _IsHalf) // 추가가 정수일때
	{
		CurrentAddHP_ += 1;
		AddHeartVector_.push_back(_Type);
	}

	if (CurrentAddHP_ + MaxRedHP_ > MaxCount)
	{
		CurrentAddHP_ = MaxCount - MaxRedHP_;
		IsHalfRed_ = false;
	}
	UpdateUI();
	return true;
}

void PlayerHP::MinusHearts(bool _IsHalf)
{
	if (true == Player::MainPlayer->IsInvincibillity()) // 무적시간 이면 스킵
	{
		return;
	}

	if (CurrentAddHP_ > 0) // 추가 하트가 있을경우
	{
		if (true == _IsHalf) // 감소가 절반짜리일때
		{
			if (true == IsHalfAdd_)// 현재상태가 절반이 였을때
			{
				if (HeartData::BlackHeart == AddHeartVector_[AddHeartVector_.size() - 1])
				{
					float4 CurrentRoomPos = RandomRoomManager::GetInst()->FindRoom(Player::MainPlayer->GetCurrentRoomPos())->GetPosition();
					GetLevel()->CreateActor<BlackHeartEffect>()->SetPosition(CurrentRoomPos);
				}
				CurrentAddHP_ -= 1;
				AddHeartVector_.pop_back();
			}

			IsHalfAdd_ = !IsHalfAdd_;
		}
		else if (false == _IsHalf) // 감소가 정수일때
		{
			if (HeartData::BlackHeart == AddHeartVector_[AddHeartVector_.size() - 1])
			{
				float4 CurrentRoomPos = RandomRoomManager::GetInst()->FindRoom(Player::MainPlayer->GetCurrentRoomPos())->GetPosition();
				GetLevel()->CreateActor<BlackHeartEffect>()->SetPosition(CurrentRoomPos);
			}
			CurrentAddHP_ -= 1;
			AddHeartVector_.pop_back();
		}
	}
	else // 빨간하트만 있을경우
	{
		if (true == _IsHalf) // 감소가 절반짜리일때
		{
			if (true == IsHalfRed_)// 현재상태가 절반이 였을때
			{
				CurrentRedHP_ -= 1;
			}

			IsHalfRed_ = !IsHalfRed_;
		}
		else if (false == _IsHalf) // 감소가 정수일때
		{
			CurrentRedHP_ -= 1;
		}
	}

	PlayerDeadCheck();
	UpdateUI();
}
