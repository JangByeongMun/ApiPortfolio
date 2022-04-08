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
#include <GameEngineBase/GameEngineSound.h>

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
	ResourcesLoad();
	ImageCut();

	CreateLevel<TitleLevel>("Title");
	CreateLevel<MenuLevel>("Menu");
	CreateLevel<LoadingLevel>("Loading");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndingLevel>("Ending");
	ChangeLevel("Ending");

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

void BindingOfIsaac::ResourcesLoad()
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
		ResourcesDirectory.Move("PlayLevel");
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

	// 사운드 로딩
	{
		GameEngineDirectory ResourcesDirectory;
		ResourcesDirectory.MoveParent("Portfolio");
		ResourcesDirectory.Move("Resources");
		ResourcesDirectory.Move("Sound");
		std::vector<GameEngineFile> AllFileVec = ResourcesDirectory.GetAllFile();
		for (int i = 0; i < AllFileVec.size(); i++)
		{
			GameEngineSound::LoadRes(AllFileVec[i].GetFullPath());
		}
	}
}
void BindingOfIsaac::ImageCut()
{
	GameEngineImage* Image = nullptr;

	Image = GameEngineImageManager::GetInst()->Find("None.bmp");
	Image->CutCount(1, 1);

	/////////////////////////////////// Character
	{
		Image = GameEngineImageManager::GetInst()->Find("001_isaac.bmp");
		Image->Cut({ 96, 96 });

		Image = GameEngineImageManager::GetInst()->Find("001_isaac_left.bmp");
		Image->Cut({ 96, 96 });
	}
	
	Image = GameEngineImageManager::GetInst()->Find("tears.bmp");
	Image->Cut({ 96, 96 });

	Image = GameEngineImageManager::GetInst()->Find("LoadingMap.bmp");
	Image->Cut({ 96, 96 });

	Image = GameEngineImageManager::GetInst()->Find("IntroIcon.bmp");
	Image->CutCount(2, 1);

	Image = GameEngineImageManager::GetInst()->Find("MenuIcon.bmp");
	Image->CutCount(2, 1);

	/////////////////////////////////// Play UI
	{
		Image = GameEngineImageManager::GetInst()->Find("ui_hearts_1.bmp");
		Image->CutCount(5, 2);

		Image = GameEngineImageManager::GetInst()->Find("ui_hearts_2.bmp");
		Image->CutCount(5, 2);

		Image = GameEngineImageManager::GetInst()->Find("ui_chargebar_1.bmp");
		Image->CutCount(4, 2);
	}


	/////////////////////////////////// Intro
	{
		Image = GameEngineImageManager::GetInst()->Find("intro01_1.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro02_1.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro03_1.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro04_1.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro05_2.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro05_3.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro05_5.bmp");
		Image->CutCount(1, 2);

		Image = GameEngineImageManager::GetInst()->Find("intro05_6.bmp");
		Image->CutCount(1, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro06_1.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro06_2.bmp");
		Image->CutCount(1, 2);

		Image = GameEngineImageManager::GetInst()->Find("intro06_3.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro07_2.bmp");
		Image->CutCount(1, 2);

		Image = GameEngineImageManager::GetInst()->Find("intro08_1.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro09_01.bmp");
		Image->CutCount(5, 2);

		Image = GameEngineImageManager::GetInst()->Find("intro09_1.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro09_2.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro09_3.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro09_4.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro09_5.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro09_6.bmp");
		Image->CutCount(4, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro09_7.bmp");
		Image->CutCount(4, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro10_1.bmp");
		Image->CutCount(1, 2);

		Image = GameEngineImageManager::GetInst()->Find("intro10_2.bmp");
		Image->CutCount(1, 2);

		Image = GameEngineImageManager::GetInst()->Find("intro12_1.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro12_2.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro13_1.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro14_1.bmp");
		Image->CutCount(2, 3);

		Image = GameEngineImageManager::GetInst()->Find("intro15_1.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro16_2.bmp");
		Image->CutCount(1, 2);

		Image = GameEngineImageManager::GetInst()->Find("intro18_2.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro18_3.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro18_4.bmp");
		Image->CutCount(1, 2);

		Image = GameEngineImageManager::GetInst()->Find("intro18_5.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro18_6.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro18_7.bmp");
		Image->CutCount(1, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro19_2.bmp");
		Image->CutCount(1, 2);

		Image = GameEngineImageManager::GetInst()->Find("intro19_3.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro20_1.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro21_2.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro22_2.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro22_4.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro23_3.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro23_4.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro24_2.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro24_3.bmp");
		Image->CutCount(1, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro25_1.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro25_3.bmp");
		Image->CutCount(1, 1);

		Image = GameEngineImageManager::GetInst()->Find("intro25_4.bmp");
		Image->CutCount(2, 1);
	}

	/////////////////////////////////// Ending
	{
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
