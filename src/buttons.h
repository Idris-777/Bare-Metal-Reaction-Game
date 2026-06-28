#include <Arduino.h>
#include <avr/io.h>
#pragma once

void btnInGame(uint8_t btn_mask);

void nextOption();
void backToMenu();
void selectOption();