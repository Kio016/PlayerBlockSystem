// Search:

	//HYBRID CRYPT
	HEADER_GC_HYBRIDCRYPT_KEYS = 152,
	HEADER_GC_HYBRIDCRYPT_SDB = 153, // SDB means Supplmentary Data Blocks
	//HYBRID CRYPT

// Add below:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
	HEADER_GC_PLAYER_BLOCK = 161,
#endif

// Search:

	HEADER_GG_CHECK_AWAKENESS = 29,

// Add below:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
	HEADER_GG_PLAYER_BLOCK = 34,
#endif

// Search:

typedef struct SPacketGGShout
{
	BYTE	bHeader;
	BYTE	bEmpire;
	char	szText[CHAT_MAX_LEN + 1];
} TPacketGGShout;

// Change:

typedef struct SPacketGGShout
{
	BYTE	bHeader;
	BYTE	bEmpire;
#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
	char	szName[CHARACTER_NAME_MAX_LEN + 1];
#endif
	char	szText[CHAT_MAX_LEN + 1];
} TPacketGGShout;

// Search:

#pragma pack()

// Add above:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
enum EPlayerBlockType
{
	PLAYER_BLOCK_TYPE_ADD,
	PLAYER_BLOCK_TYPE_REMOVE,
	PLAYER_BLOCK_TYPE_LOAD
};

typedef struct SPacketGCPlayerBlock
{
	BYTE header;
	WORD size;
	BYTE type;
} TPacketGCPlayerBlock;

typedef struct SPacketGCLoadPlayerBlock
{
	char szName[CHARACTER_NAME_MAX_LEN + 1];
} TPacketGCLoadPlayerBlock;

typedef struct SPacketGGPlayerBlock
{
	BYTE header;
	BYTE type;
	char szBlockingPlayerName[CHARACTER_NAME_MAX_LEN + 1];
	char szBlockedPlayerName[CHARACTER_NAME_MAX_LEN + 1];
} TPacketGGPlayerBlock;
#endif