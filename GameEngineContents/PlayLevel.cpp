#include "PlayLevel.h"
#include "Player.h"

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

void PlayLevel::SceneChangeStart()
{
	int a = 0;
}

void PlayLevel::SceneChangeEnd()
{
	int a = 0;
}