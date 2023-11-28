// Search:

extern void SendShout(const char *szText, BYTE bEmpire);

// Change:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
extern void SendShout(const char *szText, BYTE bEmpire, const char *szName);
#else
extern void SendShout(const char *szText, BYTE bEmpire);
#endif

// Search:

	void		IamAwake(LPDESC d, const char* c_pData);

// Add below:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
	auto		PlayerBlock(const char* c_pData) -> void;
#endif