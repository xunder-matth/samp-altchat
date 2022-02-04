#if !defined _INC_ALT_CHAT
	#define _INC_ALT_CHAT
#else
	#endinput
#endif

#if !defined _samp_included
	#error Include \"a_samp\" first.
#endif

#if !defined MAX_LINES
	#define MAX_LINES							(10)			// Number of alt. chat lines (default: 10)
#endif

#define MAX_ALT_CHAT_MESSAGE_LEN				(128)

#if !defined isnull
	#define isnull(%0) \
		((!(%0[0])) || (((%0[0]) == '\1') && (!(%0[1]))))
#endif

enum e_ALTCHAT_STATES (<<=1) {
	ALTCHAT_STATE_NONE = 0,
	ALTCHAT_STATE_CREATED = 1,
	ALTCHAT_STATE_SHOWN
};

static PlayerText: g_sAltChatPTD[MAX_PLAYERS][MAX_LINES],
	g_sAltChatText[MAX_PLAYERS][MAX_LINES][MAX_ALT_CHAT_MESSAGE_LEN char],
	e_ALTCHAT_STATES: g_sAltChatState[MAX_PLAYERS] = { ALTCHAT_STATE_NONE, ... };

stock AltChat_CreatePlayer(playerid) {
	if (!IsPlayerConnected(playerid)) {
		return 0;
	}

	if (AltChat_IsPlayerCreated(playerid)) {
		return 0;
	}

	static const emptyDummyZero[MAX_ALT_CHAT_MESSAGE_LEN char];

	for(new i = 0, PlayerText: textdrawid; i != MAX_LINES; ++ i) {
		textdrawid = g_sAltChatPTD[playerid][i] = CreatePlayerTextDraw(playerid, 35.599971, 229.573348 + (10.453385 * i), " "); // Empty textdraw string causing SA-MP to crash :/
		PlayerTextDrawLetterSize(playerid, textdrawid, 0.209600, 1.137066);
		PlayerTextDrawAlignment(playerid, textdrawid, 1);
		PlayerTextDrawColor(playerid, textdrawid, -1);
		PlayerTextDrawSetShadow(playerid, textdrawid, 0);
		PlayerTextDrawSetOutline(playerid, textdrawid, 1);
		PlayerTextDrawBackgroundColor(playerid, textdrawid, 255);
		PlayerTextDrawFont(playerid, textdrawid, 1);
		PlayerTextDrawSetProportional(playerid, textdrawid, 1);
		PlayerTextDrawSetShadow(playerid, textdrawid, 0);

		g_sAltChatText[playerid][i] = emptyDummyZero; 		
	}

	g_sAltChatState[playerid] = ALTCHAT_STATE_CREATED;
	return 1;
}

stock AltChat_DestroyPlayer(playerid) {
	if (!IsPlayerConnected(playerid)) {
		return 0;
	}

	if (!AltChat_IsPlayerCreated(playerid)) {
		return 0;
	}

	for(new i = 0; i != MAX_LINES; ++ i) {
		PlayerTextDrawDestroy(playerid, g_sAltChatPTD[playerid][i]);

		g_sAltChatText[playerid][i]{0} = EOS;
	}

	g_sAltChatState[playerid] = ALTCHAT_STATE_NONE;
	return 1;
}

stock AltChat_TogglePlayer(playerid, bool: toggle) {
	if (!IsPlayerConnected(playerid)) {
		return 0;
	}

	if (!AltChat_IsPlayerCreated(playerid)) {
		return 0;
	}
	
	new shown = AltChat_IsPlayerShown(playerid);

	if (toggle && !shown) {
		for(new i = 0; i != MAX_LINES; ++ i) {	
			PlayerTextDrawShow(playerid, g_sAltChatPTD[playerid][i]);
		}

		g_sAltChatState[playerid] ^= ALTCHAT_STATE_SHOWN;
	} else if (!toggle && shown) {
		for(new i = 0; i != MAX_LINES; ++ i) {	
			PlayerTextDrawHide(playerid, g_sAltChatPTD[playerid][i]);
		}

		g_sAltChatState[playerid] ^= ALTCHAT_STATE_SHOWN;
	}
	return 1;
}

stock AltChat_SendPlayer(playerid, message[]) {
	if (!IsPlayerConnected(playerid)) {
		return 0;
	}
	
	if (!AltChat_IsPlayerCreated(playerid) || !AltChat_IsPlayerShown(playerid)) {
		return 0;
	}

	if (isnull(message)) {
		message[0] = ' ';
	}

	for(new i = 0; i != MAX_LINES; i ++) {
		if (i == MAX_LINES - 1) {
			strpack(g_sAltChatText[playerid][i], message, 128);
			break;
		}
		
		strpack(g_sAltChatText[playerid][i], g_sAltChatText[playerid][i + 1], MAX_ALT_CHAT_MESSAGE_LEN);
	}

	for(new i = 0; i != MAX_LINES; i ++) {
		if (g_sAltChatText[playerid][i]{0} == EOS) {
			g_sAltChatText[playerid][i]{0} = ' ';
		}

		PlayerTextDrawSetString(playerid, g_sAltChatPTD[playerid][i], g_sAltChatText[playerid][i]);
	}
	return 1;
}

stock AltChat_IsPlayerCreated(playerid) {
	if (!IsPlayerConnected(playerid)) {
		return 0;
	}
	
	return (g_sAltChatState[playerid] & ALTCHAT_STATE_CREATED);
}

stock AltChat_IsPlayerShown(playerid) {
	if (!IsPlayerConnected(playerid)) {
		return 0;
	}
	
	return (g_sAltChatState[playerid] & ALTCHAT_STATE_SHOWN);
}

#if defined _INC_y_hooks
	hook OnPlayerConnect(playerid) {
#else 
	public OnPlayerConnect(playerid) {
#endif
	g_sAltChatState[playerid] = ALTCHAT_STATE_NONE;

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
