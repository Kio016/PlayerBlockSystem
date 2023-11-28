// Search:

void CPythonMessenger::Destroy()
{
	m_FriendNameMap.clear();
	m_GuildMemberStateMap.clear();
}

// Add Above:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
auto CPythonMessenger::OnPlayerBlock(const char* c_szName) -> void
{
	if (m_poMessengerHandler)
		PyCallClassMemberFunc(m_poMessengerHandler, "OnAddBlockList", Py_BuildValue("(is)", MESSENGER_GRUOP_INDEX_BLOCK, c_szName));
}
#endif