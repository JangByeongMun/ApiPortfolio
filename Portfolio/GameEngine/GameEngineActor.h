#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineUpdateObject.h>
#include <list>
#include "GameEngineEnum.h"

// 설명 :
class GameEngineRenderer;
class GameEngineLevel;
class GameEngineActor : public GameEngineNameObject, public GameEngineUpdateObject
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

	inline GameEngineLevel* GetLevel()
	{
		return level_;
	}

	inline void SetMove(float4 _value)
	{
		position_ += _value;
	}
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
	GameEngineRenderer* CreateRenderer(RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = { 0,0 });
	GameEngineRenderer* CreateRenderer(const std::string& _image, RenderPivot _pivotType = RenderPivot::CENTER, float4 _pivotPos = {0, 0});
	GameEngineRenderer* CreateRendererToScale(const std::string& _image, float4 _scale, RenderPivot _pivotType = RenderPivot::CENTER, float4 _pivotPos = {0, 0});
	void Rendering();

private:
	std::list<GameEngineRenderer*> renderList_;
	std::list<GameEngineRenderer*>::iterator startRenderIter;
	std::list<GameEngineRenderer*>::iterator endRenderIter;
};

