// Add includes

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
#include "player_block.h"
#endif

// Search:

	if (leader->IsBlockMode(BLOCK_PARTY_REQUEST))
		return false;

// Add below:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
	auto& rkPlayerBlockMgr = CPlayerBlock::Instance();
	if (rkPlayerBlockMgr.IsPlayerBlock(GetName(), leader->GetName()))
	{
		ChatPacket(CHAT_TYPE_INFO, "You cannot send a group request to the player you have blocked.");
		return false;
	}
	else if (rkPlayerBlockMgr.IsPlayerBlock(leader->GetName(), GetName()))
	{
		ChatPacket(CHAT_TYPE_INFO, "The player has blocked you.");
		return false;
	}
#endif

// Search:

	if (GetParty() && GetParty()->GetLeaderPID() != GetPlayerID())
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<��Ƽ> ��Ƽ���� �ʴ��� �� �ִ� ������ �����ϴ�."));
		return;
	}
	else if (pchInvitee->IsBlockMode(BLOCK_PARTY_INVITE))
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<��Ƽ> %s ���� ��Ƽ �ź� �����Դϴ�."), pchInvitee->GetName());
		return;
	}

// Add below:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
	auto& rkPlayerBlockMgr = CPlayerBlock::Instance();
	if (rkPlayerBlockMgr.IsPlayerBlock(GetName(), pchInvitee->GetName()))
	{
		ChatPacket(CHAT_TYPE_INFO, "You cannot send a group invite to the player you have blocked.");
		return;
	}
	else if (rkPlayerBlockMgr.IsPlayerBlock(pchInvitee->GetName(), GetName()))
	{
		ChatPacket(CHAT_TYPE_INFO, "The player has blocked you.");
		return;
	}
#endif