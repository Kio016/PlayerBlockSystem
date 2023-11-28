//Search:

void CPythonPlayer::Clear()
{

// Add above:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
auto CPythonPlayer::AddPlayerBlock(const std::string& strBlockedPlayerName) -> void
{
	m_PlayerBlockSet.emplace(strBlockedPlayerName);
}

auto CPythonPlayer::RemovePlayerBlock(const std::string& strBlockedPlayerName) -> void
{
	m_PlayerBlockSet.erase(strBlockedPlayerName);
}

auto CPythonPlayer::IsPlayerBlock(const std::string& strBlockedPlayerName) -> bool
{
	auto it = m_PlayerBlockSet.find(strBlockedPlayerName);
	return it != m_PlayerBlockSet.end();
}
#endif

// Search:

	__ClearAutoAttackTargetActorID();

// Add below:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
	m_PlayerBlockSet.clear();
#endif