#include "LoadingLevel.h"
#include "LoadingPage.h"

LoadingLevel::LoadingLevel() 
{
}

LoadingLevel::~LoadingLevel() 
{
}

void LoadingLevel::Loading()
{
	CreateActor<LoadingPage>("LoadingPage", 0);
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
