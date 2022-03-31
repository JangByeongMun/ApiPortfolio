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

// ����� �ش� �׷��� �ϳ����� �浹������ true�� ����
bool GameEngineCollision::CollisionCheck(
	const std::string& _TargetGroup,
	CollisionType _This,
	CollisionType _Target
)
{
	std::map<std::string, std::list<GameEngineCollision*>>::iterator FindTargetGroup = GetActor()->GetLevel()->AllCollision_.find(_TargetGroup);

	if (FindTargetGroup == GetActor()->GetLevel()->AllCollision_.end())
	{
		MsgBoxAssert("�������� �ʴ� �浹 �׷�� �浹�Ϸ��� �߽��ϴ�.");
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

