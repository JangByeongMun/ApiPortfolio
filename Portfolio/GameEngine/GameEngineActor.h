#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineUpdateObject.h>
#include <list>

#include "GameEngineEnum.h"
#include "GameEngineLevel.h"

// 설명 :
class GameEngineLevel;
class GameEngineRenderer;
class GameEngineCollision;
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
	inline float4 GetCameraEffectPosition()
	{
		return Position_ - GetLevel()->GetCameraPos();
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

	inline void NextLevelOn()
	{
		NextLevelOn_ = true;
	}
	inline void NextLevelOff()
	{
		NextLevelOn_ = false;
	}


	void SetOrder(int _Order) override;

protected:
	virtual void Start() {};
	virtual void Update() {};
	virtual void Render() {};

	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) {};
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) {};

	void Release();
	void DebugRectRender();
	void LevelRegist(std::string _RegistName = "");

private:
	GameEngineLevel* Level_;
	float4 Position_;
	float4 Scale_;
	bool NextLevelOn_;

	inline void SetLevel(GameEngineLevel* _Level)
	{
		Level_ = _Level;
	}

	////////////////// 렌더 기능
public:
	// 기존 타입, 피벗 사용하기용 함수추가
	GameEngineRenderer* CreateRenderer(RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = { 0,0 }, int _Order = static_cast<int>(EngineMax::RENDERORDERMAX));
	GameEngineRenderer* CreateRenderer(const std::string& _Image, RenderPivot _PivotType, float4 _PivotPos = { 0, 0 }, int _Order = static_cast<int>(EngineMax::RENDERORDERMAX));

	GameEngineRenderer* CreateRenderer(int _Order = static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = { 0,0 });
	GameEngineRenderer* CreateRenderer(const std::string& _Image, int _Order = static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot _PivotType = RenderPivot::CENTER, float4 _PivotPos = {0, 0});
	GameEngineRenderer* CreateRendererToScale(const std::string& _Image, float4 _Scale, int _Order = static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot _PivotType = RenderPivot::CENTER, float4 _PivotPos = {0, 0});
	
	void Rendering();

private:
	std::list<GameEngineRenderer*> RenderList_;
	std::list<GameEngineRenderer*>::iterator StartRenderIter;
	std::list<GameEngineRenderer*>::iterator EndRenderIter;

	////////////////// 충돌 기능
public:
	GameEngineCollision* CreateCollision(const std::string& _GroupName, float4 _Scale, float4 _Pivot = {0, 0});

private:
	std::list<GameEngineCollision*> CollisionList_;
};

