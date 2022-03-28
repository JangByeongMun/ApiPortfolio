#include "EndingLevel.h"
#include "EndingBackGround.h"

EndingLevel::EndingLevel() 
{
}

EndingLevel::~EndingLevel() 
{
}

void EndingLevel::Loading()
{
	CreateActor<EndingBackGround>(0);
}

void EndingLevel::Update()
{
}

void EndingLevel::LevelChangeStart()
{
}

void EndingLevel::LevelChangeEnd()
{
}

