#include "PlayLevel.h"
#include "Player.h"
#include "Projectile.h"

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Loading()
{
	CreateActor<Player>("Player", 0);
}

void PlayLevel::Update()
{
}

void PlayLevel::LevelChangeStart()
{
	int a = 0;
}

void PlayLevel::LevelChangeEnd()
{
	int a = 0;
}
