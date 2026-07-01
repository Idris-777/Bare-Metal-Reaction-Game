#include <Arduino.h>
#include <avr/io.h>

#define RS PD6
#define E PB4
#define D7 PD5
#define D6 PD4
#define D5 PD3
#define D4 PD2
#define dataLineMask ~0b00111100

// USED FOR SENDING ONE BYTE INSTRUCTIONS

void lcdInstruction(uint8_t cmd)
{
    // SETTING PINS TO OUTPUT
    DDRD |= (1 << D4) | (1 << D5) | (1 << D6) | (1 << D7);

    DDRD |= (1 << RS);
    DDRB |= (1 << E);

    // RS=0, RW=0
    PORTD &= ~((1 << RS));

    /// Upper nibble
    PORTD = (PORTD & dataLineMask) | (cmd & 0xF0) >> 2;

    // E pulse
    PORTB |= (1 << E);
    _delay_us(1);
    PORTB &= ~(1 << E);

    // Lower nibble
    PORTD = (PORTD & dataLineMask) | ((cmd & 0x0F) << 4) >> 2;

    // E pulse
    PORTB |= (1 << E);
    _delay_us(1);
    PORTB &= ~(1 << E);

    _delay_us(40);
}
// TO SEND ONE NIBBLE USED IN INITIALIZATION
void sendNibble(uint8_t nibble)
{

    // RS=0, RW=0
    PORTD &= ~(1 << RS);

    PORTD = (PORTD & dataLineMask) | (nibble << 4) >> 2;

    // E pulse
    PORTB |= (1 << E);
    _delay_us(1);
    PORTB &= ~(1 << E);

    _delay_us(40);
}

void initialize()
{
    // SETTING PINS TO OUTPUT
    DDRD |= (1 << D4) | (1 << D5) | (1 << D6) | (1 << D7);

    DDRD |= (1 << RS);
    DDRB |= (1 << E);

    _delay_ms(50);

    sendNibble(0x03);
    _delay_ms(5);

    sendNibble(0x03);
    _delay_us(150);

    sendNibble(0x03);
    _delay_us(150);

    sendNibble(0x02);

    lcdInstruction(0x28);
    lcdInstruction(0x0C);
    lcdInstruction(0x01);
    _delay_ms(2);
    lcdInstruction(0x06);
}

void sendData(uint8_t cmd)
{

    // RS=1, RW=0
    PORTD |= (1 << RS);

    /// Upper nibble
    PORTD = (PORTD & dataLineMask) | (cmd & 0xF0) >> 2;

    // E pulse
    PORTB |= (1 << E);
    _delay_us(1);
    PORTB &= ~(1 << E);

    // Lower nibble
    PORTD = (PORTD & dataLineMask) | ((cmd & 0x0F) << 4) >> 2;

    // E pulse
    PORTB |= (1 << E);
    _delay_us(1);
    PORTB &= ~(1 << E);

    _delay_us(50);
}

void sendLine(String text)
{

    if (text.length() > 32)
    {
    }

    else
    {
        for (unsigned int i = 0; i < text.length(); i++)
        {
            if (i == 16)
            {
                lcdInstruction(0xc0);
            }
            sendData(text[i]);
        }
    }
}

void sendLineNew(char *text, int len)
{

    if (len > 32)
    {
    }

    else
    {
        for (unsigned int i = 0; i < len; i++)
        {
            if (i == 16)
            {
                lcdInstruction(0xc0);
            }
            sendData(text[i]);
        }
    }
}

void sendNumber(int num)
{
    int digits[10];
    int len = 0;

    if (num == 0)
    {
        sendData('0');
        return;
    }

    while (num > 0)
    {
        digits[len] = num % 10;
        num /= 10;
        len++;
    }

    

    for (int i = len - 1; i >= 0; --i)
    {
        sendData('0' + digits[i]);
    }
}

void sendFloat(float num)
{
    int digits[10];
    int len = 0;

    if (num <= 10)
    {
        sendData('0');
        return;
    }

    num *= 100;

    while (num > 0)
    {
        digits[len] = static_cast<int>(num) % 10;
        num /= 10;
        len++;
    }

    for (int i = len - 1; i >= 0; --i)
    {
        sendData('0' + digits[i]);

        if (i == 2)
        {
            sendData('.');
        }
    }
}

void printTime(int time)
{

    lcdInstruction(0XC0);

    sendLine("        ");

    lcdInstruction(0XC0);

    sendNumber(time);

    sendLine("ms");

    // Serial.println(time);
}
