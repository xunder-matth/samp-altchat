#include < a_samp >
#include "altchat.inc"

main() { 
	
}

public OnPlayerCommandText(playerid, cmdtext[]) {
	if (!strcmp(cmdtext, "/state", true)) {
		new buffer[128];

		format(buffer, sizeof buffer, "Created = %d", IsPlayerAltChatCreated(playerid));
		SendClientMessage(playerid, -1, buffer);
		format(buffer, sizeof buffer, "Shown = %d", IsPlayerAltChatShown(playerid));
		SendClientMessage(playerid, -1, buffer);
	} else if (!strcmp(cmdtext, "/create", true)) {
		new buffer[128];

		format(buffer, sizeof buffer, "Create = %d", CreatePlayerAltChat(playerid));
		SendClientMessage(playerid, -1, buffer);
	} else if (!strcmp(cmdtext, "/destroy", true)) {
		new buffer[128];

		format(buffer, sizeof buffer, "Destroy = %d", DestroyPlayerAltChat(playerid));
		SendClientMessage(playerid, -1, buffer);
	} else if (!strcmp(cmdtext, "/show", true)) {
		new buffer[128];

		format(buffer, sizeof buffer, "Show = %d", TogglePlayerAltChat(playerid, true));
		SendClientMessage(playerid, -1, buffer);
	} else if (!strcmp(cmdtext, "/hide", true)) {
		new buffer[128];

		format(buffer, sizeof buffer, "Hide = %d", TogglePlayerAltChat(playerid, false));
		SendClientMessage(playerid, -1, buffer);
	} else if (!strcmp(cmdtext, "/sendmsg", true)) {
		static count = 0;
		new buffer[128],
			message[128];

		format(message, sizeof message, "Random message No. %d", (count ++));

		format(buffer, sizeof buffer, "Sent = %d", SendPlayerAltMessage(playerid, message));
		SendClientMessage(playerid, -1, buffer);
	}
	return 1;
}
