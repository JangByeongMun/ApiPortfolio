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

void BindingOfIsaac::GameLoop()
{

}

void BindingOfIsaac::GameEnd()
{
	int a = 0;
}
