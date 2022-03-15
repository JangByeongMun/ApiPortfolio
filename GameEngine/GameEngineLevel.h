#pragma once
#include <list>
#include <map>
#include <GameEngineBase/GameEngineNameObject.h>

class GameEngine;
class GameEngineActor;
class GameEngineLevel : public GameEngineNameObject
{
	friend GameEngine;
public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

protected:
	virtual void Loading() = 0;
	virtual void Update() = 0;

	virtual void SceneChangeStart() = 0; // 이 씬으로 바뀌었을때 실행되는 함수
	virtual void SceneChangeEnd() = 0; // 이 씬이 바뀌었을때 실행되는 함수
	
	template<typename ActorType>
	ActorType* CreateActor(const std::string& _name , int _order)
	{
		ActorType* newActor = new ActorType();
		newActor->SetName(_name);
		newActor->SetLevel(this);
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
		std::list<GameEngineActor*>& group = allActor_[_order];
		group.push_back(newActor);

		return nullptr;
	}

private:
	// 키값 == 업데이트의 우선순위
	std::map<int, std::list<GameEngineActor*>> allActor_;

	// 키값 == 액터의 이름
	//std::map<std::string, std::list<GameEngineActor*>> allActor_;

	void ActorUpdate();
	void ActorRender();
};

