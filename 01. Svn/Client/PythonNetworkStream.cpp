//Search:
		Set(HEADER_GC_DRAGON_SOUL_REFINE, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCDragonSoulRefine), STATIC_SIZE_PACKET));

//Add below:
#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
		Set(HEADER_GC_PLAYER_BLOCK, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCPlayerBlock), DYNAMIC_SIZE_PACKET));
#endif