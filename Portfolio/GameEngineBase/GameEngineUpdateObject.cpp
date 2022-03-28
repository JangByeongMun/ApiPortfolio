#include "GameEngineUpdateObject.h"
#include "GameEngineTime.h"

GameEngineUpdateObject::GameEngineUpdateObject() 
	: isUpdate_(true)
	, isDeath_(false)
	, deathTime_(0) // isReleaseUpdate_가 켜져있고 deathTime_이 0이면 데이터가 삭제된다.
	, isReleaseUpdate_(false)
{
}

GameEngineUpdateObject::~GameEngineUpdateObject() 
{
}

void GameEngineUpdateObject::ReleaseUpdate()
{
	if (false == isReleaseUpdate_)
	{
		return;
	}

	deathTime_ -= GameEngineTime::GetDeltaTime();

	if (0.0f >= deathTime_)
	{
		isDeath_ = true;
	}
}

