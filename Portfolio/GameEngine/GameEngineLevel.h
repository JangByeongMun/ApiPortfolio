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

		// �� ���͵鸶�� start�� �ٸ��� �ִµ� �̸� �����Լ��� �������� �ۿ��� ȣ������ ���ϵ��� ������ GameEngineActor������ ȣ�Ⱑ���ϵ��� ����
		GameEngineActor* EngineActor = NewActor;
		EngineActor->Start();

		// ------------------------------------------
		//std::map<int, std::list<GameEngineActor*>>::iterator findIter = allActor_.find(_order);
		//if (findIter == allActor_.end())
		//{
		//	// make_pair ���� ���� ������ (�ش� ������Ÿ��::���_Ÿ��) (ũ�� ���̴� ����)
		//	allActor_.insert(std::map<int, std::list<GameEngineActor*>>::value_type(_order, std::list<GameEngineActor*>()));
		//}
		// ------------------------------------------
		// �迭 �������� ����ϸ� insert�� find�� ���ÿ� �Ҽ� �ִ�. - �� ã�ƺ��� ������ �־��ټ� �ִٴ°�
		// ���� ��ũ��Ʈ�� �ϳ��� ���ļ� ������ذ�
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

	virtual void LevelChangeStart() = 0; // �� ������ �ٲ������ ����Ǵ� �Լ�
	virtual void LevelChangeEnd() = 0; // �� ���� �ٲ������ ����Ǵ� �Լ�

	void ActorLevelChangeStart(); // �� ������ �ٲ������ ���͵� �Լ� ����
	void ActorLevelChangeEnd(); // �� ���� �ٲ������ ���͵� �Լ� ����

	//////////////////// ����
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

	//////////////////// ������
private:
	std::map<int, std::list<GameEngineRenderer*>> AllRenderer_;
	std::vector<ChangeOrderItem> ChangeOrderList;
	
	void AddRenderer(GameEngineRenderer* _Renderer);
	void ChangeRenderOrder(GameEngineRenderer* _Renderer, int _NewOrder);

	//////////////////// �ݸ���
private:
	std::map<std::string, std::list<GameEngineCollision*>> AllCollision_;

	void AddCollision(const std::string& _GroupName, GameEngineCollision* _Collision);
};

