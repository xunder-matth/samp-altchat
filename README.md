# samp-altchat

Alternative chat for SA-MP (textdraw).

## Installation

Include in your code and begin using the library:

```pawn
#include < altchat >
```

## Usage

```pawn
CreatePlayerAltChat(playerid);
```

- Create player alternative chat textdraws
- Returning 1 on success
	
```pawn
DestroyPlayerAltChat(playerid); 
```

- Destroy player alternative chat textdraws
- Returning 1 on success
	
```pawn
TogglePlayerAltChat(playerid, bool: toggle); 
```

- Toggle player alt chat (show or hide)
- Returning 1 on success
	
```pawn
IsPlayerAltChatEnabled(playerid); 
``` 

- Check if player alternative chat is shown or hidden
- Returning 1 if chat is shown, 0 otherwise

```pawn
SendPlayerAltMessage(playerid, message[]);
```

- Send player alt chat message 
- Return 1 on success

## Configuration

```pawn
#define MAX_LINES
```

- Setting max alt chat lines (float)

These settings are **optional**.