#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
	PyModule_AddIntConstant(poModule, "ENABLE_PLAYER_BLOCK_SYSTEM", true);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_PLAYER_BLOCK_SYSTEM", false);
#endif