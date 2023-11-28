# Search:

	def EmptyFunction(self):
		pass

# Add below:

	if app.ENABLE_PLAYER_BLOCK_SYSTEM:
		def RemoveFriend(self, name):
			self.wndMessenger.OnRemoveList(0, name)