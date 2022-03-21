#include "BindingOfIsaac.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include "LoadingLevel.h"
#include "EndingLevel.h"
#include <conio.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <string>

std::string home = "D:\\AssortRock\\ApiPortfolio\\Portfolio\\Resources\\Image\\Player";
std::string notebook = "C:\\CppProject\\ApiPortfolio\\Portfolio\\Resources\\Image\\Player\\Player.bmp";

BindingOfIsaac::BindingOfIsaac() 
{
}

BindingOfIsaac::~BindingOfIsaac() 
{
}

void BindingOfIsaac::GameInit()
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 720 });
	GameEngineImageManager::GetInst()->Load(home + "\\Player.bmp", "Player.bmp");

	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndingLevel>("Ending");
	CreateLevel<LoadingLevel>("Loading");
	ChangeLevel("Play");
}

void BindingOfIsaac::GameLoop()
{

}

void BindingOfIsaac::GameEnd()
{
	int a = 0;
}
