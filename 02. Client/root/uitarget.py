# Search:

		self.buttonDict[localeInfo.TARGET_BUTTON_FRIEND].SetEvent(ui.__mem_func__(self.OnAppendToMessenger))

# Add below:

		if app.ENABLE_PLAYER_BLOCK_SYSTEM:
			self.buttonDict[localeInfo.TARGET_BUTTON_BLOCK].SAFE_SetEvent(self.__OnPlayerBlock)

# Search:

	def __OnVoteBlockChat(self):
		cmd = "/vote_block_chat %s" % (self.nameString)
		net.SendChatPacket(cmd)

# Add below:

	if app.ENABLE_PLAYER_BLOCK_SYSTEM:
		def __OnPlayerBlock(self):
			net.SendChatPacket("/block_player %s" % (self.nameString))

# Search:

		if not messenger.IsFriendByName(self.nameString):
			self.__ShowButton(localeInfo.TARGET_BUTTON_FRIEND)

# Add below:

		if app.ENABLE_PLAYER_BLOCK_SYSTEM:
			if player.IsPlayerBlock(self.vid):
				self.__HideButton(localeInfo.TARGET_BUTTON_BLOCK)
			else:
				self.__ShowButton(localeInfo.TARGET_BUTTON_BLOCK)