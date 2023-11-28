# Search:
	IMAGE_FILE_NAME = {	"ONLINE" : "d:/ymir work/ui/game/windows/messenger_list_online.sub",
						"OFFLINE" : "d:/ymir work/ui/game/windows/messenger_list_offline.sub", }

# Add below:

	if app.ENABLE_PLAYER_BLOCK_SYSTEM:
		IMAGE_FILE_NAME["BLOCK"] = "d:/ymir work/ui/game/windows/messenger_list_block.png"

# Search:

	def Offline(self):
		self.image.LoadImage(self.IMAGE_FILE_NAME["OFFLINE"])
		self.state = self.STATE_OFFLINE

# Add below:

	if app.ENABLE_PLAYER_BLOCK_SYSTEM:
		def BlockItemIcon(self):
			self.image.LoadImage(self.IMAGE_FILE_NAME["BLOCK"])

# Search:

	def OnRemove(self):
		net.SendGuildRemoveMemberPacket(self.key)
		return True

# Add below:

if app.ENABLE_PLAYER_BLOCK_SYSTEM:
	class MessengerBlockItem(MessengerMemberItem):
		def __init__(self, getParentEvent):
			MessengerMemberItem.__init__(self, getParentEvent)

		def CanRemove(self):
			return True

		def OnRemove(self):
			net.SendChatPacket("/unblock_player %s" % (self.key))
			return True

# Search:

class MessengerGuildGroup(MessengerGroupItem):

	def __init__(self, getParentEvent):
		MessengerGroupItem.__init__(self, getParentEvent)
		self.SetName(localeInfo.MESSENGER_GUILD)
		self.AddFlag("float")

	def AppendMember(self, key, name):
		item = MessengerGuildItem(self.getParentEvent)
		return MessengerGroupItem.AppendMember(self, item, key, name)

# Add below:

if app.ENABLE_PLAYER_BLOCK_SYSTEM:
	class MessengerBlockGroup(MessengerGroupItem):
		def __init__(self, getParentEvent):
			MessengerGroupItem.__init__(self, getParentEvent)
			self.SetName(localeInfo.MESSENGER_BLOCK)

		def AppendMember(self, key, name):
			item = MessengerBlockItem(self.getParentEvent)
			return MessengerGroupItem.AppendMember(self, item, key, name)

# Search:

			self.addFriendButton = self.GetChild("AddFriendButton")

# Add below:

			if app.ENABLE_PLAYER_BLOCK_SYSTEM:
				self.playerBlockButton = self.GetChild("PlayerBlockButton")

# Search:

		self.addFriendButton.SetEvent(ui.__mem_func__(self.OnPressAddFriendButton))

# Add below:

			self.playerBlockButton.SetEvent(ui.__mem_func__(self.OnPressPlayerBlockButton))

# Search:

        self.whisperButton.SetPosition(-20, 30)
        self.removeButton.SetPosition(20, 30)
        self.guildButton.SetPosition(60, 30)

# Change:

		if app.ENABLE_PLAYER_BLOCK_SYSTEM:
			self.playerBlockButton.SetPosition(-30, 30)
			self.whisperButton.SetPosition(0, 30)
			self.removeButton.SetPosition(30, 30)
			self.guildButton.SetPosition(60, 30)
		else:
			self.whisperButton.SetPosition(-20, 30)
			self.removeButton.SetPosition(20, 30)
			self.guildButton.SetPosition(60, 30)

# Search:

		self.removeButton = None

# Add below:

		if app.ENABLE_PLAYER_BLOCK_SYSTEM:
			self.playerBlockBoard = None

# Search:

		member = MessengerGuildGroup(ui.__mem_func__(self.GetSelf))
		member.Open()
		member.Show()
		self.groupList.append(member)

# Add below:

		if app.ENABLE_PLAYER_BLOCK_SYSTEM:
			member = MessengerBlockGroup(ui.__mem_func__(self.GetSelf))
			member.Open()
			member.Show()
			self.groupList.append(member)

# Search:

	def OnCancelAddFriend(self):
		self.friendNameBoard.Close()
		self.friendNameBoard = None
		return True

# Add below:

	if app.ENABLE_PLAYER_BLOCK_SYSTEM:
		def OnPressPlayerBlockButton(self):
			playerBlockBoard = uiCommon.InputDialog()
			playerBlockBoard.SetTitle(localeInfo.MESSENGER_PLAYER_BLOCK)
			playerBlockBoard.SetAcceptEvent(ui.__mem_func__(self.OnPlayerBlock))
			playerBlockBoard.SetCancelEvent(ui.__mem_func__(self.OnCancelPlayerBlock))
			playerBlockBoard.Open()
			self.playerBlockBoard = playerBlockBoard
	
		def OnPlayerBlock(self):
			text = self.playerBlockBoard.GetText()
			if text:
				net.SendChatPacket("/block_player %s" % (text))
			self.playerBlockBoard.Close()
			self.playerBlockBoard = None
			return True
		
		def OnCancelPlayerBlock(self):
			self.playerBlockBoard.Close()
			self.playerBlockBoard = None
			return True

# Search:

	def __AddList(self, groupIndex, key, name):
		group = self.groupList[groupIndex]
		member = group.FindMember(key)
		if not member:
			member = group.AppendMember(key, name)
			self.OnSelectItem(None)
		return member

# Add below:

	if app.ENABLE_PLAYER_BLOCK_SYSTEM:
		def OnAddBlockList(self, groupIndex, name):
			group = self.groupList[0] # 0 -> group friend
			member = group.FindMember(name)
			if member:
				group.RemoveMember(member)

			group = self.groupList[groupIndex]
			member = group.FindMember(name)

			if not member:
				member = group.AppendMember(name, name)
				self.OnSelectItem(None)

			member.SetName(name)
			member.BlockItemIcon()
			self.OnRefreshList()