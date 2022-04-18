#include "GameEngineUpdateObject.h"
#include "GameEngineTime.h"

GameEngineUpdateObject::GameEngineUpdateObject() 
	: IsUpdate_(true)
	, IsDeath_(false)
	, DeathTime_(0.0f) // isReleaseUpdate_가 켜져있고 deathTime_이 0이면 데이터가 삭제된다.
	, IsReleaseUpdate_(false)
	, AccTime_(0.0f)
{
}

GameEngineUpdateObject::~GameEngineUpdateObject() 
{
}