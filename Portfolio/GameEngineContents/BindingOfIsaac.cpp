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
	
	CreateLevel<TitleLevel>("Title");
	CreateLevel<MenuLevel>("Menu");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndingLevel>("Ending");
	CreateLevel<LoadingLevel>("Loading");
	ChangeLevel("Play");

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

	resourcesDirectory.MoveParent("Image");
	resourcesDirectory.Move("Player");
	allFileVec = resourcesDirectory.GetAllFile();
	for (int i = 0; i < allFileVec.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(allFileVec[i].GetFullPath());
	}
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
