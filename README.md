# Z Casino for Casio fx-CG50

A small casino-style game using **virtual credits only**. It has slots, dice,
and roulette. There are no real-money bets, payments, or payouts.

## Build

With fxSDK and gint installed, run:

```sh
fxsdk build-cg
```

The main add-in is generated as `Z_Casino.g3a`. `Boot_Test.g3a` is a minimal
display/input diagnostic and is not the game.

## Install

Connect the fx-CG50 over USB storage and copy `Z_Casino.g3a` to the calculator's
root directory. Safely eject the calculator, then launch **Z Casino** from the
main menu.

The game starts with 1,000 credits. Use `0` to add 500 free credits. Adjust
bets with left/right; use `EXE` to play, `EXIT` to return to the game list, and
`MENU` to quit. All credits reset when the add-in closes.