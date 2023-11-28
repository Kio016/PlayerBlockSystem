// Search:

	void	__RemoveFromList(keyA account, keyA companion);

// Change:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
	void	__RemoveFromList(keyA account, keyA companion, bool isComp = false);
#else
	void	__RemoveFromList(keyA account, keyA companion);
#endif