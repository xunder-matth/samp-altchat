#include < a_samp >
#include "altchat.inc"

main() { 
	
}

public OnPlayerConnect(playerid) {
	SetSpawnInfo(playerid, 0, 0, 0.0, 0.0, 5.0, 0.0, 0, 0, 0, 0, 0, 0);
	SpawnPlayer(playerid);
	return 1;
}

public OnPlayerCommandText(playerid, cmdtext[]) {
	if (!strcmp(cmdtext, "/state", true)) {
		new buffer[128];

		format(buffer, sizeof buffer, "Created = %d", AltChat_IsPlayerCreated(playerid));
		SendClientMessage(playerid, -1, buffer);
		format(buffer, sizeof buffer, "Shown = %d", AltChat_IsPlayerShown(playerid));
		SendClientMessage(playerid, -1, buffer);
	} else if (!strcmp(cmdtext, "/create", true)) {
		new buffer[128];

		format(buffer, sizeof buffer, "Create = %d", AltChat_CreatePlayer(playerid));
		SendClientMessage(playerid, -1, buffer);
	} else if (!strcmp(cmdtext, "/destroy", true)) {
		new buffer[128];

		format(buffer, sizeof buffer, "Destroy = %d", AltChat_DestroyPlayer(playerid));
		SendClientMessage(playerid, -1, buffer);
	} else if (!strcmp(cmdtext, "/show", true)) {
		new buffer[128];

		format(buffer, sizeof buffer, "Show = %d", AltChat_TogglePlayer(playerid, true));
		SendClientMessage(playerid, -1, buffer);
	} else if (!strcmp(cmdtext, "/hide", true)) {
		new buffer[128];

		format(buffer, sizeof buffer, "Hide = %d", AltChat_TogglePlayer(playerid, false));
		SendClientMessage(playerid, -1, buffer);
	} else if (!strcmp(cmdtext, "/sendmsg", true)) {
		static count = 0;
		new buffer[128],
			message[128];

		format(message, sizeof message, "Random message No. %d", (count ++));

		format(buffer, sizeof buffer, "Sent = %d", AltChat_SendPlayer(playerid, message));
		SendClientMessage(playerid, -1, buffer);
	}
	return 1;
}
