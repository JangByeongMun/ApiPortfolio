#pragma once
#include <map>
#include <string>
#include <GameEngineBase/GameEngineDebug.h>

class GameEngineLevel;
class GameEngine
{
public:
	// constrcuter destructer
	GameEngine();
	~GameEngine();

	// delete Function
	GameEngine(const GameEngine& _Other) = delete;
	GameEngine(GameEngine&& _Other) noexcept = delete;
	GameEngine& operator=(const GameEngine& _Other) = delete;
	GameEngine& operator=(GameEngine&& _Other) noexcept = delete;

	virtual void GameInit() = 0;
	virtual void GameLoop() = 0;
	virtual void GameEnd() = 0;
	
	template<typename GameType>
	static void Start()
	{
		GameEngineDebug::LeakCheckOn();

		GameType UserGame;
		userContents_ = &UserGame;

		WindowCreate();
		EngineEnd();
	}

	static GameEngine& GlobalEngine()
	{
		if (nullptr == userContents_)
		{
			MsgBoxAssert("Engine is not Start");
		}

		return *userContents_;
	}

	void ChangeLevel(const std::string& _name);

protected:
	template<typename levelType>
	void CreateLevel(const std::string& _name)
	{
		levelType* newLevel = new levelType();
		newLevel->SetName(_name);
		GameEngineLevel* level = newLevel;
		level->Loading();
		allLevel_.insert(std::make_pair(_name, newLevel));
	}

private:
	static std::map<std::string, GameEngineLevel*> allLevel_;
	static GameEngineLevel* currentLevel_;
	static GameEngineLevel* nextLevel_;
	static GameEngine* userContents_;

	static void WindowCreate();
	static void EngineInit();
	static void EngineLoop();
	static void EngineEnd();
};

