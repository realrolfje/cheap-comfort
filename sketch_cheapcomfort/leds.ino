
void setupLeds() {
  // Set A0-A5 as output
  DDRC = B00111111;  
  
  // Set D3-D4 as output
  DDRD = B00011000;
  clearLeds();
}

void writeLed(int led, int color){
  leds[led] = color;
}

void clearLeds() {
  writeLed(0,OFF);
  writeLed(1,OFF);
  writeLed(2,OFF);
  writeLed(3,OFF);
}

void writeLeds() {
    if (leds[0] == OFF)   { digitalWrite(A0, 0); digitalWrite(A1, 0); }
    if (leds[0] == RED)   { digitalWrite(A0, 0); digitalWrite(A1, 1); }
    if (leds[0] == GREEN) { digitalWrite(A0, 1); digitalWrite(A1, 0); }

    if (leds[1] == OFF)   { digitalWrite(A2, 0); digitalWrite(A3, 0); }
    if (leds[1] == RED)   { digitalWrite(A2, 0); digitalWrite(A3, 1); }
    if (leds[1] == GREEN) { digitalWrite(A2, 1); digitalWrite(A3, 0); }

    if (leds[2] == OFF)   { digitalWrite(A4, 0); digitalWrite(A5, 0); }
    if (leds[2] == RED)   { digitalWrite(A4, 0); digitalWrite(A5, 1); }
    if (leds[2] == GREEN) { digitalWrite(A4, 1); digitalWrite(A5, 0); }

    if (leds[3] == OFF)   { digitalWrite(3, 0); digitalWrite(4, 0); }
    if (leds[3] == RED)   { digitalWrite(3, 0); digitalWrite(4, 1); }
    if (leds[3] == GREEN) { digitalWrite(3, 1); digitalWrite(4, 0); }
}
