#include "LoadingLevel.h"
#include "LoadingPage.h"
#include "LoadingCharacter.h"
#include "LoadingMap.h"


LoadingLevel::LoadingLevel() 
{
}

LoadingLevel::~LoadingLevel() 
{
}

void LoadingLevel::Loading()
{
	CreateActor<LoadingPage>(0);
	CreateActor<LoadingCharacter>(1);
	CreateActor<LoadingMap>(2);
}

void LoadingLevel::Update()
{
}

void LoadingLevel::LevelChangeStart()
{
}

void LoadingLevel::LevelChangeEnd()
{
}
