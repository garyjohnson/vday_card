#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/wdt.h>


#define LED_PIN 0

ISR(WDT_vect) {
  //Don't do anything. This is just here so that we wake up.
}


void setup() {
  pinMode(LED_PIN, OUTPUT);
  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); //Power down everything, wake up from WDT
  sleep_enable();
}

void loop() {
  digitalWrite(LED_PIN, HIGH); 
  setup_watchdog(9); //Setup watchdog to go off after 1sec
  sleep_mode(); //Go to sleep! Wake up 1sec later and check water
  digitalWrite(LED_PIN, LOW);
  setup_watchdog(9); //Setup watchdog to go off after 1sec
  sleep_mode(); //Go to sleep! Wake up 1sec later and check water
 
}

//Sets the watchdog timer to wake us up, but not reset
//0=16ms, 1=32ms, 2=64ms, 3=128ms, 4=250ms, 5=500ms
//6=1sec, 7=2sec, 8=4sec, 9=8sec
//From: http://interface.khm.de/index.php/lab/experiments/sleep_watchdog_battery/
void setup_watchdog(int timerPrescaler) {

  if (timerPrescaler > 9 ) timerPrescaler = 9; //Limit incoming amount to legal settings

  byte bb = timerPrescaler & 7; 
  if (timerPrescaler > 7) bb |= (1<<5); //Set the special 5th bit if necessary

  //This order of commands is important and cannot be combined
  MCUSR &= ~(1<<WDRF); //Clear the watch dog reset
  WDTCR |= (1<<WDCE) | (1<<WDE); //Set WD_change enable, set WD enable
  WDTCR = bb; //Set new watchdog timeout value
  WDTCR |= _BV(WDIE); //Set the interrupt enable, this will keep unit from resetting after each int
}

