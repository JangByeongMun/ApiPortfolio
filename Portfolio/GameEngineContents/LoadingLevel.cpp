#include "LoadingLevel.h"
#include "LoadingPage.h"
#include "LoadingCharacter.h"

LoadingLevel::LoadingLevel() 
{
}

LoadingLevel::~LoadingLevel() 
{
}

void LoadingLevel::Loading()
{
	CreateActor<LoadingPage>("LoadingPage", 0);
	CreateActor<LoadingCharacter>("LoadingCharacter", 0);
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
