// Search:

	Set(HEADER_GG_CHECK_AWAKENESS, sizeof(TPacketGGCheckAwakeness), "CheckAwakeness");

// Add below:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
	Set(HEADER_GG_PLAYER_BLOCK, sizeof(TPacketGGPlayerBlock), "PlayerBlock");
#endif