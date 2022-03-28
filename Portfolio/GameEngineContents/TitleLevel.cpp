#include <GameEngine/GameEngine.h>
#include "TitleLevel.h"
#include "TitleBackGround.h"
#include "IntroPage.h"
#include "TitleForeGround.h"

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading()
{
	CreateActor<TitleBackGround>(0);
	CreateActor<IntroPage>(1);
	CreateActor<TitleForeGround>(10);
}

void TitleLevel::Update()
{
}

void TitleLevel::LevelChangeStart()
{
}

void TitleLevel::LevelChangeEnd()
{
}

