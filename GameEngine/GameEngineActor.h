#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>

// Ό³Έν :
class GameEngineLevel;
class GameEngineActor : public GameEngineNameObject
{
	friend GameEngineLevel;
public:
	// constrcuter destructer
	GameEngineActor();
	virtual ~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

protected:
	virtual void Start()  {}
	virtual void Update() {}
	virtual void Render() {}

private:
	GameEngineLevel* level_;
	float4 position_;
	float4 scale_;

	inline void SetLevel(GameEngineLevel* _level)
	{
		level_ = _level;
	}
};

