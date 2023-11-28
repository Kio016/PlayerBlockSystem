// Search:
struct command_info cmd_info[] =

// Add above:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
ACMD(do_block_player);
ACMD(do_unblock_player);
#endif

// Search:

{ "\n",		NULL,			0,			POS_DEAD,	GM_IMPLEMENTOR	}

// Add above:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
	{ "block_player", do_block_player, 0, POS_DEAD, GM_PLAYER },
	{ "unblock_player", do_unblock_player, 0, POS_DEAD, GM_PLAYER },
#endif