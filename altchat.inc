#if !defined _INC_alt_chat
	#define _INC_alt_chat
#else
	#endinput
#endif

#if !defined _samp_included
	#error Include \"a_samp\" first.
#endif

// Thanks Y_Less!
#define __ALTCHAT_STATIC_ENUM enum

#if (__Pawn & 0x0F) >= 0x0A
	#if __PawnBuild >= 2
		#undef __ALTCHAT_STATIC_ENUM
		#define __ALTCHAT_STATIC_ENUM static enum
	#endif
#endif

#if !defined MAX_ALTCHAT_LINES
	#define MAX_ALTCHAT_LINES									(15)
#endif

#if !defined DEFAULT_ALTCHAT_LINES
	#define DEFAULT_ALTCHAT_LINES								(10)
#endif

#if !defined INVALID_PLAYER_TEXT_DRAW
	#define INVALID_PLAYER_TEXT_DRAW							(PlayerText:0xFFFF)
#endif

#define MAX_ALT_CHAT_MESSAGE_LEN								(128)

#if !defined isnull
	#define isnull(%0) \
		((%0[(%0[0])=='\1'])=='\0')
#endif

__ALTCHAT_STATIC_ENUM e_ALTCHAT_STATES (<<=1) {
	ALTCHAT_STATE_NONE = 0,
	ALTCHAT_STATE_CREATED = 1,
	ALTCHAT_STATE_SHOWN
};

static PlayerText:altchat_gs_AltChatPTD[MAX_PLAYERS][MAX_ALTCHAT_LINES];
static altchat_gs_AltChatText[MAX_PLAYERS][MAX_ALTCHAT_LINES][MAX_ALT_CHAT_MESSAGE_LEN char];
static e_ALTCHAT_STATES:altchat_gs_AltChatState[MAX_PLAYERS] = { ALTCHAT_STATE_NONE, ... };
static altchat_gs_AltChatLines[MAX_PLAYERS];

stock CreatePlayerAltChat(playerid, lines = DEFAULT_ALTCHAT_LINES) {
	if (!IsPlayerConnected(playerid)) {
		return 0;
	}

	if (IsPlayerAltChatCreated(playerid)) {
		return 0;
	}

	if (lines <= 0) {
		return 0;
	}

	if (lines > MAX_ALTCHAT_LINES) {
		lines = MAX_ALTCHAT_LINES;
		printf("[altchat.inc] Warning: \"CreatePlayerAltChat\" called with \"lines = %d\". Defaulting to \"MAX_ALTCHAT_LINES\" (%d).");
	}

	altchat_gs_AltChatLines[playerid] = lines;

	static const emptyString[MAX_ALT_CHAT_MESSAGE_LEN char] = !" ";

	for(new i = 0, PlayerText: textdrawid; i != lines; ++ i) {
		textdrawid = altchat_gs_AltChatPTD[playerid][i] = CreatePlayerTextDraw(playerid, 35.599971, 323.653813 - (10.453385 * i), " "); // Empty textdraw string causing SA-MP to crash :/

		if (textdrawid == INVALID_PLAYER_TEXT_DRAW) {
			altchat_gs_AltChatLines[playerid] = i;
			printf("[altchat.inc] Warning: \"CreatePlayerTextDraw\" is returning invalid TextDraw ID in \"CreatePlayerAltChat\". Created %d lines.", i);
			break;
		}

		PlayerTextDrawLetterSize(playerid, textdrawid, 0.209600, 1.137066);
		PlayerTextDrawAlignment(playerid, textdrawid, 1);
		PlayerTextDrawColor(playerid, textdrawid, -1);
		PlayerTextDrawSetShadow(playerid, textdrawid, 0);
		PlayerTextDrawSetOutline(playerid, textdrawid, 1);
		PlayerTextDrawBackgroundColor(playerid, textdrawid, 255);
		PlayerTextDrawFont(playerid, textdrawid, 1);
		PlayerTextDrawSetProportional(playerid, textdrawid, 1);
		PlayerTextDrawSetShadow(playerid, textdrawid, 0);

		altchat_gs_AltChatText[playerid][i] = emptyString;
	}

	// If lines created are 0 and we call other functions they will stuck in infinite loop so we must check if created lines are not 0 and then set state to "CREATED"
	if (altchat_gs_AltChatLines[playerid]) {
		altchat_gs_AltChatState[playerid] = ALTCHAT_STATE_CREATED;
	}
	return 1;
}

