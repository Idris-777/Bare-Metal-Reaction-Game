
#include <avr/io.h>
#include <avr/interrupt.h>
#include <project.h>

void readHighScore()
{

    while ((EECR & (1 << EEPE)) & (SPMCSR & (1 << SELFPRGEN)))
        ;

    /* Set up address register */
    EEAR = 0x00;
    /* Start eeprom read by writing EERE */
    EECR |= (1 << EERE);
    /* Return data from Data Register */

    highScore = EEDR;

    /* Set up address register */
    EEAR = 0x01;
    /* Start eeprom read by writing EERE */
    EECR |= (1 << EERE);
    /* Return data from Data Register */

    highScore |= (EEDR << 8);
}

void writeHighScore()
{

    EECR &= ~((1 << EEPM1) | (1 << EEPM0));

    while ((EECR & (1 << EEPE)) || (SPMCSR & (1 << SELFPRGEN)))
        ;

    EEAR = 0x00;
    // upper 8 bits
    EEDR = highScore & 0xFF;

    cli();

    EECR |= (1 << EEMPE);

    EECR |= (1 << EEPE);

    sei();

    while ((EECR & (1 << EEPE)) || (SPMCSR & (1 << SELFPRGEN)))
        ;

    EEAR = 0x01;
    // lower 8 bits
    EEDR = (highScore >> 8) & 0xFF;

    cli();

    EECR |= (1 << EEMPE);

    EECR |= (1 << EEPE);

    sei();
}