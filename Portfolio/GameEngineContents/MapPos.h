#pragma once

union MapPos
{
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