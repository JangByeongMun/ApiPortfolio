#pragma once

// ������ ����
enum class ORDER
{
	BACKGROUND,
	PLAYER,
	UI,
};

// ������ ĳ���� Ÿ��
enum class CharacterType
{
	ISAAC,
	CAIN,
	MAGDALENE,
	JUDAS,
	BLUEBABY,
};

// �� ���� �����Ͱ�
enum class BlockData
{
	NORMAL = 0,
	FIRE,
	FIREBLUE,
	FIRERED,
	HOLE,
	POOP,
	POOPRED,
	STONE,
	STONEBLACK,
	THORN,

	END,
};

enum class ProjectileType
{
	PLAYER_BASIC,
	PLAYER_TRIPLE,
	PLAYER_CHASE,
	PLAYER_PEE,
	PLAYER_RED,
	PLAYER_PENETRATE,
	PLAYER_LASER,
	PLAYER_CHOCO,
	PLAYER_KNIFE,
	PLAYER_BLOODLASER,
	PLAYER_IPECAC,
	PLAYER_QUARTER,
	PLAYER_POLYPHEMUS,
	PLAYER_EYE,

	ENEMY_BASIC,
	ENEMY_CHASE,
	ENEMY_TRIPLE,
	ENEMY_FIFTH,
	ENEMY_LASER,
	ENEMY_FOURDIRECTORY,
	ENEMY_IPECAC,
	ENEMY_BONE,

};

enum class HeartType
{
	SoulHeart,
	BlackHeart,
};

enum class ItemType
{
	None,
	Bomb,
	Key,
	Money,
	Max,
};