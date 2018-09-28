#define PWML 9     // left motor power
#define PWMR 11    // right motor power

#define LIR 2      // left IR sensor
#define RIR 4      // right IR sensor

/*-------definning Outputs------*/
#define LM1 8       // left motor
#define LM2 7       // left motor
#define RM1 12      // right motor
#define RM2 13      // right motor

/*-------Defining ultrasonic--------*/
#define SONICTRIG 5
#define SONICECHO 6
  int scanTime = 0;
  // for last turn 0 means none, 1 means left, 2 means right
  int previousTurn = 0;
void setup() {
  // put your setup code here, to run once:

  pinMode(LIR,INPUT);    
  pinMode(RIR,INPUT);

  pinMode(PWML, OUTPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(PWMR, OUTPUT);
  pinMode(SONICTRIG, OUTPUT);
  pinMode(SONICECHO, INPUT);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  // change this to time for just over 1 revolution
    long duration, distance, keepGoing = 1, nearest = 0;
    if(scanTime < 2000){
      //TODO find out how much time it takes for the robot to turn 360 degrees 
       digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 62);

      digitalWrite(RM1, LOW);
      digitalWrite(RM2, HIGH);
      analogWrite(PWMR, 62);

      digitalWrite(SONICTRIG, HIGH);  //send out signal
      delayMicroseconds(1000);   //TODO might need to twesk this for better readings
      digitalWrite(SONICTRIG, LOW);
      duration = pulseIn(SONICECHO, HIGH);
      distance = (duration/2)/29.1; // converts to distance in cm 
      if (distance < nearest || nearest == 0){
        nearest = distance;}
      
      Serial.println("DRIVE");
      scanTime = scanTime + 150;  //increase the time spent scanning
      delay(150);
      }
//repeat scan until we face the object
else if(scanTime > 2000 && scanTime < 4000 && nearest != 0 && keepGoing == 1){
      //TODO find out how much time it takes for the robot to turn 360 degrees 
       digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 62);

      digitalWrite(RM1, LOW);
      digitalWrite(RM2, HIGH);
      analogWrite(PWMR, 62);

      digitalWrite(SONICTRIG, HIGH);  //send out signal
      delayMicroseconds(1000);   //TODO might need to twesk this for better readings
      digitalWrite(SONICTRIG, LOW);
      duration = pulseIn(SONICECHO, HIGH);
      distance = (duration/2)/29.1; // converts to distance in cm 
      if (distance <= nearest + 10 || distance >= nearest -10){
        // stop and exit loop 
        keepGoing = 0; // ends this loop

        // ADD IN THE CODE FOR STOPPING motors HERE
        }
      
      scanTime = scanTime + 150;  //increase the time spent scanning
      delay(150);
      }

      
 else {  if(!digitalRead(LIR) && !digitalRead(RIR)) //move forward
    {
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 60);

      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);
      analogWrite(PWMR, 60);
      Serial.println("DRIVE");

    }
    if(digitalRead(LIR) && !(digitalRead(RIR))) //turn right
    {
      previousTurn = 2;
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 62);

      digitalWrite(RM1, LOW);
      digitalWrite(RM2, HIGH);
      analogWrite(PWMR, 62);
                  //TODO adjust this value for desired turning
                  delay(500);

            Serial.println("TURN RIGHT");

    }
    if(!(digitalRead(LIR)) && digitalRead(RIR)) //turn left
    {
      previousTurn = 1;
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, HIGH);
      analogWrite(PWML, 62);

      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);
      analogWrite(PWMR, 62);  
                  //TODO adjust this value for desired turning
                  delay(500);

                    Serial.println("TURN LEFT");

    }
   if(digitalRead(LIR) && digitalRead(RIR))     // stop
    {
      /*digitalWrite(LM1, LOW);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 60);

      digitalWrite(RM1, LOW);
      digitalWrite(RM2, LOW);
      analogWrite(PWMR, 60); 
*/
// TODO i didnt add in the reverse but you can if you want

// I was thinking do this (and add the reverse if you want):
/*if (previousTurn == 1){
  back up for 400ms and turn left}
  if (previousTurn == 2){
    turn right instead}
 OR what might be better
 once both ir sensors are off the world back up 200ms turn left 400ms and record the resultant ir readings in vars
 then 800ms right and same thing, this will let us decide which way to turn. */ 

      digitalWrite(LM1, LOW);
      digitalWrite(LM2, HIGH);
      analogWrite(PWML, 60);

      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);
      analogWrite(PWMR, 60); 

      delay(2000);

      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 60);

      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);
      analogWrite(PWMR, 60);

                  Serial.println("STOP");

    }
 }
}
