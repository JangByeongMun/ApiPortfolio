#include "PlayLevel.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>

#include "Player.h"
#include "Projectile.h"
#include "PlayerHP.h"
#include "PlayBackGround.h"
#include "ActiveUI.h"
#include "Accessory.h"
#include "ContentsEnum.h"
#include "RandomRoomManager.h"
#include "PlayerUI.h"
#include "ContentsGlobal.h"
#include "PauseUI.h"

PlayLevel::PlayLevel() 
	: GlobalActor(nullptr)
	, IsLerp_(false)
	, LerpTimer_(0.0f)
	, Start_()
	, Goal_()
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::CameraLerp(float4 _Start, float4 _Goal)
{
	LerpTimer_ = 0.0f;
	IsLerp_ = true;
	Start_ = _Start;
	Goal_ = _Goal;
}

void PlayLevel::StopBGM()
{
	BgmPlayer_.Stop();
}

void PlayLevel::StopBossBGM()
{
	BgmPlayer_.Pause(false);
	BossBgmPlayer_.Pause(true);
}

void PlayLevel::PlayBossBGM()
{
	BgmPlayer_.Pause(true);
	BossBgmPlayer_.Pause(false);
}

void PlayLevel::Loading()
{
	CreateActor<PlayBackGround>((int)ORDER::BACKGROUND);
	RandomRoomManager::SetInst(CreateActor<RandomRoomManager>((int)ORDER::BACKGROUND));
	if (nullptr == Player::MainPlayer)
	{
		Player::MainPlayer = CreateActor<Player>((int)ORDER::PLAYER);
	}

	if (false == GameEngineInput::GetInst()->IsKey("PlayESC"))
	{
		GameEngineInput::GetInst()->CreateKey("PlayESC", VK_ESCAPE);
		GameEngineInput::GetInst()->CreateKey("PlayP", 'P');
		GameEngineInput::GetInst()->CreateKey("PlayCtrl", VK_CONTROL);
	}

	GlobalActor = CreateActor<GameEngineActor>();
	YSortOn(static_cast<int>(ORDER::PLAYER));
}

void PlayLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("PlayESC"))
	{
		GameEngineTime::Pause();
		Player::MainPlayer->GetPlayerUI()->SetPauseUI();

		bool Test = GameEngineTime::IsPause();
		Player::MainPlayer->GetPlayerUI()->GetPausetUI()->TurnOn(Test);
	}
	if (true == GameEngineInput::GetInst()->IsDown("PlayP"))
	{
		IsDebugModeSwitch();
		Player::MainPlayer->GetPlayerUI()->DebugMiniMap();
	}
	if (true == GameEngineInput::GetInst()->IsDown("PlayCtrl"))
	{
		IsDebugModeSwitch2();
		Player::MainPlayer->GetPlayerUI()->DebugMiniMap();
	}

	if (true == IsLerp_)
	{
		LerpTimer_ += GameEngineTime::GetDeltaTime();
		SetCameraPos(float4::Lerp(Start_, Goal_, LerpTimer_ * 4));

		if (LerpTimer_ >= 0.25f)
		{
			IsLerp_ = false;
		}
	}
}

void PlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (CurrentFloor == 1)
	{
		BgmPlayer_ = GameEngineSound::SoundPlayControl("BasementBGM.ogg");
		BossBgmPlayer_ = GameEngineSound::SoundPlayControl("basic_boss_fight.ogg");
	}
	else if (CurrentFloor == 2)
	{
		BgmPlayer_ = GameEngineSound::SoundPlayControl("the caves.ogg");
		BossBgmPlayer_ = GameEngineSound::SoundPlayControl("basic_boss_fight.ogg");
	}
	else if (CurrentFloor == 3)
	{
		BgmPlayer_ = GameEngineSound::SoundPlayControl("the depths.ogg");
		BossBgmPlayer_ = GameEngineSound::SoundPlayControl("mom fight.ogg");
	}
	BgmPlayer_.SetVolume(0.1f * Option_MUSIC);
	BossBgmPlayer_.SetVolume(0.1f * Option_MUSIC);
	BossBgmPlayer_.Pause(true);

	Player::MainPlayer->SetPosition(GameEngineWindow::GetScale().Half());
	RandomRoomManager::GetInst()->ChangeFloor(CurrentFloor);
}

void PlayLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	StopBGM();
}
