// Add includes:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
#include "player_block.h"
#endif

// Search:

		/* delete messenger list */
		MessengerManager::instance().RemoveAllList(ch->GetName());

// Add below:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
		/* player block list */
		CPlayerBlock::Instance().ChangeName(ch->GetName(), szName);
#endif