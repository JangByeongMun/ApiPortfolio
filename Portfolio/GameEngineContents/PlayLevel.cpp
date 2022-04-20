#include "PlayLevel.h"
#include "Player.h"
#include "Projectile.h"
#include "PlayerHP.h"
#include "TestMap.h"
#include "PlayBackGround.h"
#include "SpacebarUI.h"
#include "Accessory.h"
#include "ContentsEnum.h"
#include "RandomRoomManager.h"

#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>

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

void PlayLevel::Loading()
{
	CreateActor<PlayBackGround>((int)ORDER::BACKGROUND);
	//CreateActor<TestMap>((int)ORDER::BACKGROUND);
	CreateActor<Player>((int)ORDER::PLAYER);
	CreateActor<PlayerHP>((int)ORDER::UI);
	CreateActor<SpacebarUI>((int)ORDER::UI);
	
	RandomRoomManager::SetInst(CreateActor<RandomRoomManager>((int)ORDER::BACKGROUND));

	if (false == GameEngineInput::GetInst()->IsKey("PlayESC"))
	{
		GameEngineInput::GetInst()->CreateKey("PlayESC", VK_ESCAPE);
		GameEngineInput::GetInst()->CreateKey("PlayP", 'P');
	}

	GlobalActor = CreateActor<GameEngineActor>();
}

void PlayLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("PlayESC"))
	{
		Accessory* TEST = CreateActor<Accessory>();
		TEST->SetPosition(GameEngineWindow::GetScale().Half());
		TEST->SetType(AccessoryType::brokenmagnet);
	}

	if (true == GameEngineInput::GetInst()->IsDown("PlayP"))
	{
		GameEngine::ChangeDebugRender();
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
	BgmPlayer_ = GameEngineSound::SoundPlayControl("BasementBGM.ogg");
	BgmPlayer_.SetVolume(0.05f);

	Player::MainPlayer->SetPlayerInfo();
	RandomRoomManager::GetInst()->ChangeFloor(1);
}

void PlayLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BgmPlayer_.Stop();
}
