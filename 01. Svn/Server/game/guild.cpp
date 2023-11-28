// Add includes:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
#include "player_block.h"
#endif

// Search:
	GuildJoinErrCode errcode = VerifyGuildJoinableCondition(pchInvitee);

// Add above:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
	auto& rkPlayerBlockMgr = CPlayerBlock::Instance();
	if (rkPlayerBlockMgr.IsPlayerBlock(pchInviter->GetName(), pchInvitee->GetName()))
	{
		pchInviter->ChatPacket(CHAT_TYPE_INFO, "You cannot send a guild invite to the player you have blocked.");
		return;
	}
	else if (rkPlayerBlockMgr.IsPlayerBlock(pchInvitee->GetName(), pchInviter->GetName()))
	{
		pchInviter->ChatPacket(CHAT_TYPE_INFO, "The player has blocked you.");
		return;
	}
#endif