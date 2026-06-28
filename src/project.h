#pragma once


extern volatile short currLed;
extern volatile short rnd;
extern volatile short count;
extern volatile int time;
extern volatile bool blinking;
extern volatile char menuOptions[33];
extern volatile short currMenu;
extern volatile int highScore;
enum GameStates
{
  PLAY,
  LOST,
  WON,
  MENU,
  ABOUT,
  HIGHSCORE,
  NEXTROUND,
  IDLE,

};

enum ButtonPressed
{
  FirstBtnPressed,
  SecondBtnPressed,
  ThirdBtnPressed,
  Null,
};

extern GameStates gameState;       // <-- FIX: Remove the "= GameStates::MENU"
extern ButtonPressed btnPressed;   // <-- FIX: Remove the "= ButtonPressed::Null"
