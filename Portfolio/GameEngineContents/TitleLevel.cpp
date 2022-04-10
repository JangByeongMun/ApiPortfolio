#include <GameEngine/GameEngine.h>
#include "TitleLevel.h"
#include "TitleBackGround.h"
#include "IntroPage.h"
#include "TitleForeGround.h"
#include "Intro01.h"
#include "Intro02.h"
#include "Intro03.h"
#include "Intro04.h"
#include "Intro05.h"
#include "Intro06.h"
#include "Intro07.h"
#include "Intro08.h"
#include "Intro09.h"
#include "Intro10.h"
#include "Intro11.h"
#include "Intro12.h"
#include "Intro13.h"
#include "Intro14.h"
#include "Intro15.h"
#include "Intro16.h"
#include "Intro17.h"
#include "Intro18.h"
#include "Intro19.h"
#include "Intro20.h"
#include "Intro21.h"
#include "Intro22.h"
#include "Intro23.h"
#include "Intro24.h"
#include "Intro25.h"
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
}