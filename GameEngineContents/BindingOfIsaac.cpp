#include "BindingOfIsaac.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include "LoadingLevel.h"
#include "EndingLevel.h"
#include <conio.h>
#include <GameEngineBase/GameEngineWindow.h>

BindingOfIsaac::BindingOfIsaac() 
{
}

BindingOfIsaac::~BindingOfIsaac() 
{
}

void BindingOfIsaac::GameInit()
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 720 });

	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndingLevel>("Ending");
	CreateLevel<LoadingLevel>("Loading");
	ChangeLevel("Title");
}

int testI = 0;
void BindingOfIsaac::GameLoop()
{
	++testI;
	if (testI >= 10)
	{
		ChangeLevel("Play");
	}
	int a = 0;
}

void BindingOfIsaac::GameEnd()
{
	int a = 0;
}
