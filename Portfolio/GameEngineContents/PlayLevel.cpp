#include "PlayLevel.h"
#include "Player.h"
#include "Projectile.h"
#include "HpUI.h"
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
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Loading()
{
	CreateActor<PlayBackGround>((int)ORDER::BACKGROUND);
	CreateActor<TestMap>((int)ORDER::BACKGROUND);
	CreateActor<Player>((int)ORDER::PLAYER);
	CreateActor<HPUI>((int)ORDER::UI);
	CreateActor<SpacebarUI>((int)ORDER::UI);
	
	RandomRoomManager::SetInst(CreateActor<RandomRoomManager>((int)ORDER::BACKGROUND));

	if (false == GameEngineInput::GetInst()->IsKey("PlayESC"))
	{
		GameEngineInput::GetInst()->CreateKey("PlayESC", VK_ESCAPE);
		GameEngineInput::GetInst()->CreateKey("PlayP", 'P');
	}
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
}

void PlayLevel::LevelChangeStart()
{
	BgmPlayer_ = GameEngineSound::SoundPlayControl("BasementBGM.ogg");
	BgmPlayer_.SetVolume(0.05f);

	Player::MainPlayer->SetPlayerInfo();
	RandomRoomManager::GetInst()->ChangeFloor(1);
}

void PlayLevel::LevelChangeEnd()
{
	BgmPlayer_.Stop();
}