stock DestroyPlayerAltChat(playerid) {
	if (!IsPlayerConnected(playerid)) {
		return 0;
	}

	if (!IsPlayerAltChatCreated(playerid)) {
		return 0;
	}

	new lines = altchat_gs_AltChatLines[playerid];

	for(new i = 0; i != lines; ++ i) {
		PlayerTextDrawDestroy(playerid, altchat_gs_AltChatPTD[playerid][i]);
	}

	altchat_gs_AltChatState[playerid] = ALTCHAT_STATE_NONE;
	return 1;
}

stock TogglePlayerAltChat(playerid, bool:toggle) {
	if (!IsPlayerConnected(playerid)) {
		return 0;
	}

	if (!IsPlayerAltChatCreated(playerid)) {
		return 0;
	}
	
	new shown = IsPlayerAltChatShown(playerid), lines = altchat_gs_AltChatLines[playerid];

	if (toggle && !shown) {
		for(new i = 0; i != lines; ++ i) {	
			PlayerTextDrawShow(playerid, altchat_gs_AltChatPTD[playerid][i]);
		}

		altchat_gs_AltChatState[playerid] ^= ALTCHAT_STATE_SHOWN;
	} else if (!toggle && shown) {
		for(new i = 0; i != lines; ++ i) {	
			PlayerTextDrawHide(playerid, altchat_gs_AltChatPTD[playerid][i]);
		}

		altchat_gs_AltChatState[playerid] ^= ALTCHAT_STATE_SHOWN;
	}
	return 1;
}

stock SendPlayerAltChatMessage(playerid, const message[]) {
	if (!IsPlayerConnected(playerid)) {
		return 0;
	}
	
	if (!IsPlayerAltChatCreated(playerid) || !IsPlayerAltChatShown(playerid)) {
		return 0;
	}

	if (isnull(message)) {
		print("[altchat.inc] Error: \"message\" argument is empty (NULL) in \"SendPlayerAltChatMessage\", aborting.");
		return 0;
	}

	new lines = altchat_gs_AltChatLines[playerid];

	for(new i = lines - 1; i != 0; -- i) {
		altchat_gs_AltChatText[playerid][i] = altchat_gs_AltChatText[playerid][i - 1];
		PlayerTextDrawSetString(playerid, altchat_gs_AltChatPTD[playerid][i], altchat_gs_AltChatText[playerid][i]);
	}

	strpack(altchat_gs_AltChatText[playerid][0], message, MAX_ALT_CHAT_MESSAGE_LEN char);
	PlayerTextDrawSetString(playerid, altchat_gs_AltChatPTD[playerid][0], message);
	return 1;
}

#if defined _INC_y_va
	stock va_SendPlayerAltChatMessage(playerid, const fmat[], GLOBAL_TAG_TYPES:...) {
		if (numargs() == 2) {
			return SendPlayerAltChatMessage(playerid, fmat);
		} else {
			new message[MAX_ALT_CHAT_MESSAGE_LEN];

			return format(message, sizeof message, fmat, ___(2)), 
				SendPlayerAltChatMessage(playerid, message);
		}
	}
#endif

stock IsPlayerAltChatCreated(playerid) {
	if (!IsPlayerConnected(playerid)) {
		return 0;
	}
	
	return (altchat_gs_AltChatState[playerid] & ALTCHAT_STATE_CREATED);
}

stock IsPlayerAltChatShown(playerid) {
	if (!IsPlayerConnected(playerid)) {
		return 0;
	}
	
	return (altchat_gs_AltChatState[playerid] & ALTCHAT_STATE_SHOWN);
}

#if defined _INC_y_hooks
	hook OnPlayerConnect(playerid) {
#else 
	public OnPlayerConnect(playerid) {
#endif
	altchat_gs_AltChatState[playerid] = ALTCHAT_STATE_NONE;

	#if defined ALTCHAT_AUTO_CREATE
		CreatePlayerAltChat(playerid, DEFAULT_ALTCHAT_LINES);
	#endif

	#if !defined _INC_y_hooks
		#if defined ALTCHAT_OnPlayerConnect
			return ALTCHAT_OnPlayerConnect(playerid);
		#else
			return 1;
		#endif
	#endif
}

#if !defined _INC_y_hooks
	#if defined _ALS_OnPlayerConnect
		#undef OnPlayerConnect
	#else
		#define _ALS_OnPlayerConnect
	#endif
	#define OnPlayerConnect ALTCHAT_OnPlayerConnect
	#if defined ALTCHAT_OnPlayerConnect
		forward ALTCHAT_OnPlayerConnect(playerid);
	#endif
#endif
