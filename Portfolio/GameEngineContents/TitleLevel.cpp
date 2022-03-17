#include <GameEngine/GameEngine.h>
#include "TitleLevel.h"
#include "TitleLogo.h"
#include "TitleBackGround.h"

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading()
{
	CreateActor<TitleBackGround>("TitleBackGround", 0);
	CreateActor<TitleLogo>("TitleLogo", 0);
}

void TitleLevel::Update()
{
	// 임시로 다음씬 넘어가도록
	//GameEngine::GlobalEngine().ChangeLevel("Play");
}

void TitleLevel::LevelChangeStart()
{
}

void TitleLevel::LevelChangeEnd()
{
}

