#include <avr/io.h>
#include <Arduino.h>


void lcdInstruction(uint8_t cmd);
void sendNibble(uint8_t nibble);
void initialize();
void sendData(uint8_t cmd);
void sendLine(String text);
void sendNumber(int num);
void sendFloat(float num);
void printTime(int time);