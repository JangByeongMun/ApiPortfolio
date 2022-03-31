#include "MenuLevel.h"
#include "MenuUI.h"
#include "MenuStart.h"
#include "MenuFileSelect.h"

#include <GameEngineBase/GameEngineInput.h>

MenuLevel::MenuLevel()
	: CurrentScreen_(0)
{
}

MenuLevel::~MenuLevel() 
{
}

void MenuLevel::Loading()
{
	CreateActor<MenuStart>(0);
	CreateActor<MenuFileSelect>(0);

	if (false == GameEngineInput::GetInst()->IsKey("MenuOk"))
	{
		GameEngineInput::GetInst()->CreateKey("MenuOk", VK_SPACE);
	}
}

void MenuLevel::Update()
{
	if (0 == CurrentScreen_)
	{
		if (true == GameEngineInput::GetInst()->IsDown("MenuOk"))
		{
			SetCameraPos({0, 720});
			CurrentScreen_ = 1;
		}
	}
}

void MenuLevel::LevelChangeStart()
{
}

void MenuLevel::LevelChangeEnd()
{
}
