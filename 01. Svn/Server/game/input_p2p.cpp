// Add includes:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
#include "player_block.h"
#endif

// Search:

    FuncShout(const char* str, BYTE bEmpire, DWORD dwPID) : m_str(str), m_bEmpire(bEmpire)

 // Change:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
	const char* m_szName;
	FuncShout(const char* str, BYTE bEmpire, const char* szName) : m_str(str), m_bEmpire(bEmpire), m_szName(szName)
#else
	FuncShout(const char* str, BYTE bEmpire, DWORD dwPID) : m_str(str), m_bEmpire(bEmpire)
#endif

// Search:

		d->GetCharacter()->ChatPacket(CHAT_TYPE_SHOUT, "%s", m_str);

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

void SendShout(const char* szText, BYTE bEmpire)

// Change:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
void SendShout(const char* szText, BYTE bEmpire, const char* szName)
#else
void SendShout(const char* szText, BYTE bEmpire)
#endif

// Search:

	std::for_each(c_ref_set.begin(), c_ref_set.end(), FuncShout(szText, bEmpire));

// Change:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
	std::for_each(c_ref_set.begin(), c_ref_set.end(), FuncShout(szText, bEmpire, szName));
#else
	std::for_each(c_ref_set.begin(), c_ref_set.end(), FuncShout(szText, bEmpire));
#endif

// Search:

	SendShout(p->szText, p->bEmpire);

// Change:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
	SendShout(p->szText, p->bEmpire, p->szName);
#else
	SendShout(p->szText, p->bEmpire);
#endif

// Search:

	MessengerManager::instance().__RemoveFromList(p->szAccount, p->szCompanion);

// Add below:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
	auto tch = CHARACTER_MANAGER::Instance().FindPC(p->szCompanion);
	auto pkCCI = P2P_MANAGER::Instance().Find(p->szCompanion);

	if (tch || pkCCI)
		MessengerManager::instance().__RemoveFromList(p->szCompanion, p->szAccount, true);
#endif

// Search:

int CInputP2P::Analyze(LPDESC d, BYTE bHeader, const char* c_pData)

// Add above:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
auto CInputP2P::PlayerBlock(const char* c_pData) -> void
{
	auto p = (TPacketGGPlayerBlock*)c_pData;
	auto& rkPlayerBlockMgr = CPlayerBlock::Instance();

	switch(p->type)
	{
		case PLAYER_BLOCK_TYPE_ADD:
		{
			if (rkPlayerBlockMgr.IsPlayerBlock(p->szBlockingPlayerName, p->szBlockedPlayerName))
			{
				sys_err("(%s, %s) - Block Player is already in list - channel: %d", p->szBlockingPlayerName, p->szBlockedPlayerName, g_bChannel);
				return;
			}

			rkPlayerBlockMgr.BlockPlayer(p->szBlockingPlayerName, p->szBlockedPlayerName, true);
		}
		break;

		case PLAYER_BLOCK_TYPE_REMOVE:
		{
			if (!rkPlayerBlockMgr.IsPlayerBlock(p->szBlockingPlayerName, p->szBlockedPlayerName))
			{
				sys_err("(%s, %s) - Block Player is not in list - channel: %d", p->szBlockingPlayerName, p->szBlockedPlayerName, g_bChannel);
				return;
			}

			rkPlayerBlockMgr.UnBlockPlayer(p->szBlockingPlayerName, p->szBlockedPlayerName, true);
		}
		break;
	}
}
#endif

// Search:

	case HEADER_GG_CHECK_AWAKENESS:
		IamAwake(d, c_pData);
		break;

// Add below:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
	case HEADER_GG_PLAYER_BLOCK:
		PlayerBlock(c_pData);
		break;
#endif