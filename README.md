# samp-altchat

[![sampctl](https://img.shields.io/badge/sampctl-samp--altchat-2f2f2f.svg?style=for-the-badge)](https://github.com/xunder-matth/samp-altchat)

<!--
Short description of your library, why it's useful, some examples, pictures or
videos. Link to your forum release thread too.

Remember: You can use "forumfmt" to convert this readme to forum BBCode!

What the sections below should be used for:

`## Installation`: Leave this section un-edited unless you have some specific
additional installation procedure.

`## Testing`: Whether your library is tested with a simple `main()` and `print`,
unit-tested, or demonstrated via prompting the player to connect, you should
include some basic information for users to try out your code in some way.

And finally, maintaining your version number`:

* Follow [Semantic Versioning](https://semver.org/)
* When you release a new version, update `VERSION` and `git tag` it
* Versioning is important for sampctl to use the version control features

Happy Pawning!
-->

## Installation

Simply install to your project:

```bash
sampctl package install xunder-matth/samp-altchat
```

Include in your code and begin using the library:

```pawn
#include <altchat>
```

## Usage

```pawn
CreatePlayerAltChat(playerid)
```
Creating textdraws for player alt chat
Returns 1 if alt chat is created successful, otherwise returns 0 (even if chat is created previously)

```pawn
DestroyPlayerAltChat(playerid)
```
Used for destroying alt chat textdraws
Returns 1 if alt chat is destroyed successful, otherwise 0

```pawn
TogglePlayerAltChat(playerid, bool: toggle)
```
Toggling player alt chat
Returns 1 if operation is successful, otherwise returns 0


```pawn
SendPlayerAltMessage(playerid, message[])
```
Sending player alt chat message
Returns 1 if operation is successful, otherwise returns 0

```pawn
IsPlayerAltChatCreated(playerid)
```
Returns 1 if player alt chat is created (it doesn't have to be shown), otherwise 0

```pawn
IsPlayerAltChatShown
```
Returns 1 if player alt chat is displayed to player, otherwise 0

## Testing

<!--
Depending on whether your package is tested via in-game "demo tests" or
y_testing unit-tests, you should indicate to readers what to expect below here.
-->

To test, simply run the package:

```bash
sampctl package run
```

Connect to server and test with commands

```
/state
/create
/destroy
/show
/hide
/sendmsg
```
