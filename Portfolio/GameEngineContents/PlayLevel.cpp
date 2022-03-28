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
	CreateActor<Player>((int)ORDER::PLAYER);
	CreateActor<HpUI>((int)ORDER::UI);
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
