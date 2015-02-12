#define LED_PIN 0
#define PIEZO_PIN 2

const int knockFadeTime = 350;
             
byte piezoValue = 0;
int ledState = LOW;
int THRESHOLD = 100;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(PIEZO_PIN, INPUT);
}

void loop() {
  analogRead(PIEZO_PIN);
  piezoValue = analogRead(PIEZO_PIN);     
  if (piezoValue >= THRESHOLD) {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    knockDelay();
  }
}

void knockDelay(){
  int itterations = (knockFadeTime / 20);      // Wait for the peak to dissipate before listening to next one.
  for (int i=0; i < itterations; i++){
    delay(10);
    analogRead(PIEZO_PIN);                  // This is done in an attempt to defuse the analog sensor's capacitor that will give false readings on high impedance sensors.
    delay(10);
  } 
}
