#include "GameEngine.h"
#include "GameEngineLevel.h"
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineSound.h>

std::map<std::string, GameEngineLevel*> GameEngine::AllLevel_;
GameEngineLevel* GameEngine::CurrentLevel_ = nullptr;
GameEngineLevel* GameEngine::NextLevel_ = nullptr;
GameEngineLevel* GameEngine::PrevLevel_ = nullptr;
GameEngine* GameEngine::UserContents_ = nullptr;
GameEngineImage* GameEngine::WindowMainImage_ = nullptr;
GameEngineImage* GameEngine::BackBufferImage_ = nullptr;

GameEngine::GameEngine() 
{
}

GameEngine::~GameEngine() 
{
}

void GameEngine::ChangeLevel(const std::string& _Name)
{
	std::map<std::string, GameEngineLevel*>::iterator FindIter = AllLevel_.find(_Name);
	
	if (AllLevel_.end() == FindIter)
	{
		MsgBoxAssert("Level Find Error");
		return;
	}

	NextLevel_ = FindIter->second;
}

const GameEngineLevel* GameEngine::FindLevel(const std::string& _Name)
{
	std::map<std::string, GameEngineLevel*>::iterator FindIter = AllLevel_.find(_Name);

	if (AllLevel_.end() == FindIter)
	{
		MsgBoxAssert("Level Find Error");
		return nullptr;
	}

	return FindIter->second;
}

void GameEngine::WindowCreate()
{
	GameEngineWindow::GetInst().CreateGameWindow(nullptr, "Binding of Isaac: Rebirth");
	GameEngineWindow::GetInst().ShowGameWindow();
	GameEngineWindow::GetInst().MessageLoop(EngineInit, EngineLoop);
}

void GameEngine::EngineInit()
{
	UserContents_->GameInit();
	WindowMainImage_ = GameEngineImageManager::GetInst()->Create("WindowMain", GameEngineWindow::GetHDC());
	BackBufferImage_ = GameEngineImageManager::GetInst()->Create("BackBuffer", GameEngineWindow::GetScale());
}

void GameEngine::EngineLoop()
{
	GameEngineTime::GetInst()->Update();
	UserContents_->GameLoop();

	if (nullptr != NextLevel_)
	{
		PrevLevel_ = CurrentLevel_;
		if (nullptr != CurrentLevel_)
		{
			CurrentLevel_->ActorLevelChangeEnd(NextLevel_);
			CurrentLevel_->LevelChangeEnd(NextLevel_);

			CurrentLevel_->ObjectLevelMoveCheck(NextLevel_);
		}
		
		GameEngineLevel* PrevLevel = CurrentLevel_;
		CurrentLevel_ = NextLevel_;
		
		if (nullptr != CurrentLevel_)
		{
			CurrentLevel_->LevelChangeStart(PrevLevel);
			CurrentLevel_->ActorLevelChangeStart(PrevLevel);
		}

		NextLevel_ = nullptr;
		GameEngineTime::GetInst()->Reset();

		Rectangle(WindowMainImage_->ImageDC(), 0, 0, WindowMainImage_->GetScale().ix(), WindowMainImage_->GetScale().iy());
		Rectangle(BackBufferImage_->ImageDC(), 0, 0, BackBufferImage_->GetScale().ix(), BackBufferImage_->GetScale().iy());
	}

	if (nullptr == CurrentLevel_)
	{
		MsgBoxAssert("Level is nullptr => GameEngine Loop Error");
	}
	
	GameEngineSound::Update();
	GameEngineInput::GetInst()->Update(GameEngineTime::GetInst()->GetDeltaTime());

	CurrentLevel_->Update();
	CurrentLevel_->ActorUpdate();
	CurrentLevel_->ActorRender();

	CurrentLevel_->CollisionDebugRender();
	WindowMainImage_->BitCopy(BackBufferImage_);

	CurrentLevel_->ActorRelease();
}

void GameEngine::EngineEnd()
{
	UserContents_->GameEnd();

	std::map<std::string, GameEngineLevel*>::iterator StartIter = AllLevel_.begin();
	std::map<std::string, GameEngineLevel*>::iterator EndIter = AllLevel_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr == StartIter->second)
		{
			continue;
		}
		delete StartIter->second;
	}

	GameEngineSound::AllResourcesDestroy();
	GameEngineImageManager::Destroy();
	GameEngineWindow::Destroy();
	GameEngineInput::Destroy();
	GameEngineTime::Destroy();
}

HDC GameEngine::BackBufferDC()
{
	return BackBufferImage_->ImageDC();
}
