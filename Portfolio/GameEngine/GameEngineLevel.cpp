#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCollision.h"
#include "GameEngineRenderer.h"
#include <GameEngineBase/GameEngineDebug.h>

bool GameEngineLevel::IsDebug = true;

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

GameEngineActor* GameEngineLevel::FindActor(const std::string& _Name)
{
	std::map<std::string, GameEngineActor*>::iterator FindIter = RegistActor_.find(_Name);

	if (RegistActor_.end() == FindIter)
	{
		return nullptr;
	}

	return FindIter->second;
}

void GameEngineLevel::RegistActor(const std::string& _Name, GameEngineActor* _Actor)
{
	if (RegistActor_.end() != RegistActor_.find(_Name))
	{
		MsgBoxAssert("이미 존재하는 이름으로 또 등록하려고 했습니다.");
	}

	RegistActor_.insert(std::map<std::string, GameEngineActor*>::value_type(_Name, _Actor));
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
				(*StartActor)->AddAccTime(GameEngineTime::GetDeltaTime());
				if (false == (*StartActor)->IsUpdate())
				{
					continue;
				}

				(*StartActor)->Update();
			}
		}
	}

	for (int i = 0; i < ChangeOrderList.size(); i++)
	{
		ChangeOrderItem& Data = ChangeOrderList[i];
		AllActor_[Data.TargetObject->GetOrder()].remove(Data.TargetObject);
		Data.TargetObject->GameEngineUpdateObject::SetOrder(Data.ChangeOrder);
		AllActor_[Data.TargetObject->GetOrder()].push_back(Data.TargetObject);
	}

	ChangeOrderList.clear();

	// 렌더러의 릴리즈업데이트가 안되서 추가
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
	if (false == IsDebug)
	{
		return;
	}

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

void GameEngineLevel::ChangeUpdateOrder(GameEngineActor* _Actor, int _NewOrder)
{
	if (_Actor->GetOrder() == _NewOrder)
	{
		return;
	}
	ChangeOrderList.push_back({ _Actor ,_NewOrder });
}

void GameEngineLevel::AddRenderer(GameEngineRenderer* _Renderer)
{
	AllRenderer_[_Renderer->GetOrder()].push_back(_Renderer);
}

void GameEngineLevel::ChangeRenderOrder(GameEngineRenderer* _Renderer, int _NewOrder)
{
	if (_Renderer->GetOrder() == _NewOrder)
	{
		return;
	}

	AllRenderer_[_Renderer->GetOrder()].remove(_Renderer);
	_Renderer->GameEngineUpdateObject::SetOrder(_NewOrder);
	AllRenderer_[_Renderer->GetOrder()].push_back(_Renderer);
}

void GameEngineLevel::AddCollision(const std::string& _GroupName, GameEngineCollision* _Collision)
{
	_Collision->CollisionName_ = _GroupName;
	AllCollision_[_GroupName].push_back(_Collision);
}

void GameEngineLevel::ActorLevelChangeStart(GameEngineLevel* _PrevLevel)
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart = AllActor_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd = AllActor_.end();

	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& Group = GroupStart->second;
		std::list<GameEngineActor*>::iterator StartActor = Group.begin();
		std::list<GameEngineActor*>::iterator EndActor = Group.end();
		for (; StartActor != EndActor; ++StartActor)
		{
			if (false == (*StartActor)->IsUpdate())
			{
				continue;
			}

			(*StartActor)->LevelChangeStart(_PrevLevel);
		}
	}
}

void GameEngineLevel::ActorLevelChangeEnd(GameEngineLevel* _NextLevel)
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart = AllActor_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd = AllActor_.end();

	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& Group = GroupStart->second;
		std::list<GameEngineActor*>::iterator StartActor = Group.begin();
		std::list<GameEngineActor*>::iterator EndActor = Group.end();
		for (; StartActor != EndActor; ++StartActor)
		{
			if (false == (*StartActor)->IsUpdate())
			{
				continue;
			}

			(*StartActor)->LevelChangeEnd(_NextLevel);
		}
	}
}

void GameEngineLevel::ObjectLevelMoveCheck(GameEngineLevel* _NextLevel)
{
	// 렌더러
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
				if (false == (*StartRenderer)->GetActor()->NextLevelOn_)
				{
					++StartRenderer;
					continue;
				}

				GameEngineRenderer* Object = *StartRenderer;
				_NextLevel->AllRenderer_[Object->GetOrder()].push_back(Object);


				StartRenderer = Group.erase(StartRenderer);
			}
		}
	}

	// 콜리젼
	{
		std::map<std::string, std::list<GameEngineCollision*>>::iterator GroupStart = AllCollision_.begin();
		std::map<std::string, std::list<GameEngineCollision*>>::iterator GroupEnd = AllCollision_.end();

		std::list<GameEngineCollision*>::iterator StartCollision;
		std::list<GameEngineCollision*>::iterator EndCollision;


		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineCollision*>& Group = GroupStart->second;
			StartCollision = Group.begin();
			EndCollision = Group.end();
			for (; StartCollision != EndCollision; )
			{
				if (false == (*StartCollision)->GetActor()->NextLevelOn_)
				{
					++StartCollision;
					continue;
				}

				GameEngineCollision* Object = *StartCollision;
				_NextLevel->AllCollision_[Object->CollisionName_].push_back(Object);

				StartCollision = Group.erase(StartCollision);
			}
		}

	}

	// 액터
	{
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStart;
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd;

		std::list<GameEngineActor*>::iterator StartActor;
		std::list<GameEngineActor*>::iterator EndActor;

		GroupStart = AllActor_.begin();
		GroupEnd = AllActor_.end();

		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineActor*>& Group = GroupStart->second;

			StartActor = Group.begin();
			EndActor = Group.end();
			for (; StartActor != EndActor; )
			{
				if (true == (*StartActor)->NextLevelOn_)
				{
					// 여기서 옮겨간다.
					GameEngineActor* Object = *StartActor;
					Object->SetLevel(_NextLevel);
					Object->NextLevelOff();
					_NextLevel->AllActor_[Object->GetOrder()].push_back(Object);

					StartActor = Group.erase(StartActor);
					continue;
				}

				++StartActor;
			}
		}
	}
}