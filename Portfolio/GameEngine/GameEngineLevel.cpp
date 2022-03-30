#include "GameEngineLevel.h"
#include "GameEngineActor.h"

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
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart = AllActor_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd = AllActor_.end();
	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& Group = GroupStart->second;

		std::list<GameEngineActor*>::iterator BeginListIter = Group.begin();
		std::list<GameEngineActor*>::iterator EndListIter = Group.end();
		for (; BeginListIter != EndListIter;)
		{
			if (true == (*BeginListIter)->IsDeath())
			{
				delete (*BeginListIter);
				BeginListIter = Group.erase(BeginListIter);
				continue;
			}

			++BeginListIter;
		}
	}
}
