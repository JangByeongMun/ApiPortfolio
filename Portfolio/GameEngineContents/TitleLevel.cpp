#include <GameEngine/GameEngine.h>
#include "TitleLevel.h"
#include "TitleBackGround.h"
#include "IntroPage.h"
#include "TitleForeGround.h"
#include "Intro01.h"
#include "Intro02.h"
#include "Intro03.h"
#include "Intro04.h"

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading()
{
	CreateActor<TitleBackGround>(0);
	//CreateActor<IntroPage>(1);

	//CreateActor<Intro01>(1);
	//CreateActor<Intro02>(1);
	//CreateActor<Intro03>(1);
	CreateActor<Intro04>(1);

	//CreateActor<TitleForeGround>(10);
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