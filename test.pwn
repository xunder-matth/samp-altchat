#include < a_samp >
#include < Pawn.CMD >
#include < altchat >

main() { 
	print("[INC] Alt chat by Xunder > Test");
}

public OnGameModeInit() {
	SetGameModeText("Testing testing");
	return 1;
}

public OnPlayerSpawn(playerid) {
	SetPlayerPos(playerid, 0.0, 0.0, 3.0);
	return 1;
}

CMD:create(playerid, params[]) {
	CreatePlayerAltChat(playerid);
	SendClientMessage(playerid, -1, "Alt chat created.");
	return 1;
}

CMD:destroy(playerid, params[]) {
	DestroyPlayerAltChat(playerid);
	SendClientMessage(playerid, -1, "Alt chat destroyed.");
	return 1;
}

CMD:show(playerid, params[]) {
	if (TogglePlayerAltChat(playerid, true)) SendClientMessage(playerid, -1, "Alt chat enabled.");
	else SendClientMessage(playerid, -1, "You must create alt chat first.");
	return 1;
}

CMD:hide(playerid, params[]) {
	if (TogglePlayerAltChat(playerid, false)) SendClientMessage(playerid, -1, "Alt chat disabled.");
	else SendClientMessage(playerid, -1, "You must create alt chat first.");
	return 1;
}

CMD:status(playerid, params[]) {
	if (IsPlayerAltChatEnabled(playerid)) SendClientMessage(playerid, -1, "Alt chat is enabled.");
	else SendClientMessage(playerid, -1, "Alt chat is disabled.");
	return 1;
}

CMD:send(playerid, params[]) {
	SendPlayerAltMessage(playerid, params);
	return 1;
}

CMD:spawn(playerid, params[]) {
	return SpawnPlayer(playerid);
}