#include "BindingOfIsaac.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include "LoadingLevel.h"
#include "EndingLevel.h"
#include "MenuLevel.h"
#include "MenuLoadingLevel.h"
#include "RandomRoomManager.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/GameEngineRandom.h>

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
	GameEngineRandom::MainRandom = new GameEngineRandom();
	ResourcesLoad();
	ImageCut();

	CreateLevel<TitleLevel>("Title");
	CreateLevel<MenuLevel>("Menu");
	CreateLevel<MenuLoadingLevel>("MenuLoading");
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
		GameEngineInput::GetInst()->CreateKey("ChangeLevelMenuLoading", 'N');
	}
}

void BindingOfIsaac::ResourcesLoad()
{
	{
		GameEngineDirectory ResourcesDirectory;
		ResourcesDirectory.MoveParent("Portfolio");
		ResourcesDirectory.Move("Resources");
		ResourcesDirectory.Move("Image");
		ResourcesDirectory.Move("Map");
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
		ResourcesDirectory.Move("Monster");
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
		ResourcesDirectory.Move("Effect");
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
		ResourcesDirectory.Move("MenuLoadingLevel");
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
		ResourcesDirectory.Move("PlayLevel");
		ResourcesDirectory.Move("Accessory");
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
		ResourcesDirectory.Move("PickupItem");
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

		Image = GameEngineImageManager::GetInst()->Find("006_bluebaby.bmp");
		Image->Cut({ 96, 96 });

		Image = GameEngineImageManager::GetInst()->Find("006_bluebaby_left.bmp");
		Image->Cut({ 96, 96 });

		Image = GameEngineImageManager::GetInst()->Find("character_002_maggiesbeautifulgoldenlocks.bmp");
		Image->CutCount(8, 1);

		Image = GameEngineImageManager::GetInst()->Find("character_003_cainseyepatch.bmp");
		Image->CutCount(8, 1);

		Image = GameEngineImageManager::GetInst()->Find("character_004_judasfez.bmp");
		Image->CutCount(8, 1);

		Image = GameEngineImageManager::GetInst()->Find("001_isaac_Anim.bmp");
		Image->CutCount(4, 3);

		Image = GameEngineImageManager::GetInst()->Find("002_magdalene_Anim.bmp");
		Image->CutCount(4, 3);

		Image = GameEngineImageManager::GetInst()->Find("003_cain_Anim.bmp");
		Image->CutCount(4, 3);

		Image = GameEngineImageManager::GetInst()->Find("004_judas_Anim.bmp");
		Image->CutCount(4, 3);

		Image = GameEngineImageManager::GetInst()->Find("006_bluebaby_Anim.bmp");
		Image->CutCount(4, 3);
	}

	/////////////////////////////////// Menu
	{
		Image = GameEngineImageManager::GetInst()->Find("charactermenu_Characters.bmp");
		Image->CutCount(4, 2);

		Image = GameEngineImageManager::GetInst()->Find("tears.bmp");
		Image->Cut({ 96, 96 });

		Image = GameEngineImageManager::GetInst()->Find("LoadingMap.bmp");
		Image->Cut({ 96, 96 });

		Image = GameEngineImageManager::GetInst()->Find("IntroIcon.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("MenuIcon.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("optionsmenu_VolumeLeft.bmp");
		Image->CutCount(5, 3);

		Image = GameEngineImageManager::GetInst()->Find("optionsmenu_VolumeRight.bmp");
		Image->CutCount(5, 3);

		Image = GameEngineImageManager::GetInst()->Find("01_basement_Save.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("02_momkill_Save.bmp");
		Image->CutCount(2, 1);
	}

	/////////////////////////////////// Effect
	{
		Image = GameEngineImageManager::GetInst()->Find("effect_017_bombradius.bmp");
		Image->CutCount(3, 3);

		Image = GameEngineImageManager::GetInst()->Find("effect_015_tearpoofa.bmp");
		Image->CutCount(4, 4);
	}

	/////////////////////////////////// Monster
	{
		Image = GameEngineImageManager::GetInst()->Find("monster_001_pooter_Left.bmp");
		Image->CutCount(4, 4);
		Image = GameEngineImageManager::GetInst()->Find("monster_001_pooter_Right.bmp");
		Image->CutCount(4, 4);
	}

	/////////////////////////////////// Map
	{
		Image = GameEngineImageManager::GetInst()->Find("rocks_basement.bmp");
		Image->CutCount(4, 8);

		Image = GameEngineImageManager::GetInst()->Find("door_01_normaldoor_Up.bmp");
		Image->CutCount(2, 3);
		Image = GameEngineImageManager::GetInst()->Find("door_01_normaldoor_Down.bmp");
		Image->CutCount(2, 3);
		Image = GameEngineImageManager::GetInst()->Find("door_01_normaldoor_Left.bmp");
		Image->CutCount(2, 3);
		Image = GameEngineImageManager::GetInst()->Find("door_01_normaldoor_Right.bmp");
		Image->CutCount(2, 3);

		Image = GameEngineImageManager::GetInst()->Find("door_02_treasureroomdoor_Up.bmp");
		Image->CutCount(2, 3);
		Image = GameEngineImageManager::GetInst()->Find("door_02_treasureroomdoor_Down.bmp");
		Image->CutCount(2, 3);
		Image = GameEngineImageManager::GetInst()->Find("door_02_treasureroomdoor_Left.bmp");
		Image->CutCount(2, 3);
		Image = GameEngineImageManager::GetInst()->Find("door_02_treasureroomdoor_Right.bmp");
		Image->CutCount(2, 3);
	
		Image = GameEngineImageManager::GetInst()->Find("door_10_bossroomdoor_Up.bmp");
		Image->CutCount(2, 3);
		Image = GameEngineImageManager::GetInst()->Find("door_10_bossroomdoor_Down.bmp");
		Image->CutCount(2, 3);
		Image = GameEngineImageManager::GetInst()->Find("door_10_bossroomdoor_Left.bmp");
		Image->CutCount(2, 3);
		Image = GameEngineImageManager::GetInst()->Find("door_10_bossroomdoor_Right.bmp");
		Image->CutCount(2, 3);
	}

	/////////////////////////////////// Play UI
	{
		Image = GameEngineImageManager::GetInst()->Find("ui_hearts_1.bmp");
		Image->CutCount(5, 2);

		Image = GameEngineImageManager::GetInst()->Find("ui_chargebar_1.bmp");
		Image->CutCount(4, 2);

		Image = GameEngineImageManager::GetInst()->Find("hudpickups.bmp");
		Image->CutCount(3, 2);

		Image = GameEngineImageManager::GetInst()->Find("whitecounter.bmp");
		Image->CutCount(3, 4);

		Image = GameEngineImageManager::GetInst()->Find("minimap1.bmp");
		Image->CutCount(5, 8);
	}

	/////////////////////////////////// Play Item
	{
		Image = GameEngineImageManager::GetInst()->Find("pickup_001_heart.bmp");
		Image->CutCount(3, 3);
		
		Image = GameEngineImageManager::GetInst()->Find("pickup_002_coin_1.bmp");
		Image->CutCount(6, 1);

		Image = GameEngineImageManager::GetInst()->Find("pickup_002_coin_1_Shadow.bmp");
		Image->CutCount(6, 1);

		Image = GameEngineImageManager::GetInst()->Find("pickup_002_coin_2.bmp");
		Image->CutCount(8, 1);

		Image = GameEngineImageManager::GetInst()->Find("pickup_002_coin_2_Shadow.bmp");
		Image->CutCount(8, 1);

		Image = GameEngineImageManager::GetInst()->Find("pickup_002_coin_3.bmp");
		Image->CutCount(9, 1);

		Image = GameEngineImageManager::GetInst()->Find("pickup_002_coinblack_1.bmp");
		Image->CutCount(6, 1);

		Image = GameEngineImageManager::GetInst()->Find("pickup_002_coinblack_1_Shadow.bmp");
		Image->CutCount(6, 1);

		Image = GameEngineImageManager::GetInst()->Find("pickup_002_coinblack_2.bmp");
		Image->CutCount(8, 1);

		Image = GameEngineImageManager::GetInst()->Find("pickup_002_coinblack_2_Shadow.bmp");
		Image->CutCount(8, 1);

		Image = GameEngineImageManager::GetInst()->Find("pickup_002_coinblack_3.bmp");
		Image->CutCount(7, 1);

		Image = GameEngineImageManager::GetInst()->Find("pickup_002_coinsilver_1.bmp");
		Image->CutCount(6, 1);

		Image = GameEngineImageManager::GetInst()->Find("pickup_002_coinsilver_1_Shadow.bmp");
		Image->CutCount(6, 1);

		Image = GameEngineImageManager::GetInst()->Find("pickup_002_coinsilver_2.bmp");
		Image->CutCount(8, 1);

		Image = GameEngineImageManager::GetInst()->Find("pickup_002_coinsilver_2_Shadow.bmp");
		Image->CutCount(8, 1);

		Image = GameEngineImageManager::GetInst()->Find("pickup_002_coinsilver_3.bmp");
		Image->CutCount(7, 1);

		Image = GameEngineImageManager::GetInst()->Find("pickup_003_key.bmp");
		Image->CutCount(4, 1);

		Image = GameEngineImageManager::GetInst()->Find("pickup_016_bomb_One.bmp");
		Image->CutCount(3, 1);
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

		Image = GameEngineImageManager::GetInst()->Find("intro09_8.bmp");
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
	if (true == GameEngineInput::GetInst()->IsDown("ChangeLevelMenuLoading"))
	{
		ChangeLevel("MenuLoading");
	}
}
void BindingOfIsaac::GameEnd()
{
	if (nullptr != GameEngineRandom::MainRandom)
	{
		delete GameEngineRandom::MainRandom;
		GameEngineRandom::MainRandom = nullptr;
	}
}
