#include "GameEngineUpdateObject.h"
#include "GameEngineTime.h"

GameEngineUpdateObject::GameEngineUpdateObject() 
	: IsUpdate_(true)
	, IsDeath_(false)
	, DeathTime_(0.0f) // isReleaseUpdate_�� �����ְ� deathTime_�� 0�̸� �����Ͱ� �����ȴ�.
	, IsReleaseUpdate_(false)
	, AccTime_(0.0f)
{
}

GameEngineUpdateObject::~GameEngineUpdateObject() 
{
}