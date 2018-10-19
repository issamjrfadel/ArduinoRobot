/*
 * Posted on https://randomnerdtutorials.com
 * created by http://playground.arduino.cc/Code/NewPing
*/

#include <NewPing.h>
 
#define LTRIGGER_PIN 4
#define LECHO_PIN 3

//#define TRIGGER_PIN 6
//#define ECHO_PIN 5

#define TRIGGER_PIN 22
#define ECHO_PIN 23

#define MAX_DISTANCE 200

// NewPing setup of pins and maximum distance
NewPing sonarR(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 
 
void setup() {
   Serial.begin(9600);
}
 
void loop() {
   delay(50);
   unsigned int distance = sonarR.ping_cm();
   Serial.print(distance);
   Serial.println("cm");
}
