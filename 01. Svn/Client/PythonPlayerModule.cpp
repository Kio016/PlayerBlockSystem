//Search:

void initPlayer()
{

// Add above:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
auto playerIsPlayerBlock(PyObject* poSelf, PyObject* poArgs) -> PyObject*
{
	int iVID;
	if (!PyTuple_GetInteger(poArgs, 0, &iVID))
		return Py_BuildException();

	auto pTargetInstance = CPythonCharacterManager::Instance().GetInstancePtr(iVID);
	return Py_BuildValue("i", CPythonPlayer::Instance().IsPlayerBlock(pTargetInstance->GetNameString()));
}
#endif

// Search:

{ "SendDragonSoulRefine",		playerSendDragonSoulRefine,			METH_VARARGS },

// Add below:

#ifdef ENABLE_PLAYER_BLOCK_SYSTEM
		{ "IsPlayerBlock",				playerIsPlayerBlock,				METH_VARARGS },
#endif