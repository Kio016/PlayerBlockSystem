// Add includes:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
#include "player_block.h"
#endif

// Search:

			pkDesc = pkCCI->pkDesc;
			pkDesc->SetRelay(pinfo->szNameTo);
			bOpponentEmpire = pkCCI->bEmpire;

// Add above:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
			auto& rkPlayerBlockMgr = CPlayerBlock::Instance();
			if (rkPlayerBlockMgr.IsPlayerBlock(ch->GetName(), pinfo->szNameTo))
			{
				rkPlayerBlockMgr.WhisperPacket(ch->GetDesc(), "You cannot send messages to the player you have blocked.", pinfo->szNameTo);
				return iExtraLen;
			}
			else if (rkPlayerBlockMgr.IsPlayerBlock(pinfo->szNameTo, ch->GetName()))
			{
				rkPlayerBlockMgr.WhisperPacket(ch->GetDesc(), "The player has blocked you.", pinfo->szNameTo);
				return iExtraLen;
			}
#endif

// Search:

		if (ch->IsBlockMode(BLOCK_WHISPER))
		{
			if (ch->GetDesc())
			{
				TPacketGCWhisper pack;
				pack.bHeader = HEADER_GC_WHISPER;
				pack.bType = WHISPER_TYPE_SENDER_BLOCKED;
				pack.wSize = sizeof(TPacketGCWhisper);
				strlcpy(pack.szNameFrom, pinfo->szNameTo, sizeof(pack.szNameFrom));
				ch->GetDesc()->Packet(&pack, sizeof(pack));
			}

// Add below:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
			pkDesc->SetRelay("");
			return iExtraLen;
#endif

// Search:

		else if (pkChr && pkChr->IsBlockMode(BLOCK_WHISPER))
		{
			if (ch->GetDesc())
			{
				TPacketGCWhisper pack;
				pack.bHeader = HEADER_GC_WHISPER;
				pack.bType = WHISPER_TYPE_TARGET_BLOCKED;
				pack.wSize = sizeof(TPacketGCWhisper);
				strlcpy(pack.szNameFrom, pinfo->szNameTo, sizeof(pack.szNameFrom));
				ch->GetDesc()->Packet(&pack, sizeof(pack));
			}

// below:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
			pkDesc->SetRelay("");
			return iExtraLen;
#endif

// Search:

		else
		{
			BYTE bType = WHISPER_TYPE_NORMAL;

// add above:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
		auto& rkPlayerBlockMgr = CPlayerBlock::Instance();
		if (pkChr && rkPlayerBlockMgr.IsPlayerBlock(ch->GetName(), pinfo->szNameTo))
			rkPlayerBlockMgr.WhisperPacket(ch->GetDesc(), "You cannot send messages to the player you have blocked.", pinfo->szNameTo);
		else if (pkChr && rkPlayerBlockMgr.IsPlayerBlock(pinfo->szNameTo, ch->GetName()))
			rkPlayerBlockMgr.WhisperPacket(ch->GetDesc(), "The player has blocked you.", pinfo->szNameTo);
#endif

// Search:

	FEmpireChatPacket(packet_chat& p, const char* chat_msg, int len, BYTE bEmpire, int iMapIndex, int iNameLen)
		: p(p), orig_msg(chat_msg), orig_len(len), bEmpire(bEmpire), iMapIndex(iMapIndex), namelen(iNameLen)

// Change:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
	const char* m_szName;
	FEmpireChatPacket(packet_chat& p, const char* chat_msg, int len, BYTE bEmpire, int iMapIndex, int iNameLen, const char* szName)
		: p(p), orig_msg(chat_msg), orig_len(len), bEmpire(bEmpire), iMapIndex(iMapIndex), namelen(iNameLen), m_szName(szName)
#else
	FEmpireChatPacket(packet_chat& p, const char* chat_msg, int len, BYTE bEmpire, int iMapIndex, int iNameLen)
		: p(p), orig_msg(chat_msg), orig_len(len), bEmpire(bEmpire), iMapIndex(iMapIndex), namelen(iNameLen)
#endif

// Search:

		if (d->GetCharacter()->GetMapIndex() != iMapIndex)
			return;

// Add below:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
		auto& rkPlayerBlockMgr = CPlayerBlock::Instance();
		auto name = d->GetCharacter()->GetName();
		if (name != m_szName)
		{
			if (rkPlayerBlockMgr.IsPlayerBlock(name, m_szName) || rkPlayerBlockMgr.IsPlayerBlock(m_szName, name))
				return;
		}
#endif

// Search:

		p.bHeader = HEADER_GG_SHOUT;
		p.bEmpire = ch->GetEmpire();

// Add below:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
		strlcpy(p.szName, ch->GetName(), sizeof(p.szName));
#endif

// Search:

		SendShout(chatbuf, ch->GetEmpire());

// Change:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
		SendShout(chatbuf, ch->GetEmpire(), ch->GetName());
#else
		SendShout(chatbuf, ch->GetEmpire());
#endif

// Search:

			std::for_each(c_ref_set.begin(), c_ref_set.end(),
				FEmpireChatPacket(pack_chat,
					chatbuf,
					len,
					(ch->GetGMLevel() > GM_PLAYER ||
						ch->IsEquipUniqueGroup(UNIQUE_GROUP_RING_OF_LANGUAGE)) ? 0 : ch->GetEmpire(),
					ch->GetMapIndex(),
					strlen(ch->GetName())
				)
			);

// Change:

			std::for_each(c_ref_set.begin(), c_ref_set.end(),
				FEmpireChatPacket(pack_chat,
					chatbuf,
					len,
					(ch->GetGMLevel() > GM_PLAYER ||
						ch->IsEquipUniqueGroup(UNIQUE_GROUP_RING_OF_LANGUAGE)) ? 0 : ch->GetEmpire(),
					ch->GetMapIndex(), strlen(ch->GetName())
#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
					, ch->GetName()
#endif
					));


// Search:

		if (ch_companion->IsBlockMode(BLOCK_MESSENGER_INVITE))
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("상대방이 메신져 추가 거부 상태입니다."));
			return sizeof(TPacketCGMessengerAddByVID);
		}

// Add below:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
		auto& rkPlayerBlockMgr = CPlayerBlock::Instance();
		if (rkPlayerBlockMgr.IsPlayerBlock(ch->GetName(), ch_companion->GetName()))
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "You cannot send a friend request to the player you have blocked.");
			return sizeof(TPacketCGMessengerAddByVID);
		}
		else if (rkPlayerBlockMgr.IsPlayerBlock(ch_companion->GetName(), ch->GetName()))
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "The player has blocked you.");
			return sizeof(TPacketCGMessengerAddByVID);
		}
#endif

// Search:

			if (tch->IsBlockMode(BLOCK_MESSENGER_INVITE) == true)
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("상대방이 메신져 추가 거부 상태입니다."));

// Change:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
			if (tch->IsBlockMode(BLOCK_MESSENGER_INVITE) == true)
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("상대방이 메신져 추가 거부 상태입니다."));
				return CHARACTER_NAME_MAX_LEN;
			}

			auto& rkPlayerBlockMgr = CPlayerBlock::Instance();
			if (rkPlayerBlockMgr.IsPlayerBlock(ch->GetName(), tch->GetName()))
				ch->ChatPacket(CHAT_TYPE_INFO, "You cannot send a friend request to the player you have blocked.");
			else if (rkPlayerBlockMgr.IsPlayerBlock(tch->GetName(), ch->GetName()))
				ch->ChatPacket(CHAT_TYPE_INFO, "The player has blocked you.");
#else
			if (tch->IsBlockMode(BLOCK_MESSENGER_INVITE) == true)
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("상대방이 메신져 추가 거부 상태입니다."));
#endif

