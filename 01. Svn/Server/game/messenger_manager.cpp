// Search:

void MessengerManager::__RemoveFromList(MessengerManager::keyA account, MessengerManager::keyA companion)
{
	m_Relation[account].erase(companion);
	m_InverseRelation[companion].erase(account);

	LPCHARACTER ch = CHARACTER_MANAGER::instance().FindPC(account.c_str());
	LPDESC d = ch ? ch->GetDesc() : NULL;

	if (d)
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<메신져> %s 님을 메신저에서 삭제하였습니다."), companion.c_str());
}

// Change:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
void MessengerManager::__RemoveFromList(MessengerManager::keyA account, MessengerManager::keyA companion, bool isComp)
{
	m_Relation[account].erase(companion);
	m_InverseRelation[companion].erase(account);

	LPCHARACTER ch = CHARACTER_MANAGER::instance().FindPC(account.c_str());

	if (ch)
	{
		if (!isComp)
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<메신져> %s 님을 메신저에서 삭제하였습니다."), companion.c_str());
		else
			ch->ChatPacket(CHAT_TYPE_COMMAND, "RemoveFriend %s", companion.c_str());
	}
}
#else
void MessengerManager::__RemoveFromList(MessengerManager::keyA account, MessengerManager::keyA companion)
{
	m_Relation[account].erase(companion);
	m_InverseRelation[companion].erase(account);

	LPCHARACTER ch = CHARACTER_MANAGER::instance().FindPC(account.c_str());
	LPDESC d = ch ? ch->GetDesc() : NULL;

	if (d)
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<메신져> %s 님을 메신저에서 삭제하였습니다."), companion.c_str());
}
#endif

// Search:

	DBManager::instance().Query("DELETE FROM messenger_list%s WHERE account='%s' AND companion = '%s'",
		get_table_postfix(), __account, __companion, __companion, __account);

	__RemoveFromList(account, companion);

// Change:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
	DBManager::instance().Query("DELETE FROM messenger_list%s WHERE account='%s' AND companion = '%s' OR account='%s' AND companion = '%s'",
		get_table_postfix(), __account, __companion, __companion, __account);

	__RemoveFromList(account, companion);
	__RemoveFromList(companion, account, true);
#else
	DBManager::instance().Query("DELETE FROM messenger_list%s WHERE account='%s' AND companion = '%s'",
		get_table_postfix(), __account, __companion, __companion, __account);

	__RemoveFromList(account, companion);
#endif