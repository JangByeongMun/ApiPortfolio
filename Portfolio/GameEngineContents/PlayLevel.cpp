#include "PlayLevel.h"
#include "Player.h"
#include "Projectile.h"
#include "HpUI.h"
#include "TestMap.h"
#include "PlayBackGround.h"

enum class ORDER
{
	BACKGROUND,
	PLAYER,
	MONSTER,
	UI
};

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Loading()
{
	CreateActor<PlayBackGround>((int)ORDER::BACKGROUND);
	GameEngineActor* Actor = CreateActor<TestMap>((int)ORDER::BACKGROUND);
	CreateActor<Player>((int)ORDER::PLAYER);
	CreateActor<HpUI>((int)ORDER::UI);

	Actor->CreateCollision("Wall", {100, 100}, { 300, 200 });
}

void PlayLevel::Update()
{
}

void PlayLevel::LevelChangeStart()
{
}

void PlayLevel::LevelChangeEnd()
{
}
