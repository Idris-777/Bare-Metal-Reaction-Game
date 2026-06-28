
#include <Arduino.h>
#include <avr/io.h>

void timer1Init()
{

  // ENABLE GLOBAL INTERREEPT
  sei();
  // NORMAL TIMER1 MODE
  TCCR1A &= ~((1 << WGM10) | (1 << WGM11));
  TCCR1B &= ~((1 << WGM12) | (1 << WGM13));
  // 1024 PRESCALE
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TCCR1B &= ~(1 << CS11);

  // ENABLE TIMER1 OVERFLOW INTERREPT
  TIMSK1 |= (1 << TOIE1);

  // SET TIMER1 VALUE
  TCNT1 = 64723;
}

void timer2Init()
{
  DDRB |= (1 << PB3);

  // OUTPUT CAPTURE A FAST PWM NON INVERTING MODE
  TCCR2A &= ~(1 << COM2A1);
  TCCR2A |= (1 << COM2A0);
  // ctc
  TCCR2A |= (1 << WGM21);
  TCCR2A &= ~(1 << WGM20);
  TCCR2B &= ~(1 << WGM22);

  // 64 PRESCALER
  TCCR2B |= (1 << CS22);
  TCCR2B &= ~((1 << CS20) | (1 << CS21));

  // start timer2
  TCNT2 = 0;
}
