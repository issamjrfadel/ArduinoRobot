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
bool hasSearched = false;

bool objectFound = false;

bool reachedRightEdge = false;
bool reachedLeftEdge = false;
int timesTurned = 0;
int turnBack = 0;


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

void searchFunction() {
  while (hasSearched == false && objectFound == false && timesTurned < 44) {

    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    analogWrite(PWML, 60);

    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
    analogWrite(PWMR, 60);

    delay(500);

    distanceR = sonarR.ping_cm();
    distanceL = sonarL.ping_cm();
    distanceFront = sonarFront.ping_cm();

    Serial.print("DistanceL: ");
    Serial.println(distanceL);
    Serial.print("DistanceR: ");
    Serial.println(distanceR);
    Serial.print("Distance Front: ");
    Serial.println(distanceFront);

    Serial.print("Times turned: ");
    Serial.println(timesTurned);

    if (distanceFront < 75 && distanceFront != 0) {
      objectFound = true;
      Serial.println("object found");
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 60);

      digitalWrite(RM1, LOW);
      digitalWrite(RM2, LOW);
      analogWrite(PWMR, 60);
      break;

    }

    //search right
    else if ((distanceFront > 75 || distanceFront == 0) && distanceR < 10 && reachedLeftEdge == false && reachedRightEdge == false) {
      Serial.println("search right");
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 60);

      digitalWrite(RM1, LOW);
      digitalWrite(RM2, HIGH);
      analogWrite(PWMR, 60);

      delay(200);

      timesTurned = timesTurned + 1;
      turnBack = turnBack + 1;


    }
    else if ((distanceFront > 75 || distanceFront == 0) && distanceR > 10 && reachedLeftEdge == false && reachedRightEdge == false) {
      reachedRightEdge = true;
      Serial.println("reached right edge");

      digitalWrite(LM1, LOW);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 60);

      digitalWrite(RM1, LOW);
      digitalWrite(RM2, LOW);
      analogWrite(PWMR, 60);
      //delay(100);

    }

    //search left
    else if ((distanceFront > 75 || distanceFront == 0) && distanceL < 10 && reachedLeftEdge == false && reachedRightEdge == true) {
      Serial.println("search Left");
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, HIGH);
      analogWrite(PWML, 60);

      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);
      analogWrite(PWMR, 60);

      delay(200);

      timesTurned = timesTurned + 1;
    }

    else if ((distanceFront > 75 || distanceFront == 0) && reachedLeftEdge == false && reachedRightEdge == true) {
      reachedLeftEdge = true;
      Serial.println("reached left edge");

      digitalWrite(LM1, LOW);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 60);

      digitalWrite(RM1, LOW);
      digitalWrite(RM2, LOW);
      analogWrite(PWMR, 60);
      //delay(100);

    }

    else if (reachedLeftEdge == true && reachedRightEdge == true) {
      int temp = (timesTurned - turnBack) / 2;
      for (int i = 0; i < temp; i++) {
        digitalWrite(LM1, HIGH);
        digitalWrite(LM2, LOW);
        analogWrite(PWML, 60);

        digitalWrite(RM1, LOW);
        digitalWrite(RM2, HIGH);
        analogWrite(PWMR, 60);
        Serial.println(i);
        delay(200);

        digitalWrite(LM1, LOW);
        digitalWrite(LM2, LOW);
        analogWrite(PWML, 60);

        digitalWrite(RM1, LOW);
        digitalWrite(RM2, LOW);
        analogWrite(PWMR, 60);

        delay(500);
      }

      timesTurned = 44;
      Serial.println("reached both edge");
      delay(100);
      break;


    }

  }
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

  //        Serial.print("DistanceL: ");
  //        Serial.println(distanceL);
  //        Serial.print("DistanceR: ");
  //        Serial.println(distanceR);
  //        Serial.print("Distance Front: ");
  //        Serial.println(distanceFront);

  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  analogWrite(PWML, 60);

  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
  analogWrite(PWMR, 60);

  //  while (hasSearched == false && objectFound == false && timesTurned < 44){
  //
  //        digitalWrite(LM1, LOW);
  //        digitalWrite(LM2, LOW);
  //        analogWrite(PWML, 60);
  //
  //        digitalWrite(RM1, LOW);
  //        digitalWrite(RM2, LOW);
  //        analogWrite(PWMR, 60);
  //
  //        delay(500);
  //
  //        distanceR = sonarR.ping_cm();
  //        distanceL = sonarL.ping_cm();
  //        distanceFront = sonarFront.ping_cm();
  //
  //        Serial.print("DistanceL: ");
  //        Serial.println(distanceL);
  //        Serial.print("DistanceR: ");
  //        Serial.println(distanceR);
  //        Serial.print("Distance Front: ");
  //        Serial.println(distanceFront);
  //
  //        Serial.print("Times turned: ");
  //        Serial.println(timesTurned);
  //
  //      if (distanceFront < 75 && distanceFront != 0){
  //        objectFound = true;
  //        Serial.println("object found");
  //        digitalWrite(LM1, LOW);
  //        digitalWrite(LM2, LOW);
  //        analogWrite(PWML, 60);
  //
  //        digitalWrite(RM1, LOW);
  //        digitalWrite(RM2, LOW);
  //        analogWrite(PWMR, 60);
  //                    break;
  //
  //      }
  //
  //      //search right
  //      else if ((distanceFront > 75 || distanceFront == 0) && distanceR < 10 && reachedLeftEdge == false && reachedRightEdge == false){
  //      Serial.println("search right");
  //      digitalWrite(LM1, HIGH);
  //      digitalWrite(LM2, LOW);
  //      analogWrite(PWML, 60);
  //
  //      digitalWrite(RM1, LOW);
  //      digitalWrite(RM2, HIGH);
  //      analogWrite(PWMR, 60);
  //
  //      delay(200);
  //
  //      timesTurned = timesTurned + 1;
  //      turnBack = turnBack + 1;
  //
  //
  //      }
  //      else if ((distanceFront > 75 || distanceFront == 0) && distanceR > 10 && reachedLeftEdge == false && reachedRightEdge == false){
  //        reachedRightEdge =true;
  //        Serial.println("reached right edge");
  //
  //      digitalWrite(LM1, LOW);
  //      digitalWrite(LM2, LOW);
  //      analogWrite(PWML, 60);
  //
  //      digitalWrite(RM1, LOW);
  //      digitalWrite(RM2, LOW);
  //      analogWrite(PWMR, 60);
  //                  //delay(100);
  //
  //      }
  //
  //      //search left
  //      else if ((distanceFront > 75 || distanceFront == 0) && distanceL < 10 && reachedLeftEdge == false && reachedRightEdge == true){
  //        Serial.println("search Left");
  //      digitalWrite(LM1, LOW);
  //      digitalWrite(LM2, HIGH);
  //      analogWrite(PWML, 60);
  //
  //      digitalWrite(RM1, HIGH);
  //      digitalWrite(RM2, LOW);
  //      analogWrite(PWMR, 60);
  //
  //      delay(200);
  //
  //       timesTurned = timesTurned + 1;
  //      }
  //
  //      else if ((distanceFront > 75 || distanceFront == 0) && reachedLeftEdge == false && reachedRightEdge == true){
  //        reachedLeftEdge = true;
  //                Serial.println("reached left edge");
  //
  //              digitalWrite(LM1, LOW);
  //      digitalWrite(LM2, LOW);
  //      analogWrite(PWML, 60);
  //
  //      digitalWrite(RM1, LOW);
  //      digitalWrite(RM2, LOW);
  //      analogWrite(PWMR, 60);
  //                  //delay(100);
  //
  //      }
  //
  //      else if (reachedLeftEdge == true && reachedRightEdge == true){
  //        int temp = (timesTurned - turnBack)/2;
  //        for (int i = 0; i < temp; i++){
  //          digitalWrite(LM1, HIGH);
  //      digitalWrite(LM2, LOW);
  //      analogWrite(PWML, 60);
  //
  //      digitalWrite(RM1, LOW);
  //      digitalWrite(RM2, HIGH);
  //      analogWrite(PWMR, 60);
  //      Serial.println(i);
  //                  delay(200);
  //
  //                  digitalWrite(LM1, LOW);
  //        digitalWrite(LM2, LOW);
  //        analogWrite(PWML, 60);
  //
  //        digitalWrite(RM1, LOW);
  //        digitalWrite(RM2, LOW);
  //        analogWrite(PWMR, 60);
  //
  //        delay(500);
  //        }
  //
  //        timesTurned = 44;
  //                        Serial.println("reached both edge");
  //                                    delay(100);
  //                                    break;
  //
  //
  //      }
  //
  //    }

  searchFunction();

  if (objectFound) {
    //      if(distanceFront > 20 && distanceFront < 70 && distanceFront != 0){
    //      //move forward
    //      Serial.println("found forward");
    //      digitalWrite(LM1, HIGH);
    //      digitalWrite(LM2, LOW);
    //      analogWrite(PWML, 60);
    //
    //      digitalWrite(RM1, HIGH);
    //      digitalWrite(RM2, LOW);
    //      analogWrite(PWMR, 60);
    //
    //      delay(500);
    //    }
    //      else{
    //              Serial.println("Stop");
    //      digitalWrite(LM1, LOW);
    //      digitalWrite(LM2, LOW);
    //      analogWrite(PWML, 60);
    //
    //      digitalWrite(RM1, LOW);
    //      digitalWrite(RM2, LOW);
    //      analogWrite(PWMR, 60);
    //      }

    while (distanceFront > 10 && distanceFront < 75) {
      distanceR = sonarR.ping_cm();
      distanceL = sonarL.ping_cm();
      distanceFront = sonarFront.ping_cm();

      //move forward
      Serial.println("found forward");
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 60);

      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);
      analogWrite(PWMR, 60);

      delay(500);
      //if click set true
    }

    hasSearched = false;
    objectFound = false;
    timesTurned = 0;
    reachedRightEdge = false;
    reachedLeftEdge = false;
    turnBack = 0;
  }
  else {
    //move forward then run search again
//    Serial.println("move forward");
//    digitalWrite(LM1, HIGH);
//    digitalWrite(LM2, LOW);
//    analogWrite(PWML, 60);
//
//    digitalWrite(RM1, HIGH);
//    digitalWrite(RM2, LOW);
//    analogWrite(PWMR, 60);

    searchFunction();
  }


}
