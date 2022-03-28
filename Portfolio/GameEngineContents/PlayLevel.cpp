#include "PlayLevel.h"
#include "Player.h"
#include "Projectile.h"
#include "HpUI.h"

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
}

void PlayLevel::Update()
{
}

void PlayLevel::LevelChangeStart()
{
	CreateActor<Player>((int)ORDER::PLAYER);
	CreateActor<HpUI>((int)ORDER::UI);
}

void PlayLevel::LevelChangeEnd()
{
}
