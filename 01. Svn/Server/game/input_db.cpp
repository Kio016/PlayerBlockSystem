// Add includes:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
#include "player_block.h"
#endif

// Search:

	signal_timer_enable(30);

// Add below:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
	CPlayerBlock::Instance().BootPlayerBlockList();
#endif