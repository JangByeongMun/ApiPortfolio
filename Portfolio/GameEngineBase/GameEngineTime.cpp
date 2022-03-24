#include "GameEngineTime.h"
#include <Windows.h>

GameEngineTime* GameEngineTime::inst_ = new GameEngineTime();

GameEngineTime* GameEngineTime::GetInst()
{
	return inst_;
}

void GameEngineTime::Reset()
{
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&prevCount_));
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount_));
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&secondCount_));
	Update();
}

void GameEngineTime::Update()
{
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount_));

	realDeltaTime_ = (static_cast<double>(currentCount_) - static_cast<double>(prevCount_)) / static_cast<double>(secondCount_);
	prevCount_ = currentCount_;

	deltaTime_ = static_cast<float>(realDeltaTime_);
}

float GameEngineTime::GetDeltaTime()
{
	return 0.0f;
}

GameEngineTime::GameEngineTime()
{
}

GameEngineTime::~GameEngineTime() 
{
}

