#include "GameEngineCollision.h"
#include "GameEngine.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>

bool (*CollisionCheckArray[static_cast<int>(CollisionType::Max)][static_cast<int>(CollisionType::Max)])(GameEngineCollision*, GameEngineCollision*);

bool RectToRect(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	if (nullptr == _Left || nullptr == _Right)
	{
		return false;
	}

	GameEngineRect LeftRc = _Left->GetRect();
	GameEngineRect RightRc = _Right->GetRect();

	return LeftRc.OverLap(RightRc);
}

class CollisionInit
{
public:
	CollisionInit()
	{
		CollisionCheckArray[static_cast<int>(CollisionType::Rect)][static_cast<int>(CollisionType::Rect)] = RectToRect;
	}
};

CollisionInit InitInst = CollisionInit();

GameEngineCollision::GameEngineCollision() 
	: Pivot_(float4::ZERO)
	, Scale_(float4::ZERO)
	, IsCameraEffect_(true)
{
}

GameEngineCollision::~GameEngineCollision() 
{
}

// 현재는 해당 그룹중 하나에라도 충돌됬으면 true를 리턴
bool GameEngineCollision::CollisionCheck(
	const std::string& _TargetGroup,
	CollisionType _This,
	CollisionType _Target
)
{
	if (false == IsUpdate())
	{
		return false;
	}

	std::string UpperKey = GameEngineString::ToUpperReturn(_TargetGroup);
	std::map<std::string, std::list<GameEngineCollision*>>::iterator FindTargetGroup = GetActor()->GetLevel()->AllCollision_.find(UpperKey);

	if (FindTargetGroup == GetActor()->GetLevel()->AllCollision_.end())
	{
		return false;
	}

	if (nullptr == CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)])
	{
		MsgBoxAssert("처리할 수 없는 충돌조합입니다.");
		return false;
	}

	std::list<GameEngineCollision*>& TargetGroup = FindTargetGroup->second;
	std::list<GameEngineCollision*>::iterator StartIter = TargetGroup.begin();
	std::list<GameEngineCollision*>::iterator EndIter = TargetGroup.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		if (false == (*StartIter)->IsUpdate())
		{
			return false;
		}
		if (CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)](this, *StartIter))
		{
			return true;
		}
	}

	return false;
}

bool GameEngineCollision::NextPosCollisionCheck(const std::string& _TargetGroup, float4 _NextPos, CollisionType _This, CollisionType _Target)
{
	if (false == IsUpdate())
	{
		return false;
	}

	std::string UpperKey = GameEngineString::ToUpperReturn(_TargetGroup);
	std::map<std::string, std::list<GameEngineCollision*>>::iterator FindTargetGroup = GetActor()->GetLevel()->AllCollision_.find(UpperKey);

	if (FindTargetGroup == GetActor()->GetLevel()->AllCollision_.end())
	{
		// MsgBoxAssert("존재하지 않는 충돌 그룹과 충돌하려고 했습니다.");

		return false;
	}

	if (nullptr == CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)])
	{
		MsgBoxAssert("처리할수 없는 충돌체크 조합입니다.");
		return false;
	}

	std::list<GameEngineCollision*>& TargetGroup = FindTargetGroup->second;

	std::list<GameEngineCollision*>::iterator StartIter = TargetGroup.begin();
	std::list<GameEngineCollision*>::iterator EndIter = TargetGroup.end();

	NextPos_ = _NextPos;

	for (; StartIter != EndIter; ++StartIter)
	{
		if (CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)](this, *StartIter))
		{
			if (false == (*StartIter)->IsUpdate())
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}

	NextPosReset();

	return false;
}

bool GameEngineCollision::CollisionResult(const std::string& _TargetGroup, std::vector<GameEngineCollision*>& _ColResult, CollisionType _This, CollisionType _Target)
{
	size_t StartSize = _ColResult.size();

	std::string UpperKey = GameEngineString::ToUpperReturn(_TargetGroup);
	std::map<std::string, std::list<GameEngineCollision*>>::iterator FindTargetGroup = GetActor()->GetLevel()->AllCollision_.find(UpperKey);

	if (FindTargetGroup == GetActor()->GetLevel()->AllCollision_.end())
	{
		return false;
	}

	if (nullptr == CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)])
	{
		MsgBoxAssert("처리할수 없는 충돌체크 조합입니다.");
		return false;
	}

	std::list<GameEngineCollision*>& TargetGroup = FindTargetGroup->second;

	std::list<GameEngineCollision*>::iterator StartIter = TargetGroup.begin();
	std::list<GameEngineCollision*>::iterator EndIter = TargetGroup.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)](this, *StartIter))
		{
			if (true == (*StartIter)->IsUpdate())
			{
				_ColResult.push_back(*StartIter);
			}
		}
	}

	return StartSize != _ColResult.size();
}

void GameEngineCollision::DebugRender()
{
	float4 Pos = GetActor()->GetPosition();

	if (true == IsCameraEffect_)
	{
		Pos = GetActor()->GetCameraEffectPosition();
	}
	GameEngineRect DebugRect(Pos + Pivot_, Scale_);

	Rectangle(
		GameEngine::BackBufferDC(),
		DebugRect.CenterLeft(),
		DebugRect.CenterTop(),
		DebugRect.CenterRight(),
		DebugRect.CenterBot()
	);
}

