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

#if !defined isnull
	#define isnull(%0) \
		((!(%0[0])) || (((%0[0]) == '\1') && (!(%0[1]))))
#endif

enum e_ALTCHAT_STATES (<<=1) {
	ALTCHAT_STATE_NONE = 0,
	ALTCHAT_STATE_CREATED = 1,
	ALTCHAT_STATE_SHOWN
};

static PlayerText: AltChat_UI[MAX_PLAYERS][MAX_LINES],
	AltChat_Text[MAX_PLAYERS][MAX_LINES][128],
	e_ALTCHAT_STATES: gPlayerAltChatState[MAX_PLAYERS] = { ALTCHAT_STATE_NONE, ... };

stock CreatePlayerAltChat(playerid) {
	if (!IsPlayerConnected(playerid)) {
		return 0;
	}

	if (IsPlayerAltChatCreated(playerid)) {
		return 0;
	}

 	new PlayerText: textdrawid,
 		Float: position_y = 229.573348;

	for(new i = 0; i < MAX_LINES; ++ i) {
		textdrawid = AltChat_UI[playerid][i] = CreatePlayerTextDraw(playerid, 35.599971, position_y, " "); // Empty textdraw string causing SA-MP to crash :/
		PlayerTextDrawLetterSize(playerid, textdrawid, 0.209600, 1.137066);
		PlayerTextDrawAlignment(playerid, textdrawid, 1);
		PlayerTextDrawColor(playerid, textdrawid, -1);
		PlayerTextDrawSetShadow(playerid, textdrawid, 0);
		PlayerTextDrawSetOutline(playerid, textdrawid, 1);
		PlayerTextDrawBackgroundColor(playerid, textdrawid, 255);
		PlayerTextDrawFont(playerid, textdrawid, 1);
		PlayerTextDrawSetProportional(playerid, textdrawid, 1);
		PlayerTextDrawSetShadow(playerid, textdrawid, 0);

		AltChat_Text[playerid][i][0] = EOS;
 		
		position_y += (240.026733 - 229.573348); // This is spacing between two lines
	}

	gPlayerAltChatState[playerid] = ALTCHAT_STATE_CREATED;
	return 1;
}

stock DestroyPlayerAltChat(playerid) {
	if (!IsPlayerConnected(playerid)) {
		return 0;
	}

	if (!IsPlayerAltChatCreated(playerid)) {
		return 0;
	}

	for(new i = 0; i < MAX_LINES; ++ i) {
		PlayerTextDrawDestroy(playerid, AltChat_UI[playerid][i]);

		AltChat_Text[playerid][i][0] = EOS;
		strmid(AltChat_Text[playerid][i], " ", 0, 2, 2);
	}

	gPlayerAltChatState[playerid] = ALTCHAT_STATE_NONE;
	return 1;
}

stock TogglePlayerAltChat(playerid, bool: toggle) {
	if (!IsPlayerConnected(playerid)) {
		return 0;
	}

	if (!IsPlayerAltChatCreated(playerid)) {
		return 0;
	}
	
	new shown = IsPlayerAltChatShown(playerid);

	if (toggle && !shown) {
		for(new i = 0; i < MAX_LINES; ++ i) {	
			PlayerTextDrawShow(playerid, AltChat_UI[playerid][i]);
		}

		gPlayerAltChatState[playerid] ^= ALTCHAT_STATE_SHOWN;
	} else if (!toggle && shown) {
		for(new i = 0; i < MAX_LINES; ++ i) {	
			PlayerTextDrawHide(playerid, AltChat_UI[playerid][i]);
		}

		gPlayerAltChatState[playerid] ^= ALTCHAT_STATE_SHOWN;
	}
	return 1;
}

stock SendPlayerAltMessage(playerid, message[]) {
	if (!IsPlayerConnected(playerid)) {
		return 0;
	}
	
	if (!IsPlayerAltChatCreated(playerid) || !IsPlayerAltChatShown(playerid)) {
		return 0;
	}

	if (isnull(message)) {
		message[0] = ' ';
	}

	for(new i = 0; i < MAX_LINES; i ++) {
		if (i == MAX_LINES - 1) {
			strmid(AltChat_Text[playerid][i], message, 0, 128, 128);
			break;
		}
		strmid(AltChat_Text[playerid][i], AltChat_Text[playerid][i + 1], 0, 128, 128);
	}

	for (new i = 0; i < MAX_LINES; i ++) {
		if (AltChat_Text[playerid][i][0] == EOS) {
			AltChat_Text[playerid][i][0] = ' ';
		}

		PlayerTextDrawSetString(playerid, AltChat_UI[playerid][i], AltChat_Text[playerid][i]);
	}
	return 1;
}

stock IsPlayerAltChatCreated(playerid) {
	if (!IsPlayerConnected(playerid)) {
		return 0;
	}
	
	return (gPlayerAltChatState[playerid] & ALTCHAT_STATE_CREATED);
}

stock IsPlayerAltChatShown(playerid) {
	if (!IsPlayerConnected(playerid)) {
		return 0;
	}
	
	return (gPlayerAltChatState[playerid] & ALTCHAT_STATE_SHOWN);
}

#if defined _INC_y_hooks
	hook OnPlayerConnect(playerid) {
#else 
	public OnPlayerConnect(playerid) {
#endif
	for(new i = 0; i < MAX_LINES; ++ i) {
		AltChat_Text[playerid][i][0] = EOS;
	}

	gPlayerAltChatState[playerid] = ALTCHAT_STATE_NONE;

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
