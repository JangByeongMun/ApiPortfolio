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
	ChangeLevel("Menu");

	if (false == GameEngineInput::GetInst()->IsKey("Exit"))
	{
		GameEngineInput::GetInst()->CreateKey("Exit", VK_ESCAPE);
		GameEngineInput::GetInst()->CreateKey("ChangeLevelTitle", 'Z');
		GameEngineInput::GetInst()->CreateKey("ChangeLevelMenu", 'X');
		GameEngineInput::GetInst()->CreateKey("ChangeLevelLoading", 'C');
		GameEngineInput::GetInst()->CreateKey("ChangeLevelPlay", 'V');
		GameEngineInput::GetInst()->CreateKey("ChangeLevelEnding", 'B');
	}
}

void BindingOfIsaac::ImageLoad()
{
	{
		GameEngineDirectory ResourcesDirectory;
		ResourcesDirectory.MoveParent("Portfolio");
		ResourcesDirectory.Move("Resources");
		ResourcesDirectory.Move("Image");
		ResourcesDirectory.Move("UI");
		std::vector<GameEngineFile> AllFileVec = ResourcesDirectory.GetAllFile();
		for (int i = 0; i < AllFileVec.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllFileVec[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory ResourcesDirectory;
		ResourcesDirectory.MoveParent("Portfolio");
		ResourcesDirectory.Move("Resources");
		ResourcesDirectory.Move("Image");
		ResourcesDirectory.Move("UI");
		ResourcesDirectory.Move("TitleLevel");
		std::vector<GameEngineFile> AllFileVec = ResourcesDirectory.GetAllFile();
		for (int i = 0; i < AllFileVec.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllFileVec[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory ResourcesDirectory;
		ResourcesDirectory.MoveParent("Portfolio");
		ResourcesDirectory.Move("Resources");
		ResourcesDirectory.Move("Image");
		ResourcesDirectory.Move("UI");
		ResourcesDirectory.Move("MenuLevel");
		std::vector<GameEngineFile> AllFileVec = ResourcesDirectory.GetAllFile();
		for (int i = 0; i < AllFileVec.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllFileVec[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory ResourcesDirectory;
		ResourcesDirectory.MoveParent("Portfolio");
		ResourcesDirectory.Move("Resources");
		ResourcesDirectory.Move("Image");
		ResourcesDirectory.Move("UI");
		ResourcesDirectory.Move("LoadingLevel");
		std::vector<GameEngineFile> AllFileVec = ResourcesDirectory.GetAllFile();
		for (int i = 0; i < AllFileVec.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllFileVec[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory ResourcesDirectory;
		ResourcesDirectory.MoveParent("Portfolio");
		ResourcesDirectory.Move("Resources");
		ResourcesDirectory.Move("Image");
		ResourcesDirectory.Move("UI");
		ResourcesDirectory.Move("EndingLevel");
		std::vector<GameEngineFile> AllFileVec = ResourcesDirectory.GetAllFile();
		for (int i = 0; i < AllFileVec.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllFileVec[i].GetFullPath());
		}
	}
	
	{
		GameEngineDirectory ResourcesDirectory;
		ResourcesDirectory.MoveParent("Portfolio");
		ResourcesDirectory.Move("Resources");
		ResourcesDirectory.Move("Image");
		ResourcesDirectory.Move("Player");
		std::vector<GameEngineFile> AllFileVec = ResourcesDirectory.GetAllFile();
		for (int i = 0; i < AllFileVec.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllFileVec[i].GetFullPath());
		}
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

	Image = GameEngineImageManager::GetInst()->Find("IntroIcon.bmp");
	Image->CutCount(2, 1);

	Image = GameEngineImageManager::GetInst()->Find("MenuIcon.bmp");
	Image->CutCount(2, 1);


	/////////////////////////////////// Ending Level 
	Image = GameEngineImageManager::GetInst()->Find("epilogue01_2.bmp");
	Image->CutCount(2, 1);

	Image = GameEngineImageManager::GetInst()->Find("epilogue02_1.bmp");
	Image->CutCount(2, 1);

	Image = GameEngineImageManager::GetInst()->Find("epilogue03_2.bmp");
	Image->CutCount(2, 1);

	Image = GameEngineImageManager::GetInst()->Find("epilogue04_1.bmp");
	Image->CutCount(1, 2);

	Image = GameEngineImageManager::GetInst()->Find("epilogue04_2.bmp");
	Image->CutCount(1, 2);

	Image = GameEngineImageManager::GetInst()->Find("epilogue05_1.bmp");
	Image->CutCount(1, 2);

	Image = GameEngineImageManager::GetInst()->Find("epilogue07_2.bmp");
	Image->CutCount(2, 1);

	Image = GameEngineImageManager::GetInst()->Find("epilogue08_2.bmp");
	Image->CutCount(2, 1);

	Image = GameEngineImageManager::GetInst()->Find("epilogue09_2.bmp");
	Image->CutCount(2, 1);

	Image = GameEngineImageManager::GetInst()->Find("epilogue10_1.bmp");
	Image->CutCount(2, 1);

	Image = GameEngineImageManager::GetInst()->Find("epilogue10_2.bmp");
	Image->CutCount(1, 2);

	Image = GameEngineImageManager::GetInst()->Find("epilogue11_2.bmp");
	Image->CutCount(2, 1);

	Image = GameEngineImageManager::GetInst()->Find("epilogue11_3.bmp");
	Image->CutCount(2, 1);

	Image = GameEngineImageManager::GetInst()->Find("epilogue11_4.bmp");
	Image->CutCount(1, 1);

	Image = GameEngineImageManager::GetInst()->Find("epilogue12_1.bmp");
	Image->CutCount(2, 1);

	Image = GameEngineImageManager::GetInst()->Find("epilogue12_2.bmp");
	Image->CutCount(2, 1);

	Image = GameEngineImageManager::GetInst()->Find("epilogue13_1.bmp");
	Image->CutCount(2, 1);

	Image = GameEngineImageManager::GetInst()->Find("epilogue13_2.bmp");
	Image->CutCount(2, 1);

	Image = GameEngineImageManager::GetInst()->Find("epilogue14_1.bmp");
	Image->CutCount(2, 1);

	Image = GameEngineImageManager::GetInst()->Find("epilogue15_1.bmp");
	Image->CutCount(2, 1);

	Image = GameEngineImageManager::GetInst()->Find("epilogue15_2.bmp");
	Image->CutCount(2, 1);

	Image = GameEngineImageManager::GetInst()->Find("epilogue15_3.bmp");
	Image->CutCount(2, 1);
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
