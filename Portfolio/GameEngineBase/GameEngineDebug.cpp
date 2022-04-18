#include "GameEngineDebug.h"

void GameEngineDebug::LeakCheckOn()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(185);
}

GameEngineDebug::GameEngineDebug()
{
}

GameEngineDebug::~GameEngineDebug() 
{
}

