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
	float x;
	float y;
	float z;
	float w;

public:
	int ix()
	{
		return static_cast<int>(x);
	}
	int iy()
	{
		return static_cast<int>(y);
	}
	int iz()
	{
		return static_cast<int>(z);
	}
	int iw()
	{
		return static_cast<int>(w);
	}

	int hix()
	{
		return static_cast<int>(x * 0.5f);
	}
	int hiy()
	{
		return static_cast<int>(y * 0.5f);
	}
	int hiz()
	{
		return static_cast<int>(z * 0.5f);
	}
	int hiw()
	{
		return static_cast<int>(w * 0.5f);
	}

	float4 Half()
	{
		return { x * 0.5f, y * 0.5f, z * 0.5f, 1.0f };
	}
};

struct GameEngineRect
{
public:
	float4 pos;
	float4 scale;

public:
	inline int GetCenterLeft() 
	{
		return pos.ix() - scale.hix();
	}
	inline int GetCenterRight()
	{
		return pos.ix() + scale.hix();
	}
	inline int GetCenterTop()
	{
		return pos.iy() - scale.hiy();
	}
	inline int GetCenterBot()
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