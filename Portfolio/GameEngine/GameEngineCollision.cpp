#include "GameEngineCollision.h"
#include "GameEngineLevel.h"
#include <GameEngineBase/GameEngineDebug.h>

bool (*CollisionCheckArray[static_cast<int>(CollisionType::Max)][static_cast<int>(CollisionType::Max)])(GameEngineCollision*, GameEngineCollision*);

GameEngineCollision::GameEngineCollision() 
	: Pivot_(float4::ZERO)
	, Scale_(float4::ZERO)
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
	std::map<std::string, std::list<GameEngineCollision*>>::iterator FindTargetGroup = GetActor()->GetLevel()->AllCollision_.find(_TargetGroup);

	if (FindTargetGroup == GetActor()->GetLevel()->AllCollision_.end())
	{
		MsgBoxAssert("존재하지 않는 충돌 그룹과 충돌하려고 했습니다.");
		return false;
	}

	std::list<GameEngineCollision*>& TargetGroup = FindTargetGroup->second;
	std::list<GameEngineCollision*>::iterator StartIter = TargetGroup.begin();
	std::list<GameEngineCollision*>::iterator EndIter = TargetGroup.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		if (CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)](this, *StartIter))
		{
			return true;
		}
	}

	return false;
}

