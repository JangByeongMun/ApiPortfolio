#include "GameEngineTime.h"
#include <Windows.h>

GameEngineTime* GameEngineTime::inst_ = new GameEngineTime();

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

GameEngineTime::GameEngineTime()
	: secondCount_(0)
	, currentCount_(0)
	, prevCount_(0)
	, deltaTime_(0)
	, realDeltaTime_(0)
{
}

GameEngineTime::~GameEngineTime() 
{
}

