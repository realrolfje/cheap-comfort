/*
 * Controls fans to blow air through a central heating radiator
 * depending on the temperature of the radiator. This allows the
 * radiator to heat up the room quicker and at a lower temperature,
 * resulting in more comfort and less heating costs.
 * 
 * Reads temperature from a DS18B20 OneWire temperature sensor on pin D10.
 * Outputs PWM signal for driving a FET which drives PC Fans. 
 * Shows temperature and fan speed on 8 LEDs
 */
#include <OneWire.h> 
#include <DallasTemperature.h>


int fanLowTemp  = 30;
int fanHighTemp = 50;
int fanLowSpeed = 32;
int fanHighSpeed = 255;

//int fanLowTemp  = 25;
//int fanHighTemp = 30;
//int fanLowSpeed = 32;
//int fanHighSpeed = 255;


#define ONE_WIRE_BUS 2 
#define FAN_PWM 10 

#define OFF 0
#define GREEN 1
#define RED 2

OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);

int leds[4];
byte lastFanSpeed = 0;

float readTemp() {
  sensors.requestTemperatures(); 
  return sensors.getTempCByIndex(0);
}

byte calculateFanSpeed(float temp) {
  if (temp < fanLowTemp) return 0;
  float tempPercentage = (temp - fanLowTemp) / (fanHighTemp - fanLowTemp);
  float fanSpeed = fanLowSpeed + ((fanHighSpeed - fanLowSpeed) * tempPercentage);
  if (fanSpeed < fanLowSpeed) return byte(fanLowSpeed);
  if (fanSpeed > fanHighSpeed) return byte(fanHighSpeed);
  return byte(fanSpeed);
}

void setFanSpeed(byte pwmSpeed) {
  if (lastFanSpeed < fanLowSpeed && pwmSpeed >= fanLowSpeed) {
    // Start the fan with a kick
    analogWrite(FAN_PWM, 255);
    delay(500);
  
  }
  analogWrite(FAN_PWM, pwmSpeed);
  lastFanSpeed = pwmSpeed;
}

void setup() {
  Serial.begin(115200);
  sensors.begin(); 
  setpwm();
  setupLeds();

  // To test LED connections (set to true to test)
  while(false){
    writeLed(0,GREEN); delay(500); writeLeds();
    writeLed(1,GREEN); delay(500); writeLeds();
    writeLed(2,GREEN); delay(500); writeLeds();
    writeLed(3,GREEN); delay(500); writeLeds();
    clearLeds(); delay(500);

    writeLed(0,RED); delay(500); writeLeds();
    writeLed(1,RED); delay(500); writeLeds();
    writeLed(2,RED); delay(500); writeLeds();
    writeLed(3,RED); delay(500); writeLeds();
    clearLeds(); delay(500);
  }
}

void loop() {
  // The actual work
  float temp = readTemp();
  setFanSpeed(calculateFanSpeed(temp));

  // Display stuff
  clearLeds();
  if (temp > 20.00) { writeLed(0,GREEN); }
  if (temp > 23.33) { writeLed(1,GREEN); }
  if (temp > 26.66) { writeLed(2,GREEN); }
  if (temp > 29.50) { writeLed(3,GREEN); }


  if (lastFanSpeed > 0) {
    int redLeds = (3 * (lastFanSpeed - fanLowSpeed) / (fanHighSpeed - fanLowSpeed)) + 1;
    if (redLeds >= 1) { writeLed(0,RED); }
    if (redLeds >= 2) { writeLed(1,RED); }
    if (redLeds >= 3) { writeLed(2,RED); }
    if (redLeds  > 3) { writeLed(3,RED); }
  }

  Serial.print("Temperature: "); Serial.print(temp);
  Serial.print("  FanSpeed: ");  Serial.println(lastFanSpeed);
  
  writeLeds();
  delay(1000);//wait one second 
}
