# samp-altchat

[![sampctl](https://img.shields.io/badge/sampctl-samp--altchat-2f2f2f.svg?style=for-the-badge)](https://github.com/xunder-matth/samp-altchat)

## Installation

Simply install to your project:

```bash
sampctl package install xunder-matth/samp-altchat@v2
```

Include in your code and begin using the library:

```pawn
#include <altchat>
```

## Configuration

#### MAX_ALTCHAT_LINES

> -   **Default value:** 15
> -   **Info:** 15 should be fine on 1080p displays. However if you want you can crank it up if you need more max lines (1440p, 4k etc.)

#### DEFAULT_ALTCHAT_LINES

> -   **Default value:** 10
> -   **Info:** This is default alt. chat lines created if you don't pass `lines` argument to `CreatePlayerAltChat`. Why 10? It's optimal for most displays (including 900p and 1080p).

#### ALTCHAT_AUTO_CREATE

> -   **Default value:** Not defined
> -   **Info:** You can add this before including `altchat` if you don't want to manually call `CreatePlayerAltChat`. Keep in mind that this will call `CreatePlayerAltChat` in `OnPlayerConnect` and it will use `DEFAULT_ALTCHAT_LINES` as `lines` parameter.

## API

#### CreatePlayerAltChat

> -   **Parameters:**
>     -   `playerid`
>     -   `lines`
> -   **Returns:**
>     -   -   1 - success
>     -   -   0 - fail

---

#### DestroyPlayerAltChat

> -   **Parameters:**
>     -   `playerid`
> -   **Returns:**
>     -   -   1 - successfully destroyed
>     -   -   0 - fail

---

#### TogglePlayerAltChat

> -   **Parameters:**
>     -   `playerid`
>     -   `bool:toggle`
> -   **Returns:**
>     -   -   true - successfully toggled
>     -   -   false - fail (probably not created)

---

#### SendPlayerAltChatMessage

> -   **Parameters:**
>     -   `playerid`
>     -   `const message[]`
> -   **Returns:**
>     -   -   1 - successfully sended message to player
>     -   -   0 - fail (alt-chat not created or not shown for player)

---

#### IsPlayerAltChatCreated

> -   **Parameters:**
>     -   `playerid`
> -   **Returns:**
>     -   -   1 - if alt. chat is created
>     -   -   0 - if alt. chat is not created

---

#### IsPlayerAltChatShown

> -   **Parameters:**
>     -   `playerid`
> -   **Returns:**
>     -   -   1 - if alt. chat is shown
>     -   -   0 - if alt. chat is not shown

## Notes

-   If you include `y_hooks` before `altchat` include it will use `y_hooks` hooking method
-   If you include `y_va` before `altchat` include you can use `va_SendPlayerAltChatMessage` to automatically format your messages
-   `CreatePlayerAltChat` will not fail if you reach Player TextDraw limit, it will warn you in server console

## Testing

To test, simply run the package:

```bash
sampctl package run
```

Connect to server and test with commands

> /state
> /create
> /destroy
> /show
> /hide
> /sendmsg
