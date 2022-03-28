#include "BindingOfIsaac.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include "LoadingLevel.h"
#include "EndingLevel.h"
#include "MenuLevel.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineInput.h>

#include <conio.h>
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
	ImageCut();

	CreateLevel<TitleLevel>("Title");
	CreateLevel<MenuLevel>("Menu");
	CreateLevel<LoadingLevel>("Loading");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndingLevel>("Ending");
	ChangeLevel("Play");

	if (false == GameEngineInput::GetInst()->IsKey("Exit"))
	{
		GameEngineInput::GetInst()->CreateKey("Exit", VK_ESCAPE);
		GameEngineInput::GetInst()->CreateKey("ChangeLevelTitle", 'Z');
		GameEngineInput::GetInst()->CreateKey("ChangeLevelMenu", 'X');
		GameEngineInput::GetInst()->CreateKey("ChangeLevelLoading", 'C');
		GameEngineInput::GetInst()->CreateKey("ChangeLevelPlay", 'V');
		GameEngineInput::GetInst()->CreateKey("ChangeLevelEnding", 'B');
	}
	
	startTime = time(NULL);
}

void BindingOfIsaac::ImageLoad()
{
	GameEngineDirectory resourcesDirectory;
	resourcesDirectory.MoveParent("Portfolio");
	resourcesDirectory.Move("Resources");
	resourcesDirectory.Move("Image");
	resourcesDirectory.Move("UI");
	std::vector<GameEngineFile> allFileVec = resourcesDirectory.GetAllFile();
	for (int i = 0; i < allFileVec.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(allFileVec[i].GetFullPath());
	}

	resourcesDirectory.Move("LoadingLevel");
	allFileVec = resourcesDirectory.GetAllFile();
	for (int i = 0; i < allFileVec.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(allFileVec[i].GetFullPath());
	}

	resourcesDirectory.MoveParent("Image");
	resourcesDirectory.Move("Player");
	allFileVec = resourcesDirectory.GetAllFile();
	for (int i = 0; i < allFileVec.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(allFileVec[i].GetFullPath());
	}
}

void BindingOfIsaac::ImageCut()
{
	GameEngineImage* Image = nullptr;
	Image = GameEngineImageManager::GetInst()->Find("character_001_isaac.bmp");
	Image->Cut({ 96, 100 });
	
	Image = GameEngineImageManager::GetInst()->Find("tears.bmp");
	Image->Cut({ 96, 96 });

	Image = GameEngineImageManager::GetInst()->Find("LoadingMap.bmp");
	Image->Cut({ 96, 96 });

}

void BindingOfIsaac::GameLoop()
{
	if (true == GameEngineInput::GetInst()->IsDown("ChangeLevelTitle"))
	{
		ChangeLevel("Title");
	}
	if (true == GameEngineInput::GetInst()->IsDown("ChangeLevelMenu"))
	{
		ChangeLevel("Menu");
	}
	if (true == GameEngineInput::GetInst()->IsDown("ChangeLevelLoading"))
	{
		ChangeLevel("Loading");
	}
	if (true == GameEngineInput::GetInst()->IsDown("ChangeLevelPlay"))
	{
		ChangeLevel("Play");
	}
	if (true == GameEngineInput::GetInst()->IsDown("ChangeLevelEnding"))
	{
		ChangeLevel("Ending");
	}
}

void BindingOfIsaac::GameEnd()
{
}
