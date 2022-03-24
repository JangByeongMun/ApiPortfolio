#include "BindingOfIsaac.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include "LoadingLevel.h"
#include "EndingLevel.h"
#include "MenuLevel.h"
#include "CharacterTypeManager.h"

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
	
	CreateLevel<TitleLevel>("Title");
	CreateLevel<MenuLevel>("Menu");
	CreateLevel<LoadingLevel>("Loading");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndingLevel>("Ending");
	ChangeLevel("Play");

	if (false == GameEngineInput::GetInst()->IsKey("Exit"))
	{
		GameEngineInput::GetInst()->CreateKey("Exit", VK_ESCAPE);
		GameEngineInput::GetInst()->CreateKey("LevelChangeTitle", 'Z');
		GameEngineInput::GetInst()->CreateKey("LevelChangeMenu", 'X');
		GameEngineInput::GetInst()->CreateKey("LevelChangeLoading", 'C');
		GameEngineInput::GetInst()->CreateKey("LevelChangePlay", 'V');
		GameEngineInput::GetInst()->CreateKey("LevelChangeEnding", 'B');
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
	if (true == GameEngineInput::GetInst()->IsDown("LevelChangeTitle"))
	{
		ChangeLevel("Title");
	}
	if (true == GameEngineInput::GetInst()->IsDown("LevelChangeMenu"))
	{
		ChangeLevel("Menu");
	}
	if (true == GameEngineInput::GetInst()->IsDown("LevelChangeLoading"))
	{
		ChangeLevel("Loading");
	}
	if (true == GameEngineInput::GetInst()->IsDown("LevelChangePlay"))
	{
		ChangeLevel("Play");
	}
	if (true == GameEngineInput::GetInst()->IsDown("LevelChangeEnding"))
	{
		ChangeLevel("Ending");
	}

}

void BindingOfIsaac::GameEnd()
{
	int a = 0;

	CharacterTypeManager::Destroy();
}
