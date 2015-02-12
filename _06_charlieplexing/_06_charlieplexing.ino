int led_pins[] = {0,2,3,4};

void setup() {
  resetPins();
}

void loop() {
  for(int high_index = 0; high_index < 4; high_index++) {
      for(int low_index = 0; low_index < 4; low_index++) {

        if (low_index != high_index) {
          int high_pin = led_pins[high_index];
          int low_pin = led_pins[low_index];
          
          pinMode(high_pin, OUTPUT);
          digitalWrite(high_pin, HIGH);
          
          pinMode(low_pin, OUTPUT);
          digitalWrite(low_pin, LOW);
          
          delay(250);
          resetPins();
        }
      }
   }
}

void resetPins() {
  for(int index = 0; index < sizeof(led_pins); index++) {
    int input_pin = led_pins[index];
    pinMode(input_pin, INPUT);
    digitalWrite(input_pin, LOW);
  }
}
