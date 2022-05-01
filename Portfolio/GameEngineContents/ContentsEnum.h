#pragma once

// 렌더러 순서
enum class ORDER
{
	BACKGROUND,
	BACKPLAYER,
	PLAYER,
	BACKUI,
	UI,
	FRONTUI,
};

// 선택한 캐릭터 타입
enum class CharacterType
{
	ISAAC,
	CAIN,
	MAGDALENE,
	JUDAS,
	BLUEBABY,
};

// 각 블럭의 데이터값
enum class BlockType
{
	NORMAL = 0,
	FIRE,
	HOLE,
	POOP,
	STONE,
	STONEBLACK,
	STONEURN,
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

enum class HeartData
{
	SoulHeart,
	BlackHeart,
};

enum class ItemType
{
	None,
	Bomb,
	BombTwo,
	Key,
	KeyTwo,
	keyMaster,
	Money,
	MoneyBlack,
	MoneySilver,
	Battery,
	Max,
};

enum class AccessoryType
{
	None = -1,
	swallowedpenny,
	petrifiedpoop,
	aaabattery,
	brokenremote,
	purpleheart,
	brokenmagnet,
	cartridge,
	pulseworm,
	Max,
};

enum class CardType
{
	None = 0,
	TheFool,
	TheMagician,
	TheHighPriestess,
	TheEmpress,
	TheEmperor,
	TheHierophant,
	TheLovers,
	TheChariot,
	Justice,
	TheHermit,
	WheelofFortune,
	Strength,
	Death,
	TheDevil,
	TheSun,
	Max,
};

enum class DoorType
{
	Default,
	Treasure,
	Boss,
	Shop,
	Max,
};

enum class DoorDir
{
	Up,
	Down,
	Left,
	Right
};

enum class MonsterType
{
	Default,
	Pooter,
	Gaper,
	Sucker,
	RoundWorm,
	Clot,
	Clotty,
	Iblob,
	BoomFlyNormal,
	BoomFlyRed,
	Mulliboom,
	HostNormal,
	HostRed,
	FlyNormal,
	FlyRed,
	Max,
};

enum class RoomType
{
	Default,
	Treasure,
	Boss,
	Shop,
	Max,
};

enum class PassiveType
{
	Default,
	Item001,

	Max,
};

enum class ActiveType
{
	Default,
	Item034,
	Item036,
	Item045,

	Max,
};

enum class BossType
{
	Default,
	Monstro,

	Max,
};

enum class ShopType
{
	Default,
	Passive,
	Bomb, 
	Key,
	Heart,
	Max,
};