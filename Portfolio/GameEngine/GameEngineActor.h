#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include <list>
#include "GameEngineEnum.h"

// 설명 :
class GameEngineRenderer;
class GameEngineLevel;
class GameEngineActor : public GameEngineNameObject
{
	friend GameEngineLevel;
	// 베이스 기능
public:
	// constrcuter destructer
	GameEngineActor();
	virtual ~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	inline void SetPosition(float4 _value)
	{
		position_ = _value;
	}
	inline float4 GetPosition()
	{
		return position_;
	}
	inline void SetScale(float4 _value)
	{
		scale_ = _value;
	}
	inline float4 GetScale()
	{
		return scale_;
	}

protected:
	virtual void Start();
	virtual void Update();
	virtual void Render();

	void DebugRectRender();
private:
	GameEngineLevel* level_;
	float4 position_;
	float4 scale_;

	inline void SetLevel(GameEngineLevel* _level)
	{
		level_ = _level;
	}


	// 렌더 기능
public:
	void CreateRenderer(const std::string& _image, RenderPivot _pivotType = RenderPivot::CENTER, float4 _addPivot = {0, 0});

private:
	std::list<GameEngineRenderer*> renderList_;;
};

