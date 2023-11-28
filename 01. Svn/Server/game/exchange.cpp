// Add includes:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
#include "player_block.h"
#endif

// Search:

	if (victim->IsBlockMode(BLOCK_EXCHANGE))
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("������ ��ȯ �ź� �����Դϴ�."));
		return false;
	}

// Add below:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
	auto& rkPlayerBlockMgr = CPlayerBlock::Instance();
	if (rkPlayerBlockMgr.IsPlayerBlock(GetName(), victim->GetName()))
	{
		ChatPacket(CHAT_TYPE_INFO, "You cannot send a trade request to the player you have blocked.");
		return false;
	}
	else if (rkPlayerBlockMgr.IsPlayerBlock(victim->GetName(), GetName()))
	{
		ChatPacket(CHAT_TYPE_INFO, "The player has blocked you.");
		return false;
	}
#endif