# Search:

		self.serverCommander=stringCommander.Analyzer()

# Add above:

		if app.ENABLE_PLAYER_BLOCK_SYSTEM:
			serverCommandList["RemoveFriend"] = self.RemoveFriend

# At the end of the file:

	if app.ENABLE_PLAYER_BLOCK_SYSTEM:
		def RemoveFriend(self, name):
			self.interface.RemoveFriend(name)