#pragma once
#include <map>
#include <string>
#include <GameEngineBase/GameEngineDebug.h>

class GameEngineLevel;
class GameEngineImage;
class GameEngine
{
public:
	// constrcuter destructer
	GameEngine();
	virtual ~GameEngine();

	// delete Function
	GameEngine(const GameEngine& _Other) = delete;
	GameEngine(GameEngine&& _Other) noexcept = delete;
	GameEngine& operator=(const GameEngine& _Other) = delete;
	GameEngine& operator=(GameEngine&& _Other) noexcept = delete;

	inline static GameEngineImage* BackBufferImage()
	{
		return BackBufferImage_;
	}
	static HDC BackBufferDC();

	virtual void GameInit() = 0;
	virtual void GameLoop() = 0;
	virtual void GameEnd() = 0;
	
	template<typename GameType>
	static void Start()
	{
		GameEngineDebug::LeakCheckOn();

		GameType UserGame;
		UserContents_ = &UserGame;

		WindowCreate();
		EngineEnd();
	}

	inline static GameEngine& GetInst()
	{
		if (nullptr == UserContents_)
		{
			MsgBoxAssert("Engine is not Start");
		}

		return *UserContents_;
	}

	void ChangeLevel(const std::string& _Name);
	const GameEngineLevel* FindLevel(const std::string& _Name);

	static inline GameEngineLevel* GetPrevLevel()
	{
		return PrevLevel_;
	}

protected:
	template<typename levelType>
	void CreateLevel(const std::string& _Name)
	{
		levelType* newLevel = new levelType();
		newLevel->SetName(_Name);
		GameEngineLevel* level = newLevel;
		level->Loading();
		AllLevel_.insert(std::make_pair(_Name, newLevel));
	}

private:
	static std::map<std::string, GameEngineLevel*> AllLevel_;
	static GameEngineLevel* CurrentLevel_;
	static GameEngineLevel* NextLevel_;
	static GameEngineLevel* PrevLevel_;
	static GameEngine* UserContents_;
	static GameEngineImage* WindowMainImage_;
	static GameEngineImage* BackBufferImage_;

	static void WindowCreate();
	static void EngineInit();
	static void EngineLoop();
	static void EngineEnd();
};

