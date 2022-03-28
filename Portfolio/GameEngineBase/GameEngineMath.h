#pragma once

// Ό³Έν :
class GameEngineMath
{
public:
	// constrcuter destructer
	GameEngineMath();
	~GameEngineMath();

	// delete Function
	GameEngineMath(const GameEngineMath& _Other) = delete;
	GameEngineMath(GameEngineMath&& _Other) noexcept = delete;
	GameEngineMath& operator=(const GameEngineMath& _Other) = delete;
	GameEngineMath& operator=(GameEngineMath&& _Other) noexcept = delete;

protected:

private:

};

class float4
{
public:
	static float4 Left;
	static float4 Right;
	static float4 Up;
	static float4 Down;

public:
	float x;
	float y;
	float z;
	float w;

public:
	bool IsZero2D() const
	{
		return x == 0.0f && y == 0.0f;
	}

public:
	int ix() const
	{
		return static_cast<int>(x);
	}
	int iy() const
	{
		return static_cast<int>(y);
	}
	int iz() const
	{
		return static_cast<int>(z);
	}
	int iw() const
	{
		return static_cast<int>(w);
	}

	int hix() const
	{
		return static_cast<int>(x * 0.5f);
	}
	int hiy() const
	{
		return static_cast<int>(y * 0.5f);
	}
	int hiz() const
	{
		return static_cast<int>(z * 0.5f);
	}
	int hiw() const
	{
		return static_cast<int>(w * 0.5f);
	}

	float4 Half() const
	{
		return { x * 0.5f, y * 0.5f, z * 0.5f, 1.0f };
	}

	float4 operator-(const float4& _other) const
	{
		return { x - _other.x, y - _other.y, z - _other.z, 1.0f };
	}
	float4 operator+(const float4& _other) const
	{
		return { x + _other.x, y + _other.y, z + _other.z, 1.0f };
	}
	float4 operator*(const float& _value) const
	{
		return { x * _value, y * _value, z * _value, 1.0f };
	}
	float4& operator+=(const float4& _other)
	{
		x += _other.x;
		y += _other.y;
		z += _other.z;

		return *this;
	}

public:
	float4()
		: x(0)
		, y(0)
		, z(0)
		, w(1.0f)
	{
	}
	float4(float _x, float _y)
		: x(_x)
		, y(_y)
		, z(0)
		, w(1.0f)
	{
	}
	float4(float _x, float _y, float _z)
		: x(_x)
		, y(_y)
		, z(_z)
		, w(1.0f)
	{
	}
	float4(float _x, float _y, float _z, float _w)
		: x(_x)
		, y(_y)
		, z(_z)
		, w(_w)
	{
	}
};

class GameEngineRect
{
public:
	float4 pos;
	float4 scale;

public:
	inline int GetCenterLeft() const
	{
		return pos.ix() - scale.hix();
	}
	inline int GetCenterRight() const
	{
		return pos.ix() + scale.hix();
	}
	inline int GetCenterTop() const
	{
		return pos.iy() - scale.hiy();
	}
	inline int GetCenterBot() const
	{
		return pos.iy() + scale.hiy();
	}

public:
	GameEngineRect(float4 _pos, float4 _scale)
		: pos(_pos)
		, scale(_scale)
	{
	}
};