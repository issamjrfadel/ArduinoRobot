#include <NewPing.h>

#define PWML 9     // left motor power
#define PWMR 11    // right motor power

#define echoL 3      // ultrasonic sensor
#define trigL 4      // ultrasonic sensor

#define echoR 5      // ultrasonic sensor
#define trigR 6      // ultrasonic sensor

#define echoFrontTop 23 // For front top
#define trigFrontTop 22 // For front top

#define echoFrontBottom 26 // for front bottom
#define trigFrontBottom 27 // for front bottom

#define LIR 28      // left IR sensor
#define RIR 29      // left IR sensor

#define MAX_DISTANCE 150

int inPinR = 27;   // choose the input pin (for a pushbutton)
int inPinL = 26;   // choose the input pin (for a pushbutton)
int val = 0;     // variable for reading the pin status

int valR;
int valL;

// defines variables
long durationR, durationL, durationFront;
int distanceR, distanceL, distanceFront, distanceFrontBottom;

bool hasSearched = false;

bool objectFound = false;

int correctObject = 0;

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
NewPing sonarFront(trigFrontTop, echoFrontTop, MAX_DISTANCE);
NewPing sonarFrontBottom(trigFrontBottom, echoFrontBottom, MAX_DISTANCE);

void setup()
{
  pinMode(PWML, OUTPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(PWMR, OUTPUT);

  pinMode(LIR, INPUT);
  pinMode(RIR, INPUT);

  Serial.begin(9600);

  //push sensor
  pinMode(inPinR, INPUT);    // declare pushbutton as input
  pinMode(inPinL, INPUT);
}

void resetAllVar() {
  hasSearched = false;
  objectFound = false;
  timesTurned = 0;
  reachedRightEdge = false;
  reachedLeftEdge = false;
  turnBack = 0;
  correctObject = 0;
}

void backOffObject() {
bothSensorsOffTable();
resetAllVar();
searchFunction();
}
void driveForwardOnTable() {
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  analogWrite(PWML, 60);

  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
  analogWrite(PWMR, 60);
  Serial.println("DRIVE");
}
void leftSensorOffTable() {
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  analogWrite(PWML, 60);

  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
  analogWrite(PWMR, 60);

  delay(1000);

  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  analogWrite(PWML, 60);

  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
  analogWrite(PWMR, 60);

  delay(500);

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
void rightSensorOffTable() {
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  analogWrite(PWML, 60);

  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
  analogWrite(PWMR, 60);

  delay(1000);

  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  analogWrite(PWML, 60);

  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
  analogWrite(PWMR, 60);

  delay(500);

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

void bothSensorsOffTable() {
  Serial.println("BOTH SENSORS OFF");
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  analogWrite(PWML, 60);

  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
  analogWrite(PWMR, 60);

  delay(1000);

  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  analogWrite(PWML, 60);

  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
  analogWrite(PWMR, 60);

  delay(500);

  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  analogWrite(PWML, 60);

  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
  analogWrite(PWMR, 60);
  delay(1000);
  Serial.println("DONE BOTH SENSORS OFF");
}

void searchFunction() {
  while (hasSearched == false && objectFound == false && timesTurned < 43) {

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

    else if (timesTurned == 43) {
      hasSearched = true;
      Serial.println("searched 43 times");
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
      hasSearched = true;
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
  //----------------------------------
  //1) start loop, if objectfound == true, move towards object
  //2) else if objectfound == false and hassearched == true, move forward and search fcn
  //3) if
  //3) if
  //----------------------------------
  distanceR = sonarR.ping_cm();
  distanceL = sonarL.ping_cm();
  distanceFront = sonarFront.ping_cm();
  distanceFrontBottom = sonarFrontBottom.ping_cm();

  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  analogWrite(PWML, 60);

  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
  analogWrite(PWMR, 60);

  if (objectFound) {

    distanceR = sonarR.ping_cm();
    distanceL = sonarL.ping_cm();
    distanceFront = sonarFront.ping_cm();
    distanceFrontBottom = sonarFrontBottom.ping_cm();

    while (distanceFront > 1 && distanceFront < 75) {

      Serial.println("found object but has ran search - while");

      if (distanceR <= 10 && distanceL <= 10) //move forward
      {
         if(distanceFront > 4 && distanceFront <= 12){
                  if ((!digitalRead(LIR) && !digitalRead(RIR)) || (distanceFront - distanceFrontBottom) > 4) {
                    correctObject = 1;
                    while(distanceR <= 10 && distanceL <= 10){
                          distanceR = sonarR.ping_cm();
                       distanceL = sonarL.ping_cm();
                      driveForwardOnTable();
                      Serial.println("found correct object");
                  }}
                  else{
                    correctObject = 2;
                        break;
                  }
 
         }
         else{
            driveForwardOnTable();
         }
      }

      else if (distanceL > 10 && distanceR <= 10) //turn right
      {
        leftSensorOffTable();
      }

      else if (distanceL <= 10 && distanceR > 10) //turn left
      {
        rightSensorOffTable();
      }

      else if (distanceL > 10 && distanceR > 10)    // stop
      {
        bothSensorsOffTable();


      }
      distanceR = sonarR.ping_cm();
      distanceL = sonarL.ping_cm();
      distanceFront = sonarFront.ping_cm();

    }

    if (correctObject == 2){
      backOffObject();
    }
    resetAllVar();

    //searchFunction();
  }

  else if (hasSearched == true && objectFound == false) {
    Serial.println("not found object but has ran search");
    distanceR = sonarR.ping_cm();
    distanceL = sonarL.ping_cm();
    distanceFront = sonarFront.ping_cm();
    int nothingFoundCounter = 0;

    while ((distanceFront == 0 || distanceFront > 75) && nothingFoundCounter < 50) {
      Serial.println("not found object but has ran search - while");

      if (distanceR <= 10 && distanceL <= 10) //move forward
      {
        driveForwardOnTable();
        nothingFoundCounter = nothingFoundCounter + 1;

      }

      else if (distanceL > 10 && distanceR <= 10) //turn right
      {
        leftSensorOffTable();
      }

      else if (distanceL <= 10 && distanceR > 10) //turn left
      {
        rightSensorOffTable();
      }

      else if (distanceL > 10 && distanceR > 10)    // stop
      {
        bothSensorsOffTable();


      }
      distanceR = sonarR.ping_cm();
      distanceL = sonarL.ping_cm();
      distanceFront = sonarFront.ping_cm();

    }

    resetAllVar();

    Serial.println("first search");
    Serial.println(hasSearched);
    Serial.println(objectFound);
    Serial.println(timesTurned);
    Serial.println(reachedRightEdge);
    Serial.println(reachedLeftEdge);
    Serial.println(turnBack);

    searchFunction();
  }

  else if (hasSearched == false && objectFound == false) {

    resetAllVar();

    Serial.println("first search");
    Serial.println(hasSearched);
    Serial.println(objectFound);
    Serial.println(timesTurned);
    Serial.println(reachedRightEdge);
    Serial.println(reachedLeftEdge);
    Serial.println(turnBack);

    searchFunction();
  }



}
