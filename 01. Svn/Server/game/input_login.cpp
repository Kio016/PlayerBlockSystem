// Add includes:
#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
#include "player_block.h"
#endif

// Search:
	if (g_noticeBattleZone)
	{
		if (FN_is_battle_zone(ch))
		{
			ch->ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("�� �ʿ��� �������� ������ ������ �� �ֽ��ϴ�."));
			ch->ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("�� ���׿� �������� ������"));
			ch->ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("������ �ּ� �� �μ����� ���ư��ñ� �ٶ��ϴ�."));
		}
	}

// Add below:
#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
	CPlayerBlock::Instance().LoadPlayerBlockList(ch);
#endif