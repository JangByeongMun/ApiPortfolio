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
		return Level_;
	}

	inline void SetMove(float4 _Value)
	{
		Position_ += _Value;
	}
	inline void SetPosition(float4 _Value)
	{
		Position_ = _Value;
	}
	inline float4 GetPosition()
	{
		return Position_;
	}
	inline void SetScale(float4 _Value)
	{
		Scale_ = _Value;
	}
	inline float4 GetScale()
	{
		return Scale_;
	}

protected:
	virtual void Start();
	virtual void Update();
	virtual void Render();

	void DebugRectRender();

private:
	GameEngineLevel* Level_;
	float4 Position_;
	float4 Scale_;

	inline void SetLevel(GameEngineLevel* _Level)
	{
		Level_ = _Level;
	}

	////////////////// 렌더 기능
public:
	GameEngineRenderer* CreateRenderer(RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = { 0,0 });
	GameEngineRenderer* CreateRenderer(const std::string& _Image, RenderPivot _PivotType = RenderPivot::CENTER, float4 _PivotPos = {0, 0});
	GameEngineRenderer* CreateRendererToScale(const std::string& _Image, float4 _Scale, RenderPivot _PivotType = RenderPivot::CENTER, float4 _PivotPos = {0, 0});
	void Rendering();

private:
	std::list<GameEngineRenderer*> RenderList_;
	std::list<GameEngineRenderer*>::iterator StartRenderIter;
	std::list<GameEngineRenderer*>::iterator EndRenderIter;
};

