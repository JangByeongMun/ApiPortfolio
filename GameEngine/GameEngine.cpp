#include "GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngineLevel.h"

std::map<std::string, GameEngineLevel*> GameEngine::allLevel_;
GameEngineLevel* GameEngine::currentLevel_ = nullptr;
GameEngineLevel* GameEngine::nextLevel_ = nullptr;
GameEngine* GameEngine::userContents_ = nullptr;

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
	GameEngineWindow::GetInst().CreateGameWindow(nullptr, "GameWindow");
	GameEngineWindow::GetInst().ShowGameWindow();
	GameEngineWindow::GetInst().MessageLoop(EngineInit, EngineLoop);
}

void GameEngine::EngineInit()
{
	userContents_->GameInit();
}

void GameEngine::EngineLoop()
{
	userContents_->GameLoop();

	if (nullptr != nextLevel_)
	{
		if (nullptr != currentLevel_)
		{
			currentLevel_->SceneChangeEnd();
		}
		
		currentLevel_ = nextLevel_;
		
		if (nullptr != currentLevel_)
		{
			currentLevel_->SceneChangeStart();
		}

		nextLevel_ = nullptr;
	}

	if (nullptr == currentLevel_)
	{
		MsgBoxAssert("Level is nullptr => GameEngine Loop Error");
	}

	currentLevel_->Update();
	currentLevel_->ActorUpdate();
	currentLevel_->ActorRender();
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

	GameEngineWindow::Destroy();
}