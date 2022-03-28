#include "GameEngine.h"
#include "GameEngineLevel.h"
#include "GameEngineImage.h"
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

std::map<std::string, GameEngineLevel*> GameEngine::allLevel_;
GameEngineLevel* GameEngine::currentLevel_ = nullptr;
GameEngineLevel* GameEngine::nextLevel_ = nullptr;
GameEngine* GameEngine::userContents_ = nullptr;
GameEngineImage* GameEngine::windowMainImage_ = nullptr;
GameEngineImage* GameEngine::backBufferImage_ = nullptr;

GameEngine::GameEngine() 
{
}

GameEngine::~GameEngine() 
{
}

void GameEngine::ChangeLevel(const std::string& _name)
{
	std::map<std::string, GameEngineLevel*>::iterator findIter = allLevel_.find(_name);
	
	if (allLevel_.end() == findIter)
	{
		MsgBoxAssert("Level Find Error");
		return;
	}

	nextLevel_ = findIter->second;
}

void GameEngine::WindowCreate()
{
	GameEngineWindow::GetInst().CreateGameWindow(nullptr, "Binding of Isaac: Rebirth");
	GameEngineWindow::GetInst().ShowGameWindow();
	GameEngineWindow::GetInst().MessageLoop(EngineInit, EngineLoop);
}

void GameEngine::EngineInit()
{
	userContents_->GameInit();
	windowMainImage_ = GameEngineImageManager::GetInst()->Create("WindowMain", GameEngineWindow::GetHDC());
	backBufferImage_ = GameEngineImageManager::GetInst()->Create("BackBuffer", GameEngineWindow::GetScale());
}

void GameEngine::EngineLoop()
{
	GameEngineTime::GetInst()->Update();
	userContents_->GameLoop();

	if (nullptr != nextLevel_)
	{
		if (nullptr != currentLevel_)
		{
			currentLevel_->LevelChangeEnd();
		}
		
		currentLevel_ = nextLevel_;
		
		if (nullptr != currentLevel_)
		{
			currentLevel_->LevelChangeStart();
		}

		nextLevel_ = nullptr;
		GameEngineTime::GetInst()->Reset();

		Rectangle(windowMainImage_->ImageDC(), 0, 0, windowMainImage_->GetScale().ix(), windowMainImage_->GetScale().iy());
		Rectangle(backBufferImage_->ImageDC(), 0, 0, backBufferImage_->GetScale().ix(), backBufferImage_->GetScale().iy());
	}

	if (nullptr == currentLevel_)
	{
		MsgBoxAssert("Level is nullptr => GameEngine Loop Error");
	}
	
	GameEngineInput::GetInst()->Update();

	currentLevel_->Update();
	currentLevel_->ActorUpdate();
	currentLevel_->ActorRender();
	windowMainImage_->BitCopy(backBufferImage_);

	currentLevel_->ActorRelease();
}

void GameEngine::EngineEnd()
{
	userContents_->GameEnd();

	std::map<std::string, GameEngineLevel*>::iterator StartIter = allLevel_.begin();
	std::map<std::string, GameEngineLevel*>::iterator EndIter = allLevel_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr == StartIter->second)
		{
			continue;
		}
		delete StartIter->second;
	}

	GameEngineImageManager::Destroy();
	GameEngineWindow::Destroy();
	GameEngineInput::Destroy();
	GameEngineTime::Destroy();
}

HDC GameEngine::WindowMainDC()
{
	return windowMainImage_->ImageDC();
}

HDC GameEngine::BackBufferDC()
{
	return backBufferImage_->ImageDC();
}
