#include <GameEngine/GameEngine.h>
#include "TitleLevel.h"
#include "TitleBackGround.h"
#include "IntroPage.h"
#include "TitleForeGround.h"
#include "IntroManager.h"

TitleLevel::TitleLevel() 
	: IntroPtr_()
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading()
{
	CreateActor<TitleBackGround>(0);
	CreateActor<IntroPage>(1);
	IntroPtr_ = CreateActor<IntroManager>(1);

	//CreateActor<TitleForeGround>(10);
}

void TitleLevel::Update()
{
}

void TitleLevel::LevelChangeStart()
{
	IntroPtr_->Play();
}

void TitleLevel::LevelChangeEnd()
{
	IntroPtr_->Stop();
}