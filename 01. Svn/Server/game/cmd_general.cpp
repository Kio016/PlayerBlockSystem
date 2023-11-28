// Add includes:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
#include "player_block.h"
#endif

// Search: **if the equipment view system**

	if (tch->IsBlockMode(BLOCK_EQUIPMENT_REQUEST))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("%s is blocked view equipment request."), tch->GetName());
		return;
	}

// Add below:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
	auto& rkPlayerBlockMgr = CPlayerBlock::Instance();
	if (rkPlayerBlockMgr.IsPlayerBlock(ch->GetName(), tch->GetName()))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "You cannot send a profile request to the player you have blocked.");
		return;
	}
	else if (rkPlayerBlockMgr.IsPlayerBlock(tch->GetName(), ch->GetName()))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "The player has blocked you.");
		return;
	}
#endif

// Add at end of file:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
ACMD(do_block_player)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1)
		return;

	auto name = ch->GetName();
	if (name == arg1)
		return;

	auto tch = CHARACTER_MANAGER::Instance().FindPC(arg1);
	auto pkCCI = P2P_MANAGER::Instance().Find(arg1);
	auto& rkPlayerBlockMgr = CPlayerBlock::Instance();

	if (tch || pkCCI)
	{
		if (rkPlayerBlockMgr.IsPlayerBlock(name, arg1))
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "You have already blocked this player.");
			return;
		}

		rkPlayerBlockMgr.BlockPlayer(name, arg1);

		// Go P2P
		TPacketGGPlayerBlock p2p_packet;
		p2p_packet.header = HEADER_GG_PLAYER_BLOCK;
		p2p_packet.type = PLAYER_BLOCK_TYPE_ADD;
		strlcpy(p2p_packet.szBlockingPlayerName, name, sizeof(p2p_packet.szBlockingPlayerName));
		strlcpy(p2p_packet.szBlockedPlayerName, arg1, sizeof(p2p_packet.szBlockedPlayerName));
		P2P_MANAGER::Instance().Send(&p2p_packet, sizeof(p2p_packet));
	}
	else
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("%s 님은 접속되 있지 않습니다."), arg1);
}

ACMD(do_unblock_player)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1)
		return;

	auto name = ch->GetName();
	if (name == arg1)
		return;

	auto& rkPlayerBlockMgr = CPlayerBlock::Instance();
	if (!rkPlayerBlockMgr.IsPlayerBlock(name, arg1))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "The player has not already been blocked.");
		return;
	}

	rkPlayerBlockMgr.UnBlockPlayer(name, arg1);

	// Go P2P
	TPacketGGPlayerBlock p2p_packet;
	p2p_packet.header = HEADER_GG_PLAYER_BLOCK;
	p2p_packet.type = PLAYER_BLOCK_TYPE_REMOVE;
	strlcpy(p2p_packet.szBlockingPlayerName, name, sizeof(p2p_packet.szBlockingPlayerName));
	strlcpy(p2p_packet.szBlockedPlayerName, arg1, sizeof(p2p_packet.szBlockedPlayerName));
	P2P_MANAGER::Instance().Send(&p2p_packet, sizeof(p2p_packet));
}
#endif