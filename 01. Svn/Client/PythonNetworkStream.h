//Search:

	void __BettingGuildWar_SetBettingMoney(UINT uBettingMoney);

// Add below:
#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
public:
	auto RecvPlayerBlockPacket() -> bool;
#endif