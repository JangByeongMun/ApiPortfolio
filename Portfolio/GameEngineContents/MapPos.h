#pragma once

union MapPos
{
public:
	//struct
	//{
	//	int x;
	//	int y;
	//};
	__int64 n;

public:
	bool operator==(const MapPos& _other) const
	{
		return n == _other.n;
	}
	bool operator!=(const MapPos& _other) const
	{
		return n != _other.n;
	}
	bool operator>(const MapPos& _other) const
	{
		return n > _other.n;
	}
	bool operator<(const MapPos& _other) const
	{
		return n < _other.n;
	}

	//MapPos(int _x, int _y)
	//	: x(_x)
	//	, y(_y)
	//{
	//}
};