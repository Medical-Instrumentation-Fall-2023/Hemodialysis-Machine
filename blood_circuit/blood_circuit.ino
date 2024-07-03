int flow_frequency; // Measures flow sensor pulsesunsigned 

int l_hour; // Calculated litres/hour
int flowsensor = 2; // Sensor Input
float currentTime;
long cloopTime;
//LDR
int LDRinput= A0;
int Buzzer=4;
int relay_blood_pump= 3;
//servo motor
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos=0 ;
void flow () // Interrupt function

{
   flow_frequency++;
}

void setup()
{
   pinMode(flowsensor, INPUT);
   digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
   Serial.begin(9600);
   attachInterrupt(0, flow, RISING); // Setup Interrupt
   sei(); // Enable interrupts
   currentTime = millis();
   cloopTime = currentTime;
   pinMode(LDRinput, INPUT);
   pinMode(Buzzer, OUTPUT);
   pinMode(relay_blood_pump,OUTPUT);
   //servo motor
   myservo.attach(9); 
}

void loop ()
{
   //LDR
   int value = analogRead(LDRinput);
   // smoothing the value 
   int sum = 0, n =10;

   for (int i =1; i<= n;i++){
      sum += value;
      delay (10);
   }
   value = sum / n;

   if(value>720)
   {
      Serial.println("LDR value is :");//Prints the value of LDR to Serial Monitor.
      Serial.println(value);
      digitalWrite(Buzzer,HIGH);
      digitalWrite(relay_blood_pump,LOW);
      for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
         // in steps of 1 degree
         myservo.write(pos);              // tell servo to go to position in variable 'pos'
      }
      for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
         myservo.write(pos);              // tell servo to go to position in variable 'pos'
      }
   }
   else
   {
      digitalWrite(Buzzer,LOW);
      digitalWrite(relay_blood_pump,HIGH);
   }

   currentTime = millis();
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000))
   {
      cloopTime = currentTime; // Updates cloopTime
      l_hour = (flow_frequency *60 /73 ); // (Pulse frequency x 60 min) / 73 Q = flowrate in L/hour
      flow_frequency = 0; // Reset Counter
      Serial.print(l_hour); // Print litres/hour
      Serial.println(" L/hour");
   }
}
