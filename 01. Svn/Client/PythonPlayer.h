//Search:

private:
	std::map<DWORD, DWORD> m_kMap_dwAffectIndexToSkillIndex;

// Add below:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
public:
	auto AddPlayerBlock(const std::string& strBlockedPlayerName) -> void;
	auto RemovePlayerBlock(const std::string& strBlockedPlayerName) -> void;

	auto IsPlayerBlock(const std::string& strBlockedPlayerName) -> bool;

protected:
	std::set<std::string> m_PlayerBlockSet;
#endif