#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCollision.h"
#include "GameEngineRenderer.h"

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

		std::list<GameEngineActor*>::iterator StartActor = tmpGroup.begin();
		std::list<GameEngineActor*>::iterator EndActor = tmpGroup.end();
		for (; StartActor != EndActor ; ++StartActor)
		{
			if (nullptr == (*StartActor))
			{
				continue;
			}

			delete (*StartActor);
			(*StartActor) = nullptr;
		}
	}
}

void GameEngineLevel::ActorUpdate()
{
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
				(*StartActor)->ReleaseUpdate();
				if (false == (*StartActor)->IsUpdate())
				{
					continue;
				}

				(*StartActor)->Update();
			}
		}
	}

	{
		std::map<int, std::list<GameEngineRenderer*>>::iterator GroupStart = AllRenderer_.begin();
		std::map<int, std::list<GameEngineRenderer*>>::iterator GroupEnd = AllRenderer_.end();

		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineRenderer*>& TmpGroup = GroupStart->second;

			std::list<GameEngineRenderer*>::iterator StartActor = TmpGroup.begin();
			std::list<GameEngineRenderer*>::iterator EndActor = TmpGroup.end();
			for (; StartActor != EndActor; ++StartActor)
			{
				(*StartActor)->ReleaseUpdate();
			}
		}
	}
}

void GameEngineLevel::ActorRender()
{
	// 랜더러 
	{
		std::map<int, std::list<GameEngineRenderer*>>::iterator GroupStart = AllRenderer_.begin();
		std::map<int, std::list<GameEngineRenderer*>>::iterator GroupEnd = AllRenderer_.end();
		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineRenderer*>& TmpGroup = GroupStart->second;

			std::list<GameEngineRenderer*>::iterator StartRenderer = TmpGroup.begin();
			std::list<GameEngineRenderer*>::iterator EndRenderer = TmpGroup.end();
			for (; StartRenderer != EndRenderer; ++StartRenderer)
			{
				std::list<GameEngineRenderer*>::iterator Test = StartRenderer;
				if (false == (*StartRenderer)->IsUpdate())
				{
					continue;
				}

				(*StartRenderer)->Render();
			}
		}
	}

	// 액터 
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

				(*StartActor)->Render();
			}
		}
	}
}

void GameEngineLevel::ActorRelease()
{
	// 렌더러 삭제
	{
		std::map<int, std::list<GameEngineRenderer*>>::iterator GroupStart = AllRenderer_.begin();
		std::map<int, std::list<GameEngineRenderer*>>::iterator GroupEnd = AllRenderer_.end();

		std::list<GameEngineRenderer*>::iterator StartRenderer;
		std::list<GameEngineRenderer*>::iterator EndRenderer;


		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineRenderer*>& Group = GroupStart->second;
			StartRenderer = Group.begin();
			EndRenderer = Group.end();
			for (; StartRenderer != EndRenderer; )
			{
				if (false == (*StartRenderer)->IsDeath())
				{
					++StartRenderer;
					continue;
				}

				StartRenderer = Group.erase(StartRenderer);
			}
		}
	}

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

void GameEngineLevel::AddRenderer(GameEngineRenderer* _Renderer)
{
	AllRenderer_[_Renderer->GetOrder()].push_back(_Renderer);
}

void GameEngineLevel::ChangeRenderOrder(GameEngineRenderer* _Renderer, int _NewOrder)
{
	AllRenderer_[_Renderer->GetOrder()].remove(_Renderer);

	_Renderer->GameEngineUpdateObject::SetOrder(_NewOrder);

	AllRenderer_[_Renderer->GetOrder()].push_back(_Renderer);
}

void GameEngineLevel::AddCollision(const std::string& _GroupName, GameEngineCollision* _Collision)
{
	AllCollision_[_GroupName].push_back(_Collision);
}