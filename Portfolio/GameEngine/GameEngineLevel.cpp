#include "GameEngineLevel.h"
#include "GameEngineActor.h"

GameEngineLevel::GameEngineLevel() 
{
}

GameEngineLevel::~GameEngineLevel() 
{
	std::map<int, std::list<GameEngineActor*>>::iterator beginIter = allActor_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator endIter = allActor_.end();

	for (; beginIter != endIter; ++beginIter)
	{
		std::list<GameEngineActor*>& tmpGroup = beginIter->second;

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
	std::map<int, std::list<GameEngineActor*>>::iterator beginIter = allActor_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator endIter = allActor_.end();

	for (; beginIter != endIter; ++beginIter)
	{
		std::list<GameEngineActor*>& tmpGroup = beginIter->second;

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
	std::map<int, std::list<GameEngineActor*>>::iterator beginIter = allActor_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator endIter = allActor_.end();
	for (; beginIter != endIter; ++beginIter)
	{
		std::list<GameEngineActor*>& tmpGroup = beginIter->second;

		std::list<GameEngineActor*>::iterator beginListIter = tmpGroup.begin();
		std::list<GameEngineActor*>::iterator endListIter = tmpGroup.end();
		for (; beginListIter != endListIter; ++beginListIter)
		{
			if (false == (*beginListIter)->IsUpdate())
			{
				continue;
			}

			(*beginListIter)->Rendering();
		}
	}

	beginIter = allActor_.begin();
	endIter = allActor_.end();
	for (; beginIter != endIter; ++beginIter)
	{
		std::list<GameEngineActor*>& tmpGroup = beginIter->second;

		std::list<GameEngineActor*>::iterator beginListIter = tmpGroup.begin();
		std::list<GameEngineActor*>::iterator endListIter = tmpGroup.end();
		for (; beginListIter != endListIter; ++beginListIter)
		{
			if (false == (*beginListIter)->IsUpdate())
			{
				continue;
			}

			(*beginListIter)->Render();
		}
	}
}

void GameEngineLevel::ActorRelease()
{
	std::map<int, std::list<GameEngineActor*>>::iterator beginIter = allActor_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator endIter = allActor_.end();
	for (; beginIter != endIter; ++beginIter)
	{
		std::list<GameEngineActor*>& group = beginIter->second;

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
