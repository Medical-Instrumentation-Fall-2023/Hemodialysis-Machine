#include "DallasTemperature.h"
#include "OneWire.h"

// Define to which pin of the Arduino the 1-Wire bus is connected:
#define ONE_WIRE_BUS 2

// Create a new instance of the oneWire class to communicate with any OneWire device:
OneWire oneWire(ONE_WIRE_BUS);

// Pass the oneWire reference to DallasTemperature library:
DallasTemperature sensors(&oneWire);
int relay_heating_pad= 8;
int LDRinput= A0;
int LED_leakage=4;
int LED_temp=5;
int relay_pump= 9;

void setup() {
  // Begin serial communication at a baud rate of 9600:
  Serial.begin(9600);
  // Start up the library:
  sensors.begin();
  pinMode(relay_heating_pad, OUTPUT);
  pinMode(relay_pump, OUTPUT);
  pinMode(LDRinput, INPUT);
  pinMode(LED_leakage, OUTPUT);
  pinMode(LED_temp, OUTPUT);
}

void loop() {
  // Send the command for all devices on the bus to perform a temperature conversion:
  sensors.requestTemperatures();

  // Fetch the temperature in degrees Celsius for device index:
  float tempC = sensors.getTempCByIndex(0); // the index 0 refers to the first device

  // Print the temperature in Celsius in the Serial Monitor:
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.print(" Â°"); // shows degree symbol
  Serial.println("C  |  ");
  if( tempC > 30){
    digitalWrite(relay_heating_pad, LOW);
    digitalWrite(LED_temp, LOW); 
  }
  else{
    digitalWrite(relay_heating_pad, HIGH);
    digitalWrite(LED_temp, HIGH); 
  }
  //LDR
  int value = analogRead(LDRinput);
  // smoothing the value 
  int sum = 0, n =10;

  for (int i =1; i<= n;i++){
    sum += value;
    delay (10);
  }
  value = sum / n;
  Serial.println("LDR value is :");//Prints the value of LDR to Serial Monitor.
  Serial.println(value);

  if(value<800)
  {
    Serial.println("LDR value is :");//Prints the value of LDR to Serial Monitor.
    Serial.println(value);
    digitalWrite(LED_leakage,HIGH);
    digitalWrite(relay_pump,LOW);
  }
  else{
    digitalWrite(relay_pump,HIGH);
    digitalWrite(LED_leakage,LOW);
  }

  // Wait 1 second:
  delay(1000);
}
