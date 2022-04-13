#include "PlayLevel.h"
#include "Player.h"
#include "Projectile.h"
#include "HpUI.h"
#include "TestMap.h"
#include "PlayBackGround.h"
#include "SpacebarUI.h"

#include <GameEngineBase/GameEngineInput.h>

enum class ORDER
{
	BACKGROUND,
	PLAYER,
	MONSTER,
	UI
};

PlayLevel::PlayLevel() 
	: PlayerInst_(nullptr)
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Loading()
{
	CreateActor<PlayBackGround>((int)ORDER::BACKGROUND);
	GameEngineActor* Actor = CreateActor<TestMap>((int)ORDER::BACKGROUND);
	PlayerInst_ = CreateActor<Player>((int)ORDER::PLAYER);
	CreateActor<HpUI>((int)ORDER::UI);
	CreateActor<SpacebarUI>((int)ORDER::UI);

	Actor->CreateCollision("Wall", {100, 100}, { 300, 200 });

	if (false == GameEngineInput::GetInst()->IsKey("PlayESC"))
	{
		GameEngineInput::GetInst()->CreateKey("PlayESC", VK_ESCAPE);
	}
}

void PlayLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("PlayESC"))
	{

	}
}

void PlayLevel::LevelChangeStart()
{
	PlayerInst_->GetPlayerInfo();
}

void PlayLevel::LevelChangeEnd()
{
}
