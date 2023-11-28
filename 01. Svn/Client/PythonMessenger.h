// Search:

		MESSENGER_GRUOP_INDEX_GUILD,

// Add below:
#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
		MESSENGER_GRUOP_INDEX_BLOCK,
#endif

// Search:
	void RefreshGuildMember();

// Add below:
#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
	auto OnPlayerBlock(const char* c_szName) -> void;
#endif