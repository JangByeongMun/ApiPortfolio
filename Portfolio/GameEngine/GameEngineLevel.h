#pragma once
#include <list>
#include <map>
#include <vector>
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>

class GameEngineActor;
struct ChangeOrderItem
{
	GameEngineActor* TargetObject;
	int ChangeOrder;
};

class GameEngine;
class GameEngineActor;
class GameEngineCollision;
class GameEngineRenderer;
class GameEngineLevel : public GameEngineNameObject
{
	friend GameEngine;
	friend GameEngineActor;
	friend GameEngineCollision;
	friend GameEngineRenderer;

public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	bool IsDebugModeOn()
	{
		IsDebug = true;
	}
	bool IsDebugModeOff()
	{
		IsDebug = false;
	}
	bool IsDebugModeSwitch()
	{
		IsDebug = !IsDebug;
	}

	template<typename ActorType>
	ActorType* CreateActor(int _Order = 0, const std::string& _Name = "")
	{
		ActorType* NewActor = new ActorType();
		NewActor->GameEngineUpdateObject::SetOrder(_Order);
		NewActor->SetName(_Name);
		NewActor->SetLevel(this);

		// 각 액터들마다 start가 다를수 있는데 이를 가상함수로 제작한후 밖에서 호출하지 못하도록 막은후 GameEngineActor에서만 호출가능하도록 구현
		GameEngineActor* EngineActor = NewActor;
		EngineActor->Start();

		// ------------------------------------------
		//std::map<int, std::list<GameEngineActor*>>::iterator findIter = allActor_.find(_order);
		//if (findIter == allActor_.end())
		//{
		//	// make_pair 류중 제일 빠른것 (해당 데이터타입::밸류_타입) (크게 차이는 없다)
		//	allActor_.insert(std::map<int, std::list<GameEngineActor*>>::value_type(_order, std::list<GameEngineActor*>()));
		//}
		// ------------------------------------------
		// 배열 형식으로 사용하면 insert와 find를 동시에 할수 있다. - 즉 찾아보고 없으면 넣어줄수 있다는것
		// 위의 스크립트를 하나로 뭉쳐서 만들어준것
		std::list<GameEngineActor*>& Group = AllActor_[_Order];
		Group.push_back(NewActor);

		return NewActor;
	}

	inline float4 GetCameraPos()
	{
		return CameraPos_;
	}
	inline void MoveCameraPos(const float4& _Value)
	{
		CameraPos_ += _Value;
	}
	inline void SetCameraPos(const float4& _Value)
	{
		CameraPos_ = _Value;
	}

	template<typename ConvertType>
	ConvertType* FindActor(const std::string& _Name)
	{
		return dynamic_cast<ConvertType*>(FindActor(_Name));
	}
	GameEngineActor* FindActor(const std::string& _Name);

	void RegistActor(const std::string& _Name, GameEngineActor* _Actor);

protected:
	virtual void Loading() = 0;
	virtual void Update() = 0;

	virtual void LevelChangeStart() = 0; // 이 씬으로 바뀌었을때 실행되는 함수
	virtual void LevelChangeEnd() = 0; // 이 씬이 바뀌었을때 실행되는 함수

	void ActorLevelChangeStart(); // 이 씬으로 바뀌었을때 액터들 함수 실행
	void ActorLevelChangeEnd(); // 이 씬이 바뀌었을때 액터들 함수 실행

	//////////////////// 액터
private:
	static bool IsDebug;

	std::map<int, std::list<GameEngineActor*>> AllActor_;
	std::map<std::string, GameEngineActor*> RegistActor_;
	float4 CameraPos_;

	void ActorUpdate();
	void ActorRender();
	void ActorRelease();
	void CollisionDebugRender();
	void ChangeUpdateOrder(GameEngineActor* _Actor, int _NewOrder);

	//////////////////// 렌더러
private:
	std::map<int, std::list<GameEngineRenderer*>> AllRenderer_;
	std::vector<ChangeOrderItem> ChangeOrderList;
	
	void AddRenderer(GameEngineRenderer* _Renderer);
	void ChangeRenderOrder(GameEngineRenderer* _Renderer, int _NewOrder);

	//////////////////// 콜리젼
private:
	std::map<std::string, std::list<GameEngineCollision*>> AllCollision_;

	void AddCollision(const std::string& _GroupName, GameEngineCollision* _Collision);
};

