#include "TestMap.h"
#include <GameEngineBase/GameEngineWindow.h>

TestMap::TestMap() 
{
}

TestMap::~TestMap() 
{
}

void TestMap::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	CreateRenderer("01_basement.bmp");
}

