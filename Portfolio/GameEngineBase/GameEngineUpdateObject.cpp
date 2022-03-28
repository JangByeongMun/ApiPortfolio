#include "GameEngineUpdateObject.h"
#include "GameEngineTime.h"

GameEngineUpdateObject::GameEngineUpdateObject() 
	: isUpdate_(true)
	, isDeath_(false)
	, deathTime_(0) // isReleaseUpdate_�� �����ְ� deathTime_�� 0�̸� �����Ͱ� �����ȴ�.
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

