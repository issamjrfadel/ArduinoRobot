#include <NewPing.h>

#define PWML 9     // left motor power
#define PWMR 11    // right motor power

#define echoL 3      // ultrasonic sensor
#define trigL 4      // ultrasonic sensor

#define echoR 5      // ultrasonic sensor
#define trigR 6      // ultrasonic sensor

#define echoFront 23
#define trigFront 22

#define MAX_DISTANCE 150

int inPinR = 27;   // choose the input pin (for a pushbutton)
int inPinL = 26;   // choose the input pin (for a pushbutton)
int val = 0;     // variable for reading the pin status

int valR;
int valL;

// defines variables
long durationR, durationL, durationFront;
int distanceR, distanceL, distanceFront;



/*-------definning Outputs------*/
#define LM1 8       // left motor
#define LM2 7       // left motor
#define RM1 12      // right motor
#define RM2 13      // right motor

  NewPing sonarR(trigR, echoR, MAX_DISTANCE); 
  NewPing sonarL(trigL, echoL, MAX_DISTANCE); 
  NewPing sonarFront(trigFront, echoFront, MAX_DISTANCE); 

void setup()
{
  pinMode(PWML, OUTPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(PWMR, OUTPUT);
  Serial.begin(9600);
  
  //push sensor
  pinMode(inPinR, INPUT);    // declare pushbutton as input
  pinMode(inPinL, INPUT);
}

void loop()
{
        //----------------------------------
        //run the search function up top
        //searchObject();
        //----------------------------------
        distanceR = sonarR.ping_cm();
        distanceL = sonarL.ping_cm();
        distanceFront = sonarFront.ping_cm();

        Serial.print("DistanceL: ");
        Serial.println(distanceL);
        Serial.print("DistanceR: ");
        Serial.println(distanceR);
        Serial.print("Distance Front: ");
        Serial.println(distanceFront);

    if(distanceR <= 10 && distanceL <= 10) //move forward
    {
      //If we are on the table and there is an object in front of us then
      if (distanceFront <= 20)
      {
          //Stop Then check if both arms are clicked
          digitalWrite(LM1, LOW);
          digitalWrite(LM2, LOW);
          analogWrite(PWML, 60);
  
          digitalWrite(RM1, LOW);
          digitalWrite(RM2, LOW);
          analogWrite(PWMR, 60);
          Serial.println("Found: Stop");
  
          valR = digitalRead(inPinR);
          valL = digitalRead(inPinL);
          //object found, move forward
          if (valR == LOW || valL == LOW)
          {
              digitalWrite(LM1, HIGH);
              digitalWrite(LM2, LOW);
              analogWrite(PWML, 60);
  
              digitalWrite(RM1, HIGH);
              digitalWrite(RM2, LOW);
              analogWrite(PWMR, 60);
              Serial.println("CLICKED");
          }
      }
      else{
        digitalWrite(LM1, HIGH);
        digitalWrite(LM2, LOW);
        analogWrite(PWML, 60);
  
        digitalWrite(RM1, HIGH);
        digitalWrite(RM2, LOW);
        analogWrite(PWMR, 60);
        //Serial.println("DRIVE");
      }
    }
    else if(distanceL > 10 && distanceR <= 10) //turn right
    {
      //Stop First
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 60);

      digitalWrite(RM1, LOW);
      digitalWrite(RM2, LOW);
      analogWrite(PWMR, 60);

      delay(1000);

      //Reverse
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, HIGH);
      analogWrite(PWML, 60);

      digitalWrite(RM1, LOW);
      digitalWrite(RM2, HIGH);
      analogWrite(PWMR, 60);

      delay(800); 

      //Turn Right
      Serial.println("TURN RIGHT");
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 60);

      digitalWrite(RM1, LOW);
      digitalWrite(RM2, HIGH);
      analogWrite(PWMR, 60);

      delay(1000);

      Serial.println("DONE TURNING RIGHT");

    }
    else if(distanceL <= 10 && distanceR > 10) //turn left
    {
      
      Serial.println("Distance R: ");
      Serial.print(distanceR);
      //Stop
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 60);

      digitalWrite(RM1, LOW);
      digitalWrite(RM2, LOW);
      analogWrite(PWMR, 60);

      delay(1000);

      //Reverse
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, HIGH);
      analogWrite(PWML, 60);

      digitalWrite(RM1, LOW);
      digitalWrite(RM2, HIGH);
      analogWrite(PWMR, 60);

      delay(800); 

      //Turn Left
      Serial.println("TURN LEFT");
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, HIGH);
      analogWrite(PWML, 60);

      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);
      analogWrite(PWMR, 60);

      delay(1000);

      Serial.println("DONE TURN LEFT");

    }
    else if(distanceL > 10 && distanceR > 10)     // stop
    {

      //Stop
      Serial.println("BOTH SENSORS OFF");
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 60);

      digitalWrite(RM1, LOW);
      digitalWrite(RM2, LOW);
      analogWrite(PWMR, 60);

      delay(1000);

      //Reverse
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, HIGH);
      analogWrite(PWML, 60);

      digitalWrite(RM1, LOW);
      digitalWrite(RM2, HIGH);
      analogWrite(PWMR, 60);

      delay(800); 

      //Turn right
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 60);

      digitalWrite(RM1, LOW);
      digitalWrite(RM2, HIGH);
      analogWrite(PWMR, 60);
      delay(1000);
      Serial.println("DONE BOTH SENSORS OFF");

    }
}
