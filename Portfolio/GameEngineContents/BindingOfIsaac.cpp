#include "BindingOfIsaac.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include "LoadingLevel.h"
#include "EndingLevel.h"
#include "MenuLevel.h"
#include <conio.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <string>
#include <time.h>

BindingOfIsaac::BindingOfIsaac() 
{
}

BindingOfIsaac::~BindingOfIsaac() 
{
}

time_t startTime = 0;
void BindingOfIsaac::GameInit()
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 720 });
	ImageLoad();
	
	CreateLevel<TitleLevel>("Title");
	CreateLevel<MenuLevel>("Menu");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndingLevel>("Ending");
	CreateLevel<LoadingLevel>("Loading");
	ChangeLevel("Menu");

	startTime = time(NULL);
}

void BindingOfIsaac::ImageLoad()
{
	std::string home = "D:\\AssortRock\\ApiPortfolio\\Portfolio\\Resources\\Image";
	std::string notebook = "C:\\CppProject\\ApiPortfolio\\Portfolio\\Resources\\Image";

	// 타이틀
	GameEngineImageManager::GetInst()->Load(home + "\\Player\\Player.bmp", "Player.bmp");
	GameEngineImageManager::GetInst()->Load(home + "\\UI\\TitleBG.bmp", "TitleBG.bmp");
	GameEngineImageManager::GetInst()->Load(home + "\\UI\\Intro.bmp", "Intro.bmp");
	GameEngineImageManager::GetInst()->Load(home + "\\UI\\IntroGameBy.bmp", "IntroGameBy.bmp");
	GameEngineImageManager::GetInst()->Load(home + "\\UI\\IntroPage.bmp", "IntroPage.bmp");
	GameEngineImageManager::GetInst()->Load(home + "\\UI\\IntroIcon1.bmp", "IntroIcon1.bmp");
	GameEngineImageManager::GetInst()->Load(home + "\\UI\\IntroIcon2.bmp", "IntroIcon2.bmp");
	GameEngineImageManager::GetInst()->Load(home + "\\UI\\IntroName.bmp", "IntroName.bmp");
	GameEngineImageManager::GetInst()->Load(home + "\\UI\\TitleOverlay.bmp", "TitleOverlay.bmp");
	GameEngineImageManager::GetInst()->Load(home + "\\UI\\Titleshadow.bmp", "Titleshadow.bmp");

	// 메뉴
	GameEngineImageManager::GetInst()->Load(home + "\\UI\\Menu.bmp", "Menu.bmp");
	GameEngineImageManager::GetInst()->Load(home + "\\UI\\MenuName.bmp", "MenuName.bmp");
	GameEngineImageManager::GetInst()->Load(home + "\\UI\\MenuIcon1.bmp", "MenuIcon1.bmp");
	GameEngineImageManager::GetInst()->Load(home + "\\UI\\MenuIcon2.bmp", "MenuIcon2.bmp");
}

void BindingOfIsaac::GameLoop()
{
	//time_t currentTime = time(NULL);
	//if (currentTime - startTime >= 5)
	//{
	//	if (currentTime - startTime >= 10)
	//	{
	//		ChangeLevel("Play");
	//	}
	//	else
	//	{
	//		ChangeLevel("Menu");
	//	}
	//}
}

void BindingOfIsaac::GameEnd()
{
	int a = 0;
}
