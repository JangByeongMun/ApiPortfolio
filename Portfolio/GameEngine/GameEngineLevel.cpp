#include "GameEngineLevel.h"
#include "GameEngineActor.h"

GameEngineLevel::GameEngineLevel() 
{
}

GameEngineLevel::~GameEngineLevel() 
{
	std::map<int, std::list<GameEngineActor*>>::iterator groupStart = allActor_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator groupEnd = allActor_.end();

	for (; groupStart != groupEnd; ++groupStart)
	{
		std::list<GameEngineActor*>& tmpGroup = groupStart->second;

		std::list<GameEngineActor*>::iterator beginListIter = tmpGroup.begin();
		std::list<GameEngineActor*>::iterator endListIter = tmpGroup.end();
		for (; beginListIter != endListIter ; ++beginListIter)
		{
			if (nullptr == (*beginListIter))
			{
				continue;
			}

			delete (*beginListIter);
			(*beginListIter) = nullptr;
		}
	}
}

void GameEngineLevel::ActorUpdate()
{
	std::map<int, std::list<GameEngineActor*>>::iterator groupStart = allActor_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator groupEnd = allActor_.end();

	for (; groupStart != groupEnd; ++groupStart)
	{
		std::list<GameEngineActor*>& tmpGroup = groupStart->second;

		std::list<GameEngineActor*>::iterator beginListIter = tmpGroup.begin();
		std::list<GameEngineActor*>::iterator endListIter = tmpGroup.end();
		for (; beginListIter != endListIter; ++beginListIter)
		{
			(*beginListIter)->ReleaseUpdate();
			if (false == (*beginListIter)->IsUpdate())
			{
				continue;
			}

			(*beginListIter)->Update();
		}
	}
}

void GameEngineLevel::ActorRender()
{
	std::map<int, std::list<GameEngineActor*>>::iterator groupStart = allActor_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator groupEnd = allActor_.end();
	for (; groupStart != groupEnd; ++groupStart)
	{
		std::list<GameEngineActor*>& tmpGroup = groupStart->second;

		std::list<GameEngineActor*>::iterator startActor = tmpGroup.begin();
		std::list<GameEngineActor*>::iterator endActor = tmpGroup.end();
		for (; startActor != endActor; ++startActor)
		{
			if (false == (*startActor)->IsUpdate())
			{
				continue;
			}

			(*startActor)->Rendering();
		}
	}

	groupStart = allActor_.begin();
	groupEnd = allActor_.end();
	for (; groupStart != groupEnd; ++groupStart)
	{
		std::list<GameEngineActor*>& tmpGroup = groupStart->second;

		std::list<GameEngineActor*>::iterator startActor = tmpGroup.begin();
		std::list<GameEngineActor*>::iterator endActor = tmpGroup.end();
		for (; startActor != endActor; ++startActor)
		{
			if (false == (*startActor)->IsUpdate())
			{
				continue;
			}

			(*startActor)->Render();
		}
	}
}

void GameEngineLevel::ActorRelease()
{
	std::map<int, std::list<GameEngineActor*>>::iterator groupStart = allActor_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator groupEnd = allActor_.end();
	for (; groupStart != groupEnd; ++groupStart)
	{
		std::list<GameEngineActor*>& group = groupStart->second;

		std::list<GameEngineActor*>::iterator beginListIter = group.begin();
		std::list<GameEngineActor*>::iterator endListIter = group.end();
		for (; beginListIter != endListIter;)
		{
			if (true == (*beginListIter)->IsDeath())
			{
				delete (*beginListIter);
				beginListIter = group.erase(beginListIter);
				continue;
			}

			++beginListIter;
		}
	}
}
