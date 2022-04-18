#pragma once
#include <GameEngineBase/GameEngineMath.h>

union MapPos
{
public:
	MapPos()
		: x(0)
		, y(0)
	{
	}
	MapPos(float4 _Value)
		: x(static_cast<int>(_Value.x))
		, y(static_cast<int>(_Value.y))
	{
	}

public:
	struct
	{
		int x;
		int y;
	};
	__int64 n;

public:
	bool operator==(const MapPos& _Other) const
	{
		return n == _Other.n;
	}
	bool operator!=(const MapPos& _Other) const
	{
		return n != _Other.n;
	}
	bool operator>(const MapPos& _Other) const
	{
		return n > _Other.n;
	}
	bool operator<(const MapPos& _Other) const
	{
		return n < _Other.n;
	}
};