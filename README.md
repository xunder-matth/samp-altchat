# samp-altchat

[![sampctl](https://img.shields.io/badge/sampctl-samp--altchat-2f2f2f.svg?style=for-the-badge)](https://github.com/xunder-matth/samp-altchat)

## Installation

Simply install to your project:

```bash
sampctl package install xunder-matth/samp-altchat@v1
```

Include in your code and begin using the library:

```pawn
#include <altchat>
```

## API

#### AltChat_CreatePlayer
>* **Parameters:**
>	* `playerid`
>* **Returns:**
>	* - true - success
>	* - false - fail (probably already created)
 
***

#### AltChat_DestroyPlayer
>* **Parameters:**
>	* `playerid`
>* **Returns:**
>	* - true - successfully destroyed
>	* - false - fail (probably not created)
 
***

#### AltChat_TogglePlayer
>* **Parameters:**
>	* `playerid`
>	* `bool: toggle`
>* **Returns:**
>	* - true - successfully toggled
>	* - false - fail (probably not created)
 
***

#### AltChat_SendPlayer
>* **Parameters:**
>	* `playerid`
>	* `message[]`
>* **Returns:**
>	* - true - successfully sended message to player
>	* - false - fail (alt-chat not created or not shown for player)
 
***

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
