#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCollision.h"

GameEngineLevel::GameEngineLevel() 
	: CameraPos_(float4::ZERO)
{
}

GameEngineLevel::~GameEngineLevel() 
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart = AllActor_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd = AllActor_.end();

	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& tmpGroup = GroupStart->second;

		std::list<GameEngineActor*>::iterator BeginListIter = tmpGroup.begin();
		std::list<GameEngineActor*>::iterator EndListIter = tmpGroup.end();
		for (; BeginListIter != EndListIter ; ++BeginListIter)
		{
			if (nullptr == (*BeginListIter))
			{
				continue;
			}

			delete (*BeginListIter);
			(*BeginListIter) = nullptr;
		}
	}
}

void GameEngineLevel::ActorUpdate()
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart = AllActor_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd = AllActor_.end();

	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& TmpGroup = GroupStart->second;

		std::list<GameEngineActor*>::iterator BeginListIter = TmpGroup.begin();
		std::list<GameEngineActor*>::iterator EndListIter = TmpGroup.end();
		for (; BeginListIter != EndListIter; ++BeginListIter)
		{
			(*BeginListIter)->ReleaseUpdate();
			if (false == (*BeginListIter)->IsUpdate())
			{
				continue;
			}

			(*BeginListIter)->Update();
		}
	}
}

void GameEngineLevel::ActorRender()
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart = AllActor_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd = AllActor_.end();
	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& TmpGroup = GroupStart->second;

		std::list<GameEngineActor*>::iterator StartActor = TmpGroup.begin();
		std::list<GameEngineActor*>::iterator EndActor = TmpGroup.end();
		for (; StartActor != EndActor; ++StartActor)
		{
			if (false == (*StartActor)->IsUpdate())
			{
				continue;
			}

			(*StartActor)->Rendering();
		}
	}

	GroupStart = AllActor_.begin();
	GroupEnd = AllActor_.end();
	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& TmpGroup = GroupStart->second;

		std::list<GameEngineActor*>::iterator StartActor = TmpGroup.begin();
		std::list<GameEngineActor*>::iterator EndActor = TmpGroup.end();
		for (; StartActor != EndActor; ++StartActor)
		{
			if (false == (*StartActor)->IsUpdate())
			{
				continue;
			}

			(*StartActor)->Render();
		}
	}
}

void GameEngineLevel::ActorRelease()
{

	// 충돌 삭제
	{
		std::map<std::string, std::list<GameEngineCollision*>>::iterator GroupStart = AllCollision_.begin();
		std::map<std::string, std::list<GameEngineCollision*>>::iterator GroupEnd = AllCollision_.end();
		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineCollision*>& Group = GroupStart->second;
			std::list<GameEngineCollision*>::iterator StartCollision = Group.begin();
			std::list<GameEngineCollision*>::iterator EndCollision = Group.end();
			for (; StartCollision != EndCollision; )
			{
				if (false == (*StartCollision)->IsDeath())
				{
					++StartCollision;
					continue;
				}

				StartCollision = Group.erase(StartCollision);
			}
		}
	}

	// 액터 삭제
	{
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStart = AllActor_.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd = AllActor_.end();
		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineActor*>& Group = GroupStart->second;

			std::list<GameEngineActor*>::iterator StartActor = Group.begin();
			std::list<GameEngineActor*>::iterator EndActor = Group.end();
			for (; StartActor != EndActor;)
			{
				if (true == (*StartActor)->IsDeath())
				{
					delete (*StartActor);
					StartActor = Group.erase(StartActor);
					continue;
				}

				// 액터 내부의 충돌, 렌더 상태확인
				(*StartActor)->Release();
				++StartActor;
			}
		}
	}
}

void GameEngineLevel::CollisionDebugRender()
{
	std::map<std::string, std::list<GameEngineCollision*>>::iterator GroupStart = AllCollision_.begin();
	std::map<std::string, std::list<GameEngineCollision*>>::iterator GroupEnd = AllCollision_.end();

	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineCollision*>& Group = GroupStart->second;
		std::list<GameEngineCollision*>::iterator StartCollision = Group.begin();
		std::list<GameEngineCollision*>::iterator EndCollision = Group.end();
		for (; StartCollision != EndCollision; ++StartCollision)
		{
			if (false == (*StartCollision)->IsUpdate())
			{
				continue;
			}

			(*StartCollision)->DebugRender();
		}
	}
}

void GameEngineLevel::AddCollision(const std::string& _GroupName, GameEngineCollision* _Collision)
{
	AllCollision_[_GroupName].push_back(_Collision);
}