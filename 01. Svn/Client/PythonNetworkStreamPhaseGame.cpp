// Search:
		default:
			ret = RecvDefaultPacket(header);
			break;

// Add Above:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
		case HEADER_GC_PLAYER_BLOCK:
			ret = RecvPlayerBlockPacket();
			break;
#endif

// At end of file

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
auto CPythonNetworkStream::RecvPlayerBlockPacket() -> bool
{
	TPacketGCPlayerBlock PlayerBlockPacket;
	if (!Recv(sizeof(PlayerBlockPacket), &PlayerBlockPacket))
		return false;

	int iPacketSize = PlayerBlockPacket.size - sizeof(PlayerBlockPacket);
	char buf[CHARACTER_NAME_MAX_LEN + 1];

	switch (PlayerBlockPacket.type)
	{
		case PLAYER_BLOCK_TYPE_ADD:
		{
			if (!Recv(iPacketSize, &buf))
				return false;

			buf[iPacketSize] = '\0';
			CPythonPlayer::Instance().AddPlayerBlock(buf);
			CPythonMessenger::Instance().OnPlayerBlock(buf);
			__RefreshTargetBoardByName(buf);
		}
		break;

		case PLAYER_BLOCK_TYPE_REMOVE:
		{
			if (!Recv(iPacketSize, &buf))
				return false;

			buf[iPacketSize] = '\0';
			CPythonPlayer::Instance().RemovePlayerBlock(buf);
			__RefreshTargetBoardByName(buf);
		}
		break;

		case PLAYER_BLOCK_TYPE_LOAD:
		{
			TPacketGCLoadPlayerBlock load_player_block_packet;
			while (iPacketSize)
			{
				if (!Recv(sizeof(load_player_block_packet), &load_player_block_packet))
					return false;

				CPythonPlayer::Instance().AddPlayerBlock(load_player_block_packet.szName);
				CPythonMessenger::Instance().OnPlayerBlock(load_player_block_packet.szName);
				iPacketSize -= sizeof(load_player_block_packet);
			}
		}
		break;
	}

	return true;
}
#endif